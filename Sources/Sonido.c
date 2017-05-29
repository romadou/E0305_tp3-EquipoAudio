/*
 * Sonido.c
 *
 *  Created on: 5/06/2017
 *      Author: Krasowski - Madou
 */

unsigned int channel_reload_value, duration_timer;
unsigned char sound_playing=0;

void SONIDO_sound(unsigned int freq, unsigned int dur);

void SONIDO_init(){
	sound(0,10);
}

// Output a sound through the TPM1CH1 pin (PTB5): freq in [Hz], dur in [ms]
void SONIDO_sound(unsigned int freq, unsigned int dur){
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
}
