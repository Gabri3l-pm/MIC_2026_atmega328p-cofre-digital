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

#include <xc.h>
#include <stdint.h>
#include "util/delay.h"

void GPIO_config(void) {
    DDRB |= (1<<DDB5);
}

int main(void) {

    GPIO_config();

    while(1) {

        PORTB |= (1<<PORTB5);
        _delay_ms(500);

        PORTB &= ~(1<<PORTB5);
        _delay_ms(500);

    }
}