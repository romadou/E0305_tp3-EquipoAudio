/*
 * SCI.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SCI_H_
#define SCI_H_


void SCI_send_char(void); /* Env�a un car�cter del buffer al transmisor */
void SCI_receive_char(void); /* Adquiere un car�cter del receptor y lo almacena en el buffer */
void SCI_write_string_to_buffer(char *cadena); /* Escribe la cadena argumento en el buffer de transmisi�n */
unsigned char SCI_read_from_buffer(unsigned char pos); /* Devuelve el car�cter de la posici�n pos del buffer de recepci�n */

#endif /* SCI_H_ */
