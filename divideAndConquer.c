#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "definisiFungsi.h"


typedef struct point{
    // baris adalah y, kolom adalah x
    int x;
    int y;
} point;

int pathCount = 0;                  // untuk menghitung banyak path

int longestPath = 0;                // menyimpan panjang jalur yang terpanjang
char bentukLongestPath[255][255];   // menyimpan rute jalur terpanjang

int shortestPath = 65025;           // menyimpan panjang jalur yang terpendek
char bentukShortestPath[255][255];  // menyimpan rute jalur terpendek

// fungsi ini digunakan untuk mengecek apakah koordinat suatu point valid atau tidak
bool isValid_divide(char maze[255][255], point* currentPoint, int baris, int kolom) {
    if(currentPoint->x >= 0 && currentPoint->x < kolom && currentPoint->y >= 0 && currentPoint->y < baris 
    && maze[currentPoint->y][currentPoint->x] != '#' && maze[currentPoint->y][currentPoint->x] != 'x'){
        return true;
    }
    else{
        return false;
    }
}

// fungsi ini digunakan untuk menyimpan rute jalur terpanjang/terpendek
void savePath(char sumber[255][255], char destinasi[255][255], int baris, int kolom) {
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            destinasi[i][j] = sumber[i][j];
        }
    }
}

// fungsi ini digunakan untuk meng-print maze jika sudah ditemukan sebuah jalur
void printMaze_divide(char maze[255][255], int baris, int kolom, int pathLength, bool simpanMaze, FILE* fptr){
    pathCount++;


    // fungsi printMaze_divide() dapat digunakan untuk menyimpan rute maze terpanjang/terpendek
    if(simpanMaze){
        if(pathLength > longestPath) {
            longestPath = pathLength;
            savePath(maze, bentukLongestPath, baris, kolom);
        }
        if(pathLength < shortestPath) {
            shortestPath = pathLength;
            savePath(maze, bentukShortestPath, baris, kolom);
        }


    // bagian ini berfungsi untuk menulis di file external (.txt)
        char temp[50];                // digunakan untuk pemberi keterangan path ke berapa
        sprintf(temp, "Path %d: (panjang = %d)\n", pathCount, pathLength);
        fputs(temp, fptr);

    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            if(maze[i][j] == 'x'){
                fputc('1', fptr);
            }
            else{
                fputc('_', fptr);
            }
        }
        fputc('\n', fptr);
    }
    fputc('\n', fptr);

    }

    if(simpanMaze == false){
    // meng-print satu buah jalur
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            if(maze[i][j] == 'x'){
                printf("1");
            }
            else{
                printf("_");
            }
        }
        printf("\n");
    }
    printf("\n");
    }
}

// fungsi ini adalah fungsi rekursif. Digunakan untuk mencari jalur dari start sampai end
void divideAndConquer(char maze[255][255], point* currentPoint, int baris, int kolom, point* end, int pathLength, FILE* fptr) {
    if (currentPoint->x == end->x && currentPoint->y == end->y) {     // kasus basis: koordinat point sama dengan koordinat end
        maze[end->y][end->x] = 'x';
        printMaze_divide(maze, baris, kolom, pathLength+1, true, fptr);  // mencetak maze
        maze[end->y][end->x] = 'E';
        return ;
    }

    // point yang sudah dilewati ditandai dengan 'x'
    maze[currentPoint->y][currentPoint->x] = 'x';

    // mencari titik berikutnya untuk di-eksplorasi
    // ada empat kemungkinan titik berikutnya: sebelah kanan, kiri, atas, dan bawah
    int listX[4] = {1, -1, 0, 0};
    int listY[4] = {0, 0, -1, 1};
    
    for (int i = 0; i < 4; i++) {
        point* nextPoint = (point*) malloc(sizeof(point));
        nextPoint->x = currentPoint->x + listX[i];
        nextPoint->y = currentPoint->y + listY[i];
        // perhatikan bahwa point berikutnya memiliki koordinat (nextX, nextY)
        // point berikutnya adalah perubahan koordinat point saat ini pada sumbu-x saja atau sumbu-y saja

        if (isValid_divide(maze, nextPoint, baris, kolom)) {
            divideAndConquer(maze, nextPoint, baris, kolom, end, pathLength+1, fptr);
            // setiap kali divideAndConquer() dipanggil, pathLength bertambah 1
        }
    }

    // jika sudah tercapai titik END, titik yang terakhir diubah lagi dari 'x' menjadi '.'
    maze[currentPoint->y][currentPoint->x] = '.';
    // hal ini supaya fungsi rekursif dapat mencari jalur baru
    // jalur yang sebelumnya tidak akan terulangi karena menggunakan for loop.
}

void cariKoordinat(point* titik, char huruf, int baris, int kolom, char matriks[255][255]){
    for(int i = 0; i<baris; i++){
        for(int j = 0; j<kolom; j++){
            if(matriks[i][j] == huruf){
                titik->x = j;
                titik->y = i;
                matriks[i][j] = '.';
            }
        }
    }
}

int main_divide(void) {    
    // memanggil fungsi bacaFile() untuk membaca file external
    // bacaFile();
    
    // ___ kode di bawah ini untuk mengecek hasil baca file .txt
    // printf("\nBentuk maze-nya:\n");
    // for(int j=0;j<baris;j++){
    //     printf("%s", matriks[j]);
    // }
    // printf("\nJumlah baris = %d\nJumlah kolom = %d", baris, kolom);

    // menginisiasi titik start dan end
    point* start = (point*) malloc(sizeof(point));
    point* end = (point*) malloc(sizeof(point));

    // mencari titik start
    cariKoordinat(start, 'S', baris, kolom, matriks);
    // printf("\nKoordinat start: (x, y) = (%d, %d)", start->x, start->y);

    // mencari titik end
    cariKoordinat(end, 'E', baris, kolom, matriks);
    // printf("\nKoordinat end: (x, y) = (%d, %d)", end->x, end->y);


    clock_t startTime, stopTime;
    double cpu_time_used;

    // meng-inisiasi file txt eksternal untuk menyimpan semua kemungkinan maze yang ditemukan
    FILE* fptr;
    fptr = fopen("testtxt.txt", "w");


    startTime = clock();
    divideAndConquer(matriks, start, baris, kolom, end, 0, fptr);
    stopTime = clock();

    fclose(fptr);


    if(pathCount == 0){
        printf("Labirin tidak memiliki solusi.");
    }
    else{
        printf("Ada %d rute\n", pathCount);

        printf("Panjang rute terpanjang: %d\n", longestPath);
        printMaze_divide(bentukLongestPath, baris, kolom, longestPath, false, fptr);


        printf("Panjang rute terpendek: %d\n", shortestPath);
        printMaze_divide(bentukShortestPath, baris, kolom, shortestPath, false, fptr);

        // menampilkan waktu eksekusi
        cpu_time_used = ((double) (stopTime - startTime)) / CLOCKS_PER_SEC;
        printf("\nWaktu yang diperlukan untuk mencari seluruh rute: %f detik\n", cpu_time_used);
    }
    return 0;
}