#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headerfile.h"
#include "board.h"
#include "logic.h"

char* board[size][size];
int gameover = 0, redtop = 0, redbottom = 0, blackleft = 0, blackright=0, linksize = 20, numberoflinks = 0;
int memob[size][size];
int memor[size][size];

int main(){
    links* alllinks = genboard(memor,memob);
    char* player = player1;
    char string[100];
    printboard();

    while (gameover==0) {
        memo_reset(memob, memor);
        int x = getinput(player, &alllinks);
        if (x==1 && strcmp(player, player1) == 0){ // red
            if(redbottom == 1 && redtop == 1){
                for (int i = 1; i < size; i++) {
                    if (strcmp(board[0][i], player1) == 0){
                        if(checkwinred(0,i, alllinks, memor) == 1){
                            // gameover = 1;
                            // printboard();
                            printf("PLAYER %s WINS!\n", player);
                            free(alllinks);
                            return 0;
                        }
                    }
                }
                
            }
            player = player2;
        }
        else if (x == 1 && strcmp(player, player2) == 0){ //black
            if(blackleft == 1 && blackright == 1){
                for (int i = 1; i < size; i++) {
                    if (strcmp(board[i][0], player2) == 0){
                        if(checkwinblack(i,0, alllinks, memob) == 1){
                            // gameover = 1;
                            // printboard();
                            printf("PLAYER %s WINS!\n", player);
                            free(alllinks);
                            return 0;
                        }
                    }
                }
                
            }
            player = player1;
        }

        else if (x==-1){
            scanf("%s", string);
            if (strcmp(string, "quit") == 0 || strcmp(string,"q")==0 || strcmp(string,"Q")==0 ||strcmp(string, "Quit") == 0){
                free(alllinks);
                printf("%sExiting%s\n", GREEN, RESET);
                return 0;
            }
        }
    }
free(alllinks);
return 0;
}