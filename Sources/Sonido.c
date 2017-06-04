/*
 * sonido.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef PRESCALER
#define PRESCALER 4
#endif

#ifndef F_MAX
#define F_MAX 10000
#endif

#ifndef F_MIN
#define F_MIN 200
#endif

#ifndef PASO
#define PASO 100
#endif

#include <stdlib.h>
#include "sonido.h" 
#include <mc9s08sh8.h> 

extern unsigned int NC;
extern unsigned int NC0;

static unsigned int frecuenciaActual=0;
static unsigned int errorDeReproduccion=0;
static unsigned char modoActual=0;
static unsigned int TPM1C1V_aux=0;

/* Calcula el valor correspondiente a la frecuencia actual para NC y lo asigna a la variable externa de igual nombre */
void SONIDO_calcular_NC(void);
/* Calcula el valor de NC0 para que en T segundos se oigan todas las frecuencias entre F_MIN y F_MAX, a una resolución de PASO */
void SONIDO_calcular_NC0(unsigned char T);

void SONIDO_init(void){
	SONIDO_apagar();
}

void setFrecuenciaActual(unsigned int fa){
	frecuenciaActual=fa;
}

void SONIDO_siguiente_f(void){
	frecuenciaActual+=PASO;
	frecuenciaActual%=F_MAX;
	SONIDO_calcular_NC();
}

void SONIDO_prender_m1(void){
	SONIDO_calcular_NC();
	modoActual=0;
	TPM1C1V_aux = NC; /* primer NC */
}

void SONIDO_prender_m2(unsigned char T){
	frecuenciaActual=200;
	SONIDO_calcular_NC();
	modoActual=1;
	TPM1C1V_aux = NC; /* primer NC */
	SONIDO_calcular_NC0(T);
}

void SONIDO_apagar(void){
	TPM1C1V_aux = TPM1C1V;
	TPM1C1V = 0; /* apagar sonido */ //REVISAR
	TPM1C1SC_CH1IE=0;
	TPM1C0SC_CH0IE=0;
}

void SONIDO_reanudar(void){
	TPM1C1V = TPM1C1V_aux;
	TPM1C1SC_CH1IE=1;
	TPM1C0SC_CH0IE=modoActual;
}


void SONIDO_calcular_NC(void){
	unsigned long auxNC, auxFoc;
	auxNC=8000000UL/(PRESCALER*2*frecuenciaActual); /* cálculo de NC */
	NC=(unsigned int)auxNC;
	auxFoc=8000000UL/(PRESCALER*2*auxNC);
	errorDeReproduccion = abs((unsigned int)auxFoc-frecuenciaActual);
}

void SONIDO_calcular_NC0(unsigned char T){
	unsigned long auxNC0;
	unsigned int auxFrec = (T*PASO)/(F_MAX-F_MIN);
	auxNC0=8000000UL/(PRESCALER*2*auxFrec); /* cálculo de NC0 */
	NC0=(unsigned int)auxNC0;
}
