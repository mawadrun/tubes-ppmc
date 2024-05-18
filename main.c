#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "astar.c"
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
    int pilihanAlgorithm;
    bacaFile();             
    // tes print isi file txt
    printf("\nBentuk maze-nya:\n");
    for(int j=0;j<baris;j++){
        printf("%s", matriks[j]);
    }
    printf("\nJumlah baris = %d\nJumlah kolom = %d", baris, kolom);

    printf("variabel m dari divide: m = %d", baris);

    return 0;
}