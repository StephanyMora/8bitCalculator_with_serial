#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)

void mostrarResultado(long resultado);
void funcionError();
       

void main (void){
   setup_oscillator(OSC_16MHZ);
   setup_adc_ports(NO_ANALOGS);
   
   set_tris_a(0xc0);
   set_tris_b(0xf0);
   set_tris_c(0xff);
   set_tris_d(0xff);
   set_tris_e(0xf8);
     	   
   int numeroPuertoC, numeroPuertoD;
   long resultado;
   
   while(1){
      numeroPuertoC = input_c();
      numeroPuertoD = input_d();
      if(input(PIN_B4) == 1){
         resultado = numeroPuertoC + numeroPuertoD;
         mostrarResultado((long)resultado);
      }
      else if (input(PIN_B5) == 1){
         if(numeroPuertoD > numeroPuertoC){
            resultado = numeroPuertoC - numeroPuertoD;
            mostrarResultado((long)resultado);
         }
         else{
            resultado = numeroPuertoC - numeroPuertoD;
            mostrarResultado((long)resultado);
         }
      }    
      else if(input(PIN_B6) == 1){
         resultado = numeroPuertoC * numeroPuertoD;
         mostrarResultado((long)resultado);
      }    
      else if(input(PIN_B7) == 1){
         if(numeroPuertoD == 0 || numeroPuertoD > numeroPuertoC){
            funcionError();   
         }
         else{
            resultado = numeroPuertoC / numeroPuertoD;
            mostrarResultado((long)resultado);
         }
      }   
      resultado = 0;
   }
}

void funcionError(){
   long ledEncendido = 8191, ledApagado = 0;
   output_a(ledEncendido);
   output_b(ledEncendido >> 6);
   output_e(ledEncendido >> 10);
   delay_ms(500);
   output_a(ledApagado);
   output_b(ledApagado >> 6);
   output_e(ledApagado >> 10);
   delay_ms(500);	
   break;
} 

void mostrarResultado(long resultado){
   output_a(resultado);
   output_b(resultado >> 6);
   output_e(resultado >> 10);
   break;
}
	
