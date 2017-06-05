#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MEF.h"

extern unsigned char flag_r;
extern unsigned char flag_e;
extern unsigned char rxchar;

void MCU_init(void); /* Device initialization function declaration */

void main(void) {
	
  MCU_init();	/* call Device Initialization */

  MEF_init();

  for(;;) {
	  if (flag_e){
		  INTERACCION_showBL();
	  }
	  if (flag_r){
		  if (INTERACCION_analizeInput()){
			  MEF_update();
		  }
		  flag_r=0;
	  }
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
