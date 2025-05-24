
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Vlinha 15
#define Vcoluna 15
int px = 1, py = 1, dialogo = 0, tutorial = 1, Nfase = 0;
char input;
char Vmapa[Vlinha][Vcoluna];
char F1mapa[Vlinha][Vcoluna];
char Vchao[Vlinha][Vcoluna];
char F1chao[Vlinha][Vcoluna];
int i, j;
COORD coord = {0, 0};

#define key_up 119
#define key_down 115
#define enter 13

int selecionar = 0; // 0=Play, 1=Help, 2=Exit

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", x + 1, y + 1);
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
    printf("\033[20;1H\033[K");
    printf("\033[21;1H\033[K");
    printf("\033[22;1H\033[K");

    gotoxy(20, 77);
    printf("%sPlay\033[0m", selecionar == 0 ? "\033[1;31m" : "");

    gotoxy(21, 76);
    printf("%sCredit\033[0m", selecionar == 1 ? "\033[1;31m" : "");

    gotoxy(22, 77);
    printf("%sExit\033[0m", selecionar == 2 ? "\033[1;31m" : "");
}

void fase1()
{
    i = 0;
    while (i < Vlinha)
    {
        j = 0;
        while (j < Vcoluna)
        {
            if (i == 0 || i == Vlinha - 1 || j == 0 || j == Vcoluna - 1)
            {
                F1mapa[i][j] = '#';
                F1chao[i][j] = '#';
            }
            else
            {
                F1mapa[i][j] = '.';
                F1chao[i][j] = '.';
            }
            j++;
        }
        i++;
    }
    // Adiciona elementos específicos da fase 1
    F1mapa[5][5] = 'P';
    F1mapa[7][7] = 'D';
    F1mapa[px][py] = '&'; // Posiciona o jogador
}

void Vila(char Vmapa[Vlinha][Vcoluna])
{
    int i = 0, j;
    int centro_x = Vlinha / 2;
    int centro_y = Vcoluna / 2;
    int raio = 4;

    while (i < Vlinha)
    {
        j = 0;
        while (j < Vcoluna)
        {
            if (i == 0 || i == Vlinha - 1 || j == 0 || j == Vcoluna - 1)
            {
                Vmapa[i][j] = '*';
                Vchao[i][j] = '*';
            }
            else if ((i - centro_x) * (i - centro_x) + (j - centro_y) * (j - centro_y) <= raio * raio)
            {
                Vmapa[i][j] = ' ';
                Vchao[i][j] = ' ';
            }
            else
            {
                Vmapa[i][j] = '.';
                Vchao[i][j] = '.';
            }
            j++;
        }
        i++;
    }

    Vmapa[px][py] = '&';
    Vmapa[1][2] = 'P';
    Vmapa[12][7] = 'D';
    Vmapa[12][9] = 'P';
    Vmapa[13][13] = '@';
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
                        printf("%c ", (Nfase == 0) ? Vmapa[i][j] : F1mapa[i][j]);
                        j++;
                    }
                    printf("\n");
                    i++;
                }

                if (tutorial == 1)
                {
                    dialogo = 1;
                    printf("Ola Aventureiro");

                    while (dialogo == 1)
                    {
                        input = getch();
                        if (input == 101 || input == 27)
                        {
                            dialogo = 0;
                            printf("\033[16;1H\033[K");
                            tutorial = 0;
                        }
                    }
                }

                input = getch();
                if (Nfase == 0 && Vmapa[px][py] == '&')
                {
                    Vmapa[px][py] = Vchao[px][py];
                }
                else if (Nfase == 1 && F1mapa[px][py] == '&')
                {
                    F1mapa[px][py] = F1chao[px][py];
                }

                if (input == 39)
                {
                    inicio = 1;
                    goto ini;
                }

                // Verifica se está na porta aberta para trocar de mapa
                if (Nfase == 0 && Vmapa[px][py] == '=')
                {
                    system("cls");
                    fase1();
                    px = 2;
                    py = 1;
                    Nfase = 1;
                    continue;
                }

                switch (input)
                {
                case 'd':
                case 'D':
                    if (py < Vcoluna - 1)
                    {
                        char* mapaAtual = (Nfase == 0) ? &Vmapa[px][py] : &F1mapa[px][py];
                        char* chaoAtual = (Nfase == 0) ? &Vchao[px][py] : &F1chao[px][py];
                        char proximo = (Nfase == 0) ? Vmapa[px][py + 1] : F1mapa[px][py + 1];
                        
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            *chaoAtual = *mapaAtual;
                            py++;
                        }
                    }
                    break;

                case 'a':
                case 'A':
                    if (py > 0)
                    {
                        char* mapaAtual = (Nfase == 0) ? &Vmapa[px][py] : &F1mapa[px][py];
                        char* chaoAtual = (Nfase == 0) ? &Vchao[px][py] : &F1chao[px][py];
                        char proximo = (Nfase == 0) ? Vmapa[px][py - 1] : F1mapa[px][py - 1];
                        
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            *chaoAtual = *mapaAtual;
                            py--;
                        }
                    }
                    break;

                case 's':
                case 'S':
                    if (px < Vlinha - 1)
                    {
                        char* mapaAtual = (Nfase == 0) ? &Vmapa[px][py] : &F1mapa[px][py];
                        char* chaoAtual = (Nfase == 0) ? &Vchao[px][py] : &F1chao[px][py];
                        char proximo = (Nfase == 0) ? Vmapa[px + 1][py] : F1mapa[px + 1][py];
                        
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            *chaoAtual = *mapaAtual;
                            px++;
                        }
                    }
                    break;

                case 'w':
                case 'W':
                    if (px > 0)
                    {
                        char* mapaAtual = (Nfase == 0) ? &Vmapa[px][py] : &F1mapa[px][py];
                        char* chaoAtual = (Nfase == 0) ? &Vchao[px][py] : &F1chao[px][py];
                        char proximo = (Nfase == 0) ? Vmapa[px - 1][py] : F1mapa[px - 1][py];
                        
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            *chaoAtual = *mapaAtual;
                            px--;
                        }
                    }
                    break;

                case 'e':
                case 'E':
                    if (tutorial == 0)
                    {
                        if ((abs(px - 1) <= 1 && abs(py - 2) <= 1) && Nfase == 0 && Vmapa[1][2] == 'P')
                        {
                            dialogo = 1;
                            printf("Ola Aventureiro");

                            while (dialogo == 1)
                            {
                                input = getch();
                                if (input == 101 || input == 27)
                                {
                                    dialogo = 0;
                                    printf("\033[16;1H\033[K");
                                    tutorial = 0;
                                }
                            }
                        }
                    }

                    if ((abs(px - 13) <= 1 && abs(py - 13) <= 1) && Nfase == 0 && Vmapa[13][13] == '@')
                    {
                        Vmapa[13][13] = '.';
                        Vchao[13][13] = '.';

                        Vmapa[12][7] = '=';
                        Vchao[12][7] = '=';
                    }
                    break;
                }
                
                // Atualiza a posição do jogador no mapa correto
                if (Nfase == 0)
                    Vmapa[px][py] = '&';
                else
                    F1mapa[px][py] = '&';
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

int main(void)
{
    printf("\033[?25l");
    desenharmenu();

    Vila(Vmapa);

    while (1)
    {
        menu();
        entradamenu();
    }

    return 0;
}