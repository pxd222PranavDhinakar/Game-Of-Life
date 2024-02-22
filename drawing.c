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



Drawing* loadDrawingFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file %s for reading.\n", filename);
        return NULL;
    }

    int width, height;
    // Attempt to read the dimensions of the drawing from the file
    if (fscanf(file, "%d %d", &width, &height) != 2) {
        printf("Failed to read drawing dimensions from file.\n");
        fclose(file);
        return NULL;
    }

    // Ensure the read dimensions do not exceed our maximum allowed dimensions
    if (width > MAX_DRAWING_WIDTH || height > MAX_DRAWING_HEIGHT) {
        printf("Drawing dimensions in file exceed maximum allowed dimensions.\n");
        fclose(file);
        return NULL;
    }

    // Allocate memory for the drawing
    Drawing* drawing = (Drawing*)malloc(sizeof(Drawing));
    if (drawing == NULL) {
        printf("Failed to allocate memory for drawing.\n");
        fclose(file);
        return NULL;
    }

    // Initialize the drawing with the read dimensions
    initDrawing(drawing, width, height);

    // Read the grid state from the file
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (fscanf(file, "%d", &drawing->grid[y][x]) != 1) {
                printf("Failed to read cell state from file.\n");
                free(drawing);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return drawing;
}



void rotateDrawingClockwise(Drawing *d) {
    Drawing temp;
    initDrawing(&temp, d->height, d->width); // Swap width and height for the rotated drawing

    for (int i = 0; i < d->height; ++i) {
        for (int j = 0; j < d->width; ++j) {
            temp.grid[j][d->height - 1 - i] = d->grid[i][j];
        }
    }

    // Copy the rotated drawing back to the original
    *d = temp;
}


void flipDrawingXAxis(Drawing *d) {
    for (int i = 0; i < d->height / 2; ++i) {
        for (int j = 0; j < d->width; ++j) {
            // Swap cells symmetrically along the x-axis
            int temp = d->grid[i][j];
            d->grid[i][j] = d->grid[d->height - 1 - i][j];
            d->grid[d->height - 1 - i][j] = temp;
        }
    }
}

void flipDrawingYAxis(Drawing *d) {
    for (int i = 0; i < d->height; ++i) {
        for (int j = 0; j < d->width / 2; ++j) {
            // Swap cells symmetrically along the y-axis
            int temp = d->grid[i][j];
            d->grid[i][j] = d->grid[i][d->width - 1 - j];
            d->grid[i][d->width - 1 - j] = temp;
        }
    }
}
