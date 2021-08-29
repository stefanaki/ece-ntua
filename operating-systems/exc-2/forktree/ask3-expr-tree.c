#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "tree.h"
#include "proc-common.h"

extern int errno;

void fork_procs(struct tree_node *p_tree, int fd) {
    pid_t my_pid;
    int /* status, */ x, i;
    int my_fd[2][2], children_values[2];

    change_pname(p_tree->name);

    if (p_tree->nr_children == 0) {
        printf("PID: %ld, %s: this node is a leaf, writing on fd.\n", (long)getpid(), p_tree->name);
        x = atoi(p_tree->name);
        if ((write(fd, &x, sizeof(x))) < 0) {
            fprintf(stderr, "PID: %ld, write\nerrno: %s\n", (long)getpid(), strerror(errno));
    		exit(errno);
        }
        close(fd);
        exit(0);
    }

    for (i = 0; i < p_tree->nr_children; ++i) {
        if ((pipe(my_fd[i])) < 0) {
            fprintf(stderr, "PID: %ld, pipe\nerrno: %s\n", (long)getpid(), strerror(errno));
    		exit(errno);
        }
        printf("PID: %ld, %s: pipe created on process\n", (long)getpid(), p_tree->name);
        if ((my_pid = fork())  < 0) {
            fprintf(stderr, "PID: %ld, fork\nerrno: %s\n", (long)getpid(), strerror(errno));
    		exit(errno);
        }

        if (my_pid == 0) {
            // printf("%s: i am a child\n", p_tree->name);
            close(my_fd[i][0]);
            fork_procs(p_tree->children + i, my_fd[i][1]);
            exit(0);
        }
    }

    if (my_pid > 0) {
        close(my_fd[0][1]);
        close(my_fd[1][1]);
        for (i = 0; i < p_tree->nr_children; ++i) {
            // my_pid = wait(&status);
            // explain_wait_status(my_pid, status);

            if ((read(my_fd[i][0], &children_values[i], sizeof(children_values[i]))) < 0) {
                fprintf(stderr, "PID: %ld, read\nerrno: %s\n", (long)getpid(), strerror(errno));
        		exit(errno);
            }
            printf("PID: %ld, %s: child with value %d came back\n",
                (long)getpid(), p_tree->name, children_values[i]);
        }

        printf("PID: %ld, %s: values returned from children's pipes are %d and %d.\n",
            (long)getpid(), p_tree->name, children_values[0], children_values[1]);

        if (strcmp(p_tree->name, "+") == 0) {
            x = children_values[0] + children_values[1];
        } else if (strcmp(p_tree->name, "*") == 0) {
            x = children_values[0] * children_values[1];
        }
        if ((write(fd, &x, sizeof(x))) < 0) {
            fprintf(stderr, "PID: %ld, write\nerrno: %s\n", (long)getpid(), strerror(errno));
            exit(errno);
        }
        close(fd);
        exit(0);
    }
}

int main(int argc, char **argv) {
    struct tree_node *root;
    pid_t pid;
    int status, x;
    int main_fd[2];

    if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_tree_file>\n\n", argv[0]);
		exit(1);
	}

    root = get_tree_from_file(argv[1]);
    print_tree(root);

    if ((pipe(main_fd) < 0)) {
        fprintf(stderr, "PID: %ld, pipe on main.\nerrno: %s\n", (long)getpid(), strerror(errno));
		exit(errno);
    }

    if ((pid = fork()) < 0) {
        fprintf(stderr, "PID: %ld, fork on main.\nerrno: %s\n", (long)getpid(), strerror(errno));
		exit(errno);
    }

    if (pid == 0) {
        close(main_fd[0]);
        fork_procs(root, main_fd[1]);
        exit(0);
    }

    if (pid > 0) {
        close(main_fd[1]);
        pid = wait(&status);
        explain_wait_status(pid, status);
        if ((read(main_fd[0], &x, sizeof(x))) < 0) {
            fprintf(stderr, "PID: %ld, read on main.\nerrno: %s\n", (long)getpid(), strerror(errno));
    		exit(errno);
        }
        printf("\n\nPID: %ld, main: result of the expression is %d\n\n", (long)getpid(), x);
    }

    close(main_fd[0]);
    return 0;
}
