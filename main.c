#define F_CPU 32768ul//
#define nD 5//numero de dentes do encoder
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
//#include <lcd.h>
#include <stdlib.h>
//#include <delay.h>

   volatile uint32_t rpm;
   volatile uint8_t overTimer;
   volatile float freq;
   volatile unsigned int indice;
   volatile unsigned int average[10];
   volatile float correction;
   
int main(void)
{
   //CLKPR|=(1<<
   
   
   DDRB = 0xFF;			//seta portb como saída
   DDRC = 0x38;
   
   /*prepara a interrupção do encoder */
   DDRD  &= ~(1 << DDD2);     // Limpa o pino 2 ~ input
   PORTD |= (1 << PORTD2);    // habilita o pull up
   EICRA |= (1 << ISC10);    // triga a interrupção na borda de descida
   EIMSK |= (1 << INT0);     // throw a interrupção do encoder
   

   /* em tese, esse timer estoura a cada 0,2s @ 16MHz */
   ICR1 = 0x30D3;
   TCCR1B |= (1 << WGM12);
   TIMSK1 |= (1 << ICIE1);
   TCCR1B |= (1 << CS12);
    
   sei();                    // liga as interrupt
    
    while(1)
    {
     
      //freq = revo/timecount; 
     
    }
}
/*
void average_correction()
{
   if (indice > 10) { indice = 0; }
   average[indice] = revo/timecount;
   indice++;
   correction = correction + average[indice];
   revo=0;
   
}
*/
ISR(TIMER1_OVF_vect) //catch a interrupção do timer
{
    overTimer++;
	//timecount++;
    //average_correction();
}

ISR (INT0_vect)		//catch a interrupção do encoder
{
    rpm=(rmp+(15*(overTimer&(0xffff-TCNT1)))>>5)>>1; //resultado em RPMs do tempo medio de 2 pontos da revolucao
	TCNT1=0;	
	overTimer=0xffff;
}