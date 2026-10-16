# PIN Brute-Force Simulator
 
Simulador educacional de ataque de força bruta contra um PIN numérico de 4 dígitos, escrito em C. O projeto demonstra, na prática, por que mecanismos de bloqueio (delay/lockout) após tentativas erradas são essenciais para a segurança de sistemas de autenticação.(Embora eu não tenha feito o bloqueio ser progressivo)
 
Todo o "servidor" é fictício e roda localmente, dentro do próprio programa — nenhuma rede, serviço externo ou sistema de terceiros é acessado.
 
## Sobre o projeto
 
O programa gera um PIN secreto de 4 dígitos (0000 a 9999) e tenta descobri-lo por força bruta, testando combinações em ordem aleatória. Dois modos de ataque são oferecidos: um sem nenhuma proteção e outro com um mecanismo de bloqueio que entra em ação após uma sequência de tentativas erradas. Comparando os dois, fica visível o quanto um delay simples já torna um ataque de força bruta impraticável.
 
## Funcionalidades
 
- Geração de PIN aleatório de 4 dígitos
- Simulação de ataque **sem delay**, para medir a velocidade bruta do algoritmo de busca
- Simulação de ataque **automático com delay**: a cada sequência de tentativas erradas, o "servidor" bloqueia novas tentativas por alguns segundos
- Medição de tempo de execução usando `time.h` (tentativas, tempo total decorrido)

## Como funciona
 
1. Um PIN secreto de 4 dígitos é sorteado com `rand()`.
2. As 10.000 combinações possíveis (`0000` a `9999`) são embaralhadas, simulando um atacante que não sabe o PIN e não testa em ordem sequencial óbvia.
3. O programa percorre essa lista testando cada combinação contra o PIN secreto.
4. No modo **com delay**, a cada `N` tentativas erradas seguidas, o programa pausa por `D` segundos antes de continuar, simulando um bloqueio real de segurança.
5. Ao final, são exibidas estatísticas: número de tentativas necessárias e tempo total gasto.
Os valores de `N` (tentativas erradas seguidas) e `D` (duração do bloqueio em segundos) são constantes definidas em `simulacao.h`:
 
```c
#define MAX_ERROS_SEGUIDOS 5
#define DELAY_FIXO_SEGUNDOS 3
```
 
## Estrutura dos arquivos
 
```
.
├── main.c         # Ponto de entrada: loop do menu principal
├── menu.c         # Implementação da interface (banner, menu, barra de progresso)
├── menu.h         # Cores ANSI e protótipos das funções de interface
├── simulacao.c    # Lógica do simulador (geração de PIN, ataques, estatísticas)
└── simulacao.h    # Constantes e protótipos da lógica do simulador
```
 
## Compilação
 
Requer um compilador C (GCC recomendado).
 
```bash
gcc -Wall -Wextra -o brute_pin main.c menu.c simulacao.c
```
 
No Windows (gerando `brute_pin.exe`):
 
```bash
gcc -Wall -Wextra -o brute_pin.exe main.c menu.c simulacao.c
```

## Uso
 
Após compilar:
 
```bash
./brute_pin
```
 
O menu principal oferece as seguintes opções:
 
```
[1] Simular ataque SEM delay
[2] Simular ataque automático (com delay)
[3] Sobre
[0] Sair
```
 
## Conceitos praticados
 
- **`time.h`**: medição de tempo com `time()`, `difftime()` e `clock()`
- **`unistd.h`**: uso de `sleep()` para simular o atraso de segurança
- Lógica de **lockout / backoff** após tentativas de autenticação malsucedidas
- Embaralhamento de arrays (algoritmo de Fisher-Yates)
- Códigos de escape ANSI para interface de terminal (cores, limpeza de tela, controle de cursor)
## Possíveis melhorias
 
- Delay progressivo (crescente a cada novo bloqueio) em vez de fixo
- Bloqueio permanente após um número máximo de tentativas
- Registro de estatísticas em arquivo
- Modo manual, em que o próprio usuário tenta adivinhar o PIN
## Detalhe...
 
Este projeto tem fins  educacionais, para o meu estudo de lógica de programação e conceitos básicos de segurança. Ele não deve ser usado, nem serve como base, para tentar acessar sistemas reais sem autorização.
 
