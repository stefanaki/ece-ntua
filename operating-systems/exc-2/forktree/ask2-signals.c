#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "tree.h"
#include "proc-common.h"

extern int errno;

void fork_procs(struct tree_node *root) {
	int status, i;
	pid_t pids[root->nr_children];

	/*
	 * Start
	 */
	printf("PID = %ld, name %s, starting...\n",
			(long)getpid(), root->name);
	change_pname(root->name);

	if (root->nr_children == 0) {
			printf("PID = %ld, %s is a leaf, suspends.\n", (long)getpid(), root->name);
			raise(SIGSTOP);
			printf("PID = %ld, name = %s is awake\n",
				(long)getpid(), root->name);
			printf("PID = %ld, %s exiting...\n", (long)getpid(), root->name);
			exit(0);
	}

	for (i = 0; i < root->nr_children; ++i) {
		printf("PID = %ld, %s forks %s.\n", (long)getpid(), root->name, (root->children + i)->name);
        if ((pids[i] = fork())  < 0) {
            fprintf(stderr, "Error creating node %s.\nerrno: %s\n", root->name, strerror(errno));
    		exit(errno);
        }
		if (pids[i] == 0) {
			fork_procs(root->children + i);
			printf("PID = %ld, %s exiting...\n", (long)getpid(), root->name);
			exit(0);
		}
	}

	/*
	 * Suspend Self
	 */

	printf("PID = %ld, %s suspends.\n", (long)getpid(), root->name);
	wait_for_ready_children(root->nr_children);
	raise(SIGSTOP);
	printf("PID = %ld, name = %s is awake\n",
		(long)getpid(), root->name);

	for (i = 0; i < root->nr_children; ++i) {
		// printf("continuing %s...\n", (root->children + i)->name);
		if ((kill(pids[i], SIGCONT)) != 0) {
			fprintf(stderr, "Error sending SIGCONT from %s.\nerrno: %s\n", root->name, strerror(errno));
    		exit(errno);
		}
		pids[i] = wait(&status);
		explain_wait_status(pids[i], status);
	}

	/*
	 * Exit
	 */
	printf("PID = %ld, %s exiting...\n", (long)getpid(), root->name);
	exit(0);
}

/*
 * The initial process forks the root of the process tree,
 * waits for the process tree to be completely created,
 * then takes a photo of it using show_pstree().
 *
 * How to wait for the process tree to be ready?
 * In ask2-{fork, tree}:
 *      wait for a few seconds, hope for the best.
 * In ask2-signals:
 *      use wait_for_ready_children() to wait until
 *      the first process raises SIGSTOP.
 */

int main(int argc, char *argv[]) {
	pid_t pid;
	int status;
	struct tree_node *root;

	if (argc < 2){
		fprintf(stderr, "Usage: %s <tree_file>\n", argv[0]);
		exit(1);
	}

	/* Read tree into memory */
	root = get_tree_from_file(argv[1]);

	/* Fork root of process tree */
	pid = fork();
	if (pid < 0) {
		perror("main: fork");
		exit(1);
	}
	if (pid == 0) {
		/* Child */
		fork_procs(root);
		exit(1);
	}
	/*
	 * Father
	 */
	/* for ask2-signals */
	wait_for_ready_children(1);

	/* for ask2-{fork, tree} */
	/* sleep(SLEEP_TREE_SEC); */

	/* Print the process tree root at pid */
	show_pstree(pid);

	/* for ask2-signals */
	kill(pid, SIGCONT);

	/* Wait for the root of the process tree to terminate */
	wait(&status);
	explain_wait_status(pid, status);

	return 0;
}
