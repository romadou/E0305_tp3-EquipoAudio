/*
 * SCI.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SCI_H_
#define SCI_H_


void SCI_send_char(void); /* Envía un carácter del buffer al transmisor */
void SCI_receive_char(void); /* Adquiere un carácter del receptor y lo almacena en el buffer */
void SCI_write_string_to_buffer(char *cadena); /* Escribe la cadena argumento en el buffer de transmisión */
unsigned char SCI_read_from_buffer(unsigned char pos); /* Devuelve el carácter de la posición pos del buffer de recepción */

#endif /* SCI_H_ */
