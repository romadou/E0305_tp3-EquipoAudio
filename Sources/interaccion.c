/*
 * interaccion.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */
#include "interaccion.h"
#include "SCI.h"

extern unsigned int errorDeReproduccion;
static unsigned rxchar;
static unsigned char buffer_rx[32];
static char indexR;

unsigned char numero (unsigned char input);
unsigned char letra (unsigned char input);

void INTERACCION_init(){
	SCI_write_string_to_buffer("\r\nBIENVENIDOS AL PROGRAMA");
	SCI_write_string_to_buffer("\r\nESCOGER MODO DE FUNCIONAMIENTO:");
	SCI_write_string_to_buffer("\r\n Modo F: Sonido de frecuencia fija");
	SCI_write_string_to_buffer("\r\n Modo B: Barrido de frecuencias");
	SCI_write_string_to_buffer("\r\n(ingresar la letra correspondiente al modo deseado)");
}

void INTERACCION_default(){
	SCI_write_string_to_buffer("\r\nDESDE ESTE MOMENTO, EL PROGRAMA SE SIRVE DE LOS SIGUIENTES COMANDOS:");
	SCI_write_string_to_buffer("\r\n ON: Iniciar reproducción de sonido");
	SCI_write_string_to_buffer("\r\n OFF: Detener reproducción de sonido");
	SCI_write_string_to_buffer("\r\n RESET: Reiniciar programa");
}

void INTERACCION_askF(){
	SCI_write_string_to_buffer("\r\nINGRESAR LA FRECUENCIA DE SONIDO QUE DESEA ESCUCHAR:");
	SCI_write_string_to_buffer("\r\n Rango de freciencias posibles: [200 Hz - 10 KHz] con un paso de 100 Hz");
}

void INTERACCION_askB(){
	SCI_write_string_to_buffer("\r\nINGRESE EL MODO DE BARRIDO QUE DESEA:");
	SCI_write_string_to_buffer("\r\n T1: 5 seg");
	SCI_write_string_to_buffer("\r\n T2: 10 seg");
	SCI_write_string_to_buffer("\r\n T3: 15 seg");
	SCI_write_string_to_buffer("\r\n(ingresar el numero correspondiente al barrido escogido)");
} 

void INTERACCION_showError(unsigned char e){
	SCI_write_string_to_buffer("\r\n EL ERROR PRODUCIDO POR LA FRECUENCIA SELESCIONADA ES MAYOR A" + e);
}

unsigned char INTERACCION_analiceInput (void){
	static char flag_n=0;
	if (SCI_receive_char()){
		//buffer_rx =pedir buffer entrada
		rxchar=*buffer_rx;
		while(rxchar!='\n'){
			if (numero(rxchar)){
				if (!indexR & !flag_n)
					flag_n=1;
				else{
					if (indexR & !flag_n)
						return 2;
				}
			}
			else{
				if (letra (rxchar)){
					if (flag_n){
						return 2;
					}
				}
				else{
					return 2;
				}
			}
			buffer_rx++;
			indexR++;
			rxchar=*buffer_rx;
		}
		return 1;
	}
	return 0;
}

unsigned char INTERACCION_getInput (void){
	static char flag_n=0;
	char i, num;
	//buffer_rx=pedir entrada;
	if (rxchar!='\n'){
		if (numero(rxchar)){
			for (i=0;i<indexR;i++){
				num+=(buffer_rx[i]-'0')*(10^(indexR-i-1));
			}
			return num;
		}
		else
			
	}
}


unsigned char numero(unsigned char input){
	if ((tecla >= '0') && ('9' >= tecla)) return 1;
	return 0;
}

unsigned char letra (unsigned char input){
	static char comandos[] =
		{'O','o','N','n', 'F','f',
		'R','r','E','e','S','s', 'T','t'
		};
	return conmandos[input];
}
