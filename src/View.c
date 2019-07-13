
#include "View.h"

unsigned int WINDOW_WIDTH;
unsigned int WINDOW_HEIGHT;

uint8_t FIELD_SIZE = 5;

SDL_Window *WINDOW;
SDL_Surface *WINSURFACE;
SDL_GLContext *WINCONTEXT;

static void initialize_window_sizes(unsigned int world_width, unsigned int world_height) {
    unsigned int target_w = 1024;
    unsigned int target_h = 768;

    //TODO: Improve this window size calculation

    // Increasing field size until window gets filled
    unsigned int f = 1;
    while (f * world_width < target_w && f * world_height < target_h) {
        f++;
    }

    // Decrease field size until fields fit into window or field size is 1
    while (f * world_height > target_w || f * world_height > target_h) {
        if (f == 1) {
            break;
        }
        f--;
    }

    // Window size is the field count mutliplied by the field size.
    // This can still be larger than the requested size since the
    // field size will only be decremented to a minimum of 1.
    WINDOW_WIDTH  = world_width  * f;
    WINDOW_HEIGHT = world_height * f;
    FIELD_SIZE = f;
}

#ifndef USE_OPENGL
static inline uint32_t get_color(unsigned int x, unsigned int y) {
    uint8_t r = 200;
    uint8_t g;
    uint8_t b;

    // x coordinate is green
    float g_perc = x / (WINDOW_WIDTH / 100);
    g = (g_perc / 100) * 200;

    // y coordinate is blue
    float b_perc = y / (WINDOW_WIDTH / 100);
    b = (b_perc / 100) * 200;

    return SDL_MapRGB(WINSURFACE->format, r, g, b);
}
#endif

static bool initialize_sdl() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize!\n"
                "SDL_Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Create window
    WINDOW = NULL;
    WINDOW = SDL_CreateWindow("Game of Life",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (WINDOW == NULL) {
        fprintf(stderr, "Window could not be created!\n"
                "SDL_Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Get window surface
    WINSURFACE = SDL_GetWindowSurface(WINDOW);
    if (WINSURFACE == NULL) {
        fprintf(stderr, "Could not get surface of window!"
                "SDL_Error: '%s'\n", SDL_GetError());
        return false;
    }

    // Fill the surface with color
    uint32_t color = SDL_MapRGB(WINSURFACE->format, 0x00, 0xAA, 0x00);
    if (SDL_FillRect(WINSURFACE, NULL, color) != 0) {
        fprintf(stderr, "Could not fill window with color!\n"
                "SDL_Error: '%s'\n", SDL_GetError());
        return false;
    }
    if (SDL_UpdateWindowSurface(WINDOW) != 0) {
        fprintf(stderr, "Could not update sdl window surface!\n"
                "SDL_Error: '%s'\n", SDL_GetError());
        return false;
    }

    return true;
}

#ifdef USE_OPENGL
static bool initialize_opengl() {
    // Use OpenGL version 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Get OpenGL context
    WINCONTEXT = SDL_GL_CreateContext(WINDOW);

    // Try to use VSync
    if (SDL_GL_SetSwapInterval(1) != 0) {
        fprintf(stderr,
                "Enabling VSync is not supported - running without VSync\n");
    }

    // Set projection matrix to identity matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Multiply current matrix with ortho matrix
    glOrtho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, 0.f, 1.f);

    // Set clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Clear backround
    glClear(GL_COLOR_BUFFER_BIT);

    // Check if errors ocurred
    GLenum error = GL_NO_ERROR;
    error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "Error occurred when initializing OpenGL!\n"
                "OpenGL Error: '%s'\n", gluErrorString(error));
        return false;
    }

    return true;
}
#endif

bool View_initialize(unsigned int world_width, unsigned int world_height) {
    // Calculate window size
    initialize_window_sizes(world_width, world_height);

    // Initialize SDL2
    if (!initialize_sdl()) {
        return false;
    }

    #ifdef USE_OPENGL
    // Initialize OpenGl
    if (!initialize_opengl()) {
        return false;
    }
    #endif

    return true;
}

void View_deinitialize() {
    SDL_FreeSurface(WINSURFACE);
    SDL_DestroyWindow(WINDOW);

    // Quit SDL subsystems
    SDL_Quit();
}

void View_set_fields(const unsigned char *vec, unsigned int width, unsigned int height) {
    #ifdef USE_OPENGL
        // Clear so we dont have to set unset parts
        glClear(GL_COLOR_BUFFER_BIT);

        // for every set field draw a box
        for (unsigned long i = 0; i < width * height; i++) {
            unsigned int x = i % width;
            unsigned int y = i / height;
            unsigned char state = BitVector_get(vec, i);

            // Set new color
            if (state == 0x00) {
                continue;
            }
            glColor3f(0.f, 1.f, 0.f);

            glBegin(GL_QUADS);
            glVertex2f(      x * FIELD_SIZE, (y + 1) * FIELD_SIZE);
            glVertex2f((x + 1) * FIELD_SIZE, (y + 1) * FIELD_SIZE);
            glVertex2f((x + 1) * FIELD_SIZE,       y * FIELD_SIZE);
            glVertex2f(      x * FIELD_SIZE,       y * FIELD_SIZE);
            glEnd();
        }

        SDL_GL_SwapWindow(WINDOW);
    #else
        for (unsigned long i = 0; i < width * height; i++) {
            unsigned int x = i % width;
            unsigned int y = i / width;
            unsigned char state = BitVector_get(vec, i);

            SDL_Rect field;
            field.w = FIELD_SIZE;
            field.h = FIELD_SIZE;
            field.x = x * FIELD_SIZE;
            field.y = y * FIELD_SIZE;

            uint32_t color;
            if (state == 0x01) {
                color = get_color(field.x, field.y);
            } else {
                color = SDL_MapRGB(WINSURFACE->format, 0x00, 0x00, 0x00);
            }

            if (SDL_FillRect(WINSURFACE, &field, color) != 0) {
                fprintf(stderr, "Could not draw to window!\n"
                        "SDL_Error: '%s'\n", SDL_GetError());
            }
        }

        // Update window
        if (SDL_UpdateWindowSurface(WINDOW) != 0) {
            fprintf(stderr, "Could not update window surface!\n"
                    "SDL_Error: '%s'\n", SDL_GetError());
        }
    #endif
}

