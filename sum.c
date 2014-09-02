#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int sum(FILE *stream);

int main(int argc, char **argv) {
    int i;
    if (argc <= 1) {
        printf("%s: %u\n", "stdin", sum(stdin));
    } else {
        for (i = 1; i < argc; i++) {
            FILE *fp;
	    fp = fopen(argv[i], "r");
	    if (fp == NULL) {
	        perror(argv[i]);
	        exit(EXIT_FAILURE);
	    }

	    printf("%s: %u\n", argv[i], sum(fp));
        }
    }
    return 0;
}

unsigned int sum(FILE *stream) {
    int c;
    unsigned int summery = 0, seed = 18;
    while ((c = fgetc(stream)) != EOF) {
        summery += (c + seed);
    }
    fclose(stream);
    return summery;
}
