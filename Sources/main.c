#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "SCI.h"

extern unsigned char flag_r;
extern unsigned char rxchar;

void MCU_init(void); /* Device initialization function declaration */

void main(void) {
	
  MCU_init();	/* call Device Initialization */

  MEF_init();

  for(;;) {  
	  if (flag_r){
		  MEF_update(rxchar);
		  flag_r=0;
	  }
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
