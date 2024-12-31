#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Define the size of the Sudoku grid
const int GRID_SIZE = 9;

// Function to print the Sudoku grid
void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing a number in a cell is valid
bool isSafe(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    // Check the row
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check the column
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    // If no conflicts, the number is safe to place
    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    bool isEmpty = false;

    // Find the next empty cell
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    // If there are no empty cells, the Sudoku is solved
    if (!isEmpty) return true;

    // Try placing digits 1-9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Place the number in the cell
            grid[row][col] = num;

            // Recursively attempt to solve the rest of the grid
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing the number doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // If no number can be placed, return false
    return false;
}

// Function to remove cells from a fully solved Sudoku to set difficulty levels
void setDifficulty(int grid[GRID_SIZE][GRID_SIZE], string difficulty) {
    int removeCount;
    if (difficulty == "easy") {
        removeCount = 20; // Fewer cells removed
    } else if (difficulty == "medium") {
        removeCount = 40; // Moderate number of cells removed
    } else if (difficulty == "hard") {
        removeCount = 55; // More cells removed
    } else {
        cout << "Invalid difficulty level. Defaulting to 'medium'." << endl;
        removeCount = 40;
    }

    srand(time(0)); // Seed random number generator
    for (int i = 0; i < removeCount; i++) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;
        grid[row][col] = 0; // Set cell to empty (0)
    }
}

// Main function
int main() {
    // Define a fully solved Sudoku puzzle
    int solvedGrid[GRID_SIZE][GRID_SIZE] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    // Ask user for difficulty level
    string difficulty;
    cout << "Enter difficulty level (easy, medium, hard): ";
    cin >> difficulty;

    // Prepare the grid based on difficulty level
    int grid[GRID_SIZE][GRID_SIZE];
    memcpy(grid, solvedGrid, sizeof(grid)); // Copy solved grid to working grid
    setDifficulty(grid, difficulty);

    cout << "Sudoku Puzzle (" << difficulty << " level):" << endl;
    printGrid(grid);

    // Solve the puzzle and display the solution
    cout << "\nSolving Sudoku..." << endl;
    if (solveSudoku(grid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists for the given Sudoku puzzle." << endl;
    }

    return 0;
}
