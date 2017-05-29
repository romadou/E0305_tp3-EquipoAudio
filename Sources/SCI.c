/*
 * SCI.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

static unsigned char indexR=0;
static unsigned char indexW=0;
static unsigned char buffer_tx[32];
static unsigned char buffer_rx[32];

volatile unsigned char flag_r;
unsigned char rxchar;

void SCI_send_char(){
	//while(indexR!=indexW){
		/* Funcion bloqueante */
		//while(SCIS1_TDRE==0); //espera hasta que el flag exprese que el transmisor está libre
	SCID=buffer_tx[index_R];
	indexR++;
	//}
	//indexR=0;
	//indexW=0;
}

void SCI_receive_char(){
	if(SCIS1_RDRF==1){
		rxchar=SCID;
	}
	flag_r=1;
}

void SCI_write_string_to_buffer(char *cadena){
	while(*cadena!='\0'){
		buffer_tx[indexW]=*cadena;
		cadena++;
		indexW++;
	}
	SCIC2_TIE=1;
}
