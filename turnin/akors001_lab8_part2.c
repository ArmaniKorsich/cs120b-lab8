
/*	Author: armanikorsich
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
    
    TCCR1B = 0x0b;
    OCR1A = 125;
    TIMSK1 = 0x02;
    TCNT1 = 0;
    
    _avr_timer_cntcurr = _avr_timer_M;
    SREG |= 0x80;
}

void Timerff() {
    TCCR1B = 0x00;
}

void TimerISR() {
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0) {
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}


enum SM_States {START} state;
unsigned short x = 0;
unsigned short MAX = 0b1100000000;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | ( 1 << ADSC) | (1 << ADATE);
}

void TickFct() {
	switch(state) {
		case START:
			x = ADC;
			PORTB = (char)(x);	
			PORTD = (char)(x>>8);
			break;
		default:
			break;

	}

}
int main(void) {
	/* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    	

    TimerSet(300);
    TimerOn();
	ADC_init();
    PORTB = 0x01;
    /* Insert your solution below */
    while (1) {
//        while (!TimerFlag);
//        TimerFlag = 0;
   	TickFct();
	}
    return 1;    

}


