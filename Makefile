
# Basic
CXX ?= g++

INCFLAGS :=
CXXFLAGS = -Wall -std=c++11 $(INCFLAGS)
LDFLAGS := -lSDL_mixer -lSDL -lpthread

OFLAGS :=
DBGFLAGS := -DDEBUG -ggdb3
NDBGFLAGS = -DNDEBUG $(OFLAGS)

# The default mode (set it to 0 before the rendu)
DEBUG ?= 1

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
SRC_SUBDIRS := scene scenesmanager soundmanager
SRC_ALLDIRS := $(SRC_ROOTDIR) $(foreach sub_dir, $(SRC_SUBDIRS), $(SRC_ROOTDIR)/$(sub_dir))

SRC := $(foreach dir, $(SRC_ALLDIRS), $(wildcard $(dir)/*.cpp))
INCFLAGS := $(foreach dir, $(SRC_ALLDIRS), -I $(dir)/)

# Generated object files
OBJ := $(SRC:.cpp=.o)

# Utils
RM := rm -vf

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

