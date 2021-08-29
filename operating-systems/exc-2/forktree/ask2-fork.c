#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "tree.h"
#include "proc-common.h"

#define SLEEP_LEAF_SEC 10
#define SLEEP_TREE_SEC 3

extern int errno;

void fork_procs(struct tree_node *p_tree) {
    pid_t my_pid;
    int status, i;

    change_pname(p_tree->name);

    if (p_tree->nr_children == 0) {
        printf("%s is a leaf.\n%s sleeping...\n", p_tree->name, p_tree->name);
        sleep(SLEEP_LEAF_SEC);
        printf("%s exiting...\n", p_tree->name);
        exit(0);
    }

    for (i = 0; i < p_tree->nr_children; ++i) {
        printf("%s forks %s.\n", p_tree->name, (p_tree->children + i)->name);
        if ((my_pid = fork())  < 0) {
            fprintf(stderr, "Error creating node %s.\nerrno: %s\n", p_tree->name, strerror(errno));
    		exit(errno);
        }

        if (my_pid == 0) {
            fork_procs(p_tree->children + i);
            exit(0);
        }
    }

    if (my_pid > 0) {
        for (i = 0; i < p_tree->nr_children; ++i) {
            my_pid = wait(&status);
            explain_wait_status(my_pid, status);
        }
        printf("%s exiting...\n", p_tree->name);
        exit(0);
    }

}

int main(int argc, char **argv) {
    struct tree_node *root;
    pid_t pid;
    int status;

    if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_tree_file>\n\n", argv[0]);
		exit(1);
	}

    root = get_tree_from_file(argv[1]);
    print_tree(root);

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Error creating node %s.\nerrno: %s\n", root->name, strerror(errno));
		exit(errno);
    }

    if (pid == 0) {
        printf("%s begins...\n", root->name);

        fork_procs(root);
        exit(0);
    }

    if (pid > 0) {
        sleep(SLEEP_TREE_SEC);
        show_pstree(pid);
        pid = wait(&status);
        explain_wait_status(pid, status);
    }
    return 0;
}
