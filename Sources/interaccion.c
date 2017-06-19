/*
 * interaccion.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#include "interaccion.h"
#include "SCI.h"

/* Variables privadas */
static unsigned char indexR; /* Cantidad de caracteres recibidos */
static unsigned char flag_n=0; /* Flag indicador si el primer carácter recibido es un número */
static unsigned short delay; /* Delay agregado con el fin de evitar sobrecargar en buffer de transmisión */

/* Funciones privadas */
/* Corrobora que el carácter recibido sea un número */
unsigned char numero (unsigned char input);
/* Corrobora que el carácter recibido sea una letra perteneciente a alguna entrada válida */
unsigned char letra (unsigned char input);

void INTERACCION_init(void){
	SCI_write_string_to_buffer("\r\n***BIENVENIDOS AL GENERADOR DE SONIDOS***");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n\nESCOGER MODO DE FUNCIONAMIENTO:");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n Modo F: Sonido de frecuencia fija");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n Modo B: Barrido de frecuencias");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n(ingresar la letra correspondiente");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer(" al modo deseado,");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer(" para confirmar presione '.')\r\n");
}

void INTERACCION_default(void){
	SCI_write_string_to_buffer("\r\n\nDESDE ESTE MOMENTO,");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\nEL PROGRAMA SE SIRVE DE LOS SIGUIENTES COMANDOS:");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n ON: Iniciar reproduccion de sonido");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n OFF: Detener reproduccion de sonido");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n RESET: Reiniciar programa");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n(para confirmar presione '.')\r\n\n");
}

void INTERACCION_askF(void){
	SCI_write_string_to_buffer("\r\n\nINGRESAR LA FRECUENCIA DE SONIDO QUE DESEA ESCUCHAR:");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n Rango de frecuencias posibles: [200 Hz - 10 KHz]");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer(" con un paso de 100 Hz");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n(para confirmar presione '.')\r\n\n");
}

void INTERACCION_askB(void){
	SCI_write_string_to_buffer("\r\n\nINGRESE EL MODO DE BARRIDO QUE DESEA:");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n T1: 5 seg");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n T2: 10 seg");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n T3: 15 seg");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n(ingresar el numero correspondiente al barrido escogido, ");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("para confirmar \r\npresione '.')\r\n\n");
} 

void INTERACCION_showB(unsigned char b){
	SCI_write_string_to_buffer("\r\n\nOPCION GUARDADA");
	for (delay=0; delay<0xFFFF; delay++);
	switch (b){
	case 5: SCI_write_string_to_buffer("\r\n\nSE REALIZARA UN BARRIDO CADA 5 SEGUNDOS");
			break;
	case 10: SCI_write_string_to_buffer("\r\n\nSE REALIZARA UN BARRIDO CADA 10 SEGUNDOS");
			break;
	case 15: SCI_write_string_to_buffer("\r\n\nSE REALIZARA UN BARRIDO CADA 15 SEGUNDOS");
			break;
	default:;
	}
}

void INTERACCION_showF(unsigned int error){
	/* Conversión de error integer a string */
	unsigned char e[2];
	e[0]='0'+error/10;
	e[1]='0'+error%10;
	SCI_write_string_to_buffer("\r\n\nFRECUENCIA GUARDADA");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n\nEL ERROR PRODUCIDO POR LA");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer(" FRECUENCIA SELECIONADA ES DE ");
	SCI_write_string_to_buffer(e);
	SCI_write_string_to_buffer(" Hz");
}

void INTERACCION_showC(void){
	SCI_write_string_to_buffer("\r\n\nCOMANDO ACEPTADO\r\n\n");
}

void INTERACCION_showEBF(void){
	SCI_write_string_to_buffer("\r\n\nERROR: DEMASIADAS TECLAS PRESIONADAS");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n Comience nuevamente\r\n\n");
}

void INTERACCION_showEE(void){
	SCI_write_string_to_buffer("\r\n\nERROR: ENTRADA INVALIDA");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n Ingrese una entrada valida\r\n\n");
}

void INTERACCION_showEF(void){
	SCI_write_string_to_buffer("\r\n\nERROR: FRECUENCIA FUERA DE RANGO");
	for (delay=0; delay<0xFFFF; delay++);
	SCI_write_string_to_buffer("\r\n Ingrese una frecuencia valida\r\n\n");
}

unsigned char INTERACCION_analizeInput (void){
	unsigned char rxc;
	indexR=0;
	rxc=SCI_read_from_buffer(indexR);
	while(rxc!='.'){
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
		rxc=SCI_read_from_buffer(indexR);
	}
	flag_n=0;
	return 1;
}

unsigned char INTERACCION_getInput (void){
	if (SCI_read_from_buffer(0)!='.'){
		if (numero(SCI_read_from_buffer(0))){
			return SCI_read_from_buffer(0);
		}
		else{
			if ((SCI_read_from_buffer(0)=='F'||SCI_read_from_buffer(0)=='f')&& SCI_read_from_buffer(1)=='.')
				return 'f';
			if ((SCI_read_from_buffer(0)=='B'||SCI_read_from_buffer(0)=='b')&& SCI_read_from_buffer(1)=='.')
				return 'b';
			if ((SCI_read_from_buffer(0)=='O'||SCI_read_from_buffer(0)=='o')&&(SCI_read_from_buffer(1)=='N'||SCI_read_from_buffer(1)=='n')&&SCI_read_from_buffer(2)=='.')
				return '+';
			if ((SCI_read_from_buffer(0)=='O'||SCI_read_from_buffer(0)=='o')&&(SCI_read_from_buffer(1)=='F'||SCI_read_from_buffer(1)=='f')&&(SCI_read_from_buffer(2)=='F'||SCI_read_from_buffer(2)=='f')&&SCI_read_from_buffer(3)=='.')
				return '-';
			if ((SCI_read_from_buffer(0)=='R'||SCI_read_from_buffer(0)=='r')&&(SCI_read_from_buffer(1)=='E'||SCI_read_from_buffer(1)=='e')&&(SCI_read_from_buffer(2)=='S'||SCI_read_from_buffer(2)=='s')&&(SCI_read_from_buffer(3)=='E'||SCI_read_from_buffer(3)=='e')&&(SCI_read_from_buffer(4)=='T'||SCI_read_from_buffer(4)=='t')&&SCI_read_from_buffer(5)=='.')
				return '*';
			return 'e';
		}
	}
}

unsigned int INTERACCION_getFreq(void){
	unsigned char i, j;
	unsigned int num=0, x;
	if (SCI_read_from_buffer(0)!='.' && numero(SCI_read_from_buffer(0))){
		for (i=0;i<indexR;i++){
			x=SCI_read_from_buffer(i)-'0';
			for (j=0; j<indexR-i-1; j++){
				x*=10;
			}
			num+=x;
		}
	}
	else 
		return 'e';
	return num;
}

unsigned char numero(unsigned char input){
	if ((input >= '0') && ('9' >= input)) return 1;
	return 0;
}

unsigned char letra (unsigned char input){
	switch (input){ 
	case 'O':;
	case 'o':;
	case 'N':;
	case 'n':; 
	case 'F':;
	case 'f':;
	case 'B':;
	case 'b':;
	case 'R':;
	case 'r':;
	case 'E':;
	case 'e':;
	case 'S':;
	case 's':; 
	case 'T':;
	case 't': return 1;
	default: return 0;
	};
}
