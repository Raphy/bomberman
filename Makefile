
# Basic
CXX ?= g++

INCFLAGS := $(shell pkg-config --cflags)
CXXFLAGS = -Wall -std=c++11 $(INCFLAGS)
CXXFLAGS += -I lib/gdl/includes/
LDFLAGS :=  -L ./lib/gdl/libs -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk  -lpthread -ldl -lSDL2 -lSDL2_mixer
# $(shell pkg-config --libs)
OFLAGS :=
DBGFLAGS := -DDEBUG -ggdb3
NDBGFLAGS = -DNDEBUG $(OFLAGS)

# Lua lib according to the user distribution
ifeq ($(shell uname -rms | grep -o ARCH), ARCH)
LIBLUA_NAME="lua"
else
LIBLUA_NAME="lua5.2"
endif
INCFLAGS += $(shell pkg-config --cflags $(LIBLUA_NAME))
LDFLAGS += $(shell pkg-config --libs $(LIBLUA_NAME))


# The default mode (set it to 0 before the rendu)
DEBUG ?= 1

ifeq ($(DEBUG), 1)
CXXFLAGS += $(DBGFLAGS)
else
CXXFLAGS += $(NDBGFLAGS)
endif

# Optimisation (default 3, only in non-debug mode)
OPTI ?= 3
ifneq ($(OPTI), 0)
OFLAGS = -O$(OPTI)
endif

# Files and locations
TARGET := ./build/bomberman

SRC_ROOTDIR := src
SRC_SUBDIRS := scene scenesmanager sound object API Lua game menu maptext
SRC_ALLDIRS := $(SRC_ROOTDIR) $(foreach sub_dir, $(SRC_SUBDIRS), $(SRC_ROOTDIR)/$(sub_dir))

SRC := $(foreach dir, $(SRC_ALLDIRS), $(wildcard $(dir)/*.cpp))
INCFLAGS += $(foreach dir, $(SRC_ALLDIRS), -I $(dir)/)

# Generated object files
OBJ := $(SRC:.cpp=.o)

# Utils
RM := rm -vf

# Rules
all: $(TARGET)

lua_version:
		@echo $(MAVAR)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

