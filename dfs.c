#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "definisiFungsi.h"

#define MAX_SIZE 2000

// Struktur untuk menyimpan data stack
typedef struct
{
    int coordinates[MAX_SIZE][2]; // Setiap elemen stack memiliki dua nilai: X dan Y
    int topIndex;                 // Indeks atas stack
} Stack;

// Fungsi untuk membuat stack baru
Stack *initializeStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->topIndex = -1; // Inisialisasi topIndex sebagai -1 (stack kosong)
    return stack;
}

// Fungsi untuk mengecek apakah stack kosong
int checkIfEmpty(Stack *stack)
{
    return stack->topIndex == -1;
}

// Fungsi untuk mengecek apakah stack penuh
int checkIfFull(Stack *stack)
{
    return stack->topIndex == MAX_SIZE - 1;
}

// Fungsi untuk menambahkan elemen ke stack (push)
void push(Stack *stack, int y, int x)
{
    if (checkIfFull(stack))
    {
        printf("Stack penuh. Push gagal.\n");
        return;
    }
    stack->topIndex++;
    stack->coordinates[stack->topIndex][0] = y; // Menyimpan nilai Y pada stack
    stack->coordinates[stack->topIndex][1] = x; // Menyimpan nilai X pada stack
}

// Fungsi untuk mengpop elemen di dalam stack
void pop(Stack *stack)
{
    if (!checkIfEmpty(stack))
    {
        stack->topIndex--;
    }
}

// Fungsi untuk mencetak isi stack dengan format (y,x)->
void displayStack(Stack *stack)
{
    int index = 0;
    while (index <= stack->topIndex)
    {
        printf("(%d,%d)", stack->coordinates[index][0], stack->coordinates[index][1]);
        if (index < stack->topIndex)
        {
            printf("->");
        }
        index++;
    }
    printf("\nPanjang jalur : %d\n", stack->topIndex + 1);
}

// Struktur untuk menyimpan jalur
typedef struct
{
    int paths[MAX_SIZE][MAX_SIZE][2]; // Menyimpan semua jalur
    int lengths[MAX_SIZE];            // Menyimpan panjang dari setiap jalur
    int count;                        // Menyimpan jumlah jalur
} Paths;

Paths allPaths;

// Fungsi rekursif DFS untuk mencari semua jalur dalam labirin
void findAllPaths(int rows, int cols, char maze[rows][cols], int currentY, int currentX, int targetY, int targetX, Stack *stack, int visited[rows][cols])
{
    // Daftar perpindahan yang mungkin (kanan, bawah, kiri, atas)
    int deltaY[4] = {0, 1, 0, -1};
    int deltaX[4] = {1, 0, -1, 0};

    if (currentY == targetY && currentX == targetX)
    {
        // Jika mencapai titik akhir, simpan jalur saat ini
        // Buat salinan stack untuk disimpan
        Stack *tempStack = initializeStack();
        for (int i = 0; i <= stack->topIndex; i++)
        {
            push(tempStack, stack->coordinates[i][0], stack->coordinates[i][1]);
        }

        // Periksa panjang jalur sebelum menyimpannya
        int pathLength = tempStack->topIndex + 1;
        if (pathLength > 0) {
            // Simpan jalur hanya jika panjangnya lebih dari 0
            for (int i = 0; i < pathLength; i++)
            {
                allPaths.paths[allPaths.count][i][0] = tempStack->coordinates[i][0];
                allPaths.paths[allPaths.count][i][1] = tempStack->coordinates[i][1];
            }
            allPaths.lengths[allPaths.count] = pathLength;
            allPaths.count++;
        }
        
        // Bebaskan memori yang dialokasikan untuk stack sementara
        free(tempStack);
        return;
    }

    visited[currentY][currentX] = true; // Tandai koordinat saat ini sebagai sudah dikunjungi

    for (int i = 0; i < 4; i++)
    {
        int nextY = currentY + deltaY[i];
        int nextX = currentX + deltaX[i];

        if (nextY >= 0 && nextY < rows && nextX >= 0 && nextX < cols && maze[nextY][nextX] != '#' && !visited[nextY][nextX])
        {
            push(stack, nextY, nextX);
            findAllPaths(rows, cols, maze, nextY, nextX, targetY, targetX, stack, visited);
            pop(stack);
        }
    }

    visited[currentY][currentX] = false; // Tandai koordinat saat ini sebagai belum dikunjungi untuk jalur lainnya
}


// Fungsi untuk menampilkan jalur yang ditemukan dalam bentuk visual di labirin
void printAllPath(int rows, int cols, char maze[rows][cols], Stack *stack)
{
    // Buat salinan labirin untuk memvisualisasikan jalur
    char visualMaze[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            visualMaze[i][j] = maze[i][j];
        }
    }

    // Tandai jalur di dalam visualMaze dengan '1'
    for (int i = 0; i <= stack->topIndex; i++)
    {
        int y = stack->coordinates[i][0];
        int x = stack->coordinates[i][1];
        visualMaze[y][x] = '1';
    }

    // Tampilkan visualMaze
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c ", visualMaze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fungsi untuk menampilkan semua jalur dengan visualisasi
void displayAllPathsWithVisualization(int rows, int cols, char maze[rows][cols])
{
    printf("Semua jalur yang ditemukan dengan visualisasi:\n");
    for (int i = 0; i < allPaths.count; i++)
    {
        Stack *tempStack = initializeStack();
        for (int j = 0; j < allPaths.lengths[i]; j++)
        {
            push(tempStack, allPaths.paths[i][j][0], allPaths.paths[i][j][1]);
        }
        printAllPath(rows, cols, maze, tempStack);
        free(tempStack);
    }
}

// Fungsi untuk menampilkan jalur terpendek dengan visualisasi
void displayShortestPathWithVisualization(int rows, int cols, char maze[rows][cols])
{
    if (allPaths.count == 0)
        return;

    int shortestIndex = 0;
    for (int i = 1; i < allPaths.count; i++)
    {
        if (allPaths.lengths[i] < allPaths.lengths[shortestIndex])
        {
            shortestIndex = i;
        }
    }
    
    if (shortestIndex ==0) {
        printf("Shortest gagal ditemukan");
        return;
    }

    printf("Visualisasi jalur terpendek:\n");
    Stack *tempStack = initializeStack();
    for (int j = 0; j < allPaths.lengths[shortestIndex]; j++)
    {
        push(tempStack, allPaths.paths[shortestIndex][j][0], allPaths.paths[shortestIndex][j][1]);
    }

    printAllPath(rows, cols, maze, tempStack);
    free(tempStack);
}

// Fungsi untuk menampilkan jalur terpanjang dengan visualisasi
void displayLongestPathWithVisualization(int rows, int cols, char maze[rows][cols])
{
    if (allPaths.count == 0)
        return;

    int longestIndex = 0;
    for (int i = 1; i < allPaths.count; i++)
    {
        if (allPaths.lengths[i] > allPaths.lengths[longestIndex])
        {
            longestIndex = i;
        }
    }

    printf("Visualisasi jalur terpanjang:\n");
    Stack *tempStack = initializeStack();
    for (int j = 0; j < allPaths.lengths[longestIndex]; j++)
    {
        push(tempStack, allPaths.paths[longestIndex][j][0], allPaths.paths[longestIndex][j][1]);
    }
    printAllPath(rows, cols, maze, tempStack);
    free(tempStack);
}

void DFS(int totalRows, int totalCols, char maze[totalRows][totalCols], int targetY, int targetX, int startX, int startY)
{

    // Inisialisasi stack dan visited
    Stack *pathStack = initializeStack();
    int visited[totalRows][totalCols];
    int foundFlag = 0;

    // Inisialisasi visited dengan false (belum dikunjungi)
    for (int i = 0; i < totalRows; i++)
    {
        for (int j = 0; j < totalCols; j++)
        {
            visited[i][j] = 0;
        }
    }

    // Inisialisasi allPaths
    allPaths.count = 0;

    // Menambahkan posisi awal ke stack
    push(pathStack, startY, startX);

    // Pemanggilan fungsi DFS untuk mencari semua jalur
    findAllPaths(totalRows, totalCols, maze, startY, startX, targetY, targetX, pathStack, visited);

    // Menampilkan semua jalur dengan visualisasi
    //displayAllPathsWithVisualization(totalRows, totalCols, maze);

    // Menampilkan jalur terpendek dengan visualisasi
    displayShortestPathWithVisualization(totalRows, totalCols, maze);

    // Menampilkan jalur terpanjang dengan visualisasi
    displayLongestPathWithVisualization(totalRows, totalCols, maze);

    // Bebaskan memori yang dialokasikan untuk pathStack
    free(pathStack);

    return;
}

int main_dfs()
{
    // Labirin
     char matriks[11][13] = {
        {'S', '.', '.', '.', '.', '#', '.', '.', '#', '.', '.', '.', '.'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '.', '.', '.', '#', '.'},
        {'.', '.', '.', '.', '#', '.', '#', '.', '#', '.', '.', '.', '.'},
        {'.', '#', '.', '.', '.', '.', '.', '#', '.', '#', '.', '#', '.'},
        {'.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#', '#', '.'},
        {'.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '#', '.', '.'},
        {'.', '#', '.', '.', '.', '#', '.', '#', '.', '.', '.', '#', '.'},
        {'.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '#', '.', '#', '.', '#', '.', '#', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '#', '.', '#', '.', '.', 'E', '.', '#', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.'}
    };

    // Posisi awal dan target
    int startY = 0, startX = 0;
    int endY = 9, endX = 9;

    // Ukuran labirin
    int totalRows = 13, totalCols = 11;

    DFS(totalRows, totalCols, matriks, endY, endX, startX, startY);
    return 0;
}
