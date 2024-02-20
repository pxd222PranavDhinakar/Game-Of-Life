#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gliderGun.h"
#include "config.h"
#include "drawing.h"
#include "SimulationHistory.h"

// Define the window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


// Define the size of the grid
const int GRID_WIDTH = 80;
const int GRID_HEIGHT = 60;
//const int GRID_WIDTH = 160;
//const int GRID_HEIGHT = 120;

int grid[GRID_HEIGHT][GRID_WIDTH];
int nextGrid[GRID_HEIGHT][GRID_WIDTH];

// Global SimulationHistory Instance
SimulationHistory history;


/*
// Initialize SDL and create a window and renderer
void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    } else {
        window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            exit(1);
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                exit(1);
            }
        }
    }
}
*/


void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // Free SimulationHistory
    freeSimulationHistory(&history);
}




// Function to initialize the grid with a glider gun
void initializeGrid() {
    // Clear the grid
    memset(grid, 0, sizeof(grid));

    GliderGun gun = {.origin = {18, 4}};
    placeGliderGun(&gun, grid); // `grid` decays to a pointer to its first element

    //GliderGun gun = {.origin = {(GRID_WIDTH / 2), (GRID_HEIGHT / 2)}};
    GliderGun gun2 = {.origin = {60, 4}};
    placeGliderGun(&gun2, grid); // `grid` decays to a pointer to its first element
    

    //Drawing myDrawing;
    //initDrawing(&myDrawing, 5, 5); // Initialize a 5x5 drawing
    // Set some cells in the drawing
    // Set them in the pattern of a glider
    //setCell(&myDrawing, 1, 2, 1);
    //setCell(&myDrawing, 2, 3, 1);
    //setCell(&myDrawing, 3, 1, 1);
    //setCell(&myDrawing, 3, 2, 1);
    //setCell(&myDrawing, 3, 3, 1);


    
    // Place the drawing on the main grid
    //Point topLeft = {10, 10}; // Position to place the drawing on the main grid
    //placeDrawing(&myDrawing, topLeft, grid); // `grid` decays to a pointer to its first element

}


void initGame() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    } else {
        window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            exit(1);
        }
    }
    initializeGrid();
    // Initialize SimulationHistory
    initSimulationHistory(&history);
}


// Fixed boundary conditions
/*
int getAliveNeighbors(int x, int y) {
    int aliveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int nx = x + i;
            int ny = y + j;
            
            // Check if the neighbor is within the grid bounds
            if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                aliveNeighbors += grid[ny][nx];
            }
            // Cells outside the bounds are considered dead (no addition to aliveNeighbors)
        }
    }
    return aliveNeighbors;
}
*/

// Periodic boundary conditions
// The grid wraps around, creating a torus shape. This means the right edge connects to the left, and the top edge connects to the bottom, creating a continuous space without borders.

int getAliveNeighbors(int x, int y) {
    int aliveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int nx = (x + i + GRID_WIDTH) % GRID_WIDTH;
            int ny = (y + j + GRID_HEIGHT) % GRID_HEIGHT;
            aliveNeighbors += grid[ny][nx];
        }
    }
    return aliveNeighbors;
}


// Reflecting boundary conditions
// The edges reflect back into the grid, simulating a mirror at each edge. This means a cell at the edge has neighbors that include cells on the opposite side of the edge, as if the pattern were reflected back into the space.
/*
int getAliveNeighbors(int x, int y) {
    int aliveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int nx = x + i;
            int ny = y + j;
            // Reflect at edges
            if (nx < 0) nx = -nx;
            else if (nx >= GRID_WIDTH) nx = 2*GRID_WIDTH - nx - 1;
            if (ny < 0) ny = -ny;
            else if (ny >= GRID_HEIGHT) ny = 2*GRID_HEIGHT - ny - 1;
            aliveNeighbors += grid[ny][nx];
        }
    }
    return aliveNeighbors;
}
*/


void updateGame() {
    // Calculate next state of the grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            // Periodic boundary conditions
            int aliveNeighbors = getAliveNeighbors(x, y);
            // Apply the rules of Game of Life
            if (aliveNeighbors == 3 || (aliveNeighbors == 2 && grid[y][x])) {
                nextGrid[y][x] = 1;
            } else {
                nextGrid[y][x] = 0;
            }
        }
    }

    // Copy nextGrid to grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = nextGrid[y][x];
        }
    }
}


/*
void updateGame() {
    // Calculate next state of the grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            // Periodic boundary conditions
            int aliveNeighbors = getAliveNeighbors(x, y); 
            // Apply the rules of Game of Life
            if (aliveNeighbors == 3 || (aliveNeighbors == 2 && grid[y][x])) {
                nextGrid[y][x] = 1;
            } else {
                nextGrid[y][x] = 0;
            }
        }
    }
    // Copy nextGrid to grid
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = nextGrid[y][x];
        }
    }
}
*/


void renderGame() {
    // Set the background color to dark gray
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255); // Darker gray
    SDL_RenderClear(renderer);

    // Calculate the cell size
    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;

    // Determine if grid lines should be drawn based on cell size
    bool drawGridLines = cellWidth > 4 && cellHeight > 4; // Example threshold, adjust as needed

    // Optionally draw the grid lines
    if (drawGridLines) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for grid lines
        for (int i = 0; i <= GRID_HEIGHT; i++) {
            SDL_RenderDrawLine(renderer, 0, i * cellHeight, WINDOW_WIDTH, i * cellHeight);
        }
        for (int j = 0; j <= GRID_WIDTH; j++) {
            SDL_RenderDrawLine(renderer, j * cellWidth, 0, j * cellWidth, WINDOW_HEIGHT);
        }
    }

    // Draw the cells
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j] == 1) {
                SDL_Rect cell;
                // Adjust cell dimensions slightly if grid lines are not being drawn
                cell.x = j * cellWidth + (drawGridLines ? 1 : 0);
                cell.y = i * cellHeight + (drawGridLines ? 1 : 0);
                cell.w = cellWidth - (drawGridLines ? 1 : 0);
                cell.h = cellHeight - (drawGridLines ? 1 : 0);
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for cells
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for live cells
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_RenderPresent(renderer);
}








// Main function
int main() {
    initGame();

    int quit = 0;
    int stepCount = 0;
    bool running = false;

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    running = !running;
                }
                if (e.key.keysym.sym == SDLK_RIGHT && !running) {
                    if(stepForwardInHistory(&history, grid) == 0) {
                        // If there are no more states to step forward to create a new state
                        updateGame();
                        renderGame();
                        saveStateToHistory(&history, grid);
                        stepCount++;
                        printf("Iteration: %d\n", stepCount);
                    }
                    else {
                        renderGame();
                    }
                }
                if (e.key.keysym.sym == SDLK_LEFT && !running) {
                    stepBackwardInHistory(&history, grid);
                    renderGame();
                }
            }
        }

        if (running) {
            updateGame();
            renderGame();
            saveStateToHistory(&history, grid);
            stepCount++;
            printf("Iteration: %d\n", stepCount);
            SDL_Delay(10);
        }
    }

    closeSDL();
    return 0;
}






/*
int main() {
    initSDL();
    initializeGrid();

    int quit = 0; // Main loop flag
    int stepCount = 0; // Step counter


    SDL_Event e;

    // While application is running
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        updateGame(); // Update the game based on the rules
        renderGame(); // Render the game regardless
        printf("Iteration: %d\n", stepCount);
        stepCount++; // Increment the step counter

        SDL_Delay(10); // Delay to control the speed of the simulation
    }

    closeSDL();
    return 0;
}
*/


/*
int main() {
    Drawing myDrawing;
    initDrawing(&myDrawing, 10, 5); // Initialize a drawing of 10x5

    // Set a few cells to demonstrate setting values
    setCell(&myDrawing, 1, 1, 1);
    setCell(&myDrawing, 2, 2, 1);
    setCell(&myDrawing, 3, 3, 1);

    // Example: Print the drawing to console
    for (int y = 0; y < myDrawing.height; ++y) {
        for (int x = 0; x < myDrawing.width; ++x) {
            printf("%d ", myDrawing.grid[y][x]);
        }
        printf("\n");
    }

    return 0;
}
*/



