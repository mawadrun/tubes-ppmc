/** EL2208 Praktikum Pemecahan Masalah dengan C 2023/2024
 *   Modul               : Tubes
 *   Hari dan Tanggal    : Senin , 20 Mei 2024
 *   Nama (NIM)          : Joanna Alicia T (13222043)
 *   Nama File           : dfs.c
 *   Deskripsi           : Program c dengan menggunakan algoritma Depth First Search untuk mencari longest path dan shortest path
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ROWS 255
#define MAX_COLS 255

//fungsi untuk mencatat koordinat kolom dan baris
struct Coords_DFS
{
    int row, col;
};

//Fungs untuk mengecek apakah row dan col input berada dalam batras baris dan kolom maksimal
bool isSafe(int totalRows, int totalCols, int row, int col)
{
    return (row >= 0) && (row < totalRows) &&
           (col >= 0) && (col < totalCols);
}

//Fungsi untuk melakukan algoritma DFS
void DFSUtil(int totalRows, int totalCols, int row, int col, int endY, int endX, bool **visited, struct Coords_DFS path[], int pathIndex, struct Coords_DFS *shortestPath, struct Coords_DFS *longestPath, int *shortestPathLength, int *longestPathLength, char matriks[MAX_ROWS][MAX_COLS])
{    
    //Menandai suatu titik kolom dan baris sebagai tempat yag sudah ditandai
    visited[row][col] = true;
    //Menambahkan jalur pada variable path
    path[pathIndex].row = row;
    path[pathIndex].col = col;
    pathIndex++;

    //Bila pencarian jalur sudah mencapai tahap akhir
    if (row == endY && col == endX)
    {
        //Bila didapat jalur yang terbaru lebih pendek dari yang tercatat , atau sebelumnya belum pernah mencatat sama sekali (-1)
        if (*shortestPathLength == -1 || pathIndex < *shortestPathLength)
        {
            //Mengcopy path yang didapat ke variable bernama shortestPath
            for (int i = 0; i < pathIndex; i++)
            {
                shortestPath[i] = path[i];
            }
            //Mengupdate jumlah langkah terpende
            *shortestPathLength = pathIndex;
        }

        //Bila didapat jalur terbaru lebih panjang , atau sebelumnya belum pernah dicatat sama sekali(-1)
        if (*longestPathLength == -1 || pathIndex > *longestPathLength)
        {    
            //Mengcopy jalur terpanjang ke longestPath
            for (int i = 0; i < pathIndex; i++)
            {
                longestPath[i] = path[i];
            }
            //Mengupdate nilai langkah terpanjang
            *longestPathLength = pathIndex;
        }
    }
    //Bila belum mencapai akhir
    else    
    {    
        //Deklarasi matriks perpindahan yaitu atas , kiri , kanan, bawah
        int rowMove[] = {-1, 0, 0, 1};
        int colMove[] = {0, -1, 1, 0};
        //Mengiterasi sepanjang 4 kali yaitu atas kiri kanan bawah
        for (int k = 0; k < 4; ++k)
        {
            int nextRow = row + rowMove[k];
            int nextCol = col + colMove[k];
            //Bila langkah selanjutnya valid maka lakukan iterasi rekurisf
            if (isSafe(totalRows, totalCols, nextRow, nextCol) && !visited[nextRow][nextCol] && matriks[nextRow][nextCol] != '#')
            {    
                //rekursif untuk mengupdate path
                DFSUtil(totalRows, totalCols, nextRow, nextCol, endY, endX, visited, path, pathIndex, shortestPath, longestPath, shortestPathLength, longestPathLength, matriks);
            }
        }
    }
    //Bila gagal menemukan jalur maka jalur yang tercatat pada paling atas dihapus , dan visitedi false
    pathIndex--;
    visited[row][col] = false;
}

//Fungsi untuk meng mark jalur yang sudah diambil dengan V
void markPath(int totalRows, int totalCols, struct Coords_DFS *path, char matriks[MAX_ROWS][MAX_COLS], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (matriks[path[i].row][path[i].col] != 'S' && matriks[path[i].row][path[i].col] != 'E')
        {
            matriks[path[i].row][path[i].col] = 'V';
        }
    }
}
//Mengprint maze 
void printMazeDFS(int totalRows, int totalCols, char matriks[MAX_ROWS][MAX_COLS])
{
    for (int i = 0; i < totalRows; ++i)
    {
        for (int j = 0; j < totalCols; ++j)
        {
            printf("%c ", matriks[i][j]);
        }
        printf("\n");
    }
}

//Fungsi untuk eksekusi DFS
void DFS(int totalRows, int totalCols, int endY, int endX, int startX, int startY, char matriks[MAX_ROWS][MAX_COLS])
{    
    //Deklarasi array visited
    bool **visited = (bool **)malloc(totalRows * sizeof(bool *));
    for (int i = 0; i < totalRows; ++i)
    {
        visited[i] = (bool *)malloc(totalCols * sizeof(bool));
        for (int j = 0; j < totalCols; ++j)
        {
            visited[i][j] = false;
        }
    }

    //deklarasi path
    struct Coords_DFS path[MAX_ROWS * MAX_COLS];
    int pathIndex = 0;
    //Deklarasi shorets dan longest
    struct Coords_DFS shortestPath[MAX_ROWS * MAX_COLS];
    int shortestPathLength = -1;

    struct Coords_DFS longestPath[MAX_ROWS * MAX_COLS];
    int longestPathLength = -1;
    //memanggil fungsi DFS
    DFSUtil(totalRows, totalCols, startY, startX, endY, endX, visited, path, pathIndex, shortestPath, longestPath, &shortestPathLength, &longestPathLength, matriks);

    //mengrptin shortespath bila ada 
    if (shortestPathLength != -1)
    {
        char shortestPathMaze[MAX_ROWS][MAX_COLS];
        for (int i = 0; i < totalRows; ++i)
        {
            for (int j = 0; j < totalCols; ++j)
            {
                shortestPathMaze[i][j] = matriks[i][j];
            }
        }
        //menandai matriks dengan V
        markPath(totalRows, totalCols, shortestPath, shortestPathMaze, shortestPathLength);
        // Cetak matriks dengan jalur terpendek
        printf("Shortest Path:\n");
        printMazeDFS(totalRows, totalCols, shortestPathMaze);
        printf("\n");
    }
    else
    {
        printf("no path was found");
    }
    // mengprint longestpath bila ada
    if (longestPathLength != -1)
    {
        char longestPathMaze[MAX_ROWS][MAX_COLS];
        for (int i = 0; i < totalRows; ++i)
        {
            for (int j = 0; j < totalCols; ++j)
            {
                longestPathMaze[i][j] = matriks[i][j];
            }
        }
         //menandai matriks dengan V
        markPath(totalRows, totalCols, longestPath, longestPathMaze, longestPathLength);

        // Cetak matriks dengan jalur terpanjang
        printf("Longest Path:\n");
        printMazeDFS(totalRows, totalCols, longestPathMaze);
        printf("\n");
    }
    else
    {
        printf(".");
    }
    // Bebaskan memori
    for (int i = 0; i < totalRows; ++i)
    {
        free(visited[i]);
    }
    free(visited);
}

int main_DFS()
{
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
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#'}};

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
        {'.', '.', '.', '.', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#'}};

    int maze2_startY = 13, maze2_startX = 3;
    int maze2_endY = 0, maze2_endX = 1;

    printf("Maze 1:\n");
    DFS(maze1_rows, maze1_cols, maze1_endY, maze1_endX, maze1_startX, maze1_startY, maze1);

    printf("Maze 2:\n");
    DFS(maze2_rows, maze2_cols, maze2_endY, maze2_endX, maze2_startX, maze2_startY, maze2);

    return 0;
}
