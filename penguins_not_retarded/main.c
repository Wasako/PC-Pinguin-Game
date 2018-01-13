#include <stdio.h>
#include <stdlib.h>

#define BOARDX  5
#define BOARDY  5
#define BOARDW  (BOARDX*2)              

char board [BOARDY][BOARDW+1];

void print_board(void)
{
    int y, x;
    
    printf("   ");
    for(x=0; x<BOARDX; x++)
        printf("%2d", x);
    printf("\n");
    
    
    printf("   ");
    for(x=0; x<BOARDX; x++)
        printf(" -");
    printf("\n");
    
    
    for(y=0; y<=BOARDY-1; y++) {
        printf("%-2d|%s\n", y, board[y]);
    }
    
    
   
}

int main(void)
{
 
    print_board();
    return 0;
}
