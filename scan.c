#include <stdio.h>
#include <string.h>

int look_for_the(char *);

int main(void) {
    char string[101];
    int num = 0;
    
    printf("Please input the string: \n");
    fgets(string, 100, stdin);
    num = look_for_the(string);

    printf("\nThe number of 'the' in the string is: %d\n", num);

    return 0;
}

int look_for_the(char *string) {
    int n = 0, off;

    char *tmp, *offset;
    tmp = string;

    offset = strstr(tmp, "the");

    while (offset) {
        n++;
	offset = strstr(offset, "the");
    }

    return n;
}
