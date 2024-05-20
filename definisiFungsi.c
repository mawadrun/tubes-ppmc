/** EL2208 Praktikum Pemecahan Masalah dengan C 2023/2024
 *   Modul               : Tubes
 *   Hari dan Tanggal    :
 *   Nama (NIM)          :
 *   Nama File           :
 *   Deskripsi           :
 *
 */

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

void ubah255ke236(char maze255[255][255], char maze236[236][236])
{
    for (int i = 0; i < 236; i++)
    {
        for (int j = 0; j < 236; j++)
        {
            maze236[i][j] = maze255[i][j];
        }
    }
}