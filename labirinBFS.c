#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ROW 225

// Struct untuk menyimpan koordinat
typedef struct {
    int x;
    int y;
} Point;

// Struct untuk queue yang digunakan pada BFS 
typedef struct {
    Point coordinate;
    int dist;
} queueNode;

// Queue untuk BFS
typedef struct {
    int front, rear, size;
    unsigned capacity;
    queueNode* array;
} Queue;

// Create Queue
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (queueNode*)malloc(queue->capacity * sizeof(queueNode));
    return queue;
}

// Queue isFull
bool isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

// Queue is empty 
bool isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, queueNode item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

queueNode dequeue(Queue* queue) {
    queueNode item = { {-1, -1}, -1 };
    if (isEmpty(queue)) {
        return item;
    }
    item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Fungsi untuk menemukan ukuran matriks
void findSize(FILE* file, int* col, int* row) {
    char line[ROW];
    *row = 0, *col = 0;

    while (fgets(line, sizeof(line), file)) {
        (*row)++;
        if (*row == 1) {
            char* token = strtok(line, " \t\n");
            while (token != NULL) {
                (*col)++;
                token = strtok(NULL, " \t\n");
            }
        }
    }
}

// Membaca dan mapping matrix
void readMatrix(char** Map, FILE* file, int rows, int columns) {
    char c;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            do {
                c = fgetc(file);
            } while (c == ' ' || c == '\n' || c == '\t');
            Map[i][j] = c;
        }
    }
}

// Menemukan source dan destination
void findStartStop(char** Map, int rows, int columns, int* startRow, int* startCol, int* stopRow, int* stopCol) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Map[i][j] == 'S') {
                *startRow = i;
                *startCol = j;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Map[i][j] == 'E') {
                *stopRow = i;
                *stopCol = j;
            }
        }
    }
}

// Mengecek vertex valid atau tidak
bool isValid(int row, int col, int rows, int columns) {
    return (row >= 0) && (row < rows) && (col >= 0) && (col < columns);
}

// BFS untuk menemukan jalur terpendek
int BFS(char** Map, Point src, Point dest, int rows, int columns, int** visited, Point** parent) {
    if (Map[src.x][src.y] == '#' || Map[dest.x][dest.y] == '#')
        return -1;

    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    Queue* queue = createQueue(rows * columns);
    queueNode s = {src, 0};
    enqueue(queue, s);
    visited[src.x][src.y] = 1;

    while (!isEmpty(queue)) {
        queueNode curr = dequeue(queue);
        Point pt = curr.coordinate;

        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;

        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col, rows, columns) && Map[row][col] != '#' && !visited[row][col]) {
                visited[row][col] = 1;
                parent[row][col] = pt;
                queueNode Adjcell = {{row, col}, curr.dist + 1};
                enqueue(queue, Adjcell);
            }
        }
    }

    return -1;
}

// Fungsi untuk nge-print path
void printPath(Point** parent, Point dest, char** pathMatrix) {
    Point curr = dest;
    while (parent[curr.x][curr.y].x != -1 && parent[curr.x][curr.y].y != -1) {
        pathMatrix[curr.x][curr.y] = '1';
        curr = parent[curr.x][curr.y];
    }
}

int main() {
    // Input nama file
    char fileName[50];
    printf("Masukkan File TXT Struktur Maze: ");
    scanf("%s", fileName);

    // Membuka file
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File tidak bisa dibuka.\n");
        return 1;
    }

    // Menemukan ukuran matriks
    int rows, columns;
    findSize(file, &columns, &rows);
    printf("File memiliki %d baris dan %d kolom\n", rows, columns);
    fclose(file);

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File tidak bisa dibuka.\n");
        return 1;
    }

    // Mapping matrix
    char** Map = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        Map[i] = (char*)malloc(columns * sizeof(char));
    }
    readMatrix(Map, file, rows, columns);
    fclose(file);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c", Map[i][j]);
        }
        printf("\n");
    }

    // Mencari source dan destination
    int startRow, startCol, stopRow, stopCol;
    findStartStop(Map, rows, columns, &startRow, &startCol, &stopRow, &stopCol);
    printf("Start point: %d, %d\n", startCol, startRow);
    printf("Stop point: %d, %d\n", stopCol, stopRow);

    Point source = {startRow, startCol};
    Point dest = {stopRow, stopCol};

    // Alokasi memori untuk matriks visited
    int** visited = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        visited[i] = (int*)malloc(columns * sizeof(int));
        memset(visited[i], 0, columns * sizeof(int));
    }

    Point** parent = (Point**)malloc(rows * sizeof(Point*));
    for (int i = 0; i < rows; i++) {
        parent[i] = (Point*)malloc(columns * sizeof(Point));
        for (int j = 0; j < columns; j++) {
            parent[i][j].x = -1;
            parent[i][j].y = -1;
        }
    }

    // Menghitung jarak terpendek
    int dist = BFS(Map, source, dest, rows, columns, visited, parent);

    // Alokasi memori untuk menampilkan path
    char** pathMatrix = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        pathMatrix[i] = (char*)malloc(columns * sizeof(char));
        memset(pathMatrix[i], '0', columns * sizeof(char));
    }

    // Mengeset jalur yang dilewati menjadi 1 dan 0 ketika tidak dilalui
    if (dist != -1) {
        printPath(parent, dest, pathMatrix);
        pathMatrix[source.x][source.y] = '1'; 
        printf("Shortest Path is %d\n", dist);
    } else {
        printf("Shortest Path doesn't exist\n");
    }

    // Menampilkan jarak terpendek
    printf("Path Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", pathMatrix[i][j]);
        }
        printf("\n");
    }

    // Free memori
    for (int i = 0; i < rows; i++) {
        free(Map[i]);
        free(visited[i]);
        free(parent[i]);
        free(pathMatrix[i]);
    }
    free(Map);
    free(visited);
    free(parent);
    free(pathMatrix);

    return 0; 
}
