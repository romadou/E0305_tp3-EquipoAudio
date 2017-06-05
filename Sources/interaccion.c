/*
 * interaccion.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */
#include "interaccion.h"
#include "SCI.h"

extern unsigned char buffer_rx[32];

static unsigned rxc;
static unsigned char indexR;
static unsigned char flag_n=0;

unsigned char numero (unsigned char input);
unsigned char letra (unsigned char input);

void INTERACCION_init(void){
	SCI_write_string_to_buffer("\r\nBIENVENIDOS AL PROGRAMA");
	SCI_write_string_to_buffer("\r\nESCOGER MODO DE FUNCIONAMIENTO:");
	SCI_write_string_to_buffer("\r\n Modo F: Sonido de frecuencia fija");
	SCI_write_string_to_buffer("\r\n Modo B: Barrido de frecuencias");
	SCI_write_string_to_buffer("\r\n(ingresar la letra correspondiente al modo deseado,");
	SCI_write_string_to_buffer("\r\n para confirmar presione ENTER)");
}

void INTERACCION_default(void){
	SCI_write_string_to_buffer("\r\nDESDE ESTE MOMENTO, EL PROGRAMA SE SIRVE DE LOS SIGUIENTES COMANDOS:");
	SCI_write_string_to_buffer("\r\n ON: Iniciar reproducción de sonido");
	SCI_write_string_to_buffer("\r\n OFF: Detener reproducción de sonido");
	SCI_write_string_to_buffer("\r\n RESET: Reiniciar programa");
	SCI_write_string_to_buffer("\r\n (para confirmar presione ENTER)");
}

void INTERACCION_askF(void){
	SCI_write_string_to_buffer("\r\nINGRESAR LA FRECUENCIA DE SONIDO QUE DESEA ESCUCHAR:");
	SCI_write_string_to_buffer("\r\n Rango de frecuencias posibles: [200 Hz - 10 KHz] con un paso de 100 Hz");
	SCI_write_string_to_buffer("\r\n (para confirmar presione ENTER)");
}

void INTERACCION_askB(void){
	SCI_write_string_to_buffer("\r\nINGRESE EL MODO DE BARRIDO QUE DESEA:");
	SCI_write_string_to_buffer("\r\n T1: 5 seg");
	SCI_write_string_to_buffer("\r\n T2: 10 seg");
	SCI_write_string_to_buffer("\r\n T3: 15 seg");
	SCI_write_string_to_buffer("\r\n(ingresar el número correspondiente al barrido escogido,");
	SCI_write_string_to_buffer("\r\n (para confirmar presione ENTER)");
} 

void INTERACCION_showB(unsigned char b){
	SCI_write_string_to_buffer("\r\n OPCION GUARDADA");
	SCI_write_string_to_buffer("\r\n SE REALIZARÁ UN BARRIDO CADA %ud SEGUNDOS", b);
}

void INTERACCION_showF(unsigned int e){
	SCI_write_string_to_buffer("\r\n FRECUENCIA GUARDADA");
	SCI_write_string_to_buffer("\r\n EL ERROR PRODUCIDO POR LA FRECUENCIA SELECIONADA ES DE %ud HZ", e);
}

void INTERACCION_showC(unsigned char b){
	SCI_write_string_to_buffer("\r\n COMANDO ACEPTADO");
}

void INTERACCION_showEBF(void){
	SCI_write_string_to_buffer("\r\n ERROR: DEMASIADAS TECLAS PRESIONADAS");
	SCI_write_string_to_buffer("\r\n Comience nuevamente");
}

void INTERACCION_showEE(void){
	SCI_write_string_to_buffer("\r\n ERROR: ENTRADA INVÁLIDA");
	SCI_write_string_to_buffer("\r\n Comience nuevamente");
}

void INTERACCION_showEF(void){
	SCI_write_string_to_buffer("\r\n ERROR: FRECUENCIA FUERA DE RANGO");
	SCI_write_string_to_buffer("\r\n Comience nuevamente");
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


unsigned char INTERACCION_getInput (void){
	if (buffer_rx[0]!='\n'){
			if (flag_n){
				return buffer_rx[0];
			}
			else{
				if ((buffer_rx[0]=='F'||buffer_rx[0]=='f')&&buffer_rx[1]=='\n')
					return 'f';
				if ((buffer_rx[0]=='B'||buffer_rx[0]=='b')&&buffer_rx[1]=='\n')
					return 'b';
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

unsigned int INTERACCION_getFrec(void){
	unsigned char i, num=0;
	if (buffer_rx[0]!='\n' && numero(buffer_rx[0])){
		for (i=0;i<indexR;i++){
			sum+=(buffer_rx[i]-'0')*1^(indexR-i-1);
		}
	}
	return num;
}

unsigned char numero(unsigned char input){
	if ((input >= '0') && ('9' >= input)) return 1;
	return 0;
}

unsigned char letra (unsigned char input){
	static char comandos[] = 
		{'O','o','N','n', 'F','f','B','b',
		'R','r','E','e','S','s', 'T','t'
		};
	return comandos[input];
}
