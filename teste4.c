#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define key_up 119
#define key_down 115
#define enter 13

int selecionar = 0;

void handleInput() {
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

int main (void){

    while (1)
    {
        printf("%s%s\n", selecionar == 0 ? " \033[1;31m" : "", "Texto1");
        printf("\033[0m");

        printf("%s%s\n", selecionar == 1 ? " \033[1;31m" : "", "Texto2");  
        printf("\033[0m");
        

        printf("%s%s\n", selecionar == 2 ? " \033[1;31m" : "", "Texto3");
        printf("\033[0m");

        handleInput();
        system("cls");
    }
    
}