#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define linha 10
#define coluna 10
int px = 1, py = 1;

void menu (void)
{
   
    int i = 0;
    while (i < 5)
    {
        printf("\n");
        i++;
    }
    
    printf("\033[1m");
    printf("\033[3m");
    printf("%*s\n", 83, "DUNGEONS\n");
    printf("%*s\n", 80, "Of\n");
    printf("\033[0m");
    printf("\033[1;31m");
    

    i = 0;
    while (i < 2)
    {
        printf("\n");
        i++;
    }

    printf("%*s\n", 119, "####  ####      ##  ######  ######   ########    ####      ##  ##      ##   ######");
    printf("%*s\n", 114, " ##   ## ##     ##  ##      ##       ##     ##   ## ##     ##  ##      ##  ##");
    printf("%*s\n", 114, " ##   ##  ##    ##  ##      ##       ##     ##   ##  ##    ##  ##      ##  ##");
    printf("%*s\n", 119, " ##   ##   ##   ##  ######  ######   ########    ##   ##   ##  ##      ##   ######");
    printf("%*s\n", 120, " ##   ##    ##  ##  ##      ##       ##    ##    ##    ##  ##  ##      ##        ##");
    printf("%*s\n", 120, " ##   ##     ## ##  ##      ##       ##     ##   ##     ## ##  ##      ##        ##");
    printf("%*s\n", 119, "####  ##      ####  ##      ######   ##      ##  ##      ####  ##########   ######");
    printf("\033[0m");

    i = 0;
    while (i < 3)
    {
        printf("\n");
        i++;
    }
    
    printf("\033[1m");
    printf("\033[3m");
    printf("%*s\n", 82, "Play\n");
    printf("%*s\n", 82, "Help\n");
    printf("%*s\n", 82, "Exit\n");
    printf("\033[0m");
    printf("\033[1;31m");
    
}

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