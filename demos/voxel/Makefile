# compiler
CC = g++

# where to search for headers
INC = -I ../../include -I ./include

# common source files
C_FILES= $(wildcard ../../src/*.cpp) $(wildcard ./src/*.cpp)

# compiler flags debug
CFLAGS_DBG = -g -std=c++11 -Wall -Wextra -Werror -Wwrite-strings -pedantic-errors -Wno-unused
# compiler flags release
CFLAGS_REL = -O3 -std=c++11 -Wall -Wextra -Werror -Wwrite-strings -pedantic-errors -Wno-unused

# external libraries
LFLAGS = -lSDL2 -lSDL2_mixer -lGL -lGLEW -lSOIL -lm

# the build target executable:
TARGET = voxel

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp 

clean:
	$(RM) $(TARGET)

release: $(TARGET).cpp
	$(CC) $(CFLAGS_REL) -o $(TARGET) $(TARGET).cpp $(INC) $(C_FILES) $(LFLAGS)

debug: $(TARGET).cpp
	$(CC) $(CFLAGS_DBG) -o $(TARGET) $(TARGET).cpp $(INC) $(C_FILES) $(LFLAGS)
