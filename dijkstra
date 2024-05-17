#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 236

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pt;
    int dist;
} Node;


int dx[] = { 0, -1, 1, 0 }; // atas, kiri, kanan, bawah
int dy[] = { 1, 0, 0, -1 }; // atas, kiri, kanan, bawah

int isValid(int x, int y, int rows, int cols) {
    return (x >= 0 && y >= 0 && x < rows && y < cols);
}

int dijkstra(char maze[MAX][MAX], int rows, int cols, Point start, Point end) {
    int dist[MAX][MAX];
    int visited[MAX][MAX];
    Point prev[MAX][MAX];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dist[i][j] = INT_MAX;
            visited[i][j] = 0;
            prev[i][j] = (Point){-1, -1};
        }
    }

    dist[start.x][start.y] = 0;
    Node minHeap[MAX * MAX];
    int heapSize = 0;

    minHeap[heapSize++] = (Node){ start, 0 };

    while (heapSize > 0) {
        Node minNode = minHeap[0];
        minHeap[0] = minHeap[--heapSize];
        int i = 0;
        while (i * 2 + 1 < heapSize) {
            int j = i * 2 + 1;
            if (j + 1 < heapSize && minHeap[j + 1].dist < minHeap[j].dist) {
                j++;
            }
            if (minHeap[i].dist < minHeap[j].dist) {
                break;
            }
            Node temp = minHeap[i];
            minHeap[i] = minHeap[j];
            minHeap[j] = temp;
            i = j;
        }

        Point u = minNode.pt;
        if (visited[u.x][u.y]) continue;
        visited[u.x][u.y] = 1;

        for (int k = 0; k < 4; k++) {
            int newX = u.x + dx[k];
            int newY = u.y + dy[k];
            if (isValid(newX, newY, rows, cols) && maze[newX][newY] != '#' && !visited[newX][newY]) {
                int alt = dist[u.x][u.y] + 1;
                if (alt < dist[newX][newY]) {
                    dist[newX][newY] = alt;
                    prev[newX][newY] = u;
                    minHeap[heapSize++] = (Node){ (Point){newX, newY}, alt };
                    i = heapSize - 1;
                    while (i > 0 && minHeap[(i - 1) / 2].dist > minHeap[i].dist) {
                        Node temp = minHeap[i];
                        minHeap[i] = minHeap[(i - 1) / 2];
                        minHeap[(i - 1) / 2] = temp;
                        i = (i - 1) / 2;
                    }
                }
            }
        }
    }

    if (dist[end.x][end.y] == INT_MAX) {
        printf("No path found\n");
        return 0;
    }

    printf("Shortest path using Dijkstra: ");
    Point path[MAX * MAX];
    int pathLen = 0;
    for (Point at = end; at.x != -1 && at.y != -1; at = prev[at.x][at.y]) {
        path[pathLen++] = at;
    }
    for (int i = pathLen - 1; i >= 0; i--) {
        printf("(%d, %d)", path[i].y, -path[i].x); //Asumsi kebawah (-) dan keatas (+)
        if (i > 0) printf(" -> ");
    }
    printf("\n");
    return 1;
}

int main() {
    char filename[20];
    printf("Nama file yang akan dibaca: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    char maze[MAX][MAX];
    int rows = 0, cols = 0;
    Point start = { -1, -1 }, end = { -1, -1 };

    char line[MAX];
    while (fgets(line, MAX, file)) {
        int col = 0;
        for (int j = 0; line[j] != '\0'; j++) {
            if (line[j] != ' ' && line[j] != '\n') {
                maze[rows][col] = line[j];
                if (line[j] == 'S') {
                    start = (Point){ rows, col };
                } else if (line[j] == 'E') {
                    end = (Point){ rows, col };
                }
                col++;
            }
        }
        if (col > cols) cols = col;
        rows++;
    }
    fclose(file);

    if (start.x == -1 || end.x == -1) {
        printf("Invalid maze, start or end point not found.\n");
        return EXIT_FAILURE;
    }

    dijkstra(maze, rows, cols, start, end);

    return EXIT_SUCCESS;
}
