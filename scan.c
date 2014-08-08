#include <stdio.h>
#include <string.h>

int look_for_the(char *);

int main(void) {
    char *string;
    int num = 0;
    
    string = "the cv iass  vy ba comp. the csdwe fw. the csds is sldkslsl the";
    num = look_for_the(string);

    printf("The number of 'the' in the string is: %d\n", num);

    return 0;
}

int look_for_the(char *string) {
    int n = 0, off;

    char *offset;
    offset = strstr(string, "the");

    while (offset) {
        n++;
	offset = strstr(offset + 3, "the");
    }

    return n;
}
