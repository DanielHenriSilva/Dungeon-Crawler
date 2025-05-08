#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define linha 10
#define coluna 10
char mapa[linha][coluna];

void mapa1(void)
{

    int i = 0, j;

    while (i < linha)
    {
        j = 0;
        while (j < coluna)
        {
            
            mapa[i][j] = '.';
            j++;
        }
        
        i++;
    }
    
    mapa[1][1] = '&';
    mapa[4][5] = 'P';
    mapa[8][8] = 'x';

    i = 0;
    j = 0;

    while (i < linha)
    {
        j = 0;
        while (j < coluna)
        {
            
            if (i == 0 || i == linha-1 || j == 0 || j == coluna-1)
            {
                
                printf("# ");

            }

            else
            {

                printf("%c ", mapa[i][j]);

            }
            
            j++;
        }
        
        printf("\n");

        i++;
    
    }

}

void input (void)
{
    char input;
    int px = 1, py = 1; //Possição Inicial Do Personagem
    mapa[px][py] = '&';
    
    do
    {
        system("cls");
        mapa1();

        input = getch();
        mapa[px][py] = '.';

        switch (input)
        {
        case 'd': case 'D':

            if (py < linha - 2 && mapa[px][py+1] != '#')
            {
                py++;
            }
        

            break;
        
        default:
            break;
        }


    } while (input != 'q' && input != 'Q');
    
}


int main (void)
{

    input();
    
    
    
    return 0;
}