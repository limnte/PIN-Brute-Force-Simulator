#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "menu.h"
#include "simulacao.h"


int gerar_pin(void){
    return rand() % 10000; // Gera um número aleatório entre 0 e 9999
}

void sim_auto(void){
    int pin_gerado = gerar_pin();
    int tentativa; 
    int tentativas_totais = 0;
    int error_seguidos = 0;
    
    int ordem[10000];

    for(int i = 0; i < 10000; i++){
        ordem[i] = i;
    }

    for(int i = 9999; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = ordem[i];
        ordem[i] = ordem[j];
        ordem[j] = temp;
    }

    printf(C0R_GREEN "=====================================\n");
    printf(C0R_BOLD C0R_WHITE "Ataque Brute-Force Automatico\n" C0R_RESET);
    printf(C0R_GREEN "====================================\n" C0R_RESET);
    printf(C0R_WHITE "O servidor fictio guarda um PIN aleatorio de 4 digitos.\n\n");

    printf(C0R_YELLOW "PIN gerado e protegido pelo servidor.\n\n" C0R_RESET);

    printf("\x1b[s");
    fflush(stdout);

    time_t inicio_wall = time(NULL);

    for(int i = 0; i < 10000; i++){
        tentativa = ordem[i];
        tentativas_totais++;

        /* volta pro ponto salvo e limpa o quadro anterior antes
           de desenhar o atual */
        printf("\x1b[u\x1b[J");
        barra_progresso(tentativas_totais, 10000);

        if(tentativa == pin_gerado){
            time_t fim_wall = time(NULL);
            double tempo_real = difftime(fim_wall, inicio_wall);

            printf("\n\n");
            printf(C0R_WHITE C0R_BOLD "PIN Descoberto:" C0R_GREEN " %04d\n" C0R_RESET, pin_gerado);
            printf(C0R_WHITE    "Tentativas necessarias : %d\n" C0R_RESET, tentativas_totais);
            printf(C0R_WHITE    "Tempo total (c/ delays): %.0fs\n" C0R_RESET, tempo_real);

            return;
        }else{
            error_seguidos++;
        }

        if(error_seguidos >= MAX_ERROS_SEGUIDOS){
            int delay = DELAY_FIXO_SEGUNDOS;

            printf("\n\n" C0R_RED C0R_BOLD "%d tentativas erradas seguidas! Servidor bloqueando..." C0R_RESET,
                   MAX_ERROS_SEGUIDOS);
            printf("\n" C0R_YELLOW "Aguardando %d segundo(s) antes de permitir nova tentativa" C0R_RESET, delay);

            fflush(stdout);

            for(int s = 0; s < delay; s++){
                sleep(1);
                printf(C0R_YELLOW "." C0R_RESET);
                fflush(stdout);
            }
            error_seguidos = 0;
        }
    }

    printf("\n\n" C0R_RED "ERRO: Todas as combinacoes possiveis foram tentadas (nao deveria acontecer).\n" C0R_RESET);
}

void sim_sem_delay(void){
    int pin_gerado = gerar_pin();
    int tentativas_totais = 0;
 
    int ordem[10000];
    for (int i = 0; i < 10000; i++) ordem[i] = i;
    for (int i = 9999; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = ordem[i];
        ordem[i] = ordem[j];
        ordem[j] = tmp;
    }

    printf(C0R_GREEN    "==============================\n");
    printf(C0R_WHITE   "    BRUTE-FORCE SEM DELAY\n");
    printf(C0R_GREEN    "==============================\n" C0R_RESET);
    printf(C0R_WHITE "Mesma busca, mas sem nenhuma espera entre tentativas." C0R_RESET);

    clock_t inicio = clock();
 
    for (int i = 0; i < 10000; i++) {
        tentativas_totais++;
        if (ordem[i] == pin_gerado) break;
    }

    clock_t fim = clock();
    double tempo_cpu = (double) (fim - inicio) / CLOCKS_PER_SEC;
 
        printf("\n\n");
        printf(C0R_WHITE C0R_BOLD "PIN Descoberto:" C0R_GREEN " %04d\n" C0R_RESET, pin_gerado);
        printf(C0R_WHITE    "Tentativas necessarias : %d\n" C0R_RESET, tentativas_totais);
        printf(C0R_WHITE    "Tempo de Execucao     : %.6fs\n" C0R_RESET, tempo_cpu);
}


void sobre_e_estatisticas(void) {
    printf(C0R_BOLD C0R_WHITE "===========================\n");
    printf(C0R_BOLD C0R_WHITE "  Como funciona a defesa\n" C0R_RESET);
    printf(C0R_BOLD C0R_WHITE "===========================\n");
    printf("Um PIN de 4 digitos tem 10.000 combinacoes (0000-9999).\n\n");

    printf(C0R_RESET C0R_YELLOW "SEM delay:\n" C0R_RESET);
    printf("    Um programa testa as 10 mil opcoes em milissegundos.\n\n");

    printf(C0R_YELLOW "COM delay (lockout):\n" C0R_RESET);
    printf("    A cada %d erros, o tempo de espera e de %ds,\n"
           "    tornando o ataque mais lento na pratica.\n\n", MAX_ERROS_SEGUIDOS, DELAY_FIXO_SEGUNDOS);

    printf(C0R_WHITE "Tecnicas reais usadas por sistemas de verdade:\n" C0R_RESET);
    printf("    - Rate limiting (limite de tentativas por tempo)\n"
           "    - Bloqueio temporario/permanente da conta\n"
           "    - CAPTCHA apos N tentativas\n"
           "    - Autenticacao em duas etapas (2FA)\n");
}