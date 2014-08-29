#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 512

void fgrep(const char *filename, const char *gstring);

int main(int argc, char *argv[]) {
    int i;
    for (i = 2; i < argc; i++) {
        fgrep(argv[i], argv[1]);
    }

    return 0;
}

void fgrep(const char *filename, const char *gstring) {
    char buffer[BUFF_SIZE];

    FILE *fp;
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror(filename);
	exit(EXIT_FAILURE);
    }

    while (fgets(buffer, BUFF_SIZE, fp) != NULL) {
        if (strstr(buffer, gstring)) {
	    printf("%s: %s", filename, buffer);
	}
    }
    fclose(fp);
}
