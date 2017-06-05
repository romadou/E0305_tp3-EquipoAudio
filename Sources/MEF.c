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
void estado_pedir_f(unsigned char entrada);
void estado_pedir_t(unsigned char entrada);
void estado_m1_on(unsigned char entrada);
void estado_m1_off(unsigned char entrada);
void estado_m2_on(unsigned char entrada);
void estado_m2_off(unsigned char entrada);

/* FUNCIONES INTERNAS PARA FUNCIONAMIENTO */

void MEF_init(void){
	actual=INIT;
	INTERACCION_init();
	SONIDO_init();
}

void MEF_update(void){
	switch (actual){
	/* Estado central; la hora corre, la cerradura est� cerrada */
	case INIT:
		entrada = INTERACCION_getInput();
		estado_init(entrada);
		break;
		;
	/* Modificaci�n de la hora */
	case PEDIR_F:
		estado_pedir_f(entrada);
		break;
		;
	/* Modificaci�n de los minutos */
	case PEDIR_T:
		entrada = INTERACCION_getInput();
		estado_pedir_t(entrada);
		break;
		;
	/* Modificando los segundos */
	case M1_ON:
		entrada = INTERACCION_getInput();
		estado_m1_on(entrada);
		break;
		;
	/* Solicitud de modificaci�n de la clave (ingresando la clave existente) */
	case M1_OFF:
		entrada = INTERACCION_getInput();
		estado_m1_off(entrada);
		break;
		;
	/* Solicitud de desbloqueo de la cerradura (ingresando la clave existente) */
	case M2_ON:
		entrada = INTERACCION_getInput();
		estado_m2_on(entrada);
		break;
		;
	/* Desbloqueo de la cerradura */
	case M2_OFF:
		entrada = INTERACCION_getInput();
		estado_m2_off(entrada);
		break;
		;
	}
}

void estado_init(unsigned char entrada){
	switch (entrada){
	/* Elecci�n del modo 1 */
	case 'f':;
	case 'F':
		actual=PEDIR_F;
		INTERACCION_askF();
		break;
		;
	/* Elecci�n del modo 2 */
	case 'b':;
	case 'B':
		actual=PEDIR_T;
		INTERACCION_askB();
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

void estado_pedir_f(unsigned char entrada){
	static unsigned int in;
	static unsigned char aux;
	in=INTERACCION_getFreq();
	aux=verifyFreq(in);
	// -----'0' para resetear (frecuencia inv�lida o comando de reset, si v�lido)
	// -----'1' si ya hay una frecuencia definida
	// -----'2' si sigue esperando valores
	switch (aux){
	/* Opci�n de reset */
	case '0':
		MEF_init();
		actual=INIT;
		break;
		;
	/* Modo de frecuencia fija activado y a la espera */
	case '1':
		//INTERACCION_default(); (men� de opciones para reproducci�n)
		SONIDO_prender_m1();
		actual=M1_OFF;
		break;
		;
	default:
		;
	}
}

void estado_m1_on(unsigned char entrada){
	static unsigned char aux=0;
	//O hacer un men� (asociando cada n a una opci�n) y tomar directamente la entrada
	//INTERACCION_analizar entrada (puede ser if =(ej)> 0 si reset, 1 si off, 3 si no termin�)
	//aux=_INTERACCION_analizarEntrada(entrada);
	switch (aux){
	//switch (entrada){
	case '*':
		MEF_init();
		actual=INIT;
		break;
		;
	case '-':
		SONIDO_apagar();
		actual=M1_OFF;
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

void estado_m1_off(unsigned char entrada){
	static unsigned char aux=0;
	//O hacer un men� (asociando cada n a una opci�n) y tomar directamente la entrada
	//INTERACCION_analizar entrada (puede ser if =(ej)> 0 si reset, 2 si on, 3 si no termin� - ej, "OF" de "OFF")
	///aux=_INTERACCION_analizarEntrada(entrada);
	switch (aux){
	//switch (entrada){
	case '*':
		MEF_init();
		actual=INIT;
		break;
		;
	case '+':
		SONIDO_reanudar();
		actual=M1_ON;
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

void estado_pedir_t(unsigned char entrada){
	switch (entrada){
	/* Elecci�n del barrido en 5 segundos */
	case '1':
		//INTERACCION_default();(men� de opciones para reproducci�n)
		actual=M2_ON;
		//INTERACCION_segundosBarrido(5);
		SONIDO_prender_m2(5);
		break;
		;
	/* Elecci�n del barrido en 10 segundos */
	case '2':
		//INTERACCION_default();(men� de opciones para reproducci�n)
		actual=M2_ON;
		//INTERACCION_segundosBarrido(10);
		SONIDO_prender_m2(10);
		break;
		;
	/* Elecci�n del barrido en 15 segundos */
	case '3':
		//INTERACCION_default();(men� de opciones para reproducci�n)
		actual=M2_ON;
		//INTERACCION_segundosBarrido(15);
		SONIDO_prender_m2(15);
		break;
		;
	default:
		;
	}
}

void estado_m2_on(unsigned char entrada){
	static unsigned char aux=0;
	//O hacer un men� (asociando cada n a una opci�n) y tomar directamente la entrada
	//INTERACCION_analizar entrada (puede ser if =(ej)> 0 si reset, 1 si off, 3 si no termin�)
	///aux=_INTERACCION_analizarEntrada(entrada,1); 1 indica que hay que analizar n�meros para frecuencia (y mostrarlos)
	switch (aux){
	//switch (entrada){
	case '*':
		MEF_init();
		actual=INIT;
		break;
		;
	case '-':
		//SONIDO_apagar();
		actual=M2_OFF;
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

void estado_m2_off(unsigned char entrada){
	static unsigned char aux=0;
	//O hacer un men� (asociando cada n a una opci�n) y tomar directamente la entrada
	//INTERACCION_analizar entrada (puede ser if =(ej)> 0 si reset, 2 si on, 3 si no termin�)
	///aux=_INTERACCION_analizarEntrada(entrada);
	switch (aux){
	//switch (entrada){
	case '*':
		MEF_init();
		actual=INIT;
		break;
		;
	case '+':
		SONIDO_reanudar();
		actual=M2_ON;
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

