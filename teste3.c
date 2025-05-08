#include <stdio.h>

int main() {
    // Códigos ANSI para cores e estilos
    printf("\033[1;31m"); // Vermelho brilhante
    printf("Dungeons Of - Estilo Vermelho\n");
    printf("\033[0m"); // Resetar para padrão
    
    printf("\033[1;34;47m"); // Azul brilhante com fundo branco
    printf("Dungeons Of - Estilo Azul com Fundo\n");
    printf("\033[0m");
    
    printf("\033[3;35m"); // Itálico magenta
    printf("Dungeons Of - Estilo Itálico\n");
    printf("\033[0m");
    
    return 0;
}