/*
 * Mensaje.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */
#include "Mensaje.h"
#include "SCI.h"

void MENSAJE_init(){
	SCI_write_string_to_buffer("\r\nBIENVENIDOS AL PROGRAMA");
	SCI_write_string_to_buffer("\r\nESCOGER MODO DE FUNCIONAMIENTO (presionar el número correspondiente a la opción):");
	SCI_write_string_to_buffer("\r\n1- Modo 1: Sonido de frecuencia fija");
	SCI_write_string_to_buffer("\r\n2- Modo 2: Barrido de frecuencias");
	SCI_write_string_to_buffer("\r\nUNA VEZ ELEGIDO EL MODO, EL PROGRAMA SE SIRVE DE LOS SIGUIENTES COMANDOS:");
	SCI_write_string_to_buffer("\r\n8- ON: Iniciar reproducción de sonido");
	SCI_write_string_to_buffer("\r\n9- OFF: Detener reproducción de sonido");
	SCI_write_string_to_buffer("\r\n0- RESET: Reiniciar programa");
}
