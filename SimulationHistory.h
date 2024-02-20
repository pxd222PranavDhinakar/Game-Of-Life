#ifndef SIMULATION_HISTORY_H
#define SIMULATION_HISTORY_H

#include "config.h" // Ensure GRID_WIDTH and GRID_HEIGHT are defined here or elsewhere

#define HISTORY_SIZE 100

typedef struct {
    int*** grids; // Pointer to a 3D array
    int currentIndex; // Current position in the history
    int totalStates; // Total number of states stored
} SimulationHistory;

extern SimulationHistory history;

void initSimulationHistory(SimulationHistory* history);
void freeSimulationHistory(SimulationHistory* history);
void saveStateToHistory(SimulationHistory* history, const int grid[GRID_HEIGHT][GRID_WIDTH]);
void stepBackwardInHistory(SimulationHistory* history, int grid[GRID_HEIGHT][GRID_WIDTH]);
int stepForwardInHistory(SimulationHistory* history, int grid[GRID_HEIGHT][GRID_WIDTH]);

#endif // SIMULATION_HISTORY_H
