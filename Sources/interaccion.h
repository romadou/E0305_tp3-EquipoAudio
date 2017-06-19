/*
 * interaccion.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef INTERACCION_H_
#define INTERACCION_H_

void INTERACCION_init(void); /* Mensaje de inicio */
void INTERACCION_default(void); /* Men� de manipulaci�n del sonido */
void INTERACCION_askF(void); /* Men� de frecuencia fija */
void INTERACCION_askB(void); /* Men� de barrido */
void INTERACCION_showB(unsigned char b); /* Confirmaci�n de barrido guardado */
void INTERACCION_showF(unsigned int e); /* Confirmaci�n de frecuencia guardada y error producido */
void INTERACCION_showC(void); /* Confirmaci�n de comando aceptado */
void INTERACCION_showEBF(void); /* Error de buffer lleno: demasiados caracteres ingresados */
void INTERACCION_showEE(void); /* Error de entrada inv�lida */
void INTERACCION_showEF(void); /* Error de frecuencia inv�lida */
unsigned char INTERACCION_analyzeInput (void); /* Verifica si lo recibido corresponde a una entrada v�lida */
unsigned char INTERACCION_getInput (void); /* Obtiene la entrada, correspondiente a la opci�n de men�, guardada en el buffer de recepci�n */
unsigned int INTERACCION_getFreq(void); /* Obtiene la frecuencia guardada en el buffer de recepci�n */

#endif /* INTERACCION_H_ */
