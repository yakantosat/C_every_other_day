#include <stdio.h>
#include <string.h>

int palindrome(char *);

int main(void) {
    char *test = "abCdEfedcba";
    int flag = palindrome(test);

    if (flag == 0) {
        printf("Is Palindrome\n");
    } else {
        printf("Not a Palindrome\n");
    }

    return 0;
}

int palindrome(char *string) {
    char *start, *end;
    int i = 0;

    int len = strlen(string);
    start = string;
    end = string + len - 1;

    while (i != len/2) {
        if (tolower(*start) != tolower(*end)) {
            return 1;
        }
        printf("start: %c, end: %c\n", *start, *end);
        i++;
        start++;
        end--;
    }

    return 0;
}
