/* * mandel.c
 *
 * A program to draw the Mandelbrot Set on a 256-color xterm.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include "mandel-lib.h"

#define MANDEL_MAX_ITERATION 100000

/***************************
 * Compile-time parameters *
 ***************************/

sem_t *my_semaphores;

struct thread_data {
    int thread_index;
    unsigned int n;
};

/*
 * Output at the terminal is is x_chars wide by y_chars long
*/
int y_chars = 50;
int x_chars = 90;

/*
 * The part of the complex plane to be drawn:
 * upper left corner is (xmin, ymax), lower right corner is (xmax, ymin)
*/
double xmin = -1.8, xmax = 1.0;
double ymin = -1.0, ymax = 1.0;

/*
 * Every character in the final output is
 * xstep x ystep units wide on the complex plane.
 */
double xstep;
double ystep;

/*
 * This function computes a line of output
 * as an array of x_char color values.
 */
void compute_mandel_line(int line, int color_val[])
{
	/*
	 * x and y traverse the complex plane.
	 */
	double x, y;

	int n;
	int val;

	/* Find out the y value corresponding to this line */
	y = ymax - ystep * line;

	/* and iterate for all points on this line */
	for (x = xmin, n = 0; n < x_chars; x+= xstep, n++) {

		/* Compute the point's color value */
		val = mandel_iterations_at_point(x, y, MANDEL_MAX_ITERATION);
		if (val > 255)
			val = 255;

		/* And store it in the color_val[] array */
		val = xterm_color(val);
		color_val[n] = val;
	}
}

/*
 * This function outputs an array of x_char color values
 * to a 256-color xterm.
 */
void output_mandel_line(int fd, int color_val[])
{
	int i;

	char point ='@';
	char newline='\n';

	for (i = 0; i < x_chars; i++) {
		/* Set the current color, then output the point */
		set_xterm_color(fd, color_val[i]);
		if (write(fd, &point, 1) != 1) {
			perror("compute_and_output_mandel_line: write point");
			exit(1);
		}
	}

	/* Now that the line is done, output a newline character */
	if (write(fd, &newline, 1) != 1) {
		perror("compute_and_output_mandel_line: write newline");
		exit(1);
	}
}

void compute_and_output_mandel_line(int fd, int line, int n)
{
	/*
	 * A temporary array, used to hold color values for the line being drawn
	 */
	int color_val[x_chars];

	compute_mandel_line(line, color_val);
	sem_wait(&my_semaphores[line % n]);
	output_mandel_line(fd, color_val);
	sem_post(&my_semaphores[(line + 1) % n]);
}

void *safe_malloc(size_t size)
{
	void *p;

	if ((p = malloc(size)) == NULL) {
		fprintf(stderr, "Out of memory, failed to allocate %zd bytes\n",
			size);
		exit(1);
	}

	return p;
}

void usage(char *argv0)
{
	fprintf(stderr, "Usage: %s thread_count array_size\n\n"
		"Exactly two argument required:\n"
		"    thread_count: The number of threads to create.\n"
		"    array_size: The size of the array to run with.\n",
		argv0);
	exit(1);
}

int safe_papoi(char *s, int *val)
{
    long l;
    char *endp;

    l = strtol(s, &endp, 10);
    if (s != endp && *endp == '\0') {
            *val = l;
            return 0;
    } else
    	return -1;
}

void handleCtrlC(int sig) {
	reset_xterm_color(1);
	printf("\nProgram killed with SIGINT, caused by Ctrl+C, signal: %d.\n", sig);
	exit(1);
}

void *thread_routine(void *arg) {
	int line;
	struct thread_data *t = arg;
	int thread_index = t->thread_index;
	unsigned int n_threads = t->n;

	for (line = thread_index; line < y_chars; line += n_threads)
		compute_and_output_mandel_line(1, line, n_threads);

	return NULL;
}

int main(int argc, char **argv)
{
	int i;
	int n_threads;
	pthread_t *threads;
	struct thread_data *thr_data;

	if (argc != 2)
    	usage(argv[0]);
    if (safe_papoi(argv[1], &n_threads) < 0 || n_threads <= 0) {
        fprintf(stderr, "`%s' is not valid for `n_threads'\n", argv[1]);
        exit(1);
    }

	xstep = (xmax - xmin) / x_chars;
	ystep = (ymax - ymin) / y_chars;

	threads = (pthread_t *) safe_malloc(sizeof(pthread_t) * n_threads);
	my_semaphores = (sem_t *) safe_malloc(sizeof(sem_t) * n_threads);
	thr_data = (struct thread_data *) safe_malloc(sizeof(struct thread_data) * n_threads);

	sem_init(&my_semaphores[0], 0, 1);
	for (i = 1; i < n_threads; ++i)
		sem_init(&my_semaphores[i], 0, 0);

	for (i = 0; i < n_threads; ++i) {
		thr_data[i].n = n_threads;
		thr_data[i].thread_index = i;

		pthread_create(threads + i, NULL, thread_routine, thr_data + i);
	}

	signal(SIGINT, handleCtrlC);

	for (i = 0; i < n_threads; ++i) {
		pthread_join(threads[i], NULL);
		sem_destroy(&my_semaphores[i]);
    }

	free(threads);
	free(thr_data);
	free(my_semaphores);
	reset_xterm_color(1);
	return 0;
}
