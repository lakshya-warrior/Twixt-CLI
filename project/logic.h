#ifndef LOgic
#define LOgic
#include "headerfile.h"

int checkpoint(int x, int y, char* player);
int getinput(char* player, links** alllinks);
int linkpossble(int x1, int y1, int x2, int y2, float givenslope, links** alllinks);
int checkwinblack(int x, int y,links alllinks[], int memob[][size]);
int checkwinred(int x, int y,links alllinks[], int memor[][size]);

#endif