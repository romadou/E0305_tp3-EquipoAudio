/*
 * sonido.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SONIDO_H_
#define SONIDO_H_

#ifndef PRESCALER_1
#define PRESCALER_1 1
#endif

#ifndef PRESCALER_2
#define PRESCALER_2 32
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
unsigned int SONIDO_getError(void);
void SONIDO_prender_m1(unsigned int fa); /* Enciende el sonido en una frecuencia fija(se asume seteada previamente); devuelve el error (Hz) existente entre la frecuencia del sonido real respecto del deseado. */
void SONIDO_prender_m2(unsigned char T); /* Dispara el barrido de frecuencias, para que se realice en T segundos */
void SONIDO_apagar(void);
void SONIDO_reanudar(void);
void SONIDO_siguiente_f(void); /* -Para uso en modo barrido- Efectúa el cambio de una frecuencia a la siguiente */

#endif /* SONIDO_H_ */
