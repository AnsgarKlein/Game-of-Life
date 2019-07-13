FLAGS      :=  -std=c17 -g
FLAGS      +=  -Wall -Wextra -Wpedantic

SOURCEDIR  :=  src
BUILDDIR   :=  build

TARGET     :=  game

SOURCES     =  $(notdir $(wildcard $(SOURCEDIR)/*.c))
HEADERS     =  $(notdir $(wildcard $(SOURCEDIR)/*.h))
OBJECTS     =  $(SOURCES:.c=.o)

LIBRARIES   =  sdl2
LIBRARIES  +=  SDL2_image

CFLAGS      =  $(FLAGS) -x c
CFLAGS     +=  $(shell pkg-config --cflags $(LIBRARIES))

LDFLAGS     =  $(FLAGS)
LDFLAGS    +=  $(shell pkg-config --libs $(LIBRARIES))



ifdef GAMEOFLIFE_DEBUG
    CFLAGS      += -g
    LDFLAGS     += -g
endif

ifdef GAMEOFLIFE_OPTIMIZED
    CFLAGS      += -O3
    LDFLAGS     += -O3
endif

ifdef GAMEOFLIFE_PROFILING
    CFLAGS      += -pg
    LDFLAGS     += -pg
endif

ifdef GAMEOFLIFE_OPENGL
    LIBRARIES   += gl
    LIBRARIES   += glu
    CFLAGS	    += -D USE_OPENGL
endif

ifdef GAMEOFLIFE_OMP
    FLAGS      += -pthread -fopenmp
endif

.PHONY: all clean debug

all: $(BUILDDIR)/$(TARGET) $(addprefix $(SOURCEDIR)/, $(SOURCES)) $(addprefix $(SOURCEDIR)/, $(HEADERS))
	@#

clean: 
	@# Remove executable
	@if [[ -f $(BUILDDIR)/$(TARGET) ]]; then \
	  echo " [CLEAN]   $(BUILDDIR)/$(TARGET)" ; \
	  rm -f $(BUILDDIR)/$(TARGET) ; \
	fi
	
	@# Remove object files
	@for obj in $(wildcard $(BUILDDIR)/*.o); do \
	  echo " [CLEAN]   $$obj" ; \
	  rm -f $$obj ; \
	done


lint:
	splint $(shell pkg-config --cflags $(LIBRARIES)) $(addprefix $(SOURCEDIR)/, $(SOURCES))


$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/, $(OBJECTS))
	@echo " [LD]      $@"
	@$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c $(addprefix $(SOURCEDIR)/, $(HEADERS))
	@echo " [CC]      $@"
	@$(CC) $(CFLAGS) -c $< -o $@
	
