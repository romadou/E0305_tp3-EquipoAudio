/*
 * MEF.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef MEF_H_
#define MEF_H_

typedef enum {INIT, PEDIR_F, M1_ON, M1_OFF, PEDIR_T, M2_ON, M2_OFF} estado;

void MEF_init(void); /* Estado inicial de la MEF */
void MEF_update(unsigned char entrada); /* Actualización de la MEF */
	
#endif /* MEF_H_ */
