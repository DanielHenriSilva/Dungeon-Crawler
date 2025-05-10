#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 

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
    
    printf("\033[1m");
    printf("\033[3m");
    printf("%*s\n", 82, "Play\n");
    printf("%*s\n", 82, "Help\n");
    printf("%*s\n", 82, "Exit\n");
    printf("\033[0m");
    printf("\033[1;31m");
    
}

void entrada (void)
{
    char input;
    input = getch();
    printf("%c", input);
    
    



}

int main(void)
{
    menu();
    entrada();

}
