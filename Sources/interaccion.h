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
void INTERACCION_showC(unsigned char b);
void INTERACCION_showEBF(void);
void INTERACCION_showEE(void);
void INTERACCION_showEF(void);
unsigned char INTERACCION_analizeInput (void);
unsigned char INTERACCION_getInput (void);
unsigned int INTERACCION_getFrec(void);

#endif /* INTERACCION_H_ */
