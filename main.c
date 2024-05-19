#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "astar.c"
#include "Greedy.c"
#include "backtracking.c"
#include "dfs.c"
#include "dijkstra.c"
#include "divideAndConquer.c"
#include "labirinBFS.c"
#include "definisiFungsi.c"
#include "definisiFungsi.h"

// *NOTE : definisiFungsi.h isinya cuman deklarasi fungsi
//         definisiFungsi.c isinya realisasi dari definisiFungsi.h

void reduceSize(char matriks[MAX_ROW][MAX_COL], int m, int n, char newMatriks[m][n + 1])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            newMatriks[i][j] = matriks[i][j];
        }
    }
}

int main()
{
    char matriks[MAX_ROW][MAX_COL];
    int baris;
    int kolom;
    bacaFile(matriks, &baris, &kolom);
    struct Coords awal = findStart(matriks, baris, kolom);
    struct Coords akhir = findEnd(matriks, baris, kolom);
    point *start = (point *)malloc(sizeof(point));

    // Beberapa algoritma pake format ini
    start->x = awal.y; // pada Coords, x itu vertikal, sedangkan pada point, x itu horizontal
    start->y = awal.x;
    point *end = (point *)malloc(sizeof(point));
    end->x = akhir.y;
    end->y = akhir.x;

    // tes print isi file txt
    printf("\nBentuk maze-nya:\n");
    printMatrix(matriks, baris, kolom);
    printf("\nJumlah baris = %d\nJumlah kolom = %d", baris, kolom);
    printf("\nTitik awal: %d, %d\n Titik akhir: %d, %d\n", awal.x, awal.y, akhir.x, akhir.y);

    int pilihanAlgorithm;
    printf("\nMau pake algoritma apaan??\n");
    printf("1. greedy\n");
    printf("2. A*\n");
    printf("3. backtracking\n");
    printf("4. DFS\n");
    printf("5. dijkstra\n");
    printf("6. divide and conquer\n");
    printf("7. BFS\n");
    printf("> ");
    scanf("%d", &pilihanAlgorithm);

    clock_t startTime, stopTime;
    startTime = clock();
    char newMatriks[baris][(kolom + 1)];
    if (pilihanAlgorithm == 1)
    {
        int start[2] = {awal.y, awal.x};
        int end[2] = {akhir.x, akhir.y};
        int prev[2] = {-1, -1};
        reduceSize(matriks, baris, kolom, newMatriks);
        int trace[baris][kolom + 1];
        for (int i = 0; i < baris; i++)
        {
            for (int j = 0; j <= kolom; j++)
            {
                trace[i][j] = 0;
            }
        }
        findallpaths(baris, kolom + 1, newMatriks, prev, start, end, trace);
        for (int i = 0; i < baris; i++)
        {
            for (int j = 0; j < kolom; j++)
            {
                printf("%c ", newMatriks[i][j]);
            }
            printf("%c", newMatriks[i][kolom]);
        }
        stopTime = clock();
    }
    else if (pilihanAlgorithm == 2)
    {
        aStar(matriks, baris, kolom, awal, akhir);
        stopTime = clock();
    }
    else if (pilihanAlgorithm == 3)
    {
        main_back(matriks, baris, kolom, awal.x, awal.y, akhir.x, akhir.y);
        stopTime = clock();
    }
    else if (pilihanAlgorithm == 4)
    {

        DFS(baris, kolom, akhir.x, akhir.y, awal.y, awal.x, matriks);
        stopTime = clock();
    }
    else if (pilihanAlgorithm == 5)
    {
        Point_dijkstra start_point, end_point;
        start_point.x = awal.y;
        start_point.y = awal.x;
        end_point.x = akhir.y;
        end_point.y = akhir.x;
        dijkstra(matriks, baris, kolom, start_point, end_point);
        printf("Maze with shortest path marked:\n");
        printMatrix(matriks, baris, kolom);
        stopTime = clock();
    }
    else if (pilihanAlgorithm == 6)
    {
        FILE *fptr;
        fptr = fopen("output.txt", "w");

        divideAndConquer(matriks, start, baris, kolom, end, 0, fptr);
        stopTime = clock();

        printOutput_divide(baris, kolom, fptr);
    }
    else if (pilihanAlgorithm == 7)
    {
        Point_bfs source = {start->y, start->x};
        Point_bfs dest = {end->y, end->x};
        int step = BFS(matriks, source, dest, baris, kolom);
        stopTime = clock();

        // // TES OUTPUT
        if (step == -1)
        {
            printf("No path found");
        }
        else
        {
            printf("Shortest path : %d steps\n", step);
            printMatrix(matriks, baris, kolom);
        }
    }

    double cpu_time_used;
    cpu_time_used = ((double)(stopTime - startTime)) / CLOCKS_PER_SEC;
    printf("\nWaktu eksekusi: %.4f detik\n", cpu_time_used);

    return 0;
}