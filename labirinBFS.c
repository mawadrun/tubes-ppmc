#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "definisiFungsi.h"

#define ROW 255
#define COL 255

// Struct untuk menyimpan koordinat
typedef struct {
    int x;  
    int y;
} Point_bfs;

// Struct untuk node antrian
typedef struct Qnode {
    Point_bfs node;
    struct Qnode* next;
} Qnode;

// Queue untuk BFS
typedef struct {
    Qnode *front, *rear;
} Queue;

// Create Queue
Queue* createQueue(){
    Queue* que = (Queue*)malloc(sizeof(Queue));
    que->front = que->rear = NULL;
    return que;
}

// Enqueue
void enQueue(Queue* que, Point_bfs point){
    Qnode *temp = (Qnode*)malloc(sizeof(Qnode));
    temp->node = point;
    temp->next = NULL;
    if (que->rear == NULL) {
        que->front = que->rear = temp;
        return;
    }
    que->rear->next = temp;
    que->rear = temp;
}

// Dequeue
Point_bfs deQueue(Queue* que){
    if (que->front == NULL) {
        return (Point_bfs){-1, -1};
    }
    Qnode* temp = que->front;
    Point_bfs point = temp->node;
    que->front = que->front->next;
    if (que->front == NULL) {
        que->rear = NULL;
    }
    free(temp);
    return point;
}


bool isEmpty(Queue* que) {
    return (que->front == NULL);
}

// Menemukan source dan destination
void findStartStop(char Map[ROW][COL], int rows, int columns, int* startRow, int* startCol, int* stopRow, int* stopCol) { 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Map[i][j] == 'S') {
                *startRow = i;
                *startCol = j;
            }
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
int BFS(char Map[ROW][COL], Point_bfs source, Point_bfs destination, int row, int col)  {
    bool visited[row][col];
    Point_bfs parent[row][col];
    int stepCount[row][col];
    for(int i = 0; i < row; i++){
        for(int j =  0; j < col; j++){
            visited[i][j] = false; 
            parent[i][j] = (Point_bfs){-1, -1};
            stepCount[i][j] = 0; 
        }
    }

    Queue* que = createQueue(); 
    enQueue(que, source);
    visited[source.x][source.y] = true;

    int rowNum[] = {-1, 0, 0, 1};
    int colNum[] = {0, -1, 1, 0};

    while(!isEmpty(que)){
        Point_bfs curr = deQueue(que); 
        if((curr.x == destination.x) && (curr.y == destination.y)) {
            // Menandai jalur dari tujuan ke sumber
            Point_bfs trace = curr;
            while(parent[trace.x][trace.y].x != -1 && parent[trace.x][trace.y].y != -1){

                Map[trace.x][trace.y] = 'V';

                trace = parent[trace.x][trace.y];
            }

            Map[source.x][source.y] = 'V';
            Map[destination.x][destination.y] = 'V';
            free(que);
            return stepCount[curr.x][curr.y];
        }

        for (int i = 0; i < 4; i++){
            int newRow = curr.x + rowNum[i];
            int newCol = curr.y + colNum[i];
            if(isValid(newRow, newCol, row, col) && Map[newRow][newCol] != '#' && !visited[newRow][newCol]){
                visited[newRow][newCol] = true; 
                parent[newRow][newCol] = curr; 
                enQueue(que, (Point_bfs){newRow, newCol});
                stepCount[newRow][newCol] = stepCount[curr.x][curr.y] + 1;
            }
        }
    }    
    free(que);
    return -1;
}

int main_bfs() {
    // // Input nama file
    // char fileName[50];
    // printf("Masukkan File TXT Struktur Maze: ");
    // scanf("%s", fileName);

    // // Membuka file
    // FILE* file = fopen(fileName, "r");
    // while(file == NULL){
    //     printf("File tidak bisa dibuka.\n");
    //     printf("Masukkan nama file yang dapat dibaca : ");
    //     scanf("%s", fileName);
    //     file = fopen(fileName, "r");
    // }

    // Mapping file .txt dan menghitung baris serta kolom dan menghitung baris
    // int row = 0;
    // char Map[ROW][COL];
    // while(fgets(Map[row], 255, file)){
    //     row++;
    // }

    // // Menhitung Kolom
    // int col = 0; 
    // while(Map[0][col] != '\0'){
    //     col++;
    // }
    // col = col-1;

    // printf("Maze : \n");
    // for(int i = 0; i<row; i++){
    //     printf("%s", Map[i]);
    // }
    // printf("\n");
    // printf("\n");
    // Mencari source dan destination
    // int startRow, startCol, stopRow, stopCol;
    // findStartStop(Map, row, col, &startRow, &startCol, &stopRow, &stopCol);
    // printf("Start point: %d, %d\n", startRow, startCol);
    // printf("Stop point: %d, %d\n", stopRow,startCol);
    // printf("\n");

    // Point_bfs source = {startRow, startCol};
    // Point_bfs dest = {stopRow, stopCol};

    clock_t startTime, stopTime; 
    double cpu_time_used;
    // startTime = clock();
    // int step = BFS(Map, source, dest, row, col);
    // stopTime = clock();
    // printf("Shortest path : %d steps\n", step);
    // if (step != 1){
    //     printf("Shortest path : \n");
    //     for(int i = 0; i< row; i++){
    //         for(int j = 0; j<col; j++){
    //             if(Map[i][j] == 'V' || Map[i][j] == 'S' || Map[i][j] == 'E'){
    //                 printf("%c", Map[i][j]);
    //             }
    //             else if(Map[i][j] == '.'){
    //                 printf(".");
    //             } else{
    //                 printf("#");
    //             }
    //         }
    //         printf("\n");
    //     }
    // }
    // else{
    //     printf("Tidak ada jalur.\n");
    // }

    cpu_time_used = ((double)stopTime-startTime)/CLOCKS_PER_SEC;
    printf("Waktu yang diperlukan untuk mencari rute : %f detik", cpu_time_used);
    return 0; 
}