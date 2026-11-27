#ifndef TECLADO_H
#define TECLADO_H

/*
Inclui a biblioteca padrao de tipos inteiros com tamanho fixo em bits.
Usar uint8_t economiza memoria RAM e 
ciclos de clock em comparacao ao "int" tradicional.
*/
#include <stdint.h>

// Função responsável apenas por configurar os pinos do teclado na inicialização.
void teclado_init(void);

// char (antes): retorna 1 byte representando um caractere ASCII ('0' a 'F') ou 0.
// Faz uma leitura instantânea da matriz física do teclado.
char teclado_varrer(void);

// char (antes): retorna o caractere da tecla apenas no momento exato do aperto.
// Aplica o filtro de ruído (debounce) e a detecção de borda (não repete ao segurar).
char teclado_ler_tecla(void);

#endif