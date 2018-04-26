#define uC18f4620
#include<18F4620.h>
#include<stdlib.h>
#include<string.h>
#fuses XT, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT//,BORV28
#fuses NOPBADEN, MCLR, STVREN, NOLVP, NODEBUG, 
#use delay(clock=16000000)
#use RS232

int operando1 = 0, operando2 = 0;
long resultado = 0;
char valor = 'Hola mundo';

void main (void){
	setup_oscillator(OSC_16MHZ | OSC_NORMAL);
	set_tris_D(0x00);
	while(1){
		if(kbhit == 1){
			valor = getch();
			operando1 = atoi(valor);
			printf("String value = %s, Int value = %d\n", valor, operando1);
		}
		//output_toggle(PIN_D0);
		//delay_ms(1);
	}
}		