/*
 * MEF.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#include "MEF.h"
#include "SCI.h"
#include "Mensaje.h"
#include "TPM.h"
#include "Sonido.h"
#include "RTC.h"

/* Variables privadas */
static estado actual; /* Estado actual de la MEF */
static unsigned char posV; /* Posición de la contraseña a revisar, o posición del nuevo caracter a ingresar en una clave nueva */
static unsigned char ctrl; /* Control del ingreso de caracteres durante una verificación/modificación de clave */
static unsigned char auxHora; /* Control durante la modificación de la hora/minutos/segundos */
static unsigned char digito1, digito2; /* Almacenamiento temporal de caracteres durante la modificación de la hora/minutos/segundos */

/* Variables externas */
extern unsigned int NC;
extern unsigned int NC0;

/* Variables globales */
volatile unsigned char flag_PA=0;

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
/* Devolución del equivalente en número entero de dos dígitos representado por dos caracteres */
//unsigned char formarNumero(unsigned char digito1, unsigned char digito2);

void MEF_init(void){
	actual=INIT;
	MENSAJE_init();
	SONIDO_init();
}

void MEF_update(unsigned char entrada){
	switch (actual){
	/* Estado central; la hora corre, la cerradura está cerrada */
	case INIT:
		estado_init(entrada);
		break;
		;
	/* Modificación de la hora */
	case PEDIR_F:
		estado_modH(entrada);
		break;
		;
	/* Modificación de los minutos */
	case PEDIR_T:
		estado_modM(entrada);
		break;
		;
	/* Modificando los segundos */
	case M1_ON:
		estado_modS(entrada);
		break;
		;
	/* Solicitud de modificación de la clave (ingresando la clave existente) */
	case M1_OFF:
		estado_modC(entrada);
		break;
		;
	/* Solicitud de desbloqueo de la cerradura (ingresando la clave existente) */
	case M2_ON:
		estado_verificando(entrada);
		break;
		;
	/* Desbloqueo de la cerradura */
	case M2_OFF:
		estado_abierto();
		break;
		;
	}
}

void estado_init(unsigned char entrada){
	switch (entrada){
	/* Elección del modo 1 */
	case '1':
		actual=PEDIR_F;
		MENSAJE_pedirFrecuencia();
		break;
		;
	/* Elección del modo 2 */
	case '2':
		actual=PEDIR_T;
		MENSAJE_pedirTiempoBarrido();
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

void estado_pedir_f(unsigned char entrada){
	static unsigned char aux=0;
	//MENSAJE_analizar entrada (puede ser if =(ej)> 3 si reset, 2 si on, 1 si off, 0 si no terminó)
	///aux=_MENSAJE_analizarEntrada(entrada,1); 1 indica que hay que analizar números para frecuencia (y mostrarlos)
	switch (aux){
	case '3':
		MENSAJE_init();
		actual=INIT;
		break;
		;
	case '2':
		//SONIDO_prender();
		actual=M1_ON;
		break;
		;
	case '1':
		//SONIDO_apagar();
		actual=M1_OFF;
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

void estado_m1_on(unsigned char entrada){
	static unsigned char aux=0;
	//MENSAJE_analizar entrada (puede ser if =(ej)> 3 si reset, 2 si on, 1 si off, 0 si no terminó)
	///aux=_MENSAJE_analizarEntrada(entrada);
	switch (aux){
	case '3':
		MENSAJE_init();
		actual=INIT;
		break;
		;
	case '1':
		//SONIDO_apagar();
		actual=M1_OFF;
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

void estado_m1_off(unsigned char entrada){
	static unsigned char aux=0;
	//MENSAJE_analizar entrada (puede ser if =(ej)> 3 si reset, 2 si on, 1 si off, 0 si no terminó)
	///aux=_MENSAJE_analizarEntrada(entrada);
	switch (aux){
	case '3':
		MENSAJE_init();
		actual=INIT;
		break;
		;
	case '2':
		//SONIDO_prender();
		actual=M1_ON;
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

void estado_pedir_t(unsigned char entrada){
	//MENSAJE_analizar entrada (puede ser if =(ej)> 3 si reset, 2 si on, 1 si off, 0 si no terminó)
	switch (entrada){
	/* Elección del modo 1 */
	case '1':
		actual=M2_ON;
		
		//MENSAJE_segundosBarrido(5);
		break;
		;
	/* Elección del modo 2 */
	case '2':
		actual=M2_ON;
		//MENSAJE_segundosBarrido(10);
		break;
		;
	case '3':
		actual=M2_ON;
		//MENSAJE_segundosBarrido(15);
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

void estado_m2_on(unsigned char entrada){
	static unsigned char aux=0;
	//MENSAJE_analizar entrada (puede ser if =(ej)> 3 si reset, 2 si on, 1 si off, 0 si no terminó)
	///aux=_MENSAJE_analizarEntrada(entrada,1); 1 indica que hay que analizar números para frecuencia (y mostrarlos)
	switch (aux){
	case '3':
		MENSAJE_init();
		actual=INIT;
		break;
		;
	case '2':
		//SONIDO_prender();
		actual=M1_ON;
		break;
		;
	case '1':
		//SONIDO_apagar();
		actual=M1_OFF;
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

void estado_m2_off(void){
	static unsigned char aux=0;
	//MENSAJE_analizar entrada (puede ser if =(ej)> 3 si reset, 2 si on, 1 si off, 0 si no terminó)
	///aux=_MENSAJE_analizarEntrada(entrada,1); 1 indica que hay que analizar números para frecuencia (y mostrarlos)
	switch (aux){
	case '3':
		MENSAJE_init();
		actual=INIT;
		break;
		;
	case '2':
		//SONIDO_prender();
		actual=M1_ON;
		break;
		;
	/* Opción sin efecto */
	default:
		;
	}
}

