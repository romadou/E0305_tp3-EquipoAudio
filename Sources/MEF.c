/*
 * MEF.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#include "MEF.h"
#include "Mensaje.h"
#include "Sonido.h"

/* Variables privadas */
static estado actual; /* Estado actual de la MEF */

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
	MENSAJE_init();
	SONIDO_init();
}

void MEF_update(unsigned char entrada){
	switch (actual){
	/* Estado central; la hora corre, la cerradura est� cerrada */
	case INIT:
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
		estado_pedir_t(entrada);
		break;
		;
	/* Modificando los segundos */
	case M1_ON:
		estado_m1_on(entrada);
		break;
		;
	/* Solicitud de modificaci�n de la clave (ingresando la clave existente) */
	case M1_OFF:
		estado_m1_off(entrada);
		break;
		;
	/* Solicitud de desbloqueo de la cerradura (ingresando la clave existente) */
	case M2_ON:
		estado_m2_on(entrada);
		break;
		;
	/* Desbloqueo de la cerradura */
	case M2_OFF:
		estado_m2_off(entrada);
		break;
		;
	}
}

void estado_init(unsigned char entrada){
	switch (entrada){
	/* Elecci�n del modo 1 */
	case '1':
		actual=PEDIR_F;
		//MENSAJE_pedirFrecuencia();
		break;
		;
	/* Elecci�n del modo 2 */
	case '2':
		actual=PEDIR_T;
		//MENSAJE_pedirTiempoBarrido();
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

void estado_pedir_f(unsigned char entrada){
	static unsigned char aux=0;
	///aux=_MENSAJE_analizarEntrada(entrada);
	// No lo tengo claro, pero creo que en la funci�n analizarEntrada se deber�a mandar el car�cter que entr� (num�rico) as SCI (ir mostrando la frecuencia)
	// El an�lisis devuelve:
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
		//MENSAJE_(men� de opciones para reproducci�n)
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
	//MENSAJE_analizar entrada (puede ser if =(ej)> 0 si reset, 1 si off, 3 si no termin�)
	//aux=_MENSAJE_analizarEntrada(entrada);
	switch (aux){
	//switch (entrada){
	case '0':
		MEF_init();
		actual=INIT;
		break;
		;
	case '1':
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
	//MENSAJE_analizar entrada (puede ser if =(ej)> 0 si reset, 2 si on, 3 si no termin� - ej, "OF" de "OFF")
	///aux=_MENSAJE_analizarEntrada(entrada);
	switch (aux){
	//switch (entrada){
	case '0':
		MEF_init();
		actual=INIT;
		break;
		;
	case '2':
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
		//MENSAJE_(men� de opciones para reproducci�n)
		actual=M2_ON;
		//MENSAJE_segundosBarrido(5);
		SONIDO_prender_m2(5);
		break;
		;
	/* Elecci�n del barrido en 10 segundos */
	case '2':
		//MENSAJE_(men� de opciones para reproducci�n)
		actual=M2_ON;
		//MENSAJE_segundosBarrido(10);
		SONIDO_prender_m2(10);
		break;
		;
	/* Elecci�n del barrido en 15 segundos */
	case '3':
		actual=M2_ON;
		//MENSAJE_segundosBarrido(15);
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
	//MENSAJE_analizar entrada (puede ser if =(ej)> 0 si reset, 1 si off, 3 si no termin�)
	///aux=_MENSAJE_analizarEntrada(entrada,1); 1 indica que hay que analizar n�meros para frecuencia (y mostrarlos)
	switch (aux){
	//switch (entrada){
	case '0':
		MEF_init();
		actual=INIT;
		break;
		;
	case '1':
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
	//MENSAJE_analizar entrada (puede ser if =(ej)> 0 si reset, 2 si on, 3 si no termin�)
	///aux=_MENSAJE_analizarEntrada(entrada);
	switch (aux){
	//switch (entrada){
	case '0':
		MEF_init();
		actual=INIT;
		break;
		;
	case '2':
		SONIDO_reanudar();
		actual=M2_ON;
		break;
		;
	/* Opci�n sin efecto */
	default:
		;
	}
}

