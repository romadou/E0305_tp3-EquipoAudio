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
volatile unsigned char flag_e;
unsigned char rxchar;

void SCI_send_char(void){
	if (indexR < indexW){
		SCID=buffer_tx[indexR];
		indexR++;
	}
	else{
		indexR=0;
		indexW=0;
		SCIC2_TIE=0;
	}
}

void SCI_receive_char(void){
	if(SCIS1_RDRF==1){
		rxchar=SCID;
		if (++cont==32){
			flag_e=1;
			indexW=0;
			cont=0;
			return;
		}
		buffer_rx[indexW]=rxchar;
		if (rxchar=='\n'){
			indexW=0;
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

unsigned char SCI_read_string_from_buffer(void){
	return *buffer_tx;
}
