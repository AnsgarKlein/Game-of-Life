FLAGS      :=  -std=c17 -g
FLAGS      +=  -Wall -Wextra -Wpedantic
FLAGS      +=  -pthread -fopenmp

SOURCEDIR  :=  src
BUILDDIR   :=  build

TARGET     :=  game

SOURCES     =  $(notdir $(wildcard $(SOURCEDIR)/*.c))
HEADERS     =  $(notdir $(wildcard $(SOURCEDIR)/*.h))
OBJECTS     =  $(SOURCES:.c=.o)

LIBRARIES   =  sdl2
LIBRARIES  +=  SDL2_image
LIBRARIES  +=  gl
LIBRARIES  +=  glu

CFLAGS      =  $(FLAGS) -x c
CFLAGS     +=  $(shell pkg-config --cflags $(LIBRARIES))

LDFLAGS     =  $(FLAGS)
LDFLAGS    +=  $(shell pkg-config --libs $(LIBRARIES))



.PHONY: all clean debug optimized

all: $(BUILDDIR)/$(TARGET) $(addprefix $(SOURCEDIR)/, $(SOURCES)) $(addprefix $(SOURCEDIR)/, $(HEADERS))
	@#

debug: CFLAGS += -g
debug: LDFLAGS += -g
debug: all

optimized: CFLAGS += -O3
optimized: LDFLAGS += -O3
optimized: all

profiling: CFLAGS += -pg
profiling: LDFLAGS += -pg
profiling: all
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
	
