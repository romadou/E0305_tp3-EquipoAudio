/*
 * interaccion.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef INTERACCION_H_
#define INTERACCION_H_

void INTERACCION_init(void); /* Mensaje de inicio */
void INTERACCION_default(void); /* Menu de manipulación del sonido */
void INTERACCION_askF(void); /* Menu de frecuencia fija */
void INTERACCION_askB(void); /* Menu de barrido */
void INTERACCION_showB(unsigned char b); /* Confirmación de barrido guardado */
void INTERACCION_showF(unsigned int e); /* Confirmación de frecuencia guardada y error producido */
void INTERACCION_showC(void); /* Confirmación de comando aceptado */
void INTERACCION_showEBF(void); /* Error de buffer lleno: demasiados caracteres ingreados */
void INTERACCION_showEE(void); /* Error de entrada inválida */
void INTERACCION_showEF(void); /* Error de frecuencia inválida */
unsigned char INTERACCION_analizeInput (void); /* Verifica si lo recibido corresponde a una entrada válida */
unsigned char INTERACCION_getInput (void); /* Obtiene la entrada, correspondiente a la opción de menu, guardada en el buffer de recepción */
unsigned int INTERACCION_getFreq(void); /* Obtiene la frecuencia guardada en el buffer de recepción */

#endif /* INTERACCION_H_ */
