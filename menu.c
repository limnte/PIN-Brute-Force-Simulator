#include <stdio.h>
#include "menu.h"

void limpar_tela(void){
    printf("\x1b[2J\x1b[H");
}

void pausar(void){
    printf(C0R_WHITE "\nPressione ENTER para continuar...");
    getchar();
}

void exibir_banner(void){
    printf(C0R_GREEN    "==============================\n");
    printf(C0R_WHITE   "      PIN BRUTE-FORCE\n");
    printf(C0R_GREEN    "==============================\n" C0R_RESET);
    printf("Security test tool developed by: " C0R_YELLOW "Limntee" C0R_RESET "\n");
}

void exibir_menu(void){
    printf("\n\n" C0R_RESET);
    printf(C0R_GREEN "[1]" C0R_RESET " Simular ataque SEM delay\n");
    printf(C0R_GREEN "[2]" C0R_RESET " Simular ataque automatico(Com delay)\n");
    printf(C0R_GREEN "[3]" C0R_RESET " Sobre\n");
    printf(C0R_GREEN "[0]" C0R_RESET " Sair\n");
    printf("------------------------------\n" C0R_RESET);
}

void barra_progresso(int atual, int total){
    int largura = 30;
    float proporcao = (float)atual / (float)total; 
    int preenchido = (int)(proporcao * largura);

    printf("\r[" C0R_GREEN);

    printf("\r  [" C0R_GREEN);

    for (int i = 0; i < preenchido; i++) printf("-");

    printf(C0R_WHITE);

    for (int i = preenchido; i < largura; i++){
        printf("=");
    }
    

    printf(C0R_RESET "] %5.1f%%  (%d/%d)", proporcao * 100, atual, total);

    fflush(stdout);

}