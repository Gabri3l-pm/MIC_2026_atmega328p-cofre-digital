#include "configuracao.h"
#include "teclado.h"

/* (Matriz bidimensional de 4 linhas por 4 colunas)

static: variável PRIVADA para o arquivo teclado.c.
Nenhum outro arquivo consegue enxergar ou bagunçar ela.
const: avisa que esses valores são somente para leitura
char: cada posição guarda 1 caractere da tabela ASCII
*/
static const char mapa_teclas[4][4] = {
    {'0', '1', '2', '3'}, // Linha 0 (RB0 na bancada)
    {'4', '5', '6', '7'}, // Linha 1 (RB1 na bancada)
    {'8', '9', 'A', 'B'}, // Linha 2 (RB2 na bancada)
    {'C', 'D', 'E', 'F'}  // Linha 3 (RB3 na bancada)
};

/* 
VETORES DE MAPEAMENTO DOS PINOS:
Em vez de escrever o mesmo código 4 vezes,
guarda o número do bit de cada pinodentro de dois vetores de 4 posições
Dái da para varrer ele com um for

uint8_t: cada número de pino vai apenas de 0 a 7, então cabe em 8 bits.
 */
static const uint8_t pinos_linhas[4]  = { LINHA_0, LINHA_1, LINHA_2, LINHA_3 };
static const uint8_t pinos_colunas[4] = { COL_0,   COL_1,   COL_2,   COL_3   };

/*
FUNÇÃO 1: teclado_init
Chama UMA ÚNICA VEZ no início da main(), antes do while(1).
Configura a direção e o estado inicial dos 8 pinos.
*/
void teclado_init(void) {
    //Varre a matriz como dito antes
    for (uint8_t i = 0; i < 4; i++) {
        // Linhas como saída em nível ALTO (repouso)
        /*
        Botar no config.h
        // Exemplo do que vai pro configuracao.h depois:
        #define TECLADO_LINHA_DDR   DDRD
        #define TECLADO_LINHA_PORT  PORTD
        #define TECLADO_COL_DDR     DDRB
        #define TECLADO_COL_PORT    PORTB
        #define TECLADO_COL_PIN     PINB
        */
        TECLADO_LINHA_DDR  |= (1 << pinos_linhas[i]);
        TECLADO_LINHA_PORT |= (1 << pinos_linhas[i]);

        // Colunas como entrada com pull-up interno ativado
        TECLADO_COL_DDR  &= ~(1 << pinos_colunas[i]);
        TECLADO_COL_PORT |=  (1 << pinos_colunas[i]);
    }
}

/*
FUNÇÃO 2: teclado_varrer
Testa as 16 combinações (4 linhas x 4 colunas)
e devolve o caractere da tecla pressionada no instante atual.
*/
char teclado_varrer(void) {
    for (uint8_t l = 0; l < 4; l++) {
        // Ativa a linha atual colocando-a em nível BAIXO (0)
        TECLADO_LINHA_PORT &= ~(1 << pinos_linhas[l]);
        _delay_us(5); // Estabilização elétrica do sinal

        // Verifica as 4 colunas
        for (uint8_t c = 0; c < 4; c++) {
            if (!(TECLADO_COL_PIN & (1 << pinos_colunas[c]))) {
                // Restaura a linha para nível ALTO antes de sair
                TECLADO_LINHA_PORT |= (1 << pinos_linhas[l]);
                return mapa_teclas[l][c];
            }
        }

        // Desativa a linha atual (volta para nível ALTO)
        TECLADO_LINHA_PORT |= (1 << pinos_linhas[l]);
    }

    return 0; // Nenhuma tecla pressionada
}

/*
FUNÇÃO 3: teclado_ler_tecla
Essa é a que a main() vai chamar de verdade.
Resolve dois BO
  1) Ruído mecânico (debounce): a chapinha do botão treme quando encosta.
  2) Usuario lento que fica com o dedo no teclado.
*/
char teclado_ler_tecla(void) {
    //static DENTRO de função faz ela ter "memória".
    //Ela começa em 0 só na 1ª vez; depois lembra qual tecla tava apertada na volta passada.
    static char anterior = 0;

    // Pergunta pro hardware o que tá sendo apertado agora ('0'..'F' ou 0)
    char atual = teclado_varrer();

    // DETECÇÃO DE BORDA (SOBE/dece):
    // Só entra se AGORA tem tecla apertada (atual != 0) E ANTES tava tudo solto (anterior == 0).
    // Se o cara continuar com o dedo grudado no botão, 'anterior' não é 0, então ignora.
    if (atual != 0 && anterior == 0) {
        // Espera 20 ms pra tremedeira mecânica do botão passar (debounce)
        _delay_ms(20);

        // Confere de novo: depois de 20 ms ainda é a MESMA tecla? Então é clique real, não ruído
        if (teclado_varrer() == atual) {
            anterior = atual; // Trava o esquema lembrando que essa tecla já foi contada
            return atual;     // Entrega a tecla limpa pra main() (só 1 vez por clique!)
        }
    } else if (atual == 0) {
        // O usuário tirou o dedo do botão (varredura voltou 0).
        // Zera o 'anterior' pra destravar e aceitar o próximo clique (até da mesma tecla)
        anterior = 0;
    }

    // Se nada foi apertado, se o dedo ainda tá segurando ou se foi só ruído: devolve 0 (nada novo)
    return 0;
}