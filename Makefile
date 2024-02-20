# Makefile for Conway's Game of Life using SDL

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c11 -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE

# Linker Flags
LDFLAGS = -L/opt/homebrew/lib -lSDL2

# Find all .c files in the directory
SRC = $(wildcard *.c)

# Replace the .c extension with .o for all source files
OBJ = $(SRC:.c=.o)

# Executable Name
EXEC = GameOfLife

# Default target
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# To obtain object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJ)
