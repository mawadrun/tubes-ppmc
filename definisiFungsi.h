/** EL2208 Praktikum Pemecahan Masalah dengan C 2023/2024
 *   Modul               : Tubes
 *   Hari dan Tanggal    : 13 Mei 2024
 *   Nama (NIM)          : Nur Dawam Abdan Syakuro (13222046)
 *   Nama File           : astar.c
 *   Deskripsi           : Implementasi algoritma A* menggunakan priority queue sebagai penentu langkah terbaik untuk diambil, dan manhattan distance untuk menghitung jarak.
 *
 */

#define MAX_COL 255
#define MAX_ROW 255

// Deklarasi fungsi-fungsi yang akan digunakan di banyak file .c
void bacaFile();
void ubah255ke236(char maze255[255][255], char maze236[236][236]);