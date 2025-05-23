#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Vlinha 15
#define Vcoluna 15
int px = 1, py = 1, dialogo = 0, tutorial = 1;
char input;
char mapa[Vlinha][Vcoluna];
char chao[Vlinha][Vcoluna];
int i, j;
COORD coord = {0, 0};

#define key_up 119
#define key_down 115
#define enter 13

int selecionar = 0; // 0=Play, 1=Help, 2=Exit

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", x + 1, y + 1); // Código ANSI para posicionar cursor
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
    printf("\033[20;1H\033[K"); // Limpa Vlinha do Play
    printf("\033[21;1H\033[K"); // Limpa Vlinha do Credit
    printf("\033[22;1H\033[K"); // Limpa Vlinha do Exit

    gotoxy(20, 77);
    printf("%sPlay\033[0m", selecionar == 0 ? "\033[1;31m" : "");

    gotoxy(21, 76);
    printf("%sCredit\033[0m", selecionar == 1 ? "\033[1;31m" : "");

    gotoxy(22, 77);
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
                while (i < Vlinha)
                {
                    j = 0;
                    while (j < Vcoluna)
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
                            printf("\033[16;1H\033[K"); // Limpa Vlinha da fala com o npc 
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
                if (py < Vlinha - 1 && mapa[px][py + 1] != '*' && 
                    mapa[px][py + 1] != 'P' && mapa[px][py + 1] != 'D' && 
                    mapa[px][py + 1] != '@' && mapa[px][py + 1] != ' ') // Adicionado verificação do espaço vazio
                {
                    chao[px][py] = mapa[px][py];
                    py++;
                }
                break;

            case 'a':
            case 'A':
                if (py > 0 && mapa[px][py - 1] != '*' && 
                    mapa[px][py - 1] != 'P' && mapa[px][py - 1] != 'D' && 
                    mapa[px][py - 1] != '@' && mapa[px][py - 1] != ' ') // Adicionado verificação do espaço vazio
                {
                    chao[px][py] = mapa[px][py];
                    py--;
                }
                break;

            case 's':
            case 'S':
                if (px < Vlinha - 1 && mapa[px + 1][py] != '*' && 
                    mapa[px + 1][py] != 'P' && mapa[px + 1][py] != 'D' && 
                    mapa[px + 1][py] != '@' && mapa[px + 1][py] != ' ') // Adicionado verificação do espaço vazio
                {
                    chao[px][py] = mapa[px][py];
                    px++;
                }
                break;

            case 'w':
            case 'W':
                if (px > 0 && mapa[px - 1][py] != '*' && 
                    mapa[px - 1][py] != 'P' && mapa[px - 1][py] != 'D' && 
                    mapa[px - 1][py] != '@' && mapa[px - 1][py] != ' ') // Adicionado verificação do espaço vazio
                {
                    chao[px][py] = mapa[px][py];
                    px--;
                }
                break;
            // ... restante do código permanece igual

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
                                        printf("\033[16;1H\033[K"); // Limpa Vlinha da fala com o npc       
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
            printf("A todos que apoiaram e jogaram Dungeons of Infernus!");
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

void Vila(char mapa[Vlinha][Vcoluna])
{
    int i = 0, j;
    int centro_x = Vlinha / 2;
    int centro_y = Vcoluna / 2;
    int raio = 3; // Raio do círculo central

    while (i < Vlinha)
    {
        j = 0;
        while (j < Vcoluna)
        {
            // Verifica se está na borda do quadrado
            if (i == 0 || i == Vlinha - 1 || j == 0 || j == Vcoluna - 1)
            {
                mapa[i][j] = '*';
            }
            // Verifica se está dentro do círculo (usando equação do círculo)
            else if ((i - centro_x) * (i - centro_x) + (j - centro_y) * (j - centro_y) <= raio * raio)
            {
                mapa[i][j] = ' '; // Espaço vazio no círculo central
                chao[i][j] = ' ';
            }
            else
            {
                mapa[i][j] = '.'; // Chão normal
                chao[i][j] = '.';
            }
            j++;
        }
        i++;
    }

    // Mantendo os elementos originais da vila
    mapa[px][py] = '&'; // Personagem
    mapa[1][2] = 'P';   // NPC Tutorial
    mapa[12][7] = 'D';  // Porta Da Dungeon
    mapa[12][5] = 'P';  // NPC Guarda Da Dungeon
    mapa[13][6] = '*';  // Parede Da Dungeon
    mapa[13][8] = '*';  // Parede Da Dungeon
    mapa[12][6] = '*';  // Parede Da Dungeon
    mapa[12][8] = '*';  // Parede Da Dungeon
    mapa[13][13] = '@'; // Chave Para Abrir a Porta
}
int main(void)
{
    printf("\033[?25l");
    desenharmenu();

    Vila(mapa);

    while (1)
    {
        menu();
        entradamenu();
    }

    return 0;
}