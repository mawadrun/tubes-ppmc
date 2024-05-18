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

int main()
{
    char matriks[MAX_ROW][MAX_COL];
    int baris;
    int kolom;
    bacaFile(matriks, &baris, &kolom);
    struct Coords awal = findStart(matriks, baris, kolom);
    struct Coords akhir = findEnd(matriks, baris, kolom);
    point* start = (point*) malloc(sizeof(point));
    cariKoordinat(start, 'S', baris, kolom, matriks);
    point* end = (point*) malloc(sizeof(point));
    cariKoordinat(end, 'E', baris, kolom, matriks);
    // printf("Baris: %d", baris);
    // printf("Kolom: %d", kolom);
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

    if (pilihanAlgorithm == 1)
    {
        main_greedy();
    }
    else if (pilihanAlgorithm == 2)
    {
        aStar(matriks, baris, kolom, awal, akhir);
    }
    else if (pilihanAlgorithm == 3)
    {
        main_back(matriks, baris, kolom, awal.x, awal.y, akhir.x, akhir.y); // error
    }
    else if (pilihanAlgorithm == 4)
    {
        DFS(kolom, baris, matriks, akhir.x, akhir.y, awal.y, awal.x);
    }
    else if (pilihanAlgorithm == 5)
    {
        Point_dijkstra start_point, end_point;
        start_point.x = awal.y;
        start_point.y = awal.x;
        end_point.x = akhir.y;
        end_point.y = akhir.x;
        dijkstra(matriks, baris, kolom, start_point, end_point);
    }
    else if (pilihanAlgorithm == 6)
    {
        FILE* fptr;
        fptr = fopen("output.txt", "w");
        
        divideAndConquer(matriks, start, baris, kolom, end, 0, fptr);
        
        // // TES OUTPUT
        // printMaze_divide(bentukShortestPath, baris, kolom, shortestPath, false, fptr);
    }
    else if (pilihanAlgorithm == 7)
    {
        Point_bfs source = {start->y, start->x};
        Point_bfs dest = {end->y, end->x};
        int step = BFS(matriks, source, dest, baris, kolom);
        
        // // TES OUTPUT
        // printf("Shortest path : %d steps\n", step);
        // if (step != 1){
        //     printf("Shortest path : \n");
        //     for(int i = 0; i< baris; i++){
        //         for(int j = 0; j<kolom; j++){
        //             if(matriks[i][j] == 'V' || matriks[i][j] == 'S' || matriks[i][j] == 'E'){
        //                 printf("%c ", matriks[i][j]);
        //             }
        //             else if(matriks[i][j] == '.'){
        //                 printf(". ");
        //             } else{
        //                 printf("# ");
        //             }
        //         }
        //         printf("\n");
        //     }
        // }
        // else{
        //     printf("Tidak ada jalur.\n");
        // }        
    }

    return 0;
}