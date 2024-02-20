#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Define the window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


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


void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


//#define GRID_WIDTH 800
//#define GRID_HEIGHT 600

#define GRID_WIDTH 80
#define GRID_HEIGHT 60

int grid[GRID_HEIGHT][GRID_WIDTH];
int nextGrid[GRID_HEIGHT][GRID_WIDTH];

// Randomly populate the grid with dead and alive cells
/*
void initializeGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            // Randomly set a grid state to 0 or 1
            grid[i][j] = rand() % 2; // Randomly initialize the grid
        }
    }
}
*/

void initializeGrid() {
    // Ensure the rest of the grid is cleared
    memset(grid, 0, sizeof(grid));

    // Set up a glider in the top-left corner
    //grid[1][2] = 1;
    //grid[2][3] = 1;
    //grid[3][1] = 1;
    //grid[3][2] = 1;
    //grid[3][3] = 1;

    for (int i = 0; i < GRID_HEIGHT - 2; i++) { // Ensure room for glider height
        for (int j = 0; j < GRID_WIDTH - 2; j++) { // Ensure room for glider width
            // Randomly set up a glider in the grid with a 1/10 chance
            if (rand() % 100 == 0) {
                // Clear the area for the glider to prevent overlapping patterns
                for (int gi = 0; gi < 3; gi++) {
                    for (int gj = 0; gj < 3; gj++) {
                        grid[i + gi][j + gj] = 0; // Clear the cell
                    }
                }
                // Place a glider
                grid[i][j + 1] = 1; // Second cell in the first row
                grid[i + 1][j + 2] = 1; // Third cell in the second row
                grid[i + 2][j] = 1; // First cell in the third row
                grid[i + 2][j + 1] = 1; // Second cell in the third row
                grid[i + 2][j + 2] = 1; // Third cell in the third row
            }
        }
    }

}


// Periodic boundary conditions
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


void renderGame() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for cells
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j] == 1) {
                SDL_Rect cell;
                cell.x = j * (WINDOW_WIDTH / GRID_WIDTH);
                cell.y = i * (WINDOW_HEIGHT / GRID_HEIGHT);
                cell.w = WINDOW_WIDTH / GRID_WIDTH;
                cell.h = WINDOW_HEIGHT / GRID_HEIGHT;

                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    SDL_RenderPresent(renderer);
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
            if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                aliveNeighbors += grid[ny][nx];
            }
        }
    }
    return aliveNeighbors;
}
*/

// Periodic boundary conditions
// The grid wraps around, creating a torus shape. This means the right edge connects to the left, and the top edge connects to the bottom, creating a continuous space without borders.
/*
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






int main() {
    //(void)argc; // Suppress unused parameter warning
    //(void)args; // Suppress unused parameter warning

    initSDL();
    initializeGrid();

    // Main loop flag
    int quit = 0;

    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        updateGame();
        renderGame();

        SDL_Delay(100); // Delay to slow down the simulation
    }

    closeSDL();
    return 0;
}
