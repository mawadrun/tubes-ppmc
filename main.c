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

    bacaFile();             
    // tes print isi file txt
    printf("\nBentuk maze-nya:\n");
    for(int j=0;j<baris;j++){
        printf("%s", matriks[j]);
    }
    printf("\nJumlah baris = %d\nJumlah kolom = %d", baris, kolom);

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
    scanf("%d", pilihanAlgorithm);

    if(pilihanAlgorithm == 1){
        main_greedy();
    }
    else if(pilihanAlgorithm == 2){
        main_astar();
    }
    else if(pilihanAlgorithm == 3){
        main_back();
    }
    else if(pilihanAlgorithm == 4){
        main_dfs();
    }
    else if(pilihanAlgorithm == 5){
        main_dijkstra();
    }
    else if(pilihanAlgorithm == 6){
        main_divide();
    }
    else if(pilihanAlgorithm == 7){
        main_bfs();
    }

    return 0;
}