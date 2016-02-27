CC = g++

# where to search for headers
INC = -I ../../include

# common source files
C_FILES= $(wildcard ../../src/*.cpp)

CFLAGS_DBG = -g -std=c++11 -Wall -Wextra -Werror -Wwrite-strings -pedantic-errors -Wno-unused
CFLAGS_REL = -O3 -std=c++11 -Wall -Wextra -Werror -Wwrite-strings -pedantic-errors -Wno-unused

# external libraries
LFLAGS = -lSDL2 -lGL -lGLEW -lSOIL -lm

# the build target executable:
TARGET = pong

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp 

clean:
	$(RM) $(TARGET)

release: $(TARGET).cpp
	$(CC) $(CFLAGS_REL) -o $(TARGET) $(TARGET).cpp $(INC) $(C_FILES) $(LFLAGS)

debug: $(TARGET).cpp
	$(CC) $(CFLAGS_DBG) -o $(TARGET) $(TARGET).cpp $(INC) $(C_FILES) $(LFLAGS)
