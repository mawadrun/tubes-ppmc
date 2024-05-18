#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definisiFungsi.h"

// fungsi ini digunakan untuk membaca file external, lalu menyimpan isinya dalam bentuk matriks
void bacaFile(){
    // Membaca file external
    printf("Masukkan nama file yang akan dibaca: ");
    char inputFile[255];
    scanf("%s", &inputFile);

    FILE* fp = fopen(inputFile, "r");
    while (fp == NULL){
        printf("File tidak bisa dibuka\n");
        printf("Masukkan nama file yang akan dibaca: ");
        scanf("%s", &inputFile);
        fp = fopen(inputFile, "r");
    }

    // menyalin isi file external ke variabel lokal, sekaligus menghitung jumlah baris di file external tersebut
    while(fgets(matriks[baris], 255, fp)){
        baris++;
    }

    // menghitung hitung banyak kolom di file external
    while(matriks[0][kolom] != '\0'){
        kolom++;
    }
    kolom--;
}