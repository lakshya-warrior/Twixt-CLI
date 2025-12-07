#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headerfile.h"
#include "board.h"
#include "logic.h"

const int tocheckmoves[][2] = {{1,2}, {1,-2}, {2, 1}, {2, -1}, {-1, 2}, {-1,-2}, {-2,1}, {-2,-1}};

int max(int a, int b){
    if (a > b) return a;
    return b;
}
int min(int a, int b){
    if (a > b) return b;
    return a;
}

int checkpoint(int x, int y, char* player){

    if (x < 0 || x >= size || y < 0 || y >= size) return 0;

    if (strcmp(board[x][y], ".")!=0) return 0;
    
    if (strcmp(player, player1) == 0){
        if (y>0 && y<size-1) return 1;
        else return 0;
    }
    else {
        if (x>0 && x< size - 1) return 1;
        else return 0;
    }
}

int getinput(char* player, links** alllinks){
    int x, y;
    printf("Player \"%s\" turn\nEnter coordinates (%sx %sy%s)(q for quit): ", player, RGB(173, 216, 230), RGB(255, 255, 186), RESET);
    if (scanf("%d %d", &x, &y) == 2) {
        char excesschar[201];
        fgets(excesschar, 201, stdin);

        if (checkpoint(x,y, player)){
            board[x][y] = player;
            printboard();
            if (x==0) redtop = 1;
            if (y==0) blackleft = 1;
            if (x==size-1) redbottom = 1;
            if (y==size-1) blackright = 1;
            printf("Placed \"%s\" peg on the point (%d, %d)\n", player, x, y);

            for (int i = 0; i < 8; i++) {
                int checkingx = x+tocheckmoves[i][0];
                int checkingy = y+tocheckmoves[i][1];
                if (checkingx >= 0 && checkingx < size && checkingy >= 0 && checkingy < size){
                    if (strcmp(board[checkingx][checkingy], player)==0) {
                        printf("A Link is POSSIBLE between (%d,%d) and (%d,%d)\n", x,y,checkingx,checkingy);
                        float slope = (float)tocheckmoves[i][1]/(float)tocheckmoves[i][0];
                        linkpossble(checkingx,checkingy, x, y, slope, alllinks);
                    }
                }
            }
            return 1;
        }
        else {
            printf("%sCANNOT PLace There!%s\n", YELLOW, RESET);
            return 0;
        }
    }
    else{
        printf("%swrong input%s\n", YELLOW, RESET);
        return -1;
    }
}
// const int blackwin[][2] = {{-2,1},{-1, 2}, {1, 2}, {2,1}};
int checkwinblack(int x, int y,links alllinks[], int memob[][size]){
    
    if (y == size-1) return memob[x][y] = 1;
    if (memob[x][y]!=-1) return memob[x][y];
    memob[x][y] = 0;
    
    for (int i = 0; i < 8; i++) {
        int checkx = x + tocheckmoves[i][0];
        int checky = y + tocheckmoves[i][1];
        if (checkx >= 0 && checkx <= size-1 && checky<=size-1 && checky >= 0){
            if (strcmp(board[checkx][checky], player2) == 0){
                for (int k = 0; k < numberoflinks; k++) {
                    if ((alllinks[k].x1 == x || alllinks[k].x2 == x) && (alllinks[k].x1 == checkx || alllinks[k].x2 == checkx) && (alllinks[k].y1 == y || alllinks[k].y2 == y) && (alllinks[k].y1 == checky || alllinks[k].y2 == checky)) {
                        if (checkwinblack(checkx, checky, alllinks, memob) == 1) {
                            return memob[x][y] = 1;
                        }
                        break;
                    }
                }
            }
        }
    }  
return memob[x][y] = 0;
}

// const int redwin[][2] = {{1,-2},{1, 2}, {2, -1}, {2,1}};
int checkwinred(int x, int y,links alllinks[], int memor[][size]){
    
    if (x == size-1) return memor[x][y] = 1;
    if (memor[x][y]!=-1) return memor[x][y];
    memor[x][y] = 0;
    
    for (int i = 0; i < 8; i++){
        int checkx = x + tocheckmoves[i][0];
        int checky = y + tocheckmoves[i][1];
        if (checky > 0 && checky < size-1 && checkx <= size-1 && checkx >=0){
            if (strcmp(board[checkx][checky], player1) == 0) {

                for (int k = 0; k < numberoflinks; k++) {
                    if ((alllinks[k].x1 == x || alllinks[k].x2 == x) && (alllinks[k].x1 == checkx || alllinks[k].x2 == checkx) && (alllinks[k].y1 == y || alllinks[k].y2 == y) && (alllinks[k].y1 == checky || alllinks[k].y2 == checky)) {
                        if (checkwinred(checkx, checky, alllinks,memor) == 1) {
                            return memor[x][y] = 1;
                        }
                        break;
                    }
                }   
            }
        }
    }    
return memor[x][y] = 0;
}


int linkpossble(int x1, int y1, int x2, int y2, float givenslope, links** alllinks){
    for (int i = 0; i < numberoflinks; i++) {
        // I know both the points and slpoes of the links
        if ((*alllinks)[i].slope == givenslope){
            if (((*alllinks)[i].x1 == x1 || (*alllinks)[i].x1 == x2) && ((*alllinks)[i].y1 == y1 || (*alllinks)[i].y1 == y2) && ((*alllinks)[i].x2 == x1 || (*alllinks)[i].x2 == x2) && ((*alllinks)[i].y2 == y1 || (*alllinks)[i].y2 == y2)){
                printf("Link already there!\n");
                return 0;
            }
        }
        else {
            double intersectionx = (double)((float)y1 - givenslope*(float)x1 - (float)(*alllinks)[i].y1 + (*alllinks)[i].slope*(float)(*alllinks)[i].x1)/(double)((*alllinks)[i].slope - givenslope);
            double intersectiony = (double)(givenslope*intersectionx + ((float)y1 - givenslope*(float)x1));

            //printf("%d %d %d %d Number of linkes: %d\n", x1, y1, (*alllinks)[i].x1, (*alllinks)[i].y1, numberoflinks);
            // printf("y: %f, x: %f is SLOPE is: %f\n", intersectiony, intersectionx, givenslope);

            int check2 = (intersectionx > min((*alllinks)[i].x1, (*alllinks)[i].x2) && intersectionx < max((*alllinks)[i].x1, (*alllinks)[i].x2));
            int check1 = (intersectiony > min((*alllinks)[i].y1, (*alllinks)[i].y2) && intersectiony < max((*alllinks)[i].y1, (*alllinks)[i].y2));

            if ((intersectionx > min(x1, x2) && intersectionx < max(x1, x2)) && (intersectiony > min(y1, y2) && intersectiony < max(y1, y2)) && check2 && check1) {
                printf("It is Intersecting Another link!\n%sLink CANNNOT be made!%s\n", YELLOW, RESET);
                return 0;
            }
        }
    }
    printf("%sLINK MADE!%s\n", GREEN, RESET);
    if (numberoflinks >= linksize) {
        *alllinks= realloc(*alllinks, 2*linksize*sizeof(links));
        // *alllinks = temp;
        linksize *= 2;
    }

    (*alllinks)[numberoflinks].x1 = x1;
    (*alllinks)[numberoflinks].x2 = x2;
    (*alllinks)[numberoflinks].y1 = y1;
    (*alllinks)[numberoflinks].y2 = y2;
    (*alllinks)[numberoflinks].slope = givenslope;
    numberoflinks++;
  return 1;  
}

// int main(){

//     for (int i = 0; i < size; i++)
// {
//     for (int j = 0; j < size; j++)
//     {
//         printf("%d", memor[i][j]);
//     }
    
// }

// return 0;
// }