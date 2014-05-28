
# Basic
CXX ?= g++

INCFLAGS := $(shell pkg-config --cflags SDL_mixer)
CXXFLAGS = -Wall -std=c++11 $(INCFLAGS)
CXXFLAGS += -I lib/gdl/includes/
LDFLAGS := $(shell pkg-config --libs SDL_mixer) -L ./lib/gdl/libs/ -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -ldl

OFLAGS :=
DBGFLAGS := -DDEBUG -ggdb3
NDBGFLAGS = -DNDEBUG $(OFLAGS)

# Lua lib according to the user distribution
# VERY VERY DEGUEULASSE !!!!!!!!!!!!
# l'idée c'est que si la valeur de retour de la commande (uname -rms | grep -o ARCH) vaut 0 on utilise « lua » sinon « lua5.2 »
INCFLAGS += $(shell pkg-config --cflags lua) $(shell pkg-config --cflags lua5.2)
LDFLAGS += $(shell pkg-config --libs lua) $(shell pkg-config --libs lua5.2)

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

lua_version:
		@echo $(LUA_LIB)
		@echo $(DISTRIB)
		@echo $(shell pkg-config --libs --cflags lua)
		@echo $(shell pkg-config --libs --cflags lua5.2)

$(TARGET): $(OBJ)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

