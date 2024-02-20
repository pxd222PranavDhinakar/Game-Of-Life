#ifndef GLIDER_GUN_H
#define GLIDER_GUN_H

#include <stdbool.h>
#include "types.h"   // For Point, if used
#include "config.h"  // For GRID_WIDTH and GRID_HEIGHT


// Define the size of the grid from the main program
extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

// Define a point struct
//typedef struct Point {
//    int x;
//    int y;
//} Point;

// Define a glider gun struct
typedef struct GliderGun {
    Point origin;
} GliderGun;

// Function declaration to place a glider gun on the grid
void placeGliderGun(GliderGun *gun, int (*grid)[GRID_WIDTH]);
//void placeGliderGun(GliderGun gun, int grid[GRID_HEIGHT][GRID_WIDTH]);

#endif // GLIDER_GUN_H

