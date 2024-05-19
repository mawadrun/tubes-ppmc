#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROWS 255
#define MAX_COLS 255

struct Coords {
    int row, col;
};

bool isSafe(int totalRows, int totalCols, int row, int col) {
    return (row >= 0) && (row < totalRows) &&
           (col >= 0) && (col < totalCols);
}

void DFSUtil(int totalRows, int totalCols, int row, int col, int endY, int endX, bool** visited, struct Coords path[], int pathIndex, struct Coords* shortestPath, struct Coords* longestPath, int* shortestPathLength, int* longestPathLength, char matriks[MAX_ROWS][MAX_COLS]) {
    visited[row][col] = true;
    path[pathIndex].row = row;
    path[pathIndex].col = col;
    pathIndex++;

    if (row == endY && col == endX) {
        if (*shortestPathLength == -1 || pathIndex < *shortestPathLength) {
            for (int i = 0; i < pathIndex; i++) {
                shortestPath[i] = path[i];
            }
            *shortestPathLength = pathIndex;
        }

        if (*longestPathLength == -1 || pathIndex > *longestPathLength) {
            for (int i = 0; i < pathIndex; i++) {
                longestPath[i] = path[i];
            }
            *longestPathLength = pathIndex;
        }
    } else {
        int rowMove[] = {-1, 0, 0, 1};
        int colMove[] = {0, -1, 1, 0};
        for (int k = 0; k < 4; ++k) {
            int nextRow = row + rowMove[k];
            int nextCol = col + colMove[k];
            if (isSafe(totalRows, totalCols, nextRow, nextCol) && !visited[nextRow][nextCol] && matriks[nextRow][nextCol] != '#') {
                DFSUtil(totalRows, totalCols, nextRow, nextCol, endY, endX, visited, path, pathIndex, shortestPath, longestPath, shortestPathLength, longestPathLength, matriks);
            }
        }
    }
    pathIndex--;
    visited[row][col] = false;
}

void markPath(int totalRows, int totalCols, struct Coords* path, char matriks[MAX_ROWS][MAX_COLS], int length) {
    for (int i = 0; i < length; i++) {
        if (matriks[path[i].row][path[i].col] != 'S' && matriks[path[i].row][path[i].col] != 'E') {
            matriks[path[i].row][path[i].col] = 'V';
        }
    }
}

void printMazeDFS(int totalRows, int totalCols, char matriks[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < totalRows; ++i) {
        for (int j = 0; j < totalCols; ++j) {
            printf("%c ", matriks[i][j]);
        }
        printf("\n");
    }
}

void DFS(int totalRows, int totalCols, int endY, int endX, int startX, int startY, char matriks[MAX_ROWS][MAX_COLS]) {
    bool** visited = (bool**)malloc(totalRows * sizeof(bool*));
    for (int i = 0; i < totalRows; ++i) {
        visited[i] = (bool*)malloc(totalCols * sizeof(bool));
        for (int j = 0; j < totalCols; ++j) {
            visited[i][j] = false;
        }
    }

    struct Coords path[MAX_ROWS * MAX_COLS];
    int pathIndex = 0;

    struct Coords shortestPath[MAX_ROWS * MAX_COLS];
    int shortestPathLength = -1;

    struct Coords longestPath[MAX_ROWS * MAX_COLS];
    int longestPathLength = -1;

    DFSUtil(totalRows, totalCols, startY, startX, endY, endX, visited, path, pathIndex, shortestPath, longestPath, &shortestPathLength, &longestPathLength, matriks);

    char shortestPathMaze[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < totalRows; ++i) {
        for (int j = 0; j < totalCols; ++j) {
            shortestPathMaze[i][j] = matriks[i][j];
        }
    }
    markPath(totalRows, totalCols, shortestPath, shortestPathMaze, shortestPathLength);

    printf("Shortest Path:\n");
    printMazeDFS(totalRows, totalCols, shortestPathMaze);
    printf("\n");

    // Buat salinan matriks untuk menandai jalur terpanjang
    char longestPathMaze[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < totalRows; ++i) {
        for (int j = 0; j < totalCols; ++j) {
            longestPathMaze[i][j] = matriks[i][j];
        }
    }
    markPath(totalRows, totalCols, longestPath, longestPathMaze, longestPathLength);

    // Cetak matriks dengan jalur terpanjang
    printf("Longest Path:\n");
    printMazeDFS(totalRows, totalCols, longestPathMaze);
    printf("\n");

    // Bebaskan memori
    for (int i = 0; i < totalRows; ++i) {
        free(visited[i]);
    }
    free(visited);
}

int main() {
    int maze1_rows = 11, maze1_cols = 12;
    int maze2_rows = 15, maze2_cols = 15;
    
    char maze1[MAX_ROWS][MAX_COLS] = {
        {'S', '.', '.', '.', '.', '#', '.', '.', '#', '.', '.', '.'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '.', '.', '.', '#'},
        {'.', '.', '.', '.', '#', '.', '#', '.', '#', '.', '.', '.'},
        {'.', '#', '.', '.', '.', '.', '.', '#', '.', '#', '.', '#'},
        {'.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#', '#'},
        {'.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '#', '.'},
        {'.', '#', '.', '.', '.', '#', '.', '#', '.', '.', '.', '#'},
        {'.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '#', '.', '#', '.', '#', '.', '#', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '#', '.', '#', '.', '.', 'E', '.', '#'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'}
    };

    int maze1_startY = 0, maze1_startX = 0;
    int maze1_endY = 9, maze1_endX = 9;

    char maze2[MAX_ROWS][MAX_COLS] = {
        {'#', 'E', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.'},
        {'#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '.'},
        {'#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '.'},
        {'#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '.', '.'},
        {'.', '.', '#', '#', '#', '.', '#', '#', '.', '.', '.', '.', '#', '#', '.'},
        {'#', '.', '#', '.', '.', '.', '#', '#', '.', '#', '#', '.', '#', '#', '.'},
        {'.', '.', '.', '.', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.'},
        {'#', '.', '#', '.', '.', '.', '#', '.', '#', '#', '.', '.', '.', '#', '.'},
        {'.', '.', '#', '.', '.', '#', '.', '.', '#', '#', '#', '#', '.', '#', '.'},
        {'#', '.', '#', '#', '#', '.', '.', '#', '#', '.', '.', '#', '.', '#', '.'},
        {'#', '.', '#', 'S', '.', '.', '#', '.', '#', '#', '.', '.', '.', '#', '.'},
        {'.', '.', '.', '#', '.', '.', '#', '#', '.', '#', '#', '.', '#', '#', '.'},
        {'.', '.', '.', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#'}
    };

    int maze2_startY = 13, maze2_startX = 3;
    int maze2_endY = 0, maze2_endX = 1;

    printf("Maze 1:\n");
    DFS(maze1_rows, maze1_cols, maze1_endY, maze1_endX, maze1_startX, maze1_startY, maze1);

    printf("Maze 2:\n");
    DFS(maze2_rows, maze2_cols, maze2_endY, maze2_endX, maze2_startX, maze2_startY, maze2);

    return 0;
}

