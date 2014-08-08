#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prepare_key(char *);
void encrypt(char *, char const *);

int main(void) {
    char key[] = "TRAILBLAZERS";
    char data[] = "attackatdawn";

    prepare_key(key);
    encrypt(data, key);

    printf("%s\n", key);
    printf("%s\n", data);

    return 0;
}

int prepare_key(char *key) {
    /* 1. tolower & eliminate duplication */
    char key_tmp[27];
    int len_k = strlen(key);
    int i, j;

    for (i = 0; i < len_k; i++) {
        key_tmp[i] = key[i] + 32;
    }
    key_tmp[len_k] = '\0';

    printf("key: %s\n", key_tmp);

    for (i = 0; i < len_k; i++) {
        for (j = i+1; j < len_k; j++) {
	    if (key_tmp[i] == 0)
	        continue;
	    if (key_tmp[i] == key_tmp[j])
	        key_tmp[j] = 0;
	}
    }

    for (i = 0, j = 0; i < len_k; i++) {
        if (key_tmp[i] != 0)
	    key_tmp[j++] = key_tmp[i];
    }
    key_tmp[j] = '\0';

    strcpy(key, key_tmp);

    return 1;
}

void encrypt(char *data, char const *key) {
    char key1[] = "abcdefghijklmnopqrstuvwxyz";
    char key2[27];
    char key3[] = "abcdefghijklmnopqrstuvwxyz";

    int i, j;
    for (i = 0; i < strlen(key); i++) {
        key2[i] = key[i];
    }

    for (i = 0; i < 27; i++) {
        for (j = 0; j < strlen(key); j++) {
	    if (key1[i] == 0)
	        continue;
	    if (key1[i] == key[j])
	        key1[i] = 0;
	}
    }

    for (i = 0, j = strlen(key); i < 27; i++) {
        if (key1[i] != 0)
	    key2[j++] = key1[i];
    }
    key2[j] = '\0';
    printf("key2: %s\n", key2);

    int len_t = strlen(data);
    for (i = 0; i < len_t; i++) {
        for (j = 0; j < 27; j++) {
	    if (data[i] == key3[j]) {
	        data[i] = key2[j];
		break;
	    }
	}
    }
}
