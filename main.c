#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "drawing.h"
#include "SimulationHistory.h"

// Define the window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


// Define the size of the grid
const int GRID_WIDTH = 200;
const int GRID_HEIGHT = 150;
//const int GRID_WIDTH = 160;
//const int GRID_HEIGHT = 120;

int grid[GRID_HEIGHT][GRID_WIDTH];
int nextGrid[GRID_HEIGHT][GRID_WIDTH];

// Global SimulationHistory Instance
SimulationHistory history;


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

    //Drawing* gun = loadDrawingFromFile("drawings/glider_gun.txt");
    // Use the drawing...
    //placeDrawing(gun, (Point){0, 0}, grid); // Example usage
    // When done with the drawing
    //free(gun);


    //Drawing* eater = loadDrawingFromFile("drawings/glider_eater.txt");
    // Use the drawing...
    //placeDrawing(eater, (Point){75, 61}, grid); // Example usage
    // When done with the drawing
    //free(eater);

    Drawing* gun_eater = loadDrawingFromFile("drawings/big_gun_eater.txt");
    // Use the drawing...
    placeDrawing(gun_eater, (Point){0, 0}, grid); // Example usage
    // Use the drawing again
    placeDrawing(gun_eater, (Point){80, 0}, grid); // Example usage
    // Use the drawing again
    placeDrawing(gun_eater, (Point){160, 0}, grid); // Example usage
    // Use the drawing again
    placeDrawing(gun_eater, (Point){0, 80}, grid); // Example usage
    // Use the drawing again
    placeDrawing(gun_eater, (Point){80, 80}, grid); // Example usage
    // Use the drawing again
    placeDrawing(gun_eater, (Point){160, 80}, grid); // Example usage
    
    // When done with the drawing
    free(gun_eater);

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


/*
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
*/


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
void renderGame() {
    // Set the background color to dark gray
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255); // Darker gray
    SDL_RenderClear(renderer);

    // Calculate the cell size
    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;

    // Always draw the grid lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for grid lines
    for (int i = 0; i <= GRID_HEIGHT; i++) {
        SDL_RenderDrawLine(renderer, 0, i * cellHeight, WINDOW_WIDTH, i * cellHeight);
    }
    for (int j = 0; j <= GRID_WIDTH; j++) {
        SDL_RenderDrawLine(renderer, j * cellWidth, 0, j * cellWidth, WINDOW_HEIGHT);
    }

    // Optionally draw the cells (if any are alive)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for live cells
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j] == 1) {
                SDL_Rect cell;
                cell.x = j * cellWidth;
                cell.y = i * cellHeight;
                cell.w = cellWidth;
                cell.h = cellHeight;
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
*/

void renderGame() {
    // Set the background color to dark gray
    SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255); // Darker gray
    SDL_RenderClear(renderer);

    // Calculate the cell size
    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;

    // Determine the opacity of the grid lines based on the grid size
    // For example, start fading out lines for grid sizes larger than 100x100
    int maxGridSizeForLines = 100;
    int alpha = 255; // Default fully opaque
    if (GRID_WIDTH > maxGridSizeForLines || GRID_HEIGHT > maxGridSizeForLines) {
        // Calculate a fading effect based on how much larger the grid is
        float fadeFactor = (float)GRID_WIDTH / maxGridSizeForLines; // Example fading calculation
        alpha = (int)(255 / fadeFactor);
        if (alpha < 0) alpha = 0; // Ensure alpha doesn't go negative
        if (alpha > 255) alpha = 255; // Ensure alpha doesn't exceed 255
    }

    // Set the color for grid lines with calculated opacity
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha); // White color for grid lines with dynamic opacity

    // Optionally draw the grid lines
    if (cellWidth > 4 && cellHeight > 4) { // Adjust as needed for visibility
        for (int i = 0; i <= GRID_HEIGHT; i++) {
            SDL_RenderDrawLine(renderer, 0, i * cellHeight, WINDOW_WIDTH, i * cellHeight);
        }
        for (int j = 0; j <= GRID_WIDTH; j++) {
            SDL_RenderDrawLine(renderer, j * cellWidth, 0, j * cellWidth, WINDOW_HEIGHT);
        }
    }

    // Draw the cells (if any are alive)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for live cells
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j] == 1) {
                SDL_Rect cell;
                cell.x = j * cellWidth;
                cell.y = i * cellHeight;
                cell.w = cellWidth;
                cell.h = cellHeight;
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_RenderPresent(renderer);
}









void saveCurrentDrawingToFile(const int (*grid)[GRID_WIDTH], int width, int height, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file %s for writing.\n", filename);
        return;
    }

    // Write the dimensions
    fprintf(file, "%d %d\n", width, height);

    // Write the grid state
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(file, "%d ", grid[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Drawing saved to %s\n", filename);
}





void toggleCellState(int mouseX, int mouseY, int (*grid)[GRID_WIDTH]) {
    int cellWidth = WINDOW_WIDTH / GRID_WIDTH;
    int cellHeight = WINDOW_HEIGHT / GRID_HEIGHT;

    int gridX = mouseX / cellWidth;
    int gridY = mouseY / cellHeight;

    // Toggle cell state, ensuring we're within grid bounds
    if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) {
        grid[gridY][gridX] = !grid[gridY][gridX];
    }
}



void drawMode(int (*grid)[GRID_WIDTH]) {
    bool drawing = true;
    bool mouseDown = false; // Track if the mouse button is pressed down

    SDL_Event e;

    while (drawing) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                drawing = false;
                break; // Exit drawing mode if window is closed
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouseDown = true; // Set mouseDown to true when mouse button is pressed

                // Calculate grid coordinates
                int gridX = e.button.x / (WINDOW_WIDTH / GRID_WIDTH);
                int gridY = e.button.y / (WINDOW_HEIGHT / GRID_HEIGHT);

                printf("Mouse clicked at grid coordinates: (%d, %d)\n", gridX, gridY);

                toggleCellState(e.button.x, e.button.y, grid);
                renderGame();
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                mouseDown = false; // Reset mouseDown when mouse button is released
            }
            else if (e.type == SDL_MOUSEMOTION && mouseDown) {
                // Handle dragging to draw live cells
                toggleCellState(e.motion.x, e.motion.y, grid);
                renderGame();
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
                // Save the current drawing to a file
                //saveCurrentDrawingToFile(grid, GRID_WIDTH, GRID_HEIGHT, "current_drawing.txt");
                // Press Enter to exit drawing mode
                drawing = false;
            }
        }
    }
}


/*
int main() {
    // Initialize the game (SDL, grid, history, etc.)
    initGame();

    // Main loop control flags
    int quit = 0;      // Flag to indicate the program should exit
    int stepCount = 0; // Counter for the number of simulation steps executed
    bool running = false; // Flag to control the running state of the simulation

    SDL_Event e; // SDL event structure to handle events

    // Render the initial state of the grid
    renderGame();

    // Enter interactive drawing mode before starting the main loop
    // Allows the user to manually create the initial state
    drawMode(grid);

    // Main event loop
    while (!quit) {
        // Process SDL events
        while (SDL_PollEvent(&e) != 0) {
            // Handle window close event
            if (e.type == SDL_QUIT) {
                quit = 1; // Set the flag to exit the main loop
            } 
            // Handle mouse click events when not running
            else if (e.type == SDL_MOUSEBUTTONDOWN && !running) {
                // Calculate grid coordinates
                int gridX = e.button.x / (WINDOW_WIDTH / GRID_WIDTH);
                int gridY = e.button.y / (WINDOW_HEIGHT / GRID_HEIGHT);

                printf("Mouse clicked at grid coordinates: (%d, %d) in main loop\n", gridX, gridY);
            }
            // Handle key press events
            else if (e.type == SDL_KEYDOWN) {
                // Toggle simulation running state with SPACE key
                if (e.key.keysym.sym == SDLK_SPACE) {
                    running = !running;
                }
                // Step forward in simulation with RIGHT arrow key, when not running
                else if (e.key.keysym.sym == SDLK_RIGHT && !running) {
                    if(stepForwardInHistory(&history, grid) == 0) {
                        // If no more steps forward, update and render a new state
                        updateGame();
                        saveStateToHistory(&history, grid);
                        stepCount++;
                    }
                    renderGame(); // Render the current state regardless
                    printf("Iteration: %d\n", stepCount);
                }
                // Step backward in simulation with LEFT arrow key, when not running
                else if (e.key.keysym.sym == SDLK_LEFT && !running) {
                    stepBackwardInHistory(&history, grid);
                    renderGame();
                }
            }
        }

        // If the simulation is running, update and render the next state
        if (running) {
            updateGame();
            saveStateToHistory(&history, grid);
            stepCount++;
            renderGame();
            printf("Iteration: %d\n", stepCount);
            SDL_Delay(100); // Delay to control the simulation speed
        }
    }

    // Clean up resources before exiting
    closeSDL();
    return 0;
}
*/


// Main function
int main() {
    // Initialize the game (SDL, grid, history, etc.)
    initGame();

    // Main loop control flags
    int quit = 0;      // Flag to indicate the program should exit
    int stepCount = 0; // Counter for the number of simulation steps executed
    bool running = false; // Flag to control the running state of the simulation
    int simulationDelay = 100; // Delay in milliseconds

    SDL_Event e; // SDL event structure to handle events

    // Render the initial state of the grid
    renderGame();

    // Enter interactive drawing mode before starting the main loop
    drawMode(grid);

    // Main event loop
    while (!quit) {
        // Process SDL events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } 
            else if (e.type == SDL_MOUSEBUTTONDOWN && !running) {
                int gridX = e.button.x / (WINDOW_WIDTH / GRID_WIDTH);
                int gridY = e.button.y / (WINDOW_HEIGHT / GRID_HEIGHT);
                printf("Mouse clicked at grid coordinates: (%d, %d)\n", gridX, gridY);
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:
                        running = !running;
                        break;
                    case SDLK_RIGHT:
                        if (!running) {
                            // Logic for stepping forward in simulation
                        }
                        break;
                    case SDLK_LEFT:
                        if (!running) {
                            // Logic for stepping backward in simulation
                        }
                        break;
                    case SDLK_UP:
                        // Decrease delay to speed up the simulation, ensuring it doesn't drop below a minimum threshold
                        simulationDelay = simulationDelay > 10 ? simulationDelay - 10 : 1; // If simulationDelay > 10, decrease by 10, else set to 1
                        break;
                    case SDLK_DOWN:
                        // Increase delay to slow down the simulation, with a maximum limit if necessary
                        simulationDelay += 10;
                        break;
                }
            }
        }

        if (running) {
            updateGame();
            saveStateToHistory(&history, grid);
            stepCount++;
            renderGame();
            printf("Iteration: %d\n", stepCount);
            SDL_Delay(simulationDelay); // Use the dynamic simulation delay
        }
    }

    closeSDL();
    return 0;
}

