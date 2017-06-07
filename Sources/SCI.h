/*
 * SCI.h
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#ifndef SCI_H_
#define SCI_H_


void SCI_send_char(void);
void SCI_receive_char(void);
void SCI_write_string_to_buffer(char *cadena);
unsigned char SCI_read_from_buffer(unsigned char pos);

#endif /* SCI_H_ */
