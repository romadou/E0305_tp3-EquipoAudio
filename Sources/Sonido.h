/*
 * sonido.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SONIDO_H_
#define SONIDO_H_

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

void SONIDO_init(void);
void setFrecuenciaActual(unsigned int fa);
void SONIDO_prender_m1(void); /* Enciende el sonido en una frecuencia fija(se asume seteada previamente); devuelve el error (Hz) existente entre la frecuencia del sonido real respecto del deseado. */
void SONIDO_prender_m2(unsigned char T); /* Dispara el barrido de frecuencias, para que se realice en T segundos */
void SONIDO_apagar(void);
void SONIDO_reanudar(void);
void SONIDO_siguiente_f(void); /* **Para uso en modo barrido** Efectúa el cambio de una frecuencia a la siguiente */

#endif /* SONIDO_H_ */
