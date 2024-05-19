#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "definisiFungsi.h"

int findallpaths(int m, int n, char matrix[m][n], int prev[2], int current[2], int end[2], int trace[m][n]){
    int i, j, nextc[2], corner = 0, found[4], foundnode = 0;
    char next;

    int pref[4];
    
    //printf("%d , %d, %c\n", current[0], current[1], matrix[current[1]][current[0]]);

    for(i = 0; i < 4; i++){
        pref[i] = 0;
        found[i] = 0;
    }

// finding preference
// comparing x and y difference
    if(abs(current[0] - end[0]) > abs(current[1]- end[1])){

        pref[0] += 1;
        pref[2] += 1;

        if((current[0] - end[0]) > 0){
            pref[0] += 2;
        }
        else{
            pref[2] += 2;
        }

        if((current[1] - end[1]) < 0){
            pref[1] += 2;
        }
        else{
            pref[3] += 2;
        }
    }

    else{
        
        pref[1] += 1;
        pref[3] += 1;

        if((current[0] - end[0]) > 0){
            pref[1] += 2;
        }
        else{
            pref[3] += 2;
        }

        if((current[1] - end[1]) < 0){
            pref[0] += 2;
        }

        else{
            pref[2] += 2;
        }
    }
    

    if(matrix[current[1]][current[0]] != 'S'){
        matrix[current[1]][current[0]] = '-';
    }

    trace[current[1]][current[0]] += 1;


    if (current[1] != 0 && matrix[current[1] - 1][current[0]] == '#'){
        corner += 1;
    }
    if (current[0] != n-1 && matrix[current[1]][current[0] + 1] == '#'){
        corner += 1;
    }
    if (current[1] != m-1 && matrix[current[1] + 1][current[0]] == '#'){
        corner += 1;
    }
    if (current[0] != 0 && matrix[current[1]][current[0] - 1] == '#'){
        corner += 1;
    }

    for(i = 0; i < 4 && corner < 3 && trace[current[1]][current[0]] < 3; i++){
        if(pref[i] == 0 && current[1] != 0 && matrix[current[1] - 1][current[0]] != '#'){
            nextc[0] = current[0];
            nextc[1] = current[1] - 1;
            if(!(nextc[0] == prev[0] && nextc[1] == prev[1]))
            {next = matrix[nextc[1]][nextc[0]];
            if(next == '.' || next == '-'){
                found[0] = findallpaths(m, n, matrix, prev, nextc, end, trace);
            }
            if(next == 'E' || next == 'V'){
                found[0] = 1;
            }
            }
        
        }
        
        if(pref[i] == 1 && current[0] != n-1 && matrix[current[1]][current[0] + 1] != '#'){
            nextc[0] = current[0] + 1;
            nextc[1] = current[1];

            next = matrix[nextc[1]][nextc[0]];
            if(!(nextc[0] == prev[0] && nextc[1] == prev[1]))
            {if(next == '.'|| next == '-'){
                found[1] = findallpaths(m, n, matrix, prev, nextc, end, trace);

        }
            if(next == 'E' || next == 'V'){
                found[1] = 1;
            }
            }         
        }
        
        if(pref[i] == 2 && current[1] != m-1 && matrix[current[1] + 1][current[0]] != '#' ){
            nextc[0] = current[0];
            nextc[1] = current[1] + 1;
            
            if(!(nextc[0] == prev[0] && nextc[1] == prev[1])){
                next = matrix[nextc[1]][nextc[0]];  
                if(next == '.'|| next == '-'){
                    found[2] = findallpaths(m, n, matrix, prev, nextc, end, trace);
                }
                if(next == 'E' || next == 'V'){
                    found[2] = 1;
                }    
    }
             
        }
        
        if(pref[i] == 3 && current[0] != 0 && matrix[current[1]][current[0] - 1] != '#'){
            nextc[0] = current[0] - 1;
            nextc[1] = current[1];
            
                next = matrix[nextc[1]][nextc[0]]; 
            if(!(nextc[0] == prev[0] && nextc[1] == prev[1])){
                if(next == '.'|| next == '-'){
                    
                    found[3] = findallpaths(m, n, matrix, prev, nextc, end, trace);
                } 
                if(next == 'E' || next == 'V'){
                    found[3] = 1;
                }
            }  
        }       
        
        }
        
    for(i = 0; i < 4; i++){
        if(found[i] == 1){
            foundnode = 1;
        }
    }

    if(foundnode == 1 && matrix[current[1]][current[0]] != 'S'){
        matrix[current[1]][current[0]] = 'V';
    }

    //printf("%c\n", next);



    return foundnode;
}


int main_greedy(void) {
    int i = 0,j = 0, m = 1, n, start[2], end[2], prev[2];
    char filename[255], buff[255];
    


    // Inisialisasi file eksternal
    /*printf("Nama file yang akan dibaca: ");
    scanf("%s", filename);*/

    FILE* fp = fopen("Maze.txt", "r");
    while (fp == NULL){
        printf("File tidak bisa dibuka\n");
        printf("Nama file yang akan dibaca: ");
        scanf("%s", filename);
        fp = fopen(filename, "r");
    }

    


    fgets(buff, 255, fp);
    n = strlen(buff);

    while(!feof(fp)){
        fgets(buff, 255, fp);
        m += 1;
    }

    char matrix[m][n];
    int trace[m][n];

    fseek(fp, 0, SEEK_SET);

    for(i = 0; i < m; i ++){
        
        fgets(buff, 255, fp);
        for(j =0; j < n; j ++){
            matrix[i][j] = buff[j];
            trace[i][j] = 0;
        
        if(matrix[i][j] == 'S'){
            start[0] = j;
            
            start[1] = i;
            
        }
        if(matrix[j][i] == 'E'){
            end[0] = j;
            
            end[1] = i;
        }
        }
    }


    fclose(fp);

    /*    for(i = 0;i < m; i++){
        for(j = 0; j < n; j++){
            printf("%c",matrix[i][j]);
        }
    }
    printf("\n\n");*/

    prev[0] = -1;
    prev[1] = -1;

    findallpaths(m, n, matrix, prev, start, end, trace);

    /*for(i = 0;i < m; i++){
        for(j = 0; j < n; j++){
            printf("%c",matrix[i][j]);
        }
    }*/

    return 0;
}
