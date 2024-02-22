// drawing.h

#ifndef DRAWING_H
#define DRAWING_H

#define MAX_DRAWING_WIDTH 1000
#define MAX_DRAWING_HEIGHT 1000

#include "types.h"   // For Point, if used
#include "config.h"  // For GRID_WIDTH and GRID_HEIGHT


// Represents a drawable subsection of the grid
typedef struct {
    int grid[MAX_DRAWING_HEIGHT][MAX_DRAWING_WIDTH]; // 2D array for the drawing
    int width;  // Width of the drawing
    int height; // Height of the drawing
} Drawing;

// Function prototypes
void initDrawing(Drawing *d, int width, int height);
void setCell(Drawing *d, int x, int y, int value);
void clearDrawing(Drawing *d);
void placeDrawing(const Drawing *drawing, Point topLeft, int (*mainGrid)[GRID_WIDTH]);
Drawing* loadDrawingFromFile(const char* filename);
void rotateDrawingClockwise(Drawing *d);
void flipDrawingXAxis(Drawing *d);
void flipDrawingYAxis(Drawing *d);

#endif // DRAWING_H
