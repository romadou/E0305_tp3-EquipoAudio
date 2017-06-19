#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MEF.h"
#include "interaccion.h"

/* Variables externas */
extern unsigned char flag_r;
extern unsigned char flag_ebf;

void MCU_init(void); /* Device initialization function declaration */

void main(void) {
	
  MCU_init();	/* call Device Initialization */

  MEF_init();

  for(;;) {
	  if (flag_ebf){
		  INTERACCION_showEBF();
		  flag_ebf=0;
	  }
	  if (flag_r){
		  if (INTERACCION_analizeInput()){
			  MEF_update();
		  }
		  else{
			  INTERACCION_showEE();
		  }
		  flag_r=0;
	  }
  } /* loop forever */
  
  /* please make sure that you never leave main */
}
