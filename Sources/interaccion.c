/*
 * interaccion.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */
#include "interaccion.h"
#include "SCI.h"

extern unsigned int errorDeReproduccion;
extern unsigned char buffer_rx[32];

static unsigned rxc;
static unsigned char indexR;
static unsigned char flag_n=0;

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
	SCI_write_string_to_buffer("\r\n Rango de frecuencias posibles: [200 Hz - 10 KHz] con un paso de 100 Hz");
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

unsigned char INTERACCION_analizeInput (void){
	rxc=buffer_rx[0];
	while(rxc!='\n'){
		if (numero(rxc)){
			if (!indexR)
				flag_n=1;
			else{
				if (!flag_n){
					return 0;
				}
			}
		}
		else{
			if (letra (rxc)){
				if (flag_n){
					flag_n=0;
					return 0;
				}
			}
			else{
				return 0;
			}
		}
		indexR++;
		rxc=buffer_rx[indexR];
	}
	return 1;
}

unsigned char INTERACCION_getInput (void){
	unsigned char i, num=0; 
	if (buffer_rx[0]!='\n'){
			if (flag_n){
				for (i=0;i<indexR;i++){
					num+=(buffer_rx[i]-'0')*(10^(indexR-i-1));
				}
				return num;
			}
			else{
				if ((buffer_rx[0]=='O'||buffer_rx[0]=='o')&&(buffer_rx[1]=='N'||buffer_rx[1]=='n')&&buffer_rx[2]=='\n')
					return '+';
				if ((buffer_rx[0]=='O'||buffer_rx[0]=='o')&&(buffer_rx[1]=='F'||buffer_rx[1]=='f')&&(buffer_rx[2]=='F'||buffer_rx[2]=='f')&&buffer_rx[3]=='\n')
					return '-';
				if ((buffer_rx[0]=='R'||buffer_rx[0]=='r')&&(buffer_rx[1]=='E'||buffer_rx[1]=='e')&&(buffer_rx[2]=='S'||buffer_rx[2]=='s')&&(buffer_rx[3]=='E'||buffer_rx[3]=='e')&&(buffer_rx[4]=='T'||buffer_rx[4]=='t')&&buffer_rx[5]=='\n')
					return '*';
				return 'e';
			}
	}
}


unsigned char numero(unsigned char input){
	if ((input >= '0') && ('9' >= input)) return 1;
	return 0;
}

unsigned char letra (unsigned char input){
	static char comandos[] =
		{'O','o','N','n', 'F','f',
		'R','r','E','e','S','s', 'T','t'
		};
	return comandos[input];
}
