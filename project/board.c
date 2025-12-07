#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headerfile.h"
#include "board.h"
#include "logic.h"

void printboard(){
    printf("%sx%s\\%sy0 1%s  ", RGB(173, 216, 230), RESET, RGB(255, 255, 186), RESET);
    for (int i = 2; i < size; i++) {
        if (i < 10) printf("%s%d%s  ",RGB(255, 255, 186), i, RESET);
        else printf("%s%d%s ", RGB(255, 255, 186), i, RESET);
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        if (i == 1) {
            printf(" ");
            for (int i = 0; i < size; i++) printf("%s---", RED);
            printf("%s\n", RESET);
        }
        if (i==0 || i == size-1) printf("%s%02d%s  %s|%s", RGB(173, 216, 230), i,RESET, BLACK, RESET);
        else printf("%s%02d%s %s%s|%s", RGB(173, 216, 230), i,RESET, board[i][0], BLACK, RESET);

        for (int j = 1; j < size-2; j++)
        {
            printf("%s  ", board[i][j]);
        }
        if (i == 0 || i == size-1) printf("%s%s|%s  ", board[i][size-2],BLACK, RESET);
        else printf("%s%s|%s %s", board[i][size-2],BLACK, RESET, board[i][size-1]);

        printf("\n");
        if (i == size-2) {
            printf(" ");
            for (int i = 0; i < size; i++) printf("%s---", RED);
            printf("%s\n", RESET);
        }
    }
}


links* genboard(int memor[][size], int memob[][size]){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ".";
        }  
    }
    links* alllinks = (links*)malloc(linksize*sizeof(links));

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
        {
            memor[i][j] = -1;
            memob[i][j] = -1;
        }
    }
    return alllinks;
}

void memo_reset(int memob[][size], int memor[][size]){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            //memo reset
            if (memor[i][j] == 0) memor[i][j] = -1;
            if (memob[i][j] == 0) memob[i][j] = -1;
        }
    }
}
