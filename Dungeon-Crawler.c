#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define linha 15
#define coluna 15
int px = 1, py = 1, dialogo = 0, tutorial = 1;
char input;
char mapa[linha][coluna];
char chao[linha][coluna];
int i, j;
COORD coord = {0, 0};

#define key_up 119
#define key_down 115
#define enter 13

int selecionar = 0; // 0=Play, 1=Help, 2=Exit

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1); // Código ANSI para posicionar cursor
}

void desenharmenu(void)
{
    system("cls");

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
}

void menu()
{
    // Limpa apenas as áreas que serão atualizadas
    printf("\033[20;1H\033[K"); // Limpa linha do Play
    printf("\033[21;1H\033[K"); // Limpa linha do Credit
    printf("\033[22;1H\033[K"); // Limpa linha do Exit

    gotoxy(77, 20);
    printf("%sPlay\033[0m", selecionar == 0 ? "\033[1;31m" : "");

    gotoxy(76, 21);
    printf("%sCredit\033[0m", selecionar == 1 ? "\033[1;31m" : "");

    gotoxy(77, 22);
    printf("%sExit\033[0m", selecionar == 2 ? "\033[1;31m" : "");
}

void entradamenu(void)
{
    int inicio = 0;
    ini:
    if (inicio == 1)
    {
        desenharmenu();
        menu();
    }
    
    int input = getch();

    if (input == 0 || input == key_down || input == key_up)
    {
        switch (input)
        {
        case key_up:
            if (selecionar > 0)
                selecionar--;
            else
                selecionar = 2;
            break;
        case key_down:
            if (selecionar < 2)
                selecionar++;
            else
                selecionar = 0;
            break;
        }
    }
    else if (input == enter)
    {
        system("cls");
        switch (selecionar)
        {
        case 0:
            printf("Iniciando Jogo...\n");
            Sleep(1000);

            while (1)
            {
                COORD pos = {0, 0};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

                i = 0;
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

                if(tutorial == 1)
                {
                    dialogo = 1;
                    printf("Ola Aventureiro");

                    while (dialogo == 1)
                    {
                        input = getch();
                        if(input == 101 || input == 27)
                        {
                            dialogo = 0;
                            printf("\033[16;1H\033[K"); // Limpa linha da fala com o npc 
                            tutorial = 0;        
                        }
                    }
                }

                input = getch();
                if (mapa[px][py] == '&') 
                {
                    mapa[px][py] = chao[px][py];
                }

                if(input == 39)
                {

                    inicio = 1;
                    goto ini;

                }

                switch (input)
                {
                    case 'd':
                    case 'D':
                        if (py < linha - 1 && mapa[px][py + 1] != '*' && mapa[px][py + 1] != 'P' && mapa[px][py + 1] != 'D' && mapa[px][py + 1] != '@') 
                        {
                            chao[px][py] = mapa[px][py];
                            py++;
                        }
                        break;

                    case 'a':
                    case 'A':
                        if (py > 0 && mapa[px][py - 1] != '*' && mapa[px][py - 1] != 'P' && mapa[px][py - 1] != 'D' && mapa[px][py - 1] != '@')
                        {
                            chao[px][py] = mapa[px][py];
                            py--;
                        }
                        break;

                    case 's':
                    case 'S':
                        if (px < linha - 1 && mapa[px + 1][py] != '*' && mapa[px + 1][py] != 'P' && mapa[px + 1][py] != 'D' && mapa[px + 1][py] != '@')
                        {
                            chao[px][py] = mapa[px][py];
                            px++;
                        }
                        break;

                    case 'w':
                    case 'W':
                        if (px > 0 && mapa[px - 1][py] != '*' && mapa[px - 1][py] != 'P' && mapa[px - 1][py] != 'D' && mapa[px - 1][py] != '@')
                        {
                            chao[px][py] = mapa[px][py];
                            px--;
                        }
                        break;

                    case 'e':
                    case 'E':

                        if(tutorial == 0)
                        {
                            if ((abs(px - 1) <= 1 && abs(py - 2) <= 1) && mapa[1][2] == 'P')
                            {
                                dialogo = 1;
                                printf("Ola Aventureiro");

                                while (dialogo == 1)
                                {
                                    input = getch();
                                    if(input == 101 || input == 27)
                                    {
                                        dialogo = 0;
                                        printf("\033[16;1H\033[K"); // Limpa linha da fala com o npc       
                                        tutorial = 0;                           
                                    }
                                }
                            }
                        }
    
                        if ((abs(px - 13) <= 1 && abs(py - 13) <= 1) && mapa[13][13] == '@')
                        {
                            mapa[13][13] = '.';
                            chao[13][13] = '.';

                            mapa[12][7] = '=';
                            chao[12][7] = '=';
                        }
                        break;
                }  
                mapa[px][py] = '&';
                
            }
            break;

        case 1:
            printf("\tDesenvolvido por:\n");
            printf("Programacao Por: Icaro Sousa, Daniel Silva, Rafael Rian\n");
            printf("Design Do Jogo Por:Daniel Silva\n");
            printf("Historia Do Jogo Por: Icaro Sousa\n");
            printf("\n\tAgradecimentos Especiais:\n");
            printf("A todos que apoiaram e jogaram Dungeons of Inferno!");
            break;

        case 2:
            printf("\033[1;31mOs portais de Dungeons of Infernus sempre estarao abertos para voce. Volte quando quiser, mas cuidado... o fogo do inferno nunca se apaga.\033[0m\n");
            exit(0);
        }
        getch();
        desenharmenu();
    }
}

void entrada(void)
{
    input = getch();
    printf("%c", input);
}

void mapa1(char mapa[linha][coluna])
{

    int i = 0, j;

    while (i < linha)
    {
        j = 0;
        while (j < coluna)
        {
            if (i == 0 || i == linha - 1 || j == 0 || j == coluna - 1)
            {
                mapa[i][j] = '*';
            }

            else 
            {
                mapa[i][j] = '.';
                chao[i][j] = '.';
            }
            j++;
        }
        i++;
    }

    mapa[px][py] = '&'; // Personagem
    mapa[1][2] = 'P'; // NPC Tutorial
    /*mapa[2][5] = 'P'; // NPC 
    mapa[1][2] = 'P'; // NPC 
    mapa[1][2] = 'P'; // NPC 
    mapa[1][2] = 'P'; // NPC 
    mapa[1][2] = 'P'; // NPC*/ 
    mapa[12][7] = 'D'; // Porta Da Dungeon
    mapa[11][6] = 'P'; // NPC Guarda Da Dungeon
    mapa[13][6] = '*'; // Parede Da Dungeon
    mapa[13][8] = '*'; // Parede Da Dungeon
    mapa[12][6] = '*'; // Parede Da Dungeon
    mapa[12][8] = '*'; // Parede Da Dungeon
    mapa[13][13] = '@'; // Chave Para Abrir a Porta
}

int main(void)
{
    printf("\033[?25l");
    desenharmenu();

    mapa1(mapa);

    while (1)
    {
        menu();
        entradamenu();
    }

    return 0;
}