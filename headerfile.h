#ifndef TESTING
#define TESTING

typedef struct links{
    int x1;
    int y1;
    int x2;
    int y2; 
    float slope;
}links;

#define RED "\033[1;31m"
#define RESET "\033[0m"
#define BLACK "\x1b[1;30m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RGB(r,g,b) "\x1b[38;2;" #r ";" #g ";" #b "m"

#define size 24
#define player1 "\033[1;31mR\033[0m" 
#define player2 "\x1b[1;30mB\033[0m"
extern char* board[size][size];
extern int redtop, redbottom, blackleft, blackright,linksize, numberoflinks;

void memo_reset(int memob[][size], int memor[][size]);

#endif