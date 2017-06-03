/*
 * sonido.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SONIDO_H_
#define SONIDO_H_

void SONIDO_init(void);
void setFrecuenciaActual(unsigned int fa);
unsigned int SONIDO_prender_m1(void); /* Enciende el sonido en una frecuencia fija(se asume seteada previamente); devuelve el error (Hz) existente entre la frecuencia del sonido real respecto del deseado. */
void SONIDO_prender_m2(unsigned char T); /* Dispara el barrido de frecuencias, para que se realice en T segundos */
void SONIDO_apagar(void);
void SONIDO_siguiente_f(void); /* **Para uso en modo barrido** Efectúa el cambio de una frecuencia a la siguiente */

#endif /* SONIDO_H_ */
