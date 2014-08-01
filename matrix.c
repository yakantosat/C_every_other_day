#include <stdio.h>

void matrix_multiply(int *m1, int *m2, int *r,
                     int x, int y, int z);

int main(void) {
    int i, j;

    int m1[3][2] = { {2, -6},
                     {3, 5},
                     {1, -1}
                   };

    int m2[2][4] = {
                       {4, -2, -4, -5},
                       {-7, -3, 6, 7}
                   };

    int r[3][4];

    matrix_multiply(m1[0], m2[0], r[0], 3, 2, 4);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", r[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void matrix_multiply(int *m1, int *m2, int *r,
                     int x, int y, int z) {
    register int *m1p, *m2p;
    int k;
    int row, col;

    for (row = 0; row < x; row++) {
        for (col = 0; col < z; col++) {
            m1p = m1 + row * y;
            m2p = m2 + col;
            *r = 0;

            for (k = 0; k < y; k++) {
                *r += *m1p * *m2p;
                m1p += 1;
                m2p += z;
            }

            r++;
        }
    }
}
