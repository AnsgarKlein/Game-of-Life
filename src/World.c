#include "World.h"

const unsigned char DEAD  = 0x00;
const unsigned char ALIVE = 0x01;

// These are the fields *not* the dimensions of the array!
unsigned int WORLD_WIDTH = 32;
unsigned int WORLD_HEIGHT = 32;

// Access only via function!!
// Size of array is *unknown* !
// Layout: row -> column -> depth
unsigned char *WORLD = NULL;

void world_set8(unsigned int byte, uint8_t val) {
    if (byte >= (WORLD_WIDTH * WORLD_HEIGHT) / 8) {
        fprintf(stderr,
                "Setting illegal 8 fields in byte %d on world of size (%d,%d) (%d elements, %d byte)\n",
                byte, WORLD_WIDTH, WORLD_HEIGHT, WORLD_WIDTH * WORLD_HEIGHT,
                (WORLD_WIDTH * WORLD_HEIGHT) / 8);
    }

    BitVector_set8(WORLD, byte, val);
}

void world_seti(unsigned int index, unsigned char state) {
    if (index >= WORLD_WIDTH * WORLD_HEIGHT) {
        fprintf(stderr,
                "Setting illegal field (index: %d) on world of size (%d,%d) (%d elements)\n",
                index, WORLD_WIDTH, WORLD_HEIGHT, WORLD_WIDTH * WORLD_HEIGHT);
    }

    BitVector_set(WORLD, index, state);
}

void world_setxy(unsigned int x, unsigned int y, unsigned char state) {
    if (x >= WORLD_WIDTH || y >= WORLD_HEIGHT) {
        fprintf(stderr, "Setting illegal field (%d,%d) on world of size (%d,%d)\n",
                x, y, WORLD_WIDTH, WORLD_HEIGHT);
    }

    int index = y * WORLD_WIDTH + x;
    world_seti(index, state);
}

unsigned char world_get(unsigned int x, unsigned int y) {
    unsigned int index = y * WORLD_WIDTH + x;

    // Fields outside of game board are dead
    if (x >= WORLD_WIDTH || y >= WORLD_HEIGHT) {
        fprintf(stderr, "Getting illegal field (%d,%d) on world of size (%d,%d)\n",
                x, y, WORLD_WIDTH, WORLD_HEIGHT);
        return DEAD;
    }

    unsigned char state = BitVector_get(WORLD, index);
    return state;
}

static void world_init(unsigned long width, unsigned long height) {
    // Width and height have to be divisable by 8
    WORLD_WIDTH  = (width  % 8 == 0) ? width  : (width  / 8) * 8 + 8;
    WORLD_HEIGHT = (height % 8 == 0) ? height : (height / 8) * 8 + 8;

    // Calculate number of elements in world
    unsigned int number = width * height;

    WORLD = NULL;
    WORLD = BitVector_init(number);
    assert(WORLD != NULL);
}

void world_deinit() {
    BitVector_deinit(WORLD);
    WORLD = NULL;
}

void load_level(const char *level, unsigned int width, unsigned int height) {
    if (WORLD != NULL) {
        world_deinit();
    }
    world_init(width, height);

    for (unsigned int y = 0; y < WORLD_HEIGHT; y++) {
        for (unsigned int x = 0; x < WORLD_WIDTH; x++) {
            if (level[y * WORLD_WIDTH + x] == ALIVE) {
                world_setxy(x, y, ALIVE);
            } else if (level[y * WORLD_WIDTH + x] == DEAD) {
                world_setxy(x, y, DEAD);
            } else {
                fprintf(stderr, "Invalid data in level\n");
                assert(NULL != NULL);
            }
        }
    }
}

void load_random_level(unsigned int width, unsigned int height) {
    if (WORLD != NULL) {
        world_deinit();
    }

    printf("Trying to generate random world %d x %d...\n", width, height);
    world_init(width, height);

    printf("Filling initialized world with random data...\n");
    for (unsigned int y = 0; y < WORLD_HEIGHT; y++) {
        for (unsigned int x = 0; x < WORLD_WIDTH; x++) {
            unsigned int rnd = rand() % 2;
            world_setxy(x, y, rnd);
        }
    }
    printf("Filling initialized world with random data...DONE\n");
}

void world_print() {
    //const char *BORDER = "\u2588";
    const char *BORDER = "#";

    // Print upper border
    for (unsigned int i = 0; i < WORLD_WIDTH + 2; i++) {
        printf("%s", BORDER);
    }
    printf("\n");

    for (unsigned int y = 0; y < WORLD_HEIGHT; y++) {
        printf("%s", BORDER);
        for (unsigned int x = 0; x < WORLD_WIDTH; x++) {
            char f = world_get(x, y);
            if (f == DEAD) {
                printf(" ");
            } else if (f == ALIVE) {
                printf("\u2588");
            } else {
                printf("?");
            }
        }
        printf("%s\n", BORDER);
    }

    // Print lower border
    for (unsigned int i = 0; i < WORLD_WIDTH + 2; i++) {
        printf("%s", BORDER);
    }
    printf("\n");
}

