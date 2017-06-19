/*
 * SCI.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */
#include "SCI.h"
#include <mc9s08sh8.h> 

static unsigned char indexR=0;
static unsigned char indexW=0;
static unsigned char buffer_tx[32];
static unsigned char buffer_rx[32];
static unsigned char cont=0;

volatile unsigned char flag_r;
volatile unsigned char flag_ebf;
unsigned char rxchar;

void SCI_send_char(void){
	if (indexR < indexW){
		/* Hay caracteres para enviar al transmisor. Se envía uno */
		SCID=buffer_tx[indexR];
		indexR++;
	}
	else{
		/* Buffer de transmisión completamente enviado. Se resetea */
		indexR=0;
		indexW=0;
		SCIC2_TIE=0;
	}
}

void SCI_receive_char(void){
	if(SCIS1_RDRF==1){
		/* Hay un carácter disponible en el receptor */
		rxchar=SCID;
		if (++cont==31){
			/* Buffer lleno. Avisa y se reinicia */
			flag_ebf=1;
			indexW=0;
			cont=0;
			return;
		}
		/* Se guarda el carácter en el buffer */
		buffer_rx[indexW]=rxchar;
		if (rxchar=='.'){
			/* Fin de mensaje de entrada */
			indexW=0;
			cont=0;
			flag_r=1;
		}
		else{
			indexW++;
		}
	}
}

void SCI_write_string_to_buffer(char *cadena){
	while(*cadena!='\0'){
		buffer_tx[indexW]=*cadena;
		cadena++;
		indexW++;
	}
	SCIC2_TIE=1;
}

unsigned char SCI_read_from_buffer(unsigned char pos){
	return buffer_rx[pos];
}
