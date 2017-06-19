/*
 * sonido.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SONIDO_H_
#define SONIDO_H_

/* Predivisor del TPM1 */
#ifndef PRESCALER_1
#define PRESCALER_1 1
#endif

/* Predivisor del TPM2 */
#ifndef PRESCALER_2
#define PRESCALER_2 32
#endif

/* Frecuencia máxima permitida */
#ifndef F_MAX
#define F_MAX 10000
#endif

/* Frecuencia mínima permitida */
#ifndef F_MIN
#define F_MIN 200
#endif

/* Resolución de la representación de frecuencias*/
#ifndef PASO
#define PASO 100
#endif

void SONIDO_init(void); /* Inicialización del sonido */
unsigned int SONIDO_getError(void); /* Devuelve el error de reproducción de la última frecuencia seteada */
void SONIDO_prender_mf(unsigned int fa); /* Prepara el sistema para sonar en una frecuencia fija (se asume seteada previamente) */
void SONIDO_prender_mb(unsigned char T); /* Prepara el sistema para sonar en un barrido de frecuencias que se realice en T segundos */
void SONIDO_apagar(void);
void SONIDO_reanudar(void);
void SONIDO_siguiente_f(void); /* -Para uso en modo barrido- Efectúa el cambio de una frecuencia a la siguiente */

#endif /* SONIDO_H_ */
