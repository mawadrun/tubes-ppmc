typedef struct point{
    // baris adalah y, kolom adalah x
    int x;
    int y;
} point;

char matriks[255][255];  // Menyimpan matriks labirin
int baris;  // Jumlah baris dari labirin
int kolom;  // Jumlah kolom dari labirin

// Deklarasi fungsi-fungsi yang akan digunakan di berbagai file .c

void bacaFile();

void cariKoordinat(point* titik, char huruf, int baris, int kolom, char matriks[255][255]);