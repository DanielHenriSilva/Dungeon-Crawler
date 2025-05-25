#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MaximoDeLinhas 45
#define MaximoDeColunas 45
#define TFases 4

char mapas[TFases][MaximoDeLinhas][MaximoDeColunas];
char chaos[TFases][MaximoDeLinhas][MaximoDeColunas];

int dimensoesfases[TFases][2] =
    {
        {15, 15}, // Fase 0: Vila
        {15, 15}, // Fase 1: Dungeon 1
        {25, 25}, // Fase 2: Dungeon 2
        {45, 45}  // Fase 3: Dungeon 3
};

int pxinicial[TFases] = {1, 1, 1, 1}, pyinicial[TFases] = {1, 1, 1, 1};

int px, py;
int dialogo = 0, Nfase = 0, tutorial = 1;

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

    // Adiciona elementos específicos de casa fase
    if (fase == 0) // Fase Da Vila
    {
        mapas[fase][1][2] = 'P';
        mapas[fase][12][7] = 'D';
        mapas[fase][13][13] = '@';
    }
    else if (fase == 1) // Dungeon 1
    {
        mapas[fase][5][5] = 'P';
        mapas[fase][12][7] = 'D';
        mapas[fase][13][13] = '@';
    }
    else if (fase == 2) // Dungeon 2
    {
        mapas[fase][12][7] = 'D';
        mapas[fase][13][13] = '@';
    }

    // Adiconar os outros mapas

    if (fase == Nfase)
    {
        mapas[fase][pxinicial[fase]][pyinicial[fase]] = '&';
    }
}

void RenderizarMapa()
{
    int linhas = dimensoesfases[Nfase][0];
    int colunas = dimensoesfases[Nfase][1];

    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

    int i = 0, j = 0;
    while (i < linhas)
    {
        j = 0;
        while (j < colunas)
        {
            printf("%c ", mapas[Nfase][i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}

void TrocarFase(int novafase)
{
    mapas[Nfase][px][py] = chaos[Nfase][px][py]; // Limpa Jogador Na Fase Atual

    // Att Fase
    Nfase = novafase;
    px = pxinicial[Nfase];
    py = pyinicial[Nfase];

    // Coloca Jogador Na Nova Fase
    mapas[Nfase][px][py] = '&';

    system("cls");
    Sleep(500);
    printf("Descendo Para o Andar %d...Cada Vez Mais Perto Do Inferno!", Nfase + 1);
    system("cls");

    RenderizarMapa();
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

            int fase = 0;
            while (fase < TFases)
            {
                IniFase(fase);
                fase++;
            }

            // Coloca o Jogador Na Fase Inicial
            Nfase = 0;
            px = pxinicial[Nfase];
            py = pyinicial[Nfase];
            mapas[Nfase][px][py] = '&';

            while (1)
            {
                COORD pos = {0, 0};
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

                // Carrega Mapa Atual
                int linhas = dimensoesfases[Nfase][0];
                int colunas = dimensoesfases[Nfase][1];

                int i = 0, j = 0;
                while (i < linhas)
                {
                    j = 0;
                    while (j < colunas)
                    {
                        printf("%c ", mapas[Nfase][i][j]);
                        j++;
                    }
                    printf("\n");
                    i++;
                }

                if (tutorial == 1)
                {
                    dialogo = 1;
                    printf("Anciao: Ola Aventureiro, Vamos Para Um Breve Tutorial, Use 'WASD' Para Andar, Use 'E' Para Interagir Com 'P'(NPC), '@'(Chave), 'O'(Botao)\n");
                    printf("\033[3;35HLegenda Dos Caracteres:\033[4;35H'P' = NPC\033[5;35H'@' = Chave\033[6;35H'O' = Botao" 
                    "\033[7;35H'D' = Porta\033[8;35H'=' = Porta Aberta\033[9;35H'#' = Espinhos\033[10;35H'*' = Parede\033[11;35H'>' = Teletransporte"
                    "\033[12;35H'X' = Monstro Nivel 1\033[13;35H'V' = Monstro Nivel 2");

                    while (dialogo == 1)
                    {
                        input = getch();
                        if (input == 101 || input == 27 || input == 69)
                        {
                            dialogo = 0;
                            printf("\033[16;1H\033[K");
                            tutorial = 0;
                        }
                    }
                }

                input = getch();

                // Limpa Posição
                mapas[Nfase][px][py] = chaos[Nfase][px][py];

                if (input == 39)
                {
                    inicio = 1;
                    goto ini;
                }

                // Verifica se está na porta aberta para trocar de mapa
                if (mapas[Nfase][px][py] == '=')
                {
                    if (Nfase < TFases - 1)
                    {
                        TrocarFase(Nfase + 1);
                    }
                    else
                    {
                        printf("Você chegou ao nível mais profundo do inferno!");
                    }
                }

                switch (input)
                {
                case 'd':
                case 'D':
                    if (py < dimensoesfases[Nfase][1] - 1)
                    {
                        char proximo = mapas[Nfase][px][py + 1];
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            py++;
                        }
                    }
                    break;

                case 'a':
                case 'A':
                    if (py > 0)
                    {
                        char proximo = mapas[Nfase][px][py - 1];
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            py--;
                        }
                    }
                    break;

                case 's':
                case 'S':
                    if (px < dimensoesfases[Nfase][0] - 1)
                    {
                        char proximo = mapas[Nfase][px + 1][py];
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            px++;
                        }
                    }
                    break;

                case 'w':
                case 'W':
                    if (px > 0)
                    {
                        char proximo = mapas[Nfase][px - 1][py];
                        if (proximo != '*' && proximo != '#' && proximo != 'P' && proximo != 'D' && proximo != '@' && proximo != ' ')
                        {
                            px--;
                        }
                    }
                    break;

                case 'e':
                case 'E':
                    if (tutorial == 0)
                    {
                        int i = px - 1;
                        while (i <= px + 1)
                        {
                            int j = py - 1;
                            while (j <= py + 1)
                            {
                                // Verifica se está dentro dos limites do mapa
                                if (i >= 0 && i < dimensoesfases[Nfase][0] &&
                                    j >= 0 && j < dimensoesfases[Nfase][1])
                                {

                                    char obj = mapas[Nfase][i][j];
                                    if (obj == 'P')
                                    {
                                        dialogo = 1;
                                        if(Nfase == 0)
                                        {
                                            printf("\033[s");
                                            printf("\n");
                                            printf("\n\033[1mAnciao: Esse eh o grande abismo do inferno, dizem que a seculos ou milenios atras,"
                                            " caiu um grande meteoro carregado de magia bem nesse lugar, e fez essa \ncratera enorme,"
                                            " com o passar dos seculos, os aventureiros tentaram explorar o abismo para obter recursos,"
                                            " e perceberam que os recursos eram extremamente \nabundantes, diversos itens magicos e materiais "
                                            "de valor altissimo, e fazendo diversas obras de construcao, tijolo por tijolo ate formar uma grande"
                                            " masmorra \ncom centenas, ou ate milhares de andares, agora milenios depois nossa vila foi construida"
                                            " em volta dessa masmorra e nos nao conhecemos o responsavel pela \nconstrucao e muito menos o quao profunda"
                                            " ela pode ir, so sabemos que varios aventureiros descem e poucos dos que exploram os andares mais profundos"
                                            " \nconseguem retornar.\033[0m");
                                        }

                                        while (dialogo == 1)
                                        {
                                            input = getch();
                                            if (input == 101 || input == 27 || input == 69)
                                            {
                                                printf("\033[u");
                                                printf("\033[0J");
                                                dialogo = 0;
                                            }
                                        }
                                    }
                                    else if (obj == '@')
                                    {
                                        mapas[Nfase][i][j] = '.';
                                        printf("Voce coletou um item especial!");
                                        Sleep(500);
                                        printf("\033[16;1H\033[K");

                                        // Na Vila, transforma a porta em '=' quando pega o item
                                        if (Nfase == 0)
                                        {
                                            mapas[0][12][7] = '=';
                                            chaos[0][12][7] = '=';
                                        }

                                        else if (Nfase == 1)
                                        {
                                            mapas[1][12][7] = '=';
                                            chaos[1][12][7] = '=';
                                        }
                                        else if (Nfase == 2)
                                        {
                                            mapas[2][12][7] = '=';
                                            chaos[2][12][7] = '=';    
                                        }
                                    }
                                }
                                j++;
                            }
                            i++;
                        }
                    }
                    break;
            }

            // Atualiza a posição do jogador
            mapas[Nfase][px][py] = '&';
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

    while (1)
    {
        menu();
        entradamenu();
    }

    return 0;
}