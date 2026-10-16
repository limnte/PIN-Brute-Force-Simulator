#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "menu.h"
#include "simulacao.h"

int main(){
    srand((unsigned int)time(NULL));
    int opcao;

    do{
        limpar_tela();
        exibir_banner();
        exibir_menu();

        printf(C0R_BOLD C0R_WHITE"\nDigite a opcao desejada: " C0R_RESET);

        if(scanf("%d", &opcao) != 1) {
            /* limpa entrada inválida */
            while (getchar() != '\n');
            opcao = -1;
        }
        
        while (getchar() != '\n');

        switch(opcao){
            case 1:
                limpar_tela();
                sim_sem_delay();
                pausar();
                break;
            case 2:
                limpar_tela();
                sim_auto();
                pausar();
                break;
            case 3:
                limpar_tela();
                sobre_e_estatisticas();
                pausar();
                break;
            case 0:
                limpar_tela();
                break;
            default:
                printf(C0R_RED "\nOpcao invalida! Tente novamente.\n" C0R_RESET);
                getchar();
        }
    } while(opcao != 0);

    return 0;
}

