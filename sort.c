#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(void *arr, int count, size_t size, int (*cmp)(int, int));

int comp_int(int a, int b) {
    if (a == b) return 0;
    return (a > b) ? 1 : -1;
}

void swap(char *i, char *j, int size) {
    char x;

    while ( size-- > 0) {
        x = *i;
	*i++ = *j;
	*j++ = x;
    }
}

int main(void) {
    int i;
    int arr[] = {34, 23, 78, 2, 13, 33};
    printf("Before sort:\n");
    for (i = 0; i < sizeof(arr)/sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("After sort:\n");
    sort(arr, 6, sizeof(int), comp_int);
    for (i = 0; i < sizeof(arr)/sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void sort(void *arr, int count, size_t size, int (*cmp)(int, int)) {
    char *i, *j, *last;

    last = arr + (count - 1) * size;
    for (i = arr; i < last; i += size) {
        for (j = i + size; j <= last; j += size) {
	    if (comp_int(*i, *j) > 0)
	        swap(i, j, size);
	}
    }
}
