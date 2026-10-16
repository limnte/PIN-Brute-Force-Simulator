#ifndef MENU_H
#define MENU_H

#define C0R_RESET   "\x1b[0m"
#define C0R_RED     "\x1b[31m"
#define C0R_GREEN   "\x1b[32m"
#define C0R_YELLOW  "\x1b[33m"
#define C0R_WHITE   "\x1b[97m"
#define C0R_BOLD    "\x1b[1m"

void limpar_tela(void);
void pausar(void);
void exibir_banner(void);
void exibir_menu(void);
void barra_progresso(int atual, int toal);

#endif // MENU_H