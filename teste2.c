#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define linha 10
#define coluna 10
int px = 1, py = 1;

void mapa1 (char mapa[linha][coluna])
{
    int i = 0, j;

    while (i < linha)
    {
        j = 0;
        while (j < coluna)
        {
            if (i == 0 || i == linha - 1 || j == 0 || j == coluna - 1)
            {
                mapa[i][j] = '#';
            }
            
            else
            {
                mapa[i][j] = '.';
            }

            j++;
        }
        
        i++;
    }

    mapa[px][py] = '&'; //Personagem
    mapa[5][5] = 'P'; //NPC

}


int main (void)
{
    char mapa[linha][coluna];
    int px = 1, py = 1;
    char input;
    int i, j;

    mapa1(mapa);

    while (1)
    {
            
        system("cls");

        i  = 0;
        while (i < linha)
        {
            j = 0;
            while (j < coluna)
            {
                printf("%c ", mapa[i][j]);
                j++;
            }

            printf("\n");
            i++;            

        }
        
        input = getch();

        mapa[px][py] = '.';

        switch (input)
        {
        case 'd': case 'D':
            if (py < coluna - 2 && mapa[px][py+1] != '#')
            {
                py++;
            }
            break;

        case 'a': case 'A':

            if (py < linha + 2 && mapa[py][py-1] != '#')
            {
                py--;
            }
        
        default:
            break;
        }

        mapa[px][py] = '&';

    }
    
    return 0;
}