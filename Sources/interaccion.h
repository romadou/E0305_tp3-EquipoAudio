/*
 * interaccion.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef INTERACCION_H_
#define INTERACCION_H_

void INTERACCION_init(void);
void INTERACCION_default(void);
void INTERACCION_askF(void);
void INTERACCION_askB(void);
void INTERACCION_showB(unsigned char b);
void INTERACCION_showF(unsigned int e);
void INTERACCION_showC(void);
void INTERACCION_showEBF(void);
void INTERACCION_showEE(void);
void INTERACCION_showEF(void);
unsigned char INTERACCION_analizeInput (void); /* Verifica si lo recibido corresponde a una entrada válida */
unsigned char INTERACCION_getInput (void); /* Obtiene la entrada, correspondiente a la opción de menu, guardada en el buffer de recepción */
unsigned int INTERACCION_getFreq(void); /* Obtiene la frecuencia guardada en el buffer de recepción */

#endif /* INTERACCION_H_ */
