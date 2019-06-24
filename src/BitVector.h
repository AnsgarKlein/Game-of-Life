#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

unsigned char* BitVector_init(unsigned long length);

void BitVector_deinit(unsigned char *vec);

void BitVector_set(unsigned char *vec, unsigned long index, uint8_t val);

void BitVector_set8(unsigned char *vec, unsigned int byte, uint8_t val);

unsigned char BitVector_get(const unsigned char *vec, unsigned long index);

#endif
