#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gliderGun.h"
#include "config.h"
#include "types.h"


void placeGliderGun(GliderGun *gun, int (*grid)[GRID_WIDTH]) {
    // Clear the area where the glider gun will be placed if needed
    // ...

    // Place the glider gun based on the origin given by gun->origin.x and gun->origin.y
    //int topLeftX = gun.origin.x;
    //int topLeftY = gun.origin.y;
    // Assuming gun->origin.x and gun->origin.y are within bounds
    int topLeftX = gun->origin.x - 18; // Adjust based on actual glider gun size
    int topLeftY = gun->origin.y - 4;  // Adjust based on actual glider gun size


    // Adjusted loop to clear an area - assuming this was the intention?
    // Note: The loop logic here seems to intend to clear an area but does so incorrectly.
    // It should likely iterate from 0 up to the dimensions of the structure you're clearing,
    // offset by topLeftX and topLeftY for the starting position.
    // Example of clearing an area (corrected):
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 36; j++) {
            // Ensure you're within bounds of the grid
            if ((topLeftY + i) < GRID_HEIGHT && (topLeftX + j) < GRID_WIDTH) {
                grid[topLeftY + i][topLeftX + j] = 0; // Clear the cell
            }
        }
    }

    // Updating gun's position is not usual unless you're tracking it for some reason
    // gun->origin.x = 0;

    // Setup the actual glider gun structure...
    // Make sure to use grid[y][x] = 1; within bounds checks

    // Example:
    // if ((topLeftY + 4) < gridHeight && (topLeftX) < gridWidth) {
    //     grid[topLeftY + 4][topLeftX] = 1;
    // }
    // ... rest of your glider gun setup ensuring each access is within bounds

        // Set up the glider gun
    // First set up a block five cells down from the top left corner
    grid[topLeftY + 4][topLeftX] = 1;
    grid[topLeftY + 4][topLeftX + 1] = 1;
    grid[topLeftY + 5][topLeftX] = 1;
    grid[topLeftY + 5][topLeftX + 1] = 1;

    // Second set up another block two cells down from the top left corner
    grid[topLeftY + 2][topLeftX + 35] = 1;
    grid[topLeftY + 2][topLeftX + 34] = 1;
    grid[topLeftY + 3][topLeftX + 35] = 1;
    grid[topLeftY + 3][topLeftX + 34] = 1;


    // Third set up the glider gun's "barrel"
    // Move 8 cells to the right of the first block and set up a block
    grid[topLeftY + 4][topLeftX + 10] = 1;
    grid[topLeftY + 5][topLeftX + 10] = 1;
    grid[topLeftY + 6][topLeftX + 10] = 1;

    // Top of barrel
    grid[topLeftY + 3][topLeftX + 11] = 1;
    grid[topLeftY + 2][topLeftX + 12] = 1;
    grid[topLeftY + 2][topLeftX + 13] = 1;

    // Bottom of the barrel
    grid[topLeftY + 7][topLeftX + 11] = 1;
    grid[topLeftY + 8][topLeftX + 12] = 1;
    grid[topLeftY + 8][topLeftX + 13] = 1;

    // Set up the glider gun's "tub"
    grid[topLeftY + 5][topLeftX + 14] = 1;

    // Top of the tub
    grid[topLeftY + 5][topLeftX + 16] = 1;
    grid[topLeftY + 5][topLeftX + 17] = 1;
    grid[topLeftY + 4][topLeftX + 16] = 1;
    grid[topLeftY + 6][topLeftX + 16] = 1;

    grid[topLeftY + 3][topLeftX + 15] = 1;
    grid[topLeftY + 7][topLeftX + 15] = 1;

    // Set up the glider gun's "tail"
    grid[topLeftY + 3][topLeftX + 20] = 1;
    grid[topLeftY + 2][topLeftX + 20] = 1;
    grid[topLeftY + 4][topLeftX + 20] = 1;
    grid[topLeftY + 3][topLeftX + 21] = 1;
    grid[topLeftY + 2][topLeftX + 21] = 1;
    grid[topLeftY + 4][topLeftX + 21] = 1;

    grid[topLeftY + 1][topLeftX + 22] = 1;
    grid[topLeftY + 5][topLeftX + 22] = 1;

    grid[topLeftY + 1][topLeftX + 24] = 1;
    grid[topLeftY][topLeftX + 24] = 1;

    grid[topLeftY + 5][topLeftX + 24] = 1;
    grid[topLeftY + 6][topLeftX + 24] = 1;
}


/*
void placeGliderGun(GliderGun gun, int grid[GRID_HEIGHT][GRID_WIDTH]) {
    // Clear the area where the glider gun will be placed if needed
    // ...

     // Place the glider gun based on the origin given by gun.origin.x and gun.origin.y
    int topLeftX = gun.origin.x;
    int topLeftY = gun.origin.y;

    // Set up a block at the origin
    //grid[topLeftY][topLeftX] = 1;
    //grid[topLeftY][topLeftX + 1] = 1;
    //grid[topLeftY + 1][topLeftX] = 1;
    //grid[topLeftY + 1][topLeftX + 1] = 1;




    // Set up a 9 tall x 36 wide rectangle in the center
    for (int i = topLeftX; i < (topLeftX+9); i++) {
        for (int j = topLeftY; j < (topLeftY+36); j++) {
            // Clear the area for the glider gun to prevent overlapping patterns
            grid[topLeftX + i][topLeftY + j] = 0; // Clear the cell
        }
    }

    gun.origin.x = 0;

    // Randomly populate the entire grid
    //for (int i = 0; i < GRID_WIDTH; i++) {
    //    for (int j = 0; j < GRID_HEIGHT; j++) {
    //        grid[i][j] = rand() % 2;
    //    }
    //}

    
    // Set up the glider gun
    // First set up a block five cells down from the top left corner
    grid[topLeftY + 4][topLeftX] = 1;
    grid[topLeftY + 4][topLeftX + 1] = 1;
    grid[topLeftY + 5][topLeftX] = 1;
    grid[topLeftY + 5][topLeftX + 1] = 1;

    // Second set up another block two cells down from the top left corner
    grid[topLeftY + 2][topLeftX + 35] = 1;
    grid[topLeftY + 2][topLeftX + 34] = 1;
    grid[topLeftY + 3][topLeftX + 35] = 1;
    grid[topLeftY + 3][topLeftX + 34] = 1;


    // Third set up the glider gun's "barrel"
    // Move 8 cells to the right of the first block and set up a block
    grid[topLeftY + 4][topLeftX + 10] = 1;
    grid[topLeftY + 5][topLeftX + 10] = 1;
    grid[topLeftY + 6][topLeftX + 10] = 1;

    // Top of barrel
    grid[topLeftY + 3][topLeftX + 11] = 1;
    grid[topLeftY + 2][topLeftX + 12] = 1;
    grid[topLeftY + 2][topLeftX + 13] = 1;

    // Bottom of the barrel
    grid[topLeftY + 7][topLeftX + 11] = 1;
    grid[topLeftY + 8][topLeftX + 12] = 1;
    grid[topLeftY + 8][topLeftX + 13] = 1;

    // Set up the glider gun's "tub"
    grid[topLeftY + 5][topLeftX + 14] = 1;

    // Top of the tub
    grid[topLeftY + 5][topLeftX + 16] = 1;
    grid[topLeftY + 5][topLeftX + 17] = 1;
    grid[topLeftY + 4][topLeftX + 16] = 1;
    grid[topLeftY + 6][topLeftX + 16] = 1;

    grid[topLeftY + 3][topLeftX + 15] = 1;
    grid[topLeftY + 7][topLeftX + 15] = 1;

    // Set up the glider gun's "tail"
    grid[topLeftY + 3][topLeftX + 20] = 1;
    grid[topLeftY + 2][topLeftX + 20] = 1;
    grid[topLeftY + 4][topLeftX + 20] = 1;
    grid[topLeftY + 3][topLeftX + 21] = 1;
    grid[topLeftY + 2][topLeftX + 21] = 1;
    grid[topLeftY + 4][topLeftX + 21] = 1;

    grid[topLeftY + 1][topLeftX + 22] = 1;
    grid[topLeftY + 5][topLeftX + 22] = 1;

    grid[topLeftY + 1][topLeftX + 24] = 1;
    grid[topLeftY][topLeftX + 24] = 1;

    grid[topLeftY + 5][topLeftX + 24] = 1;
    grid[topLeftY + 6][topLeftX + 24] = 1;
    
    
}
*/




// Glider code
// Set up a glider in the top-left corner
//grid[1][2] = 1;
//grid[2][3] = 1;
//grid[3][1] = 1;
//grid[3][2] = 1;
//grid[3][3] = 1;