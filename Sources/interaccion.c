/*
 * interaccion.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */
#include "interaccion.h"
#include "SCI.h"

void INTERACCION_init(){
	SCI_write_string_to_buffer("\r\nBIENVENIDOS AL PROGRAMA");
	SCI_write_string_to_buffer("\r\nESCOGER MODO DE FUNCIONAMIENTO:");
	SCI_write_string_to_buffer("\r\n Modo F: Sonido de frecuencia fija");
	SCI_write_string_to_buffer("\r\n Modo B: Barrido de frecuencias");
	SCI_write_string_to_buffer("\r\n(ingresar la letra correspondiente al modo deseado)");
}

void INTERACCION_default(){
	SCI_write_string_to_buffer("\r\nDESDE ESTE MOMENTO, EL PROGRAMA SE SIRVE DE LOS SIGUIENTES COMANDOS:");
	SCI_write_string_to_buffer("\r\n ON: Iniciar reproducción de sonido");
	SCI_write_string_to_buffer("\r\n OFF: Detener reproducción de sonido");
	SCI_write_string_to_buffer("\r\n RESET: Reiniciar programa");
}

void INTERACCION_askF(){
	SCI_write_string_to_buffer("\r\nINGRESAR LA FRECUENCIA DE SONIDO QUE DESEA ESCUCHAR:");
	SCI_write_string_to_buffer("\r\n Rango de freciencias posibles:  [100 - 2 MHz]");
}

void INTERACCION_askB(){
	SCI_write_string_to_buffer("\r\nINGRESE EL MODO DE BARRIDO QUE DESEA:");
	SCI_write_string_to_buffer("\r\n T1: Iniciar reproducción de sonido");
	SCI_write_string_to_buffer("\r\n T2: Detener reproducción de sonido");
	SCI_write_string_to_buffer("\r\n T3: Reiniciar programa");
	SCI_write_string_to_buffer("\r\n(ingresar el numero correspondiente al barrido escogido)");
}
