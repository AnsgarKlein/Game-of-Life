#ifndef VIEW_H
#define VIEW_H

#include <stdbool.h>
#include <stdlib.h>

#include <SDL.h>

#ifdef USE_OPENGL
#include <SDL_opengl.h>
#include <GL/glu.h>
#endif

#include "BitVector.h"

bool View_initialize(unsigned int world_width, unsigned int world_height);

void View_deinitialize();

void View_set_fields(const unsigned char *vec, unsigned int width, unsigned int height);

#endif
