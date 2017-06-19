/*
 * MEF.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#include "MEF.h"
#include "SCI.h"
#include "interaccion.h"
#include "sonido.h"

/* Variables privadas */
static estado actual; /* Estado actual de la MEF */
static unsigned char entrada;

/* Variables externas */
extern unsigned int NC;
extern unsigned int NC0;

/* Funciones privadas */
/* Comportamiento de cada uno de los estados */
void estado_init(unsigned char entrada);
void estado_pedir_f(void);
void estado_pedir_t(unsigned char entrada);
void estado_mf_on(unsigned char entrada);
void estado_mf_off(unsigned char entrada);
void estado_mb_on(unsigned char entrada);
void estado_mb_off(unsigned char entrada);
/* Verifica si la entrada pertenece al rango de frecuencias permitidas */
unsigned char verifyFreq(unsigned int freq);

void MEF_init(void){
	actual=INIT;
	INTERACCION_init();
	SONIDO_init();
}

void MEF_update(void){
	switch (actual){
	/* Estado inicial */
	case INIT:
		entrada = INTERACCION_getInput();
		estado_init(entrada);
		break;
		;
	/* Pedido de frecuencia para reproducción en frecuencia fija */
	case PEDIR_F:
		estado_pedir_f();
		break;
		;
	/* Pedido de modo para reproducción en barrido de frecuencias */
	case PEDIR_T:
		entrada = INTERACCION_getInput();
		estado_pedir_t(entrada);
		break;
		;
	/* Modo F; sonido encendido */
	case MF_ON:
		entrada = INTERACCION_getInput();
		estado_mf_on(entrada);
		break;
		;
	/* Modo F; sonido apagado */
	case MF_OFF:
		entrada = INTERACCION_getInput();
		estado_mf_off(entrada);
		break;
		;
	/* Modo B; sonido encendido */
	case MB_ON:
		entrada = INTERACCION_getInput();
		estado_mb_on(entrada);
		break;
		;
	/* Modo B; sonido apagado */
	case MB_OFF:
		entrada = INTERACCION_getInput();
		estado_mb_off(entrada);
		break;
		;
	}
}

void estado_init(unsigned char entrada){
	switch (entrada){
	/* Elección del modo f */
	case 'f':
		actual=PEDIR_F;
		INTERACCION_askF();
		break;
		;
	/* Elección del modo b */
	case 'b':
		actual=PEDIR_T;
		INTERACCION_askB();
		break;
		;
	/* Entrada no válida */
	default:
		INTERACCION_showEE();
	}
}

void estado_pedir_f(){
	static unsigned int in;
	in=INTERACCION_getFreq();
	if (in!='e'){
		if (verifyFreq(in)){
			/* Modo de frecuencia fija activado y a la espera */
			SONIDO_prender_mf(in);
			in = SONIDO_getError();
			INTERACCION_showF(in);
			INTERACCION_default(); /* Menú de opciones para reproducción */
			actual=MF_OFF;
		}
		else{
			/* Frecuencia no válida */
			INTERACCION_showEF();
		}
	}
	else 
		/* Entrada no válida */
		INTERACCION_showEE();
}

void estado_mf_on(unsigned char entrada){
	switch (entrada){
	/* Reset: apagar sonido y reiniciar el sistema */
	case '*':
		INTERACCION_showC();
		MEF_init();
		actual=INIT;
		break;
		;
	/* Apagar sonido */	
	case '-':
		INTERACCION_showC();
		SONIDO_apagar();
		actual=MF_OFF;
		break;
		;
	default:
		/* Entrada no válida */
		INTERACCION_showEE();
		;
	}
}

void estado_mf_off(unsigned char entrada){
	switch (entrada){
	/* Reset: apagar sonido y reiniciar el sistema */
	case '*':
		INTERACCION_showC();
		MEF_init();
		actual=INIT;
		break;
		;
	/* Encender sonido de frecuencia fija */	
	case '+':
		INTERACCION_showC();
		SONIDO_reanudar();
		actual=MF_ON;
		break;
		;
	default:
		/* Entrada no válida */
		INTERACCION_showEE();
		;
	}
}

void estado_pedir_t(unsigned char entrada){
	switch (entrada){
	/* Elección del barrido en 5 segundos */
	case '1':
		actual=MB_OFF;
		INTERACCION_showB(5);
		INTERACCION_default(); /* Menú de opciones para reproducción */
		SONIDO_prender_mb(5);
		break;
		;
	/* Elección del barrido en 10 segundos */
	case '2':
		actual=MB_OFF;
		INTERACCION_showB(10);
		INTERACCION_default();
		SONIDO_prender_mb(10);
		break;
		;
	/* Elección del barrido en 15 segundos */
	case '3':
		actual=MB_OFF;
		INTERACCION_showB(15);
		INTERACCION_default();
		SONIDO_prender_mb(15);
		break;
		;
	default:
		/* Entrada no válida */
		INTERACCION_showEE();
		;
	}
}

void estado_mb_on(unsigned char entrada){
	switch (entrada){
	/* Reset: apagar sonido y reiniciar el sistema */
	case '*':
		INTERACCION_showC();
		MEF_init();
		actual=INIT;
		break;
		;
	/* Apagar sonido */
	case '-':
		INTERACCION_showC();
		SONIDO_apagar();
		actual=MB_OFF;
		break;
		;
	default:
		/* Entrada no válida */
		INTERACCION_showEE();
		;
	}
}

void estado_mb_off(unsigned char entrada){
	switch (entrada){
	/* Reset: apagar sonido y reiniciar el sistema */
	case '*':
		INTERACCION_showC();
		MEF_init();
		actual=INIT;
		break;
		;
	/* Encender sonido en barrido de frecuencias */
	case '+':
		INTERACCION_showC();
		SONIDO_reanudar();
		actual=MB_ON;
		break;
		;
	default:
		/* Entrada no válida */
		INTERACCION_showEE();
		;
	}
}

unsigned char verifyFreq(unsigned int freq){
	return (freq>=F_MIN && freq<=F_MAX && freq%100==0);
}

