#include <stdio.h>
#include <time.h>

#define MAX_ROW 256
#define MAX_COL 256

struct Coords
{
    int x, y;
};

int isInList(struct Coords val, struct Coords *list)
{
}

int aStar(char *matrix, int m, int n)
{
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
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
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