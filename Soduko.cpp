#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring> // For memcpy
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

    return true;
}

// Function to solve the Sudoku using backtracking
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    bool isEmpty = false;

    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    if (!isEmpty) return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

// Function to remove cells from a solved Sudoku grid based on difficulty level
void setDifficulty(int grid[GRID_SIZE][GRID_SIZE], int removeCount) {
    srand(time(0)); // Seed random number generator
    for (int i = 0; i < removeCount; i++) {
        int row = rand() % GRID_SIZE;
        int col = rand() % GRID_SIZE;

        // Ensure that the cell being removed is not already empty
        while (grid[row][col] == 0) {
            row = rand() % GRID_SIZE;
            col = rand() % GRID_SIZE;
        }

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
    int choice;
    cout << "Select difficulty level:\n";
    cout << "1. Easy\n2. Medium\n3. Hard\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    // Determine the number of cells to remove based on the difficulty level
    int removeCount;
    if (choice == 1) {
        removeCount = 20; // Easy: Remove 20 cells
    } else if (choice == 2) {
        removeCount = 40; // Medium: Remove 40 cells
    } else if (choice == 3) {
        removeCount = 55; // Hard: Remove 55 cells
    } else {
        cout << "Invalid choice! Defaulting to Easy level." << endl;
        removeCount = 20; // Default to Easy level
    }

    // Prepare the grid based on the selected difficulty
    int grid[GRID_SIZE][GRID_SIZE];
    memcpy(grid, solvedGrid, sizeof(grid)); // Copy solved grid to working grid
    setDifficulty(grid, removeCount);

    cout << "\nSudoku Puzzle (" << (choice == 1 ? "Easy" : choice == 2 ? "Medium" : "Hard") << " level):" << endl;
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