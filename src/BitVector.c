
#include "BitVector.h"

unsigned char* BitVector_init(unsigned long length) {
    if (length % 8 != 0) {
        fprintf(stderr, "BitVector can only be used for lengths divisable by 8!\n");
        assert(length % 8 == 0);
    }

    unsigned long size = length / 8;
    unsigned char *new = malloc(size);
    if (new == NULL) {
        fprintf(stderr, "Could not allocate %ld byte for BitVector\n", size);
    }
    assert(new != NULL);

    //TODO: Is initializing this with 0 necessary?
    for (unsigned long i = 0; i < size; i++) {
        new[i] = 0;
    }

    return new;
}

void BitVector_deinit(unsigned char *vec) {
    free(vec);
}

void BitVector_set(unsigned char *vec, unsigned long index, uint8_t val) {
    int byte   = index / 8;
    int offset = index % 8;

    // TODO: Remove unnecessary assertions
    if (val != 0x00 && val != 0x01) {
        fprintf(stderr, "Invalid value for BitVector! Value is neither 0x00 nor 0x01\n");
        assert(val == 0x00 || val == 0x01);
    }

    if (val == 0x01) {
        vec[byte] |= (0x01 << offset);
    } else if (val == 0x00) {
        vec[byte] &= ~(0x01 << offset);
    }

    //printf("field[%d] is in byte %d at offset %d\t=> 0x%0X\n", i, location, offset, WORLD[location]);
}

void BitVector_set8(unsigned char *vec, unsigned int byte, uint8_t val) {
    vec[byte] = val;
}

unsigned char BitVector_get(const unsigned char *vec, unsigned long index) {
    int byte = index / 8;
    int offset = index % 8;

    //printf("Reading field (%d,%d) (field nr %d) from byte %d << %d...\n",
    //        x, y, index, byte, offset);

    unsigned char bit = ((unsigned char)vec[byte] >> offset) & 0x01;

    return bit;
}

