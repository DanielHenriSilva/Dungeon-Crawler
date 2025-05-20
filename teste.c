#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define key_up 119
#define key_down 115
#define enter 13

int selecionar = 0; // 0=Play, 1=Help, 2=Exit

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

    i = 0;
    while (i < 2)
    {
        printf("\n");
        i++;
    }
    
    printf("\033[1;31m");
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
    
    printf("%*s%s\n", 81, selecionar == 0 ? "\033[1;31m" : "\033[0m", "Play");
    printf("\033[0m");

    printf("%*s%s\n", 80, selecionar == 1 ? "\033[1;31m" : "\033[0m", "Credit");
    printf("\033[0m");

    printf("%*s%s\n", 81, selecionar == 2 ? "\033[1;31m" : "\033[0m", "Exit");
    printf("\033[0m");
}

void entradamenu (void)
{
    int input = getch();    

    switch(input) {
        case key_up:
            if (selecionar > 0) selecionar--;
            else selecionar = 2;
            break;
        case key_down:
            if (selecionar < 2) selecionar++;
            else selecionar = 0;
            break;
  
    }


}

void entrada (void)
{
    char input;
    input = getch();
    printf("%c", input);
    
}

int main(void)
{
    while (1)
    {
        menu();
        entradamenu();
        system("cls");
    }



}
