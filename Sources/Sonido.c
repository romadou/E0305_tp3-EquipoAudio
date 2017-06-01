/*
 * Sonido.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

#include <math.h>
#include "Sonido.h"
#include <mc9s08sh8.h> 

#ifndef PRESCALER
#define PRESCALER 4
#endif

unsigned int channel_reload_value, duration_timer;
unsigned char sound_playing=0;

extern unsigned int NC;
extern unsigned int NC0;



void SONIDO_init(){
	SONIDO_apagar();
}

unsigned int SONIDO_calcular_NC(unsigned int frec, unsigned int* NC){
	unsigned long auxNC, auxFoc;
	auxNC=8000000UL/(PRESCALER*2*frec); /* cálculo de NC */
	*NC=(unsigned int)auxNC;
	auxFoc=8000000UL/(PRESCALER*2*auxNC);
	return fabs((unsigned int)auxFoc-frec);
}

void SONIDO_prender(unsigned int NC){
	TPM1C1V = NC; /* primer NC */
	TPM1C1SC_CH1IE=1;
}

void SONIDO_apagar(void){
	TPM1C1V = 0; /* apagar sonido */ //REVISAR
	TPM1C1SC_CH1IE=0;
}

// Output a sound through the TPM1CH1 pin (PTB5): freq in [Hz], dur in [ms]
/*void SONIDO_sound(unsigned int freq, unsigned int dur){
  unsigned long temp;	
  
  while (sound_playing);      // if a sound is playing, wait until if finishes
  // the channel reload value is equal to half the period of the signal
  temp=4000000UL/freq;			//8000000UL/(2*frec)
  channel_reload_value = (unsigned int)temp;
  channel_reload_value >>=1;
  duration_timer = dur;       // set the total duration time
  // set channel 1 to compare mode (toggling the channel pin)
  TPM1C1V = channel_reload_value; // set the first compare value 
  TPM1C1SC = 0x14U; 
  TPM1C1SC_CH1IE=1;
  sound_playing = 1;          // sound is playing (until the flag is cleared)
}*/
