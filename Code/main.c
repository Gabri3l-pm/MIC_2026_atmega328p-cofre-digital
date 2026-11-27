/*
*main.c
*
*Create: 10/05/2026 17:33:46 AM
*Author: Gabriel Demossi P. Machado, Lucas Cechin Mario
*/

/*
Projeto de cofre utilizando um microcontroladores atmega328p
*/

#define F_CPU 16000000  
#include <avr/io.h> 

int main(void) {
    // inicia sistema
    // carrega senha padrao
    
    // controle de tentativas
    uint8_t nTentativas = 0;
    
    // Variáveis dummy
    uint8_t enterPressed = 0; 
    uint16_t senhaDigitada = 0;
    uint16_t Senha = 0; 

    while(nTentativas <= 3) {
        // Mostrar mensagem: "Tentativas restantes: X"
        
        // Mostrar mensagem "Insira a Senha"
        
        while(!enterPressed) {
            // Se o botão for pressionado (nível baixo), enterPressed vira 1
            if(!(PIND & (1<<PIND2))) { 
                enterPressed = 1;
            }
            // envia para display...
        }
        enterPressed = 0; // Importante: reseta o botão para o próximo ciclo
/*
        while(!enterPressed) {
            // envia para display o número selecionado
            // armazena o número digitado até então
            // envia som bip curto caso uma tecla seja pressionada
        }

 O enterPressed começa em 0 e nunca muda para 1. No Python, 
 ele era uma variável mágica que o sistema atualizava sozinho. 
 No C para microcontrolador, você tem que ler o pino físico para saber se o botão foi apertado.
*/
        if(senhaDigitada == Senha) {
            // envia sinal para abrir
            // envia som de 3 bips curtos
            // Mostrar mensagem "Cofre Aberto"
        } else {
            // envia som longo
            // limpa display e senhaDigitada
            // Mostrar mensagem "Senha incorreta"
        }
        
        nTentativas = nTentativas + 1;
        
        if((3 - nTentativas) == 0) {
            // Mostrar mensagem "Cofre travado" e a mensagem a seguir
            // Mostrar mensagem: "Teclado Bloqueado por 20 segundos"
        }
    }
    
    return 0;
}