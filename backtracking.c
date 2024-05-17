#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Structure to represent a cell in the maze
typedef struct {
    int row, col;
} Cell;

// Function prototypes
void findShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end);
void backtrackShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *minLength, Cell path[], Cell shortestPath[]);
void findLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end);
void backtrackLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *maxLength, Cell path[], Cell longestPath[]);
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols);

int main() {
    char maze[MAX_ROWS][MAX_COLS];
    Cell start, end;
    int rows = 0, cols = 0; // Initialize rows and cols

    char filename[100]; 
    printf("\nEnter file name: "); 
    scanf("%s", filename); 

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file\n");
        return 1;
    }

    // Read maze
    int row = 0;
    while (fscanf(file, "%s", maze[row]) != EOF) {
        // Update cols if needed
        int current_cols = strlen(maze[row]);
        if (current_cols > cols)
            cols = current_cols;

        // Find start and end positions
        for (int j = 0; j < current_cols; j++) {
            if (maze[row][j] == 'S') {
                start.row = row;
                start.col = j;
            } else if (maze[row][j] == 'E') {
                end.row = row;
                end.col = j;
            }
        }
        row++;

        // Update rows if needed
        rows++;
    }

    fclose(file);

    // Find and print shortest path
    printf("\nShortest Path:\n");
    findShortestPath(maze, rows, cols, start, end);
    maze[start.row][start.col] = '1'; // Change the start position to 1
    maze[end.row][end.col] = '1'; // Change the end position to 1
    printMaze(maze, rows, cols);

    // Find and print longest path
    printf("\nLongest Path:\n");
    Cell path[MAX_ROWS * MAX_COLS], longestPath[MAX_ROWS * MAX_COLS];
    int maxLength = 0;
    findLongestPath(maze, rows, cols, start, end);
    for (int i = 0; i < maxLength; i++) {
        maze[longestPath[i].row][longestPath[i].col] = '1';
    }
    maze[start.row][start.col] = '1'; // Change the start position to 1
    maze[end.row][end.col] = '1'; // Change the end position to 1
    printMaze(maze, rows, cols);

    return 0;
}

// Function to check if a cell is valid (within maze bounds and not a wall)
bool isValid(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int row, int col) {
    return (row >= 0 && row < rows && col >= 0 && col < cols && maze[row][col] != '#');
}

// Function to find the shortest path using backtracking
void findShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end) {
    // Array to store the path
    Cell path[MAX_ROWS * MAX_COLS];
    Cell shortestPath[MAX_ROWS * MAX_COLS];
    int minLength = rows * cols + 1;

    // Mark start cell as visited
    maze[start.row][start.col] = '#';

    // Start backtracking
    backtrackShortestPath(maze, rows, cols, start, end, 0, &minLength, path, shortestPath);

    // Mark the shortest path
    for (int i = 0; i < minLength; i++) {
        maze[shortestPath[i].row][shortestPath[i].col] = '1';
    }
}

// Function for backtracking to find shortest path
void backtrackShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *minLength, Cell path[], Cell shortestPath[]) {
    // Base case: reached the end
    if (current.row == end.row && current.col == end.col) {
        if (currLength < *minLength) {
            *minLength = currLength;
            for (int i = 0; i < currLength; i++) {
                shortestPath[i] = path[i];
            }
        }
        return;
    }

    // Try moving in all four directions
    if (isValid(maze, rows, cols, current.row - 1, current.col)) { // Up
        Cell next = {current.row - 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid(maze, rows, cols, current.row + 1, current.col)) { // Down
        Cell next = {current.row + 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid(maze, rows, cols, current.row, current.col - 1)) { // Left
        Cell next = {current.row, current.col - 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid(maze, rows, cols, current.row, current.col + 1)) { // Right
        Cell next = {current.row, current.col + 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
}

// Function to find the longest path using backtracking
void findLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end) {
    // Array to store the path
    Cell path[MAX_ROWS * MAX_COLS];
    Cell longestPath[MAX_ROWS * MAX_COLS];
    int maxLength = 0;

    // Mark start cell as visited
    maze[start.row][start.col] = '#';

    // Start backtracking
    backtrackLongestPath(maze, rows, cols, start, end, 0, &maxLength, path, longestPath);

    // Mark the longest path
    for (int i = 0; i < maxLength; i++) {
        maze[longestPath[i].row][longestPath[i].col] = '1';
    }
}

// Function for backtracking to find longest path
void backtrackLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *maxLength, Cell path[], Cell longestPath[]) {
    // Base case: reached the end
    if (current.row == end.row && current.col == end.col) {
        if (currLength > *maxLength) {
            *maxLength = currLength;
            for (int i = 0; i < currLength; i++) {
                longestPath[i] = path[i];
            }
        }
        return;
    }

    // Try moving in all four directions
    if (isValid(maze, rows, cols, current.row - 1, current.col)) { // Up
        Cell next = {current.row - 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid(maze, rows, cols, current.row + 1, current.col)) { // Down
        Cell next = {current.row + 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid(maze, rows, cols, current.row, current.col - 1)) { // Left
        Cell next = {current.row, current.col - 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid(maze, rows, cols, current.row, current.col + 1)) { // Right
        Cell next = {current.row, current.col + 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
}

// Function to print the maze
void printMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}