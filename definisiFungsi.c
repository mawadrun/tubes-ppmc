#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definisiFungsi.h"

// fungsi ini digunakan untuk membaca file external, lalu menyimpan isinya dalam bentuk matriks
void bacaFile(char matrix[MAX_ROW][MAX_COL], int *row, int *col)
{
    // Membaca file external
    int baris; // Jumlah baris dari labirin
    int kolom; // Jumlah kolom dari labirin
    printf("Masukkan nama file yang akan dibaca: ");
    char inputFile[MAX_ROW];
    scanf("%s", &inputFile);

    FILE *fp = fopen(inputFile, "r");
    while (fp == NULL)
    {
        printf("File tidak bisa dibuka\n");
        printf("Masukkan nama file yang akan dibaca: ");
        scanf("%s", &inputFile);
        fp = fopen(inputFile, "r");
    }

    // menyalin isi file external ke variabel lokal, sekaligus menghitung jumlah baris di file external tersebut
    while (fgets(matrix[baris], MAX_ROW, fp))
    {
        baris++;
    }

    // menghitung hitung banyak kolom di file external
    while (matrix[0][kolom] != '\0')
    {
        kolom++;
    }
    kolom--;
    *row = baris;
    *col = kolom;
}