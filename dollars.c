#include <stdio.h>
#include <string.h>

void dollars(char *, char const *);

int main(void) {
    char dst[20];
    char const *src = "12";
    dollars(dst, src);

    printf("%s\n", dst);

    return 0;
}

void dollars(char *dst, char const *src) {
    int len;

    if (dst == NULL || src == NULL)
        return ;

    *dst++ = '$';
    len = strlen(src);

    if (len >= 3) {
        int i;

	for (i = len - 2; i > 0; ) {
	    *dst++ = *src++;
	    if ( --i > 0 && i % 3 == 0)
	        *dst++ = ',';
	}
    } else
        *dst++ = '0';

    *dst++ = '.';
    *dst++ = len < 2 ? '0' : *src++;
    *dst++ = len < 1 ? '0' : *src;
    *dst = '\0';
}
