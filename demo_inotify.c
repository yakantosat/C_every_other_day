#include <sys/inotify.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static char *getOutput(FILE *fp, char *buffer);
typedef struct inotify_event* ie_ptr;
#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))
#define BUF_SIZE 	1024

long int offset = 0;

static void
displayInotifyEvent(ie_ptr i, FILE *fp, char *buffer) {
    printf("    wd = %2d; ", i->wd);
    if (i->cookie > 0)
        printf("cookie =%4d; ", i->cookie);

    printf("mask = ");
    if (i->mask & IN_ACCESS)		printf("IN_ACCESS ");
    if (i->mask & IN_ATTRIB)		printf("IN_ATTRIB ");
    if (i->mask & IN_CLOSE_NOWRITE)	printf("IN_CLOSE_NOWRITE ");
    if (i->mask & IN_CLOSE_WRITE)	printf("IN_CLOSE_WRITE ");
    if (i->mask & IN_CREATE)		printf("IN_CREATE ");
    if (i->mask & IN_DELETE)		printf("IN_DELETE ");
    if (i->mask & IN_DELETE_SELF)	printf("IN_DELETE_SELF ");
    if (i->mask & IN_IGNORED)		printf("IN_IGNORED ");
    if (i->mask & IN_ISDIR)		printf("IN_ISDIR ");
    //if (i->mask & IN_MODIFY)		printf("IN_MODIFY ");
    if (i->mask & IN_MODIFY)		printf("Modified: %s", getOutput(fp, buffer));
    if (i->mask & IN_MOVE_SELF)		printf("IN_MOVE_SELF ");
    //if (i->mask & IN_MOVE_FROM)		printf("IN_MOVE_FROM ");
    //if (i->mask & IN_MOVE_TO)		printf("IN_MOVE_TO ");
    if (i->mask & IN_OPEN)		printf("IN_OPEN ");
    if (i->mask & IN_Q_OVERFLOW)	printf("IN_Q_OVERFLOW ");
    if (i->mask & IN_UNMOUNT)		printf("IN_UNMOUNT ");
    printf("\n");

    if (i->len > 0)
        printf("	name = %s\n", i->name);
}

static char *
getOutput(FILE *fp, char *buffer) {
    int r;
    char *c;
    int len;
    //r = fgetpos(fp, &pos);
    r = fseek(fp, offset, SEEK_SET);
    if (r != 0) {
        perror("fseek: ");
        exit(EXIT_FAILURE);
    }

    c = fgets(buffer, BUF_SIZE, fp);
    if (c == NULL) {
        perror("fgets: ");
        exit(EXIT_FAILURE);
    }

    offset = ftell(fp);
    if (r != 0) {
        perror("fsetpos: ");
        exit(EXIT_FAILURE);
    }

    return buffer;
}

sig_atomic_t signaled = 0;

void my_handler(int param) {
    signaled = 1;
    printf("Termailed.\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    int inotifyFd, wd, j;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    char buffer[BUF_SIZE];
    ssize_t numRead;
    char *p;
    ie_ptr event;
    FILE *fp;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        perror("Input: ");
        exit(EXIT_FAILURE);
    }

    inotifyFd = inotify_init();
    if (inotifyFd == -1) {
        perror("inotify_init(): ");
        exit(EXIT_FAILURE);
    }

    for (j = 1; j < argc; j++) {
        wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);
        if (wd == -1) {
            perror("inotify_add_watch: ");
            exit(EXIT_FAILURE);
        }
        fp = fopen(argv[j], "r");
        if (fp == NULL) {
            perror("fopen: ");
            exit(EXIT_FAILURE);
        }
        //fsetpos(fp, &pos);
        fseek(fp, 0, SEEK_END);
        offset = ftell(fp);

        printf("Watching %s using wd %d\n", argv[j], wd);
    }

    for (;;) {
        if (signal (SIGINT, my_handler) == SIG_IGN) {
            printf("Termailed\n");
            fclose(fp);
            signal (SIGINT, SIG_DFL);
        }
        numRead = read(inotifyFd, buf, BUF_LEN);
        if (numRead == 0) {
            perror("read: ");
            exit(EXIT_FAILURE);
        }
        printf("Read %ld bytes from inotify fd\n", (long) numRead);

        for (p = buf; p < buf + numRead;) {
            event = (ie_ptr) p;
            displayInotifyEvent(event, fp, buffer);

            p += sizeof(struct inotify_event) + event->len;
        }
    }

    return 0;
}
