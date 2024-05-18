#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "definisiFungsi.h"
#define MAX 236

typedef struct {
    int x, y;
} Point_dijkstra;

typedef struct {
    Point_dijkstra pt;
    int dist;
} Node;

int dx[] = { 0, -1, 1, 0 }; // atas, kiri, kanan, bawah
int dy[] = { 1, 0, 0, -1 }; // atas, kiri, kanan, bawah

int isValid_dijkstra(int x, int y, int rows, int cols) { //cek boundary
    return (x >= 0 && y >= 0 && x < rows && y < cols);
}

void printMaze(char maze[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

void markShortestPath(char maze[MAX][MAX], Point_dijkstra path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        if (maze[path[i].x][path[i].y] != 'S' && maze[path[i].x][path[i].y] != 'E') {
            maze[path[i].x][path[i].y] = '*';
        }
    }
}

int dijkstra(char maze[MAX][MAX], int rows, int cols, Point_dijkstra start, Point_dijkstra end) {
    int dist[MAX][MAX];
    int visited[MAX][MAX];
    Point_dijkstra prev[MAX][MAX];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dist[i][j] = INT_MAX;
            visited[i][j] = 0;
            prev[i][j] = (Point_dijkstra){-1, -1};
        }
    }

    dist[start.x][start.y] = 0; //start Point_dijkstra di 0
    Node minHeap[MAX * MAX]; //min heap untuk nodes
    int heapSize = 0;
    minHeap[heapSize++] = (Node){ start, 0 };

    while (heapSize > 0) { //ambil node dengan distance min
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

        Point_dijkstra u = minNode.pt;
        if (visited[u.x][u.y]) continue;
        visited[u.x][u.y] = 1;

        for (int k = 0; k < 4; k++) { //ke node tetangga
            int newX = u.x + dx[k];
            int newY = u.y + dy[k];
            if (isValid_dijkstra(newX, newY, rows, cols) && maze[newX][newY] != '#' && !visited[newX][newY]) {
                int alt = dist[u.x][u.y] + 1;
                if (alt < dist[newX][newY]) {
                    dist[newX][newY] = alt;
                    prev[newX][newY] = u;
                    minHeap[heapSize++] = (Node){ (Point_dijkstra){newX, newY}, alt };
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

    if (dist[end.x][end.y] == INT_MAX) { // kalo Point_dijkstra end gabisa di reach
        printf("No path found\n");
        return 0;
    }

    printf("Shortest path using Dijkstra: ");
    Point_dijkstra path[MAX * MAX]; 
    int pathLen = 0;
    for (Point_dijkstra at = end; at.x != -1 && at.y != -1; at = prev[at.x][at.y]) {
        path[pathLen++] = at;
    }
        for (int i = pathLen - 1; i >= 0; i--) { //print shortest path
        printf("(%d, %d)", path[i].y, path[i].x);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    // Mark the shortest path with '*'
    markShortestPath(maze, path, pathLen);

    return 1;
}

int main_dijkstra() {
    char filename[20];
    printf("Enter file name (something.txt): ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    char maze[MAX][MAX];
    int rows = 0, cols = 0;
    Point_dijkstra start = { -1, -1 }, end = { -1, -1 };

    char line[MAX];
    while (fgets(line, MAX, file)) {
        int col = 0;
        for (int j = 0; line[j] != '\0'; j++) {
            if (line[j] != ' ' && line[j] != '\n') {
                maze[rows][col] = line[j];
                if (line[j] == 'S') {
                    start = (Point_dijkstra){ rows, col };
                } else if (line[j] == 'E') {
                    end = (Point_dijkstra){ rows, col };
                }
                col++;
            }
        }
        if (col > cols) cols = col;
        rows++;
    }
    fclose(file);

    clock_t start_time = clock();
    int result = dijkstra(maze, rows, cols, start, end);
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", time_taken);

    if (result) {
        printf("Maze with shortest path marked:\n");
        printMaze(maze, rows, cols);
    }

    return EXIT_SUCCESS;
}

