#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "definisiFungsi.h"

#define MAX_ROWS 255
#define MAX_COLS 255

typedef struct
{
    int row, col;
} Cell;

// Deklarasi Fungsi
void findShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end);
void backtrackShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *minLength, Cell path[], Cell shortestPath[]);
void findLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end);
void backtrackLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *maxLength, Cell path[], Cell longestPath[]);
void printMaze_back(char maze[MAX_ROWS][MAX_COLS], int rows, int cols);

int main_back(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int start_row, int start_col, int end_row, int end_col)
{
    // char maze[MAX_ROWS][MAX_COLS];
    Cell start, end;
    start.col = start_col;
    start.row = start_row;
    end.col = end_col;
    end.row = end_row;

    printMatrix(maze, rows, cols);

    // Alokasi Memori
    Cell *path = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));
    Cell *shortestPath = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));
    Cell *longestPath = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));

    // Mencetak Shortest Path
    printf("\nShortest Path:\n");
    findShortestPath(maze, rows, cols, start, end);
    maze[start.row][start.col] = '1';
    maze[end.row][end.col] = '1';
    printMaze_back(maze, rows, cols);

    // Mencetak Longest Path
    printf("\nLongest Path:\n");
    int maxLength = 0;
    findLongestPath(maze, rows, cols, start, end);
    for (int i = 0; i < maxLength; i++)
    {
        maze[longestPath[i].row][longestPath[i].col] = '1';
    }
    maze[start.row][start.col] = '1';
    maze[end.row][end.col] = '1';
    printMaze_back(maze, rows, cols);

    // Free Memori
    free(path);
    free(shortestPath);
    free(longestPath);

    return 0;
}

// Fungsi untuk Mengecek Validasi Cell pada Matriks Labirin
bool isValid_back(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int row, int col)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols && maze[row][col] != '#');
}

// Fungsi untuk Mencari Shortest Path
void findShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end)
{
    // Array untuk Menyimpan Path
    Cell *path = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));
    Cell *shortestPath = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));
    int minLength = rows * cols + 1;

    // Menandai Posisi Start sudah dilalui
    maze[start.row][start.col] = '#';

    // Backtracking
    backtrackShortestPath(maze, rows, cols, start, end, 0, &minLength, path, shortestPath);

    // Menandai Shortest Path
    for (int i = 0; i < minLength; i++)
    {
        maze[shortestPath[i].row][shortestPath[i].col] = '1';
    }

    // Free Memori
    free(path);
    free(shortestPath);
}

// Fungsi untuk Backtracking Shortest Path
void backtrackShortestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *minLength, Cell path[], Cell shortestPath[])
{
    // Base case: Mencapai Cell Terakhir
    if (current.row == end.row && current.col == end.col)
    {
        if (currLength < *minLength)
        {
            *minLength = currLength;
            for (int i = 0; i < currLength; i++)
            {
                shortestPath[i] = path[i];
            }
        }
        return;
    }

    // Melakukan Pengecekan ke Segala Arah
    if (isValid_back(maze, rows, cols, current.row - 1, current.col))
    { // Arah Atas
        Cell next = {current.row - 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid_back(maze, rows, cols, current.row + 1, current.col))
    { // Arah Bawah
        Cell next = {current.row + 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid_back(maze, rows, cols, current.row, current.col - 1))
    { // Arah Kiri
        Cell next = {current.row, current.col - 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid_back(maze, rows, cols, current.row, current.col + 1))
    { // Arah Kanan
        Cell next = {current.row, current.col + 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackShortestPath(maze, rows, cols, next, end, currLength + 1, minLength, path, shortestPath);
        maze[next.row][next.col] = '.';
    }
}

// Fungsi untuk Mencari Longest Path
void findLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell start, Cell end)
{
    // Array untuk Menyimpan Path
    Cell *path = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));
    Cell *longestPath = malloc(MAX_ROWS * MAX_COLS * sizeof(Cell));
    int maxLength = 0;

    // Menandai Posisi Start sudah dilalui
    maze[start.row][start.col] = '#';

    // Backtracking
    backtrackLongestPath(maze, rows, cols, start, end, 0, &maxLength, path, longestPath);

    // Menandai Longest Path
    for (int i = 0; i < maxLength; i++)
    {
        maze[longestPath[i].row][longestPath[i].col] = '1';
    }

    // Free Memori
    free(path);
    free(longestPath);
}

// Fungsi untuk Backtracking Longest Path
void backtrackLongestPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Cell current, Cell end, int currLength, int *maxLength, Cell path[], Cell longestPath[])
{
    // Base case: Mencapai Cell Terakhir
    if (current.row == end.row && current.col == end.col)
    {
        if (currLength > *maxLength)
        {
            *maxLength = currLength;
            for (int i = 0; i < currLength; i++)
            {
                longestPath[i] = path[i];
            }
        }
        return;
    }

    // Melakukan Pengecekan ke Segala Arah
    if (isValid_back(maze, rows, cols, current.row - 1, current.col))
    { // Arah Atas
        Cell next = {current.row - 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid_back(maze, rows, cols, current.row + 1, current.col))
    { // Arah Bawah
        Cell next = {current.row + 1, current.col};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid_back(maze, rows, cols, current.row, current.col - 1))
    { // Arah Kiri
        Cell next = {current.row, current.col - 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
    if (isValid_back(maze, rows, cols, current.row, current.col + 1))
    { // Arah Kanan
        Cell next = {current.row, current.col + 1};
        maze[next.row][next.col] = '#';
        path[currLength] = next;
        backtrackLongestPath(maze, rows, cols, next, end, currLength + 1, maxLength, path, longestPath);
        maze[next.row][next.col] = '.';
    }
}

// Fungsi untuk Mencetak Path yang dilalui
void printMaze_back(char maze[MAX_ROWS][MAX_COLS], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}
