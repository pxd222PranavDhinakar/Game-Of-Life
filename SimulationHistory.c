#include "SimulationHistory.h"
#include <stdlib.h> // For malloc, free
#include <string.h> // For memcpy
#include <stdio.h>

// Assuming GRID_WIDTH and GRID_HEIGHT are globally defined constants
extern const int GRID_WIDTH;
extern const int GRID_HEIGHT;

SimulationHistory history;

void initSimulationHistory(SimulationHistory* history) {
    // Allocate memory for the 3D array
    history->grids = (int***)malloc(HISTORY_SIZE * sizeof(int**));
    // Loop through the 3D array and allocate memory for each 2D array
    for (int i = 0; i < HISTORY_SIZE; ++i) {
        // Allocate memory for each row in the 2D array
        history->grids[i] = (int**)malloc(GRID_HEIGHT * sizeof(int*));
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            // Allocate cell in the 2D array
            history->grids[i][j] = (int*)malloc(GRID_WIDTH * sizeof(int));
            // Optionally initialize the grid to zero
            memset(history->grids[i][j], 0, GRID_WIDTH * sizeof(int));
        }
    }
    history->currentIndex = -1; // Start with no state saved
    history->totalStates = 0;
}

void freeSimulationHistory(SimulationHistory* history) {
    // Free the memory for each 2D array and then the 3D array
    for (int i = 0; i < HISTORY_SIZE; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            free(history->grids[i][j]);
        }
        free(history->grids[i]);
    }
    free(history->grids);
    history->grids = NULL;
    history->currentIndex = -1;
    history->totalStates = 0;
}

void saveStateToHistory(SimulationHistory* history, const int grid[GRID_HEIGHT][GRID_WIDTH]) {
    // If there is space in the history, save the current state
    if (history->totalStates < HISTORY_SIZE) {
        history->currentIndex = (history->currentIndex + 1) % HISTORY_SIZE;
        if (history->currentIndex == -1) history->currentIndex = 0; // First time save adjustment
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            memcpy(history->grids[history->currentIndex][i], grid[i], GRID_WIDTH * sizeof(int));
        }
        history->totalStates += (history->totalStates < HISTORY_SIZE) ? 1 : 0;
    }
    // If the history is full, overwrite the oldest state
    else {
        history->currentIndex = (history->currentIndex + 1) % HISTORY_SIZE;
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            memcpy(history->grids[history->currentIndex][i], grid[i], GRID_WIDTH * sizeof(int));
        }
    }
}

void stepBackwardInHistory(SimulationHistory* history, int grid[GRID_HEIGHT][GRID_WIDTH]) {
    if (history->totalStates > 0 && history->currentIndex > 0) {
        history->currentIndex = (history->currentIndex - 1 + HISTORY_SIZE) % HISTORY_SIZE;
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            memcpy(grid[i], history->grids[history->currentIndex][i], GRID_WIDTH * sizeof(int));
        }
    }
}

int stepForwardInHistory(SimulationHistory* history, int grid[GRID_HEIGHT][GRID_WIDTH]) {
    // If there are states saved and the next state is not empty get the latest saved state
    // DONT WRAP AROUND TO AN OLD STATE
    if (history->totalStates > 0 && ((history->currentIndex + 1) % HISTORY_SIZE) < history->totalStates) {
        history->currentIndex = (history->currentIndex + 1) % HISTORY_SIZE;
        //printf("I JUMP \n"); // FIX LATER
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            memcpy(grid[i], history->grids[history->currentIndex][i], GRID_WIDTH * sizeof(int));
        }
        return 1;
    }
    else if (history->totalStates > 0 && ((history->currentIndex + 1) % HISTORY_SIZE) >= history->totalStates) {
        //printf("I DONT JUMP \n"); // FIX LATER
        return 0;
    }
    else {
        return 0;
    }
}
