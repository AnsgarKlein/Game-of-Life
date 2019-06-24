
#include "Main.h"

static void help(char *argv0, bool error) {
    FILE *out = error ? stderr : stdout;

    fprintf(out, "Usage: %s [-h|--help]\n", argv0);
}

static bool parse_arguments(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            // Print help and exit
            help(argv[0], false);
            return false;
        } else {
            // Unknown parameter - print help and exit
            help(argv[0], true);
            return false;
        }
    }

    return true;
}

int main(int argc, char **argv) {
    if(!parse_arguments(argc, argv)) {
        return 0;
    }

    // Construct level 1
    const char D = DEAD;
    const char A = ALIVE;
    const char lev1[] =
        {D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,
         D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,
         D,D,D,A,A,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,A,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,A,A,D,D,D,D,D,A,D,A,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,A,A,D,D,D,D,D,D,A,D,A,D,D,D,D,A,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,A,D,A,D,D,A,D,A,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,A,D,A,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,A,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,D,D,D,A,D,D,A,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,A,D,D,D,D,A,D,D,A,D,D,A,A,D,D,D,
         D,A,A,D,D,D,D,D,D,D,D,D,D,A,D,A,D,D,D,D,D,D,A,A,D,D,A,D,D,A,D,D,
         A,A,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,D,D,D,D,D,D,D,D,D,D,A,A,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,A,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,
         A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,
         A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,
         D,D,D,D,D,D,D,D,D,D,A,A,A,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D,D};

    // Load level
    load_level(lev1, 32, 32);

    // Load random level
    //load_random_level(1000, 1000);


    // Measure time for 50 runs
    //struct timespec start, end;
    //clock_gettime(CLOCK_MONOTONIC, &start);
    //for (int i = 0; i < 50; i++) {
    //    //printf("Step %d\n", i);
    //    //world_print();
    //    step();
    //}
    //clock_gettime(CLOCK_MONOTONIC, &end);
    //double runtime = end.tv_sec - start.tv_sec;
    //double msec = abs(end.tv_nsec - start.tv_nsec) / 1000000000.0;
    //runtime += msec;
    //printf("\n50 runs took: %f\n", runtime);
    //return 0;


    if (!View_initialize(WORLD_WIDTH, WORLD_HEIGHT)) {
        fprintf(stderr, "Could not initialize view\n");
        return 1;
    }
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Process event queue
        while(SDL_PollEvent(&e) != 0) {
            // Check which type of event happened
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }

        // Do Stuff
        struct timespec timer;
        timer.tv_sec  = 0;
        timer.tv_nsec = 200000000L;
        nanosleep(&timer, NULL);

        step();
        View_set_fields(WORLD, WORLD_WIDTH, WORLD_HEIGHT);
    }

    // Quit
    View_deinitialize();
    world_deinit();
}

