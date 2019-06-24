#ifndef WORLD_H
#define WORLD_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "BitVector.h"


extern const unsigned char DEAD;
extern const unsigned char ALIVE;

extern unsigned int WORLD_WIDTH;
extern unsigned int WORLD_HEIGHT;

extern unsigned char *WORLD;


unsigned char world_get(unsigned int x, unsigned int y);

void world_set8(unsigned int byte, uint8_t val);

void world_seti(unsigned int index, unsigned char state);

void world_setxy(unsigned int x, unsigned int y, unsigned char state);

void load_level(const char *level, unsigned int width, unsigned int height);

void load_random_level(unsigned int width, unsigned int height);

void world_print();

void world_deinit();


#endif
