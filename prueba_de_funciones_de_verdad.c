//Configurar fusibles necesarios
#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)

//Anexamos la directiva del protocolo de comunicación serie RS232 con sus respectivos parámetros
#use rs232(baud = 9600, xmit = pin_c6, rcv = pin_c7, parity = N, bits = 8)


void mostrarResultado(long resultado);
void funcionError();
       

void main (void){
   setup_oscillator(OSC_16MHZ);
   setup_adc_ports(NO_ANALOGS);
   
   //Configurar el puerto C (el pin RC6 debe ser de salida y el RC7 de entrada)
   set_tris_c(00000001);
     	   
   //Crear las variable de 8 bits sin signo operando1 y operando2    
   unsigned short int operando1, operando2;

   /*Crear una cariable de tipo entero igual a 0 que funja como indice para recorrer un vector*/
   int indice = 0;

   //Crear la variable de 16 bits sin signo resultado
   long resultado;

   /*crear el vector tipo char para leer la cadena que introduzca el usuario*/
   char lectura[12] = "";

   /*Crear variable que guarde la operacion*/
   char operacion;
   
   //Abrir un ciclo dentro del cual se ejecutarán las siguientes instrucciones
   while(1){
   //Revisar si el usuario ha introducido un dato
      if(kbhit == 1){
         //Si el usuario ha introducido un dato guardarlo
         lectura[indice] = getch();      	
         indice++;	
      }
      //Transformar el dato a un número de 8 bits
      while(lectura[indice] != ','){
      	operado1 == operando1 * 10 - (lectura[indice] - '0');
        indice++;
      }
      while(lectura[indice] != ','){
      	operado2 == operando2 * 10 - (lectura[indice] - '0');
      	indice++;
      }
      while(lectura[indice] != '>'){
      	operacion == (lectura[indice] - '0');
      }
   //Realizar la operación que ha seleccionado el usuario
      switch(operacion){
         case'+':
            resultado = (long)(operando1 + operando2);
            //fijate como imprimir el dato      
            break;
         case'-':
            if(operando2)
            resultado = (long)(operando1 - operando2);
            //fijate como imprimir el dato      
            break;
         case'*':
            resultado = (long)(operando1 * operando2);
            //fijate como imprimir el dato      
            break;
         case'/':
            if(operando2 == 0){
            	//llamar funcion error
               printf("Dato%s\n", );
            }
            //si operando2 > operando1, hacer la operacion y mostrar el resultado, como tipo FLOAT PORQUE SERÁ UNA FRACCIÓN
            //sino, se hace la operación como si nada
            resultado = (long)(operando1 / operando2);      
            break;            
      }
   //Retornar el resultado   	
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