#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MaximoDeLinhas 40
#define MaximoDeColunas 40
#define TFases 4

char mapas[TFases][MaximoDeLinhas][MaximoDeColunas];
char chaos[TFases][MaximoDeLinhas][MaximoDeColunas];

int dimensoesfases[TFases][2] = {
    {15, 15}, // Fase 0: Vila
    {15, 15}, // Fase 1: Dungeon 1
    {25, 25}, // Fase 2: Dungeon 2
    {40, 40}  // Fase 3: Dungeon 3
};

int pxinicial[TFases] = {1, 1, 1, 1}, pyinicial[TFases] = {1, 1, 1, 1};

int px, py;
int dialogo = 0, Nfase = 0, falainicial = 1, jogar = 1;
int tentativasFase = 0;

char input;
COORD coord = {0, 0};

#define key_up 119
#define key_down 115
#define enter 13

int selecionar = 0; // 0=Play, 1=Credit, 2=Exit

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", x + 1, y + 1);
}

void desenharmenu(void)
{
    system("cls || clear");

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

void MostrarDerrota()
{
    system("cls || clear");
    printf("\033[1;31m");
    printf("\n\n\n\n\n\n\n");
    printf("%*s\n", 45, "VOCE FRACASSOU!");
    printf("%*s\n", 45, "As masmorras do inferno consumiram voce.");
    printf("%*s\n", 40, "Tente novamente, aventureiro!");
    printf("\033[0m");
    Sleep(3000);
    Nfase = 0;
    jogar = 0;
    tentativasFase = 0;
    system("cls || clear");
    desenharmenu();
}

void IniFase(int fase)
{
    int linhas = dimensoesfases[fase][0];
    int colunas = dimensoesfases[fase][1];

    int li = 0, co = 0;
    while (li < linhas)
    {
        co = 0;
        while (co < colunas)
        {
            if (li == 0 || li == linhas - 1 || co == 0 || co == colunas - 1)
            {
                mapas[fase][li][co] = '*';
                chaos[fase][li][co] = mapas[fase][li][co];
            }
            else if (fase == 0)
            {
                int centroX = linhas / 2;
                int centroY = colunas / 2;
                int raio = 4;

                if ((li - centroX) * (li - centroX) + (co - centroY) * (co - centroY) <= raio * raio)
                {
                    mapas[fase][li][co] = ' ';
                    chaos[fase][li][co] = ' ';
                }
                else
                {
                    mapas[fase][li][co] = '.';
                    chaos[fase][li][co] = '.';
                }
            }
            else
            {
                mapas[fase][li][co] = '.';
                chaos[fase][li][co] = '.';
            }
            co++;
        }
        li++;
    }

    // Adiciona elementos específicos de cada fase
    if (fase == 0)
    { // Fase Da Vila
        mapas[fase][1][2] = 'P';
        mapas[fase][12][5] = 'P';
        mapas[fase][12][7] = 'D';
        mapas[fase][13][13] = '@';
    }
    else if (fase == 1)
    { // Dungeon 1
        mapas[fase][5][5] = 'P';
        mapas[fase][12][7] = 'D';
        mapas[fase][3][5] = '#';
        mapas[fase][3][6] = '#';
        mapas[fase][3][7] = '#';
        mapas[fase][3][8] = '#';
        mapas[fase][3][9] = '#';
        mapas[fase][3][10] = '#';
        mapas[fase][3][11] = '#';
        mapas[fase][3][12] = '#';
        mapas[fase][4][7] = '#';
        mapas[fase][5][7] = '#';
        mapas[fase][6][7] = '#';
        mapas[fase][6][9] = 'X';
        mapas[fase][8][9] = '#';
        mapas[fase][7][7] = '#';
        mapas[fase][8][7] = '#';
        mapas[fase][8][8] = '#';
        mapas[fase][8][9] = '#';
        mapas[fase][9][9] = '#';
        mapas[fase][10][9] = '#';
        mapas[fase][11][9] = '#';
        mapas[fase][12][9] = '#';
        mapas[fase][13][9] = '#';
        mapas[fase][13][13] = '@';
        mapas[fase][10][10] = 'X';
    }
    else if (fase == 2)
    { // Dungeon 2
        mapas[fase][3][3] = 'D';
        mapas[fase][4][3] = '@';
        //mapas[fase][12][7] = 'D';
        mapas[fase][13][11] = 'X';
        mapas[fase][16][9] = 'X';
        mapas[fase][12][15] = 'X';
        mapas[fase][12][16] = 'X';
        //mapas[fase][21][21] = '@';
        mapas[fase][5][10] = '*';
        mapas[fase][5][9] = '*';
        mapas[fase][5][8] = '*';
        mapas[fase][5][11] = '*';
        mapas[fase][5][12] = '*';
        mapas[fase][6][8] = '*';
        mapas[fase][7][8] = '*';
        mapas[fase][8][8] = '*';
        mapas[fase][9][8] = '*';
        mapas[fase][10][8] = '*';
        mapas[fase][10][9] = '*';
        mapas[fase][6][12] = '*';
        mapas[fase][7][12] = '*';
        mapas[fase][8][12] = '*';
        mapas[fase][9][12] = '*';
        mapas[fase][10][12] = '*';
        mapas[fase][10][11] = '*';
        mapas[fase][2][8] = '*';
        mapas[fase][2][9] = '*';
        mapas[fase][2][10] = '*';
        mapas[fase][2][11] = '*';
        mapas[fase][2][12] = '*';
        mapas[fase][2][13] = '*';
        mapas[fase][2][14] = '*';
        mapas[fase][2][15] = '*';
        mapas[fase][2][16] = '*';
        mapas[fase][5][6] = '*';
        mapas[fase][4][6] = '*';
        mapas[fase][3][6] = '*';
        mapas[fase][2][6] = '*';
        mapas[fase][5][5] = '*';
        mapas[fase][5][4] = '*';
        mapas[fase][5][3] = '*';
        mapas[fase][5][2] = '*';
        mapas[fase][5][1] = '*';
        mapas[fase][6][6] = '*';
        mapas[fase][7][6] = '*';
        mapas[fase][8][6] = '*';
        mapas[fase][9][6] = '*';
        mapas[fase][10][6] = '*';
        mapas[fase][10][3] = 'X';
        mapas[fase][11][6] = '*';
        mapas[fase][12][6] = '*';
        mapas[fase][13][6] = '*';
        mapas[fase][13][4] = 'X';
        mapas[fase][14][6] = '*';
        mapas[fase][15][6] = '*';
        mapas[fase][16][6] = '*';
        mapas[fase][17][4] = 'X';
        mapas[fase][17][6] = '*';
        mapas[fase][15][2] = '*';
        mapas[fase][16][2] = '*';
        mapas[fase][17][2] = '*';
        mapas[fase][18][2] = '*';
        mapas[fase][19][21] = '*';
        mapas[fase][18][21] = '*';
        mapas[fase][19][2] = '*';
        mapas[fase][20][2] = '*';
        mapas[fase][20][3] = '*';
        mapas[fase][20][4] = '*';
        mapas[fase][20][5] = '*';
        mapas[fase][20][6] = '*';
        mapas[fase][20][7] = '*';
        mapas[fase][20][8] = '*';
        mapas[fase][20][9] = '*';
        mapas[fase][20][10] = '*';
        mapas[fase][20][11] = '*';
        mapas[fase][20][12] = '*';
        mapas[fase][20][13] = '*';
        mapas[fase][20][14] = '*';
        mapas[fase][20][15] = '*';
        mapas[fase][20][16] = '*';
        mapas[fase][20][17] = '*';
        mapas[fase][20][18] = '*';
        mapas[fase][20][19] = '*';
        mapas[fase][20][20] = '*';
        mapas[fase][20][21] = '*';
        mapas[fase][20][23] = '*';
        mapas[fase][21][23] = '*';
        mapas[fase][22][23] = '*';
        mapas[fase][23][23] = '*';
        mapas[fase][20][12] = '*';
        mapas[fase][22][19] = 'X';
        mapas[fase][2][5] = 'X';
        mapas[fase][5][14] = 'X';
        mapas[fase][6][10] = '#';
        mapas[fase][7][10] = '#';
        mapas[fase][8][10] = 'O';
        mapas[fase][17][16] = 'X';
        mapas[fase][18][20] = 'X';
        mapas[fase][21][2] = '#';
        mapas[fase][23][3] = '#';
        mapas[fase][21][4] = '#';
        mapas[fase][23][6] = '#';
        mapas[fase][22][6] = '#';
        mapas[fase][21][8] = '#';
        mapas[fase][22][8] = '#';
        mapas[fase][22][9] = '#';
        mapas[fase][22][10] = '#';
        mapas[fase][21][10] = '#';
        mapas[fase][22][10] = '#';
        mapas[fase][23][12] = '#';
        mapas[fase][22][12] = '#';
        mapas[fase][22][13] = '#';
        mapas[fase][22][14] = '#';
        mapas[fase][22][15] = '#';
    }
    else
    { // Dungeon 3
        mapas[fase][12][7] = 'D';
        mapas[fase][13][13] = '@';
        mapas[fase][1][10] = '*';
        mapas[fase][2][10] = '*';
        mapas[fase][3][10] = '*';
        mapas[fase][4][10] = '*';
        mapas[fase][5][10] = '*';
        mapas[fase][6][10] = '*';
        mapas[fase][7][10] = '*';
        mapas[fase][15][15] = 'X';
        mapas[fase][8][9] = 'V';
        mapas[fase][8][10] = '*';
        mapas[fase][9][10] = '*';
        mapas[fase][9][9] = '*';
        mapas[fase][9][8] = '*';
        mapas[fase][9][7] = '*';
        mapas[fase][9][6] = '*';
        mapas[fase][9][5] = '*';
        mapas[fase][9][4] = '*';
        mapas[fase][10][10] = '*';
        mapas[fase][11][10] = '*';
        mapas[fase][12][10] = '*';
        mapas[fase][13][10] = '*';
        mapas[fase][14][10] = '*';
        mapas[fase][15][10] = '*';
        mapas[fase][15][9] = '*';
        mapas[fase][15][8] = '*';
        mapas[fase][15][7] = '*';
        mapas[fase][15][6] = '*';
        mapas[fase][15][5] = '*';
        mapas[fase][15][4] = '*';
        mapas[fase][15][3] = '*';
        mapas[fase][15][2] = '*';
        mapas[fase][15][1] = '*';
        mapas[fase][13][7] = 'X';
        mapas[fase][12][4] = 'X';
        mapas[fase][14][9] = 'X';
        mapas[fase][13][3] = 'X';
        mapas[fase][10][9] = '>'; // Teletransporte 1
        chaos[fase][10][9] = '>'; // Chão abaixo é normal

        mapas[fase][28][38] = '*';
        mapas[fase][28][37] = '*';
        mapas[fase][28][36] = '*';
        mapas[fase][28][35] = '*';
        mapas[fase][28][34] = '*';
        mapas[fase][28][33] = '*';
        mapas[fase][28][32] = '*';
        mapas[fase][28][31] = '*';
        mapas[fase][28][30] = '*';
        mapas[fase][28][29] = '*';
        mapas[fase][28][28] = '*';
        mapas[fase][28][27] = '*';
        mapas[fase][28][26] = '*';
        mapas[fase][28][25] = '*';
        mapas[fase][28][24] = '*';
        mapas[fase][29][24] = '*';
        mapas[fase][30][24] = '*';
        mapas[fase][31][24] = '*';
        mapas[fase][32][24] = '*';
        mapas[fase][33][24] = '*';
        mapas[fase][34][24] = '*';
        mapas[fase][35][24] = '*';
        mapas[fase][36][24] = '*';
        mapas[fase][37][24] = '*';
        mapas[fase][38][24] = '*';
        mapas[fase][36][33] = 'X';
        mapas[fase][36][34] = 'X';
        mapas[fase][36][35] = 'X';
        mapas[fase][36][36] = 'X';
        mapas[fase][36][37] = 'X';
        mapas[fase][36][38] = 'X';
        mapas[fase][37][31] = 'X';
        mapas[fase][37][33] = 'X';
        mapas[fase][38][33] = 'X';
        mapas[fase][38][38] = '@';
        mapas[fase][30][30] = '>'; // Teletransporte 2
        chaos[fase][30][30] = '>'; // Chão abaixo é normal

        //ESPINHOSSXXXXXXX
        mapas[fase][36][25] = 'O';
        mapas[fase][37][23] = '#';
        mapas[fase][37][22] = '#';
        mapas[fase][37][21] = '#';
        mapas[fase][38][19] = '#';
        mapas[fase][37][19] = '#';
        mapas[fase][36][19] = '#';
        mapas[fase][35][23] = '#';
        mapas[fase][34][23] = '#';
        mapas[fase][36][21] = '#';
        mapas[fase][35][21] = '#';
        mapas[fase][34][21] = '#';
        mapas[fase][34][20] = '#';
        mapas[fase][34][19] = '#';
        mapas[fase][34][18] = '#';
        mapas[fase][34][17] = '#';
        mapas[fase][34][16] = '#';
        mapas[fase][35][16] = '#';
        mapas[fase][36][16] = '#';
        mapas[fase][37][16] = '#';
        mapas[fase][37][15] = '#';
        mapas[fase][37][14] = '#';
        mapas[fase][37][13] = '#';
        mapas[fase][36][13] = '#';
        mapas[fase][35][13] = '#';
        mapas[fase][34][13] = '#';
        mapas[fase][33][13] = '#';
        mapas[fase][33][12] = '#';
        mapas[fase][33][11] = '#';
        mapas[fase][33][10] = '#';
        mapas[fase][33][9] = '#';
        mapas[fase][37][11] = '#';
        mapas[fase][38][11] = '#';
        mapas[fase][36][11] = '#';
        mapas[fase][35][11] = '#';
        mapas[fase][35][10] = '#';
        mapas[fase][35][9] = '#';
        mapas[fase][35][8] = '#';
        mapas[fase][35][7] = '#';
        mapas[fase][35][6] = '#';
        mapas[fase][34][6] = '#';
        mapas[fase][33][6] = '#';
        mapas[fase][32][6] = '#';
        mapas[fase][31][6] = '#';
        mapas[fase][31][5] = '#';
        mapas[fase][31][4] = '#';
        mapas[fase][31][3] = '#';
        mapas[fase][30][3] = '#';
        mapas[fase][29][3] = '#';
        mapas[fase][28][3] = '#';
        mapas[fase][27][3] = '#';
        mapas[fase][27][3] = '#';
        mapas[fase][27][3] = '#';
        mapas[fase][27][3] = '#';
        mapas[fase][27][3] = '#';
        mapas[fase][26][3] = '#';
        mapas[fase][25][3] = '#';
        mapas[fase][24][3] = '#';
        mapas[fase][23][3] = '#';
        mapas[fase][23][4] = '#';
        mapas[fase][23][5] = '#';
        mapas[fase][23][6] = '#';
        mapas[fase][23][7] = '#';
        mapas[fase][23][8] = '#';
        mapas[fase][23][9] = '#';
        mapas[fase][23][10] = '#';
        mapas[fase][23][11] = '#';
        mapas[fase][23][12] = '#';
        mapas[fase][24][12] = '#';
        mapas[fase][25][12] = '#';

    }
    if (fase == Nfase)
    {
        mapas[fase][pxinicial[fase]][pyinicial[fase]] = '&';
    }
}

void MostrarLegendas()
{
    if (Nfase == 0)
    { // Mostra legendas apenas na vila
        gotoxy(1, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1mLegenda:\033[0m");
        gotoxy(2, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;33m&\033[0m - Jogador");
        gotoxy(3, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;36mP\033[0m - NPC");
        gotoxy(4, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;32m@\033[0m - Chave");
        gotoxy(5, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;34mD\033[0m - Porta");
        gotoxy(6, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;34m=\033[0m - Porta Aberta");
        gotoxy(7, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;33mO\033[0m - Botao");
        gotoxy(8, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;31m#\033[0m - Espinhos");
        gotoxy(9, dimensoesfases[Nfase][1] * 2 + 5);
        printf("* - Parede");
        gotoxy(10, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;37m>\033[0m - Teletransporte");
        gotoxy(11, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;31mX\033[0m - Monstro Nivel 1");
        gotoxy(12, dimensoesfases[Nfase][1] * 2 + 5);
        printf("\033[1;31mV\033[0m - Monstro Nivel 2");
    }
}

void RenderizarMapa()
{
    int linhas = dimensoesfases[Nfase][0];
    int colunas = dimensoesfases[Nfase][1];

    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            char c = mapas[Nfase][i][j];

            // Aplica cores diferentes para cada elemento
            if (c == '&')
                printf("\033[1;33m%c \033[0m", c); // Jogador - amarelo
            else if (c == 'P')
                printf("\033[1;36m%c \033[0m", c); // NPC - ciano
            else if (c == '@')
                printf("\033[1;32m%c \033[0m", c); // Chave - verde
            else if (c == 'D' || c == '=')
                printf("\033[1;34m%c \033[0m", c); // Porta - azul
            else if (c == 'O')
                printf("\033[1;33m%c \033[0m", c); // Botão - amarelo (alterado de magenta para amarelo)
            else if (c == '#')
                printf("\033[1;31m%c \033[0m", c); // Espinho - vermelho
            else if (c == '>')
                printf("\033[1;37m%c \033[0m", c); // Teletransporte - branco
            else if (c == 'X' || c == 'V')
                printf("\033[1;31m%c \033[0m", c); // Monstros - vermelho
            else
                printf("%c ", c); // Demais elementos - cor padrão
        }
        printf("\n");
    }

    // Mostra informações adicionais abaixo do mapa
    printf("\nFase: %d | Tentativas restantes: %d\n", Nfase, 3 - tentativasFase);
    printf("Use WASD para mover, E para interagir\n");

    // Mostra legendas apenas na vila
    MostrarLegendas();
}

void ReiniciarFase()
{
    tentativasFase++;

    if (tentativasFase < 3)
    {
        px = pxinicial[Nfase];
        py = pyinicial[Nfase];
        IniFase(Nfase);
        system("cls || clear");
        RenderizarMapa();
        gotoxy(dimensoesfases[Nfase][0] + 2, 0);
        printf("\033[1;31mFase reiniciada! Tentativas restantes: %d\033[0m", 3 - tentativasFase);
        Sleep(500);
        system("cls || clear");
        RenderizarMapa();
    }
    else
    {
        MostrarDerrota();
        tentativasFase = 0;
    }
}

int PodeMoverPara(int x, int y)
{
    char celula = mapas[Nfase][x][y];
    return (celula == '.' || celula == '=' || celula == '>' || celula == '&');
}

void VerificarEspinhos()
{
    if (mapas[Nfase][px][py] == '#')
    {
        ReiniciarFase();
    }
}

void Monstros()
{
    if (Nfase < 1)
        return;

    int linhas = dimensoesfases[Nfase][0];
    int colunas = dimensoesfases[Nfase][1];

    // Primeiro passada: marca posições atuais dos monstros
    int monstrosX[100], monstrosY[100], tipos[100];
    int numMonstros = 0;

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (mapas[Nfase][i][j] == 'X' || mapas[Nfase][i][j] == 'V')
            {
                monstrosX[numMonstros] = i;
                monstrosY[numMonstros] = j;
                tipos[numMonstros] = mapas[Nfase][i][j];
                numMonstros++;
            }
        }
    }

    // Segunda passada: move os monstros
    for (int m = 0; m < numMonstros; m++)
    {
        int i = monstrosX[m];
        int j = monstrosY[m];
        char tipo = tipos[m];

        if (tipo == 'X')
        { // Monstro nível 1 (movimento aleatório)
            int direcao = rand() % 4;
            int ni = i, nj = j;

            switch (direcao)
            {
            case 0:
                ni--;
                break; // Cima
            case 1:
                ni++;
                break; // Baixo
            case 2:
                nj--;
                break; // Esquerda
            case 3:
                nj++;
                break; // Direita
            }

            // Verifica se pode mover para a nova posição
            if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)
            {
                char destino = mapas[Nfase][ni][nj];
                if (destino == '.' || destino == '&')
                {
                    mapas[Nfase][i][j] = chaos[Nfase][i][j];
                    mapas[Nfase][ni][nj] = 'X';

                    if (ni == px && nj == py)
                    {
                        ReiniciarFase();
                        return;
                    }
                }
            }
        }
        else if (tipo == 'V')
        { // Monstro nível 2 (persegue o jogador)
            int di = (px > i) ? 1 : (px < i) ? -1
                                             : 0;
            int dj = (py > j) ? 1 : (py < j) ? -1
                                             : 0;

            // Tenta mover na direção X primeiro
            int ni = i + di;
            int nj = j;

            if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)
            {
                char destino = mapas[Nfase][ni][nj];
                if (destino == '.' || destino == '&')
                {
                    mapas[Nfase][i][j] = chaos[Nfase][i][j];
                    mapas[Nfase][ni][nj] = 'V';

                    if (ni == px && nj == py)
                    {
                        ReiniciarFase();
                        return;
                    }
                    continue; // Movimento concluído
                }
            }

            // Se não conseguiu mover em X, tenta mover em Y
            ni = i;
            nj = j + dj;

            if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas)
            {
                char destino = mapas[Nfase][ni][nj];
                if (destino == '.' || destino == '&')
                {
                    mapas[Nfase][i][j] = chaos[Nfase][i][j];
                    mapas[Nfase][ni][nj] = 'V';

                    if (ni == px && nj == py)
                    {
                        ReiniciarFase();
                        return;
                    }
                }
            }
        }
    }
}

void TrocarFase(int novafase)
{
    mapas[Nfase][px][py] = chaos[Nfase][px][py]; // Limpa jogador na fase atual
    Nfase = novafase;
    px = pxinicial[Nfase];
    py = pyinicial[Nfase];
    tentativasFase = 0; // Reseta tentativas ao mudar de fase

    // Coloca jogador na nova fase
    mapas[Nfase][px][py] = '&';

    system("cls");
    Sleep(500);
    printf("Descendo Para o Andar %d...Cada Vez Mais Perto Do Inferno!", Nfase);
    Sleep(1000);
    system("cls || clear");
    RenderizarMapa();
}

void MostrarVitoria()
{
    system("cls || clear");
    printf("\033[1;32m");
    printf("\n\n\n\n\n\n\n");
    printf("%*s\n", 50, "PARABENS AVENTUREIRO!");
    printf("%*s\n", 45, "Voce conquistou as masmorras");
    printf("%*s\n", 40, "do inferno!");
    printf("\033[0m");
    Sleep(3000);
    Nfase = 0;
    tentativasFase = 0;
    system("cls || clear");
    desenharmenu();
}

void InteragirComObjetos()
{
    // Verifica todas as células ao redor
    for (int i = px - 1; i <= px + 1; i++)
    {
        for (int j = py - 1; j <= py + 1; j++)
        {
            // Verifica se está dentro dos limites do mapa
            if (i >= 0 && i < dimensoesfases[Nfase][0] &&
                j >= 0 && j < dimensoesfases[Nfase][1])
            {

                char obj = mapas[Nfase][i][j];

                if (obj == 'P')
                {
                    dialogo = 1;
                    // Mantém o jogador visível durante o diálogo
                    mapas[Nfase][px][py] = '&';

                    if (Nfase == 0)
                    {
                        if (i == 1 && j == 2)
                        { // Primeiro NPC
                            if (Nfase <= 1)
                            {
                                printf("\033[19;H");
                                printf("\033[s");

                                printf("\033[20;H\033[1mAnciao: Esse eh o grande abismo do inferno, dizem que a seculos ou milenios atras,"
                                       " caiu um grande meteoro carregado de magia bem nesse lugar, e fez essa \ncratera enorme,"
                                       " com o passar dos seculos, os aventureiros tentaram explorar o abismo para obter recursos,"
                                       " e perceberam que os recursos eram extremamente \nabundantes, diversos itens magicos e materiais "
                                       "de valor altissimo, e fazendo diversas obras de construcao, tijolo por tijolo ate formar uma grande"
                                       " masmorra \ncom centenas, ou ate milhares de andares, agora milenios depois nossa vila foi construida"
                                       " em volta dessa masmorra e nos nao conhecemos o responsavel pela \nconstrucao e muito menos o quao profunda"
                                       " ela pode ir, so sabemos que varios aventureiros descem e poucos dos que exploram os andares mais profundos"
                                       " \nconseguem retornar.\033[0m");
                            }
                            else if (Nfase == 2)
                            {
                                printf("\033[29;25H");
                                printf("\033[s");
                            }
                            else
                            {
                                printf("\033[44;40H");
                                printf("\033[s");
                            }
                        }
                        else if (i == 12 && j == 5) // Segundo NPC (Líder)
                        {
                            printf("\033[20;H\033[1mLider: Bem vindo novato, vou te explicar sobre como funcionam as expedicoes. Se prepare com seus melhores equipamentos e quando estiver pronto desca pelo elevador, e parta direto pelo fundo da masmorra, nos definimos os setores por regioes a primeira area eh tranquila mas ja foi saqueada por completo, do segundo setor para baixo comecam a aparecer os monstros nos ainda nao descobrimos sua origem porem construimos algumas armadilhas para lidar com eles, so ficar atento e tomar cuidado por onde olha, ate o momento o maximo que conseguimos descer foi por 3 regioes a partir dai as coisas comecam a ficar perigosas demais, o ar comeca a falhar e a pressao fica prestes a destruir nossos corpos."
                                   "Se voce quiser continuar descendo saiba que vai ser por conta propria\033[0m");
                        }
                    }
                    else if (Nfase == 1)
                    {
                        printf("\nAventureiro: Cuidado com os espinhos (#)! Eles reiniciam a fase.\n");
                    }
                    else if (Nfase == 2)
                    {
                        printf("\nAventureiro: Os botoes (O) podem revelar caminhos secretos!\n");
                    }
                    else if (Nfase == 3)
                    {
                        printf("\nAventureiro: Use os teletransportes (>) com cuidado!\n");
                    }

                    printf("\n\nPressione E para continuar...");

                    while (dialogo == 1)
                    {
                        input = getch();
                        if (input == 'e' || input == 'E' || input == 27)
                        {
                            dialogo = 0;
                            printf("\033[u");
                            printf("\033[0J");
                        }
                    }
                    return; // Sai da função após interação para evitar múltiplos diálogos
                }
                else if (obj == '@')
                { // Chave
                    mapas[Nfase][i][j] = '.';
                    chaos[Nfase][i][j] = '.';
                    gotoxy(dimensoesfases[Nfase][0] + 3, 0);
                    printf("\033[1;32mChave coletada! A porta agora esta aberta.\033[0m");
                    Sleep(800);
                    if (Nfase <= 1)
                    {
                        printf("\033[19;H");
                        printf("\033[s");
                        printf("\033[K");
                    }
                    else if (Nfase == 2)
                    {
                        printf("\033[29;H");
                        printf("\033[s");
                        printf("\033[K");
                    }
                    else
                    {
                        printf("\033[44;H");
                        printf("\033[s");
                        printf("\033[K");
                    }

                    // Abre todas as portas 'D' na fase
                    for (int x = 0; x < dimensoesfases[Nfase][0]; x++)
                    {
                        for (int y = 0; y < dimensoesfases[Nfase][1]; y++)
                        {
                            if (mapas[Nfase][x][y] == 'D')
                            {
                                mapas[Nfase][x][y] = '=';
                                chaos[Nfase][x][y] = '=';
                            }
                        }
                    }
                }
                else if (obj == 'O')
                { // Botão
                    gotoxy(dimensoesfases[Nfase][0] + 3, 0);
                    printf("\033[1;33mGuerreiros : ola quer uma ajudinha ?,venha aqui temos armas insanas pra voce!!\033[0m");
                    Sleep(500);

                    if (Nfase == 2)
                    {
                        printf("\033[29;H");
                        printf("\033[s");
                        printf("\033[K");
                        // Remove algumas paredes na fase 2
                        mapas[2][6][9] = 'P';
                        mapas[2][6][11] = 'P';
                        chaos[2][8][9] = '#';
                        chaos[2][8][11] = '#';
                    }
                    else if(Nfase == 3)
                    {
                        printf("\033[44;H");
                        printf("\033[s");
                        printf("\033[K");
                        mapas[3][12][10] = '.';
                        mapas[3][38][24] = '.';
                        chaos[3][38][24] = '.';
                        chaos[3][38][24] = '*';
                    }
                }
            }
        }
    }
}
void VerificarTeletransporte()
{
    // Verifica se o jogador está em cima de um teletransporte
    if (mapas[Nfase][px][py] == '>')
    {
        int linhas = dimensoesfases[Nfase][0];
        int colunas = dimensoesfases[Nfase][1];

        // Encontra o outro teletransporte
        for (int x = 0; x < linhas; x++)
        {
            for (int y = 0; y < colunas; y++)
            {
                if (mapas[Nfase][x][y] == '>' && (x != px || y != py))
                {
                    // Salva o que estava no chão da posição atual
                    char chaoAtual = chaos[Nfase][px][py];

                    // Remove o jogador da posição atual
                    mapas[Nfase][px][py] = chaoAtual;

                    // Salva o que está no chão da nova posição
                    char chaoNovo = chaos[Nfase][x][y];

                    // Move o jogador para o outro teletransporte
                    px = x;
                    py = y;
                    mapas[Nfase][px][py] = '&';
                    chaos[Nfase][px][py] = chaoNovo;

                    // Atualiza o display
                    gotoxy(dimensoesfases[Nfase][0] + 3, 0);
                    printf("\033[1;35mTeletransportado!\033[0m");
                    Sleep(500);
                    system("cls || clear");
                    RenderizarMapa();
                    return;
                }
            }
        }
    }
}

void entradamenu(void)
{
    jogar = 1;
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
        case 0: // Jogar
            printf("Iniciando Jogo...\n");
            Sleep(1000);

            // Inicializa todas as fases
            for (int fase = 0; fase < TFases; fase++)
            {
                IniFase(fase);
            }

            // Coloca o jogador na fase inicial
            Nfase = 0;
            px = pxinicial[Nfase];
            py = pyinicial[Nfase];
            mapas[Nfase][px][py] = '&';
            tentativasFase = 0;

            while (jogar == 1)
            {
                RenderizarMapa();

                if (falainicial == 1)
                {
                    dialogo = 1;
                    printf("\033[19;H");
                    printf("\033[s");
                    printf("\033[20;H\033[1mAnciao: Esse eh o grande abismo do inferno, dizem que a seculos ou milenios atras,"
                           " caiu um grande meteoro carregado de magia bem nesse lugar, e fez essa \ncratera enorme,"
                           " com o passar dos seculos, os aventureiros tentaram explorar o abismo para obter recursos,"
                           " e perceberam que os recursos eram extremamente \nabundantes, diversos itens magicos e materiais "
                           "de valor altissimo, e fazendo diversas obras de construcao, tijolo por tijolo ate formar uma grande"
                           " masmorra \ncom centenas, ou ate milhares de andares, agora milenios depois nossa vila foi construida"
                           " em volta dessa masmorra e nos nao conhecemos o responsavel pela \nconstrucao e muito menos o quao profunda"
                           " ela pode ir, so sabemos que varios aventureiros descem e poucos dos que exploram os andares mais profundos"
                           " \nconseguem retornar.\033[0m");

                    printf("\n\nPressione E para continuar...");

                    while (dialogo == 1)
                    {
                        input = getch();
                        if (input == 'e' || input == 'E' || input == 27)
                        {
                            dialogo = 0;
                            falainicial = 0;
                            printf("\033[u");
                            printf("\033[0J");
                        }
                    }
                }

                input = getch();

                // Limpa posição atual do jogador
                mapas[Nfase][px][py] = chaos[Nfase][px][py];

                if (input == 39)
                { // Tecla ' para voltar ao menu
                    inicio = 1;
                    goto ini;
                }

                // Verifica se está na porta aberta para trocar de fase
                if (mapas[Nfase][px][py] == '=')
                {
                    if (Nfase < TFases - 1)
                    {
                        TrocarFase(Nfase + 1);
                        continue;
                    }
                    else if (Nfase == 3)
                    {
                        MostrarVitoria();
                        break;
                    }
                }

                // Verifica espinhos e monstros
                VerificarEspinhos();
                Monstros();

                // Processa movimento ou interação
                switch (input)
                {
                case 'd':
                case 'D': // Direita
                    if (py < dimensoesfases[Nfase][1] - 1)
                    {
                        char destino = mapas[Nfase][px][py + 1];
                        if (PodeMoverPara(px, py + 1))
                        {
                            py++;
                        }
                        else if (destino == '#')
                        {
                            ReiniciarFase();
                        }
                    }
                    VerificarTeletransporte();
                    break;
                    VerificarTeletransporte();

                    // Atualiza posição do jogador
                    mapas[Nfase][px][py] = '&';
                    break;

                case 'a':
                case 'A': // Esquerda
                    if (py > 0)
                    {
                        char destino = mapas[Nfase][px][py - 1];
                        if (PodeMoverPara(px, py - 1))
                        {
                            py--;
                        }
                        else if (destino == '#')
                        {
                            ReiniciarFase();
                        }
                    }
                    VerificarTeletransporte();
                    break;
                    VerificarTeletransporte();

                    // Atualiza posição do jogador
                    mapas[Nfase][px][py] = '&';
                    break;

                case 's':
                case 'S': // Baixo
                    if (px < dimensoesfases[Nfase][0] - 1)
                    {
                        char destino = mapas[Nfase][px + 1][py];
                        if (PodeMoverPara(px + 1, py))
                        {
                            px++;
                        }
                        else if (destino == '#')
                        {
                            ReiniciarFase();
                        }
                    }
                    VerificarTeletransporte();
                    break;
                    VerificarTeletransporte();

                    // Atualiza posição do jogador
                    mapas[Nfase][px][py] = '&';
                    break;

                case 'w':
                case 'W': // Cima
                    if (px > 0)
                    {
                        char destino = mapas[Nfase][px - 1][py];
                        if (PodeMoverPara(px - 1, py))
                        {
                            px--;
                        }
                        else if (destino == '#')
                        {
                            ReiniciarFase();
                        }
                    }
                    VerificarTeletransporte();
                    break;
                    VerificarTeletransporte();

                    // Atualiza posição do jogador
                    mapas[Nfase][px][py] = '&';
                    break;

                case 'e':
                case 'E': // Interagir
                    if (falainicial == 0)
                    {
                        InteragirComObjetos();
                    }
                    break;
                }

                // Atualiza posição do jogador
                mapas[Nfase][px][py] = '&';
                VerificarTeletransporte();
            }
            break;

        case 1: // Créditos
            printf("\tDesenvolvido por:\n");
            printf("Programacao Por: Icaro Sousa, Daniel Silva, Rafael Albuquerque\n");
            printf("Design Do Jogo Por: Daniel Silva e Rafael Albuquerque\n");
            printf("Historia Do Jogo Por: Icaro Sousa\n");
            printf("\n\tAgradecimentos Especiais:\n");
            printf("A todos que apoiaram e jogaram Dungeons of Infernus!");
            break;

        case 2: // Sair
            printf("\033[1;31mOs portais de Dungeons of Infernus sempre estarao abertos para voce. Volte quando quiser, mas cuidado... o fogo do inferno nunca se apaga.\033[0m\n");
            exit(0);
        }
        getch();
        desenharmenu();
    }
}

int main(void)
{
    srand(time(NULL));   // Inicializa semente para números aleatórios
    printf("\033[?25l"); // Esconde cursor
    desenharmenu();

    while (1)
    {
        menu();
        entradamenu();
    }

    return 0;
}