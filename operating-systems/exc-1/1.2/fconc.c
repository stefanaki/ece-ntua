#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

extern int errno;

void doWrite(int fd, const char *buff, size_t len) {
    size_t i = 0;
	ssize_t wcnt;

	do {
		if ((wcnt = write(fd, buff + i, len - i)) < 0) {
	    	// perror("fconc: Error while writing on output file.");
			printf("%s\n", strerror(errno));
			exit(errno);
		}
		i += wcnt;
	} while (i < len);
}

void writeFile(int fd, const char *infile) {
    size_t inLength;
	ssize_t rcnt;
    char buffer[1024];
    int input_fd = open(infile, O_RDONLY);
    if (input_fd < 0) {
        // perror("fconc: Error while opening file.");
		printf("%s\n", strerror(errno));
        exit(errno);
    }

    while (1) {
        rcnt = read(input_fd, buffer, sizeof(buffer));
        if (rcnt == 0) break;
        if (rcnt == -1) {
            // perror("fconc: Error while reading file.");
      		printf("%s\n", strerror(errno));
	   		exit(errno);
        }

		inLength = rcnt;
        doWrite(fd, buffer, inLength);
    }
    close(input_fd);
}

int main(int argc, char **argv) {
    int output_fd, oflags = O_WRONLY | O_CREAT | O_TRUNC;
    char *infile1Name = argv[1], *infile2Name = argv[2];

    if (argc < 3 || argc > 4) {
        printf("Usage: %s infile1 infile2 [outfile (default:fconc.out)]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

	if (argv[3] != NULL) {
        if (strcmp(argv[1], argv[3]) == 0 || strcmp(argv[2], argv[3]) == 0) {
            printf("Usage: %s infile1 infile2 [outfile (default:fconc.out)]\n", argv[0]);
    		exit(EXIT_FAILURE);
        }
        output_fd = open(argv[3], oflags, 0644);
    	writeFile(output_fd, infile1Name);
	    writeFile(output_fd, infile2Name);
   	} else {
    	output_fd = open("fconc.out", oflags, 0644);
    	writeFile(output_fd, infile1Name);
    	writeFile(output_fd, infile2Name);
    }

    close(output_fd);
    return 0;
}
