/*
 * MEF.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef MEF_H_
#define MEF_H_

typedef enum {INIT, PEDIR_F, MF_ON, MF_OFF, PEDIR_T, MB_ON, MB_OFF} estado;

void MEF_init(void); /* Estado inicial de la MEF */
void MEF_update(void); /* Actualización de la MEF */
	
#endif /* MEF_H_ */
