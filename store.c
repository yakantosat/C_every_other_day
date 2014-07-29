#include <stdio.h>

int store_bit_field(int original_value, int value_to_store,
                    unsigned starting_bit, unsigned ending_bit);

int main(void) {

    int result = store_bit_field(0x0, 0x1, 4, 4);

    printf("0x%x\n", result);

    return 0;
}

int store_bit_field(int original_value, int value_to_store,
                    unsigned starting_bit, unsigned ending_bit) {
    int mask, i;

    // 1) create mask
    mask = 0;
    for (i = 0; i <= (starting_bit - ending_bit); i++) {
        mask |= 1;
        mask <<= 1;
    }
    printf("mask: %d\n", mask);
    mask <<= (ending_bit - 1);

    // 2) 
    original_value &= ~(mask);

    // 3)
    value_to_store <<= ending_bit;

    // 4)
    value_to_store &= mask;

    // 5)
    original_value |= value_to_store;

    return original_value;
}
