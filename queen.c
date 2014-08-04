#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int m[8][8] = {0};
int num = 0;

bool check(int row, int column) {
    if (row == 1) return true;

    int i, j;

    for (i = 0; i <= row-2; i++) {
        if (m[i][column-1] == 1) return false;
    }

    i = row - 2;
    j = i - (row - column);

    while (i >= 0 && j >= 0) {
        if (m[i][j] == 1) return false;
        i--;
        j--;
    }

    i = row - 2;
    j = row + column - i - 2;

    while (i >= 0 && j <= 7) {
        if (m[i][j] == 1) return false;
        i--;
        j++;
    }
    return true;
}

void output() {
    int i, j;
    num++;
    printf("answer %d:\n", num);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void solve(int row) {
    int j;

    for (j = 0; j < 8; j++) {
        m[row - 1][j] = 1;

        if (check(row, j+1) == true) {
            if (row == 8) output();
            else solve(row+1);
        }
        m[row-1][j] = 0;
    }
}

int main(void) {
    solve(1);
    return 0;
}
