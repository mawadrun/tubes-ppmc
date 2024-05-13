#include <stdio.h>
#include <sys/time.h>
#include <math.h>

#define MAX_ROW 256
#define MAX_COL 256

struct Coords
{
    int x, y;
    int g, h;
};

int isInList(struct Coords val, struct Coords *list)
{
}

int manhattanDistance(struct Coords p1, struct Coords p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

struct Coords findStart(char matrix[MAX_COL][MAX_ROW], int m, int n)
{
    struct Coords val;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 'S')
            {
                val.x = i;
                val.y = j;
                return val;
            }
        }
    }
    return val;
}

struct Coords findEnd(char matrix[MAX_COL][MAX_ROW], int m, int n)
{
    struct Coords val;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 'E')
            {
                val.x = i;
                val.y = j;
                return val;
            }
        }
    }
    return val;
}

int aStar(char matrix[MAX_COL][MAX_ROW], int m, int n)
{
    struct Coords start = findStart(matrix, m, n);
    struct Coords end = findEnd(matrix, m, n);
    int distance = manhattanDistance(start, end);

    printf("Start: %d, %d\nEnd: %d, %d\n", start.x, start.y, end.x, end.y);
    printf("Distance: %d\n", distance);

    /*
    - Buat dua buah list, open dan closed.
      Open list digunakan untuk menyimpan kandidat titik yang dapat dikunjungi,
      dan closed list digunakan untuk menyimpan titik yang sudah dikunjungi.
    - Masukkan titik awal ke closed list. Jadikan ia sebagai titik aktif
    - Masukkan keempat tetangga dari titik aktif yang mungkin
      dikunjungi; yakni arah bawah, kanan, atas, dan kiri; ke dalam open list.
    - Selama open list tidak kosong:
      - Dapatkan koordinat dari open list yang memiliki cost terkecil. Jadikan
        sebagai titik aktif.
      - Hilangkan titik aktif dari open list. Tambahkan ke closed list
      - Periksa keempat tetangga dari titik aktif yang mungkin dikunjungi dan
        tidak ada di closed list, tambahkan keempatnya ke open list.

    ALTERNATIF
    - Buat open list untuk menyimpan kandidat titik yang dapat dikunjungi.
    - Masukkan titik awal ke closed list. Jadikan ia sebagai titik aktif
    - Masukkan keempat tetangga dari titik aktif yang mungkin
      dikunjungi; yakni arah bawah, kanan, atas, dan kiri; ke dalam open list.
      Jadikan titik aktif sebagai parent dari keempatnya.
    - Selama open list tidak kosong:
      - Dapatkan koordinat dari open list yang memiliki cost terkecil. Jadikan
        sebagai titik aktif.
      - Hilangkan titik aktif dari open list.
      - Periksa keempat tetangga dari titik aktif yang mungkin dikunjungi dan
        tidak ada di closed list, tambahkan keempatnya ke open list. Jadikan
        titik aktif sebagai parent dari keempatnya.
    */
}

int main()
{
    struct timeval time1; // Start time
    struct timeval time2; // Finish time
    long dt;              // Delta time (us)

    // Variables
    int m = 7, n = 7;
    char matrix[MAX_COL][MAX_ROW] = {
        {'S', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'X', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'X', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'X', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'X', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'X', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'E'},
    };

    gettimeofday(&time1, NULL);
    aStar(matrix, m, n);
    gettimeofday(&time2, NULL);
    dt = (time2.tv_sec - time1.tv_sec) * 1000000 + time2.tv_usec - time1.tv_usec;
    printf("Done.\n");
    printf("A-Star took %d us.");

    return 0;
}