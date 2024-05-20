/** EL2208 Praktikum Pemecahan Masalah dengan C 2023/2024
 *   Modul               : Tubes
 *   Hari dan Tanggal    : 13 Mei 2024
 *   Nama (NIM)          : Nur Dawam Abdan Syakuro (13222046)
 *   Nama File           : astar.c
 *   Deskripsi           : Implementasi algoritma A* menggunakan priority queue sebagai penentu langkah terbaik untuk diambil, dan manhattan distance untuk menghitung jarak.
 *
 */

#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>
#include "definisiFungsi.h"

/*
x, y: titik koordinat
g: jarak titik koordinat dari titik awal
h: jarak titik koordinat dari titik akhir
parent: titik sebelumnya yang dilalui sebelum mencapai titik ini dari arah titik awal
*/
struct Coords
{
    int x, y;
    int g, h;
    struct Coords *parent;
};

/*
coords: titik koordinat yang dimuat di node priority queue
next: node berikutnya
*/
struct PriorityQueueNode
{
    struct Coords coords;
    struct PriorityQueueNode *next;
};

// Menghitung jarak Manhattan antara p1 dan p2
int manhattanDistance(struct Coords p1, struct Coords p2)
{
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

// Membandingkan koordinat p1 dan p2, me-return 1 jika dan hanya jika keduanya sama.
int isSameCoords(struct Coords p1, struct Coords p2)
{
    int val;
    val = p1.x == p2.x && p1.y == p2.y ? 1 : 0;
    return val;
}

// Memasukkan coords ke priority queue head dengan mempertahankan keterurutan priority queue berdasarkan cost y = g + h, dari yang terpendek.
void enqueue_astar(struct Coords coords, struct PriorityQueueNode **head)
{
    // Case priority queue masih kosong, simpan coords sebagai elemen pertama
    if (*head == NULL)
    {
        struct PriorityQueueNode *new = (struct PriorityQueueNode *)malloc(sizeof(struct PriorityQueueNode));
        new->coords = coords;
        new->next = NULL;
        *head = new;
        return;
    }
    // Case queue tidak kosong, cari posisi agar isi priority queue berurutan berdasarkan y = g + h, ambil posisi paling kanan yang mungkin
    struct PriorityQueueNode *current = *head;
    while (current->next != NULL && (coords.g + coords.h) >= ((current->next)->coords.g + (current->next)->coords.h))
    {
        current = current->next;
    }
    // Jika posisi yang ditemukan berisi koordinat yang sama dengan argumen, jangan simpan argumen ke priority queue
    if (!isSameCoords(coords, current->coords))
    {
        struct PriorityQueueNode *new = (struct PriorityQueueNode *)malloc(sizeof(struct PriorityQueueNode));
        new->coords = coords;
        new->next = current->next;
        current->next = new;
    }
}

// dequeue_astar biasa
struct Coords dequeue_astar(struct PriorityQueueNode **head)
{
    struct Coords val = (*head)->coords;
    *head = (*head)->next;
    return val;
}

// melakukan printing isi matriks berukuran m x n
void printMatrix(char matrix[MAX_COL][MAX_ROW], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Mencari titik awal dari map dengan format matriks berukuran m x n
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

// Mencari titik akhir dari map dengan format matriks berukuran m x n
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

// Mencari tetangga yang valid dan menambahnya ke priority queue. Jika tidak ditemukan jalan, return 0
int addNeighbors(struct Coords *coords, struct PriorityQueueNode **head, char matrix[MAX_COL][MAX_ROW], int m, int n, struct Coords end)
{
    struct Coords new_coords;
    struct Coords *new_parent = (struct Coords *)malloc(sizeof(struct Coords));
    *new_parent = *coords;
    if (matrix[coords->x + 1][coords->y] != '#' && matrix[coords->x + 1][coords->y] != '0' && coords->x + 1 < m)
    {
        new_coords.x = coords->x + 1;
        new_coords.y = coords->y;
        new_coords.g = coords->g + 1;
        new_coords.h = manhattanDistance(new_coords, end);
        new_coords.parent = new_parent;
        if (isSameCoords(new_coords, end))
        {
            return 1;
        }
        enqueue_astar(new_coords, head);
    }
    if (matrix[coords->x][coords->y + 1] != '#' && matrix[coords->x][coords->y + 1] != '0' && coords->y + 1 < n)
    {
        new_coords.x = coords->x;
        new_coords.y = coords->y + 1;
        new_coords.g = coords->g + 1;
        new_coords.parent = new_parent;
        new_coords.h = manhattanDistance(new_coords, end);
        if (isSameCoords(new_coords, end))
        {
            return 1;
        }
        enqueue_astar(new_coords, head);
    }
    if (matrix[coords->x - 1][coords->y] != '#' && matrix[coords->x - 1][coords->y] != '0' && coords->x - 1 >= 0)
    {
        new_coords.x = coords->x - 1;
        new_coords.y = coords->y;
        new_coords.g = coords->g + 1;
        new_coords.parent = new_parent;
        new_coords.h = manhattanDistance(new_coords, end);
        if (isSameCoords(new_coords, end))
        {
            return 1;
        }
        enqueue_astar(new_coords, head);
    }
    if (matrix[coords->x][coords->y - 1] != '#' && matrix[coords->x][coords->y - 1] != '0' && coords->y - 1 >= 0)
    {
        new_coords.x = coords->x;
        new_coords.y = coords->y - 1;
        new_coords.g = coords->g + 1;
        new_coords.parent = new_parent;
        new_coords.h = manhattanDistance(new_coords, end);
        if (isSameCoords(new_coords, end))
        {
            return 1;
        }
        enqueue_astar(new_coords, head);
    }
    return 0;
}

// Algoritma A*
int aStar(char matrix[MAX_COL][MAX_ROW], int m, int n, struct Coords start, struct Coords end)
{
    int distance = manhattanDistance(start, end);

    printf("Start: %d, %d\nEnd: %d, %d\n", start.x, start.y, end.x, end.y);
    printf("Distance: %d\n", distance);

    struct PriorityQueueNode *head = NULL;
    struct Coords *curr_coords = (struct Coords *)malloc(sizeof(struct Coords));
    *curr_coords = start;
    int found = 0;
    char matrix_original[MAX_COL][MAX_ROW];

    // Copy matriks original
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix_original[i][j] = matrix[i][j];
        }
    }

    found = addNeighbors(curr_coords, &head, matrix, m, n, end);
    while (head != NULL && !found)
    {
        // Priority queue debug, uncomment to show in output
        // printf("\n");
        // printf("Priority Queue: ");
        // struct PriorityQueueNode *print = head;
        // while (print != NULL)
        // {
        //     printf("(%d, %d, %d, %d) ", (print->coords).x, (print->coords).y, (print->coords).g, (print->coords).h);
        //     print = print->next;
        // }
        // printf("\n");
        matrix[curr_coords->x][curr_coords->y] = '0'; // tandai titik yang telah ditelusuri
        *curr_coords = dequeue_astar(&head);
        found = addNeighbors(curr_coords, &head, matrix, m, n, end);
    }

    if (!found)
    {
        printf("\nNo path found\n");
    }
    else
    { // Print result
        while (!isSameCoords(*curr_coords, start))
        {
            matrix_original[curr_coords->x][curr_coords->y] = 'V';
            *curr_coords = *(curr_coords->parent);
        }
        printf("\nFinal Path:\n");
        printMatrix(matrix_original, m, n);
    }
}

int main_astar()
{
    struct timeval time1; // Start time
    struct timeval time2; // Finish time
    long dt;              // Delta time (us)

    int m = 18, n = 23;
    char matrix[MAX_COL][MAX_ROW] = {
        {'S', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '#', '.'},
        {'.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.', '#', '.', '#', '.', '.', '#', '.', '#', '.'},
        {'.', '#', '#', '.', '.', '.', '#', '.', '.', '#', '#', '#', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '#', '#', '.', '.', '#', '.', '.', '.', '.', '#', '.', '#', '#', '.', '.', '.', '#', '#', '.'},
        {'#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#'},
        {'.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '#', '.', '.'},
        {'#', '#', '#', '.', '.', '#', '#', '.', '.', '#', '#', '#', '.', '.', '.', '.', '#', '#', '#', '.', '.', '#', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '#', '#', '.', '.', '#', '.', '.', '.', '.', '#', '.', '#', '#', '.', '.', '.', '#', '#', '#'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'#', '#', '#', '.', '.', '.', '#', '.', '.', '#', '#', '#', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#', '#', '#'},
        {'.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.'},
        {'.', '.', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'E', '.', '.'},
    };

    struct Coords start = findStart(matrix, m, n);
    struct Coords end = findEnd(matrix, m, n);

    gettimeofday(&time1, NULL);
    aStar(matrix, m, n, start, end);
    gettimeofday(&time2, NULL);
    dt = (time2.tv_sec - time1.tv_sec) * 1000000 + time2.tv_usec - time1.tv_usec;
    printf("Done.\n");
    printf("A-Star took %d us.", dt);

    return 0;
}