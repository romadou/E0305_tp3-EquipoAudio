/*
 * Sonido.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SONIDO_H_
#define SONIDO_H_

void SONIDO_init(void);
unsigned int SONIDO_calcular_NC(unsigned int frec, unsigned int* NC);
void SONIDO_prender(unsigned int NC);
void SONIDO_apagar(void);

#endif /* SONIDO_H_ */
