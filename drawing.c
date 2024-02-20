// drawing.c
#include <string.h> // For memset
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "drawing.h" // For Drawing and related functions
#include "types.h"   // For Point, if used
#include "config.h"  // For GRID_WIDTH and GRID_HEIGHT


// Initializes a Drawing with specified dimensions
void initDrawing(Drawing *d, int width, int height) {
    d->width = width;
    d->height = height;
    clearDrawing(d); // Clear the drawing to start with a blank slate
}

// Sets the value of a specific cell in the drawing
void setCell(Drawing *d, int x, int y, int value) {
    if (x >= 0 && x < d->width && y >= 0 && y < d->height) {
        d->grid[y][x] = value;
    }
}

// Clears the drawing, setting all cells to 0
void clearDrawing(Drawing *d) {
    for (int i = 0; i < d->height; ++i) {
        memset(d->grid[i], 0, d->width * sizeof(int));
    }
}

// Implement the placeDrawing function
void placeDrawing(const Drawing *drawing, Point topLeft, int (*mainGrid)[GRID_WIDTH]) {
    for (int i = 0; i < drawing->height; i++) {
        for (int j = 0; j < drawing->width; j++) {
            // Calculate the position in the main grid
            int posY = topLeft.y + i;
            int posX = topLeft.x + j;

            // Check bounds before placing
            if (posX >= 0 && posX < GRID_WIDTH && posY >= 0 && posY < GRID_HEIGHT) {
                mainGrid[posY][posX] = drawing->grid[i][j];
            }
        }
    }
}


