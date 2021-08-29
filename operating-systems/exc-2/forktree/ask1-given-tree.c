#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "proc-common.h"

#define SLEEP_LEAF_SEC 10
#define SLEEP_TREE_SEC 3

extern int errno;

void fork_procs(void) {
    int status;

    change_pname("A");
    printf("A begins...\n");
    printf("A forks B...\n");
    pid_t pid_1 = fork();

    if (pid_1 < 0) {
        fprintf(stderr, "Error creating process B.\nerrno: %s\n", strerror(errno));
        exit(errno);
    }

    if (pid_1 == 0) {
        change_pname("B");
        printf("B begins...\n");
        printf("B forks D...\n");
        pid_t pid_2 = fork();

        if (pid_2 < 0) {
            fprintf(stderr, "Error creating process D.\nerrno: %s\n", strerror(errno));
            exit(errno);
        }

        if (pid_2 == 0) {
            change_pname("D");
            printf("D begins...\n");
            printf("D sleeping...\n");
            sleep(SLEEP_LEAF_SEC);
            printf("D exiting...\n");
            exit(13);
        }

        if (pid_2 > 0) { // exw ftiaxei to D
            printf("B waiting for D...\n");
            pid_2 = wait(&status);
            explain_wait_status(pid_2, status);
            printf("B exiting...\n");
            exit(19);
        }
    }

    if (pid_1 > 0) {
        printf("A forks C...\n");
        pid_t pid_3 = fork();
        if (pid_3 < 0) {
            fprintf(stderr, "Error creating process C.\nerrno: %s\n", strerror(errno));
            exit(errno);
        }

        if (pid_3 == 0) {
            change_pname("C");
            printf("C begins...\n");
            printf("C sleeping...\n");
            sleep(SLEEP_LEAF_SEC);
            printf("C exiting...\n");
            exit(17);
        }

        if (pid_3 > 0) {
            printf("A waits for B and C...\n");
            pid_1 = wait(&status);
            explain_wait_status(pid_1, status);
            pid_3 = wait(&status);
            explain_wait_status(pid_3, status);
            printf("A exiting...\n");
            exit(16);
        }
    }
}

int main(void) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Error creating process A.\nerrno: %s\n", strerror(errno));
        exit(errno);
    }

    if (pid == 0) {
        fork_procs();
        exit(1);
    }

    sleep(SLEEP_TREE_SEC);
    show_pstree(getpid());

    pid = wait(&status);
	explain_wait_status(pid, status);
    return 0;
}
