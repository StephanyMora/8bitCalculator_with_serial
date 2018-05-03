#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)

#use RS232(baud = 9600, xmit = pin_c6, rcv = pin_c7, parity = N, bits = 8, stream = uart)

void mostrarResultado(long resultado);
void funcionError();
void limpiarVariables();

set_tris_a(0b00000010);
set_tris_b(0x00);
set_tris_e(0xf8);
       
unsigned int operando1 = 0, operando2 = 0, indice = 0, flag = 0;
signed long resultado = 0;
unsigned char lectura[12] = "";
char operacion;   

void main (void){
   setup_oscillator(OSC_16MHZ);
   setup_adc_ports(NO_ANALOGS);
   printf("INGRESE 2 NUMEROS Y LA OPERACION A EFECTUAR CON EL SIGUIENTE FORMATO\n\r");
   printf("             >Operando 1, Operando 2, Operacion<: \t\n\r");
   while(1){
      if(kbhit()){      
         lectura[indice] = getch(uart);
         
         if(lectura[indice] == 13){
            flag = 1;
         }
         
         if(lectura[indice] >= 42 && lectura[indice] <= 57){
            indice++;       
         }       
      }   
      if(flag == 1){
         indice = 0;
         while(lectura[indice] != ','){
            operando1 = operando1 * 10 + (lectura[indice] - '0');
            indice++;
         }
         indice++;
         while(lectura[indice] != ','){
      	    operando2 = operando2 * 10 + (lectura[indice] - '0');
      	    indice++;
         }
         indice++;
         operacion = lectura[indice];
         fprintf(uart, "Operando 1: %f\t\n\r",(float)operando1);
         fprintf(uart, "Operando 2: %f\t\n\r",(float)operando2);
         switch(operacion){
            case '+':
               resultado = (long)operando1 + (long)operando2;
               fprintf(uart, "Resultado: %f\t\n\r",(float)resultado);
               mostrarResultado((long)resultado);
               break;
            case'-':
               resultado = (long)operando1 - (long)operando2;
               fprintf(uart, "Resultado:  %f\t\n\r",(float)resultado);
               mostrarResultado((long)resultado);
               break;
            case'*':
               resultado = (long)operando1 * (long)operando2;
               fprintf(uart, "Resultado:  %f\t\n\r",(float)resultado);
               mostrarResultado((long)resultado);
               break;
            case'/':
               if(operando2 == 0){
                  fprintf(uart, "ERROR: La division entre cero esta indeterminada\t\n\r");
                  funcionError();
               }
               else{
                  resultado = (long)operando1 / (long)operando2;
                  fprintf(uart, "Resultado:  %.0f\t\n\r",(float)resultado);
                  mostrarResultado((long)resultado);
               }
               break;
         }        
         flag = 0;      
      limpiarVariables();
      }
   }
}
   
void limpiarVariables(){
   operando1 = 0;
   operando2 = 0;
   resultado = 0;
   operacion = null;
   indice = 0;
   for(indice = 0; indice < 12; indice++){
      lectura[indice] = null;
   }
   break;
}

void funcionError(){
   long ledEncendido = 65535, ledApagado = 0;
   output_a(ledEncendido);
   output_b(ledEncendido >> 6);
   output_e(ledEncendido >> 13);
   delay_ms(500);
   output_a(ledApagado);
   output_b(ledApagado >> 6);
   output_e(ledApagado >> 13);
   delay_ms(500);	
   break;
} 

void mostrarResultado(long resultado){
   output_a(resultado);
   output_b(resultado >> 6);
   output_e(resultado >> 13);
   break;
}

