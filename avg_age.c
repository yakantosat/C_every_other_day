#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(void) {
    char buffer[BUFFER_SIZE];

    FILE *fp;
    fp = fopen("age.txt", "r");
    if (fp == NULL) {
        perror("age.txt");
	exit(EXIT_FAILURE);
    }

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        int age[10];
	int members, sum, i;

	members = sscanf(buffer, "%d %d %d %d %d %d %d %d %d %d",
	    age, age + 1, age + 2, age + 3, age + 4, age + 5, age + 6,
	    age + 7, age + 8, age + 9);
	if (members == 0)
	    continue;

	sum = 0;
	for (i = 0; i < members; i++) {
	    sum += age[i];
	}

	printf("%5.2f: %s", (double) sum / members, buffer);
    }
    fclose(fp);

    return 0;
}
