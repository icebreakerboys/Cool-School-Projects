#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int nextArr[20][30];
int array[20][30];

void displayGrid();
void updateGrid();
void updateCell();
void switchArrays();

void main()
{
    srand(time(NULL));
    for(int i = 0; i < 20; i++){
         for(int j = 0; j < 30; j++){
              array[i][j] = rand() % 2;
         }
    }
	
    updateGrid();
}

void displayGrid(){
    //system(“clear”);
    for(int i = 0; i < 20; i++){
        printf("(");
        for(int j = 0; j < 30; j++){
            if (array[i][j] == 0){
                    printf(" ");
            }else{
                    printf("*");
            }
        }
        printf(")\n");
    }
    printf("\n");
	
    sleep(1);
    
}

void updateCell(int x, int y){
    int aliveNeighbours = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if((x+i>=0 && x+i<20) && (y+j>=0 && y+j<30)){
                aliveNeighbours = aliveNeighbours + array[x + i][y + j];
            }
        }
    }
    aliveNeighbours -= array[x][y];
    
    if((array[x][y] == 1) && (aliveNeighbours < 2)){
        nextArr[x][y] = 0;
    } else if((array[x][y] == 1) && (aliveNeighbours > 3)){
        nextArr[x][y] = 0;
    } else if((array[x][y] == 0) && (aliveNeighbours == 3)){
        nextArr[x][y] = 1;
    } else {
        nextArr[x][y] = array[x][y];
    }
}

void switchArrays(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j++){
            array[i][j] = nextArr[i][j];
        }
    }
}

void updateGrid(){
    displayGrid();
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j++){
            updateCell(i, j);
        }
    }
    switchArrays();
    updateGrid();
}

