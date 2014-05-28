
# Basic
CXX ?= g++

INCFLAGS := $(shell pkg-config --cflags SDL_mixer) $(shell pkg-config --cflags lua)
CXXFLAGS = -Wall -std=c++11 $(INCFLAGS)
CXXFLAGS += -I lib/gdl/includes/
LDFLAGS := $(shell pkg-config --libs SDL_mixer) -L ./lib/gdl/libs/ -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -ldl $(shell pkg-config --libs lua)

OFLAGS :=
DBGFLAGS := -DDEBUG -ggdb3
NDBGFLAGS = -DNDEBUG $(OFLAGS)

# The default mode (set it to 0 before the rendu)
DEBUG ?= 1

CXXFLAGS += $(DGBFLAGS)

ifeq ($(DEBUG), 1)
CXXFLAGS += $(DGBFLAGS)
else
CXXFLAGS += $(NDBGFLAGS)
endif

# Optimisation (default 3, only in non-debug mode)
OPTI ?= 3
ifneq ($(OPTI), 0)
OFLAGS = -O$(OPTI)
endif

# Files and locations
TARGET := bomberman

SRC_ROOTDIR := src
SRC_SUBDIRS := scene scenesmanager soundmanager object API Lua
SRC_ALLDIRS := $(SRC_ROOTDIR) $(foreach sub_dir, $(SRC_SUBDIRS), $(SRC_ROOTDIR)/$(sub_dir))

SRC := $(foreach dir, $(SRC_ALLDIRS), $(wildcard $(dir)/*.cpp))
INCFLAGS += $(foreach dir, $(SRC_ALLDIRS), -I $(dir)/)

# Generated object files
OBJ := $(SRC:.cpp=.o)

# Utils
RM := rm -vf

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

