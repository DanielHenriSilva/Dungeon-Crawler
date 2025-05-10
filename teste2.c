#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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


void redesenharmapa1(char mapa[linha][coluna], int novopx, int novopy){

    if (novopx >= 0 && novopx < linha && novopy >= 0 && novopy < coluna && mapa[novopx][novopy] != '#')
    {

        mapa[px][py] = '.';
        COORD coord = {py * 2, px};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf(". ");

        px = novopx;
        py = novopy;
        mapa[px][py] = '&';

        coord.X = py * 2;
        coord.Y = px;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("& ");
    
    }

}

int main (void)
{
    char mapa[linha][coluna];
    char input;
    int i = 0, j;

    mapa1(mapa);

    CONSOLE_CURSOR_INFO cursorInfo = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    system("cls");
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

    while (1)
    {
        if (_kbhit())
        {

            input = _getch();

            switch (input)
            {
            case 'd': case 'D':
                redesenharmapa1(mapa, px, py+1);
            
                break;

            case 'a': case 'A':
                redesenharmapa1(mapa, px, py-1);
            
                break;

            case 's': case 'S':
                redesenharmapa1(mapa, px+1, py);
            
                break;
            
            case 'w': case 'W':
                redesenharmapa1(mapa, px-1, py);
            
                break;
        
            default:
                break;
            }   
        }
    }
    
    return 0;
}