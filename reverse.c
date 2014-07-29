#include <stdio.h>

unsigned int reverse_bits(unsigned int value);

int main(void) {
    unsigned int result = reverse_bits(25);

    printf("%ld\n", result);

    return 0;
}

unsigned int reverse_bits(unsigned int value) {
    unsigned int answer;
    unsigned int i;

    answer = 0;

    for (i = 1; i != 0; i <<= 1) {
        answer <<= 1;
        if (value & 1)
            answer |= 1;
        value >>= 1;
    }

    return answer;
}
