#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 2000

// Struktur untuk menyimpan data stack
typedef struct {
    int coordinates[MAX_SIZE][2]; // Setiap elemen stack memiliki dua nilai: X dan Y
    int topIndex; // Indeks atas stack
} Stack;

// Fungsi untuk membuat stack baru
Stack* initializeStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->topIndex = -1; // Inisialisasi topIndex sebagai -1 (stack kosong)
    return stack;
}

// Fungsi untuk mengecek apakah stack kosong
int checkIfEmpty(Stack* stack) {
    return stack->topIndex == -1;
}

// Fungsi untuk mengecek apakah stack penuh
int checkIfFull(Stack* stack) {
    return stack->topIndex == MAX_SIZE - 1;
}

// Fungsi untuk menambahkan elemen ke stack (push)
void push(Stack* stack, int y, int x) {
    if (checkIfFull(stack)) {
        printf("Stack penuh. Push gagal.\n");
        return;
    }
    stack->topIndex++;
    stack->coordinates[stack->topIndex][0] = y; // Menyimpan nilai Y pada stack
    stack->coordinates[stack->topIndex][1] = x; // Menyimpan nilai X pada stack
}

// Fungsi untuk mengpop elemen di dalam stack
void pop(Stack *stack){
    stack->coordinates[stack->topIndex][0] = -1; // Menyimpan nilai Y pada stack
    stack->coordinates[stack->topIndex][1] = -1; // Menyimpan nilai X pada stack
    stack->topIndex--;
}

// Fungsi untuk mencetak isi stack dengan format (y,x)->
void displayStack(Stack* stack) {
    int index = 0;
    while (index <= stack->topIndex) {
        printf("(%d,%d)", stack->coordinates[index][0], stack->coordinates[index][1]);
        if (index < stack->topIndex) {
            printf("->");
        }
        index++;
    }
    printf("\n");
    printf("Panjang jalur : %d" , stack->topIndex+1);
}

// Fungsi rekursif DFS untuk mencari jalur dalam labirin
void depthFirstSearch(int rows, int cols, char maze[rows][cols], int currentY, int currentX, int targetY, int targetX, Stack* stack, int visited[rows][cols], int *foundFlag) {
    // Daftar perpindahan yang mungkin (atas, kanan, bawah, kiri)
    int deltaY[4] = {0, 1, 0, -1};
    int deltaX[4] = {1, 0, -1, 0};

    visited[currentY][currentX] = true; // Tandai koordinat saat ini sebagai sudah dikunjungi

    // Iterasi ke semua arah
    int i = 0;
    while (i < 4) {
        int nextY = currentY + deltaY[i];
        int nextX = currentX + deltaX[i];

        if ((nextY >= 0) && (nextY < rows) && (nextX >= 0) && (nextX < cols) && (maze[nextY][nextX] != '#') && !visited[nextY][nextX]) {
            if ((nextY == targetY && nextX == targetX) && *foundFlag == 0) {
                // Jika target ditemukan atau mencapai titik akhir, tambahkan target ke dalam stack dan kembalikan
                *foundFlag = 1;
                push(stack, nextY, nextX);
                return;
            } else {
                if (*foundFlag == 0) {
                    // Jika belum menemukan target, lanjutkan pencarian dengan menambahkan koordinat ke dalam stack
                    push(stack, nextY, nextX);
                }
                // Lanjutkan pencarian rekursif
                depthFirstSearch(rows, cols, maze, nextY, nextX, targetY, targetX, stack, visited, foundFlag);
                if (*foundFlag == 0) {
                    // Jika belum menemukan target setelah menjelajahi jalur ini, hapus koordinat dari stack
                    pop(stack);
                }
            }
        }
        i++;
    }
}

int main() {
    // Labirin
    char labyrinth[10][10] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '.', '.'},
        {'#', 'S', '.', '#', '.', '.', '#', '.', '.', '#'},
        {'#', '#', '.', '#', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '#', '#', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '.', '#', '.', '#'},
        {'#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '.', '#', '#', '.', '.', '#'},
        {'#', '#', '#', '#', 'E', '#', '.', '.', '.', '#'}
    };

    // Posisi awal dan target
    int startY = 1, startX = 1;
    int endY = 9, endX = 4;

    // Ukuran labirin
    int totalRows = 10, totalCols = 10;

    // Inisialisasi stack dan visited
    Stack* pathStack = initializeStack();
    int visited[totalRows][totalCols];
    int foundFlag = 0;

    // Inisialisasi visited dengan false (belum dikunjungi)
    int rowIndex = 0;
    while (rowIndex < totalRows) {
        int colIndex = 0;
        while (colIndex < totalCols) {
            visited[rowIndex][colIndex] = 0;
            colIndex++;
        }
        rowIndex++;
    }

    // Pemanggilan fungsi DFS untuk mencari jalur
    depthFirstSearch(totalRows, totalCols, labyrinth, startY, startX, endY, endX, pathStack, visited, &foundFlag);
    displayStack(pathStack);
    if(foundFlag == 0){
        printf("Tidak ditemukan Jalur");
    }
    return 0;
}