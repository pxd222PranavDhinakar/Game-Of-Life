# Makefile for Conway's Game of Life using SDL

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c11 `sdl2-config --cflags`

# Linker Flags
LDFLAGS = `sdl2-config --libs`

# Source Files
SRC = main.c

# Object Files
OBJ = $(SRC:.c=.o)

# Executable Name
EXEC = GameOfLife

# Default target
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJ)
