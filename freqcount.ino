#include <avr/interrupt.h>
uint32_t count=0;
uint8_t overTimer=0;
float valor=0;
float A=234375/1048576; //constante de ajuste
void setup() {
  // put your setup code here, to run once:
  //setup timer 1
  TIMSK1=(1<<TOIE1); //habilita o timmer 1(16b)
  TCNT1=0x00; //valor inicial do contador
  TCCR1B = (1<<CS12); //prescale 256 
  //setup int0
  EICRA = (1 << ISC01)| (1 << ISC00);    // set INT0 to trigger on ANY logic change
  EIMSK |= (1 << INT0);    // Turns on INT0
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB=0x10;
  //atualiza o lcd
  valor=(0xffffff-count)*A;
  //print valor LCD
  delay(100);
}
//interrupção do timer
ISR(TIMER1_OVF_vect) {
     overTimer++;
}

//interrupção externa(encoder)
ISR(INT0_vect){
  count=(((TCNT1*overTimer)/12)+count)>>1;
  TCNT1=0;
  overTimer=1;
}
