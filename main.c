#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
void MCU_init(void);
void SCI_init(void);
void delay(int);
void delay1ms(void);
unsigned int i;
unsigned char datoRecibido;

/* #### Rutina que permite Transmitir un Byte de Datos ####*/
void transmite(unsigned char x) {
	while(!SCI2S1_TDRE); // Verifica y espera hasta que el dato ya haya sido transmitido.
	SCI2D=x;
	return;
}


interrupt VectorNumber_Vsci2rx void sci_rx(){
//	while(!SCI2S1_RDRF); // Espera mientras se esta recibiendo el dato.
	flag_rx=SCI2S1_RDRF;
	if(SCI2D == 101){
		PTED_PTED0 = !PTED_PTED0;
	}
}
void SCI_init(void)
{
											/* SCIC2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=0,RE=0,RWU=0,SBK=0 */
	SCI2C2 = 0x00;							/* Disable the SCI module */
	(void)(SCI2S1 == 0); 					/* Dummy read of the SCIS1 registr to clear flags */
	(void)(SCI2D == 0);						/* Dummy read of the SCID registr to clear flags */
	SCI2S2 = 0x00;							/* SCIS2: BRK13=0,RAF=0 */
	SCI2BDH = 0x00;	
	SCI2BDL = 27;	
	/* SCIC1: LOOPS=0,SCISWAI=0,RSRC=0,M=0,WAKE=0,ILT=0,PE=0,PT=0 */
	SCI2C1 = 0x00;							/* SCIC2: TIE=0,TCIE=0,RIE=0,ILIE=0,TE=1,RE=1,RWU=0,SBK=0 */
	SCI2C2 = 0x0C;							/* SCIC3: R8=0,T8=0,TXDIR=0,TXINV=0,ORIE=0,NEIE=0,FEIE=0,PEIE=0 */
	SCI2C3 = 0x00;
	/* ### */
	asm CLI;
}


void main(void) {
	SCI_init();
  EnableInterrupts;
  /* include your code here */
  i=0;
  
  for(;;) {
		transmite(14);
		delay(250);
  }
}

void delay(int limite) {
	int j;
	for (j = 0; j < limite; j++) {
		delay1ms();
	}
}

// Funcion para generar un retardo de 1 ms (depende de la frecuencia de bus del MCU)
void delay1ms(void) {
	int k;
	for (k = 0; k < 597; k++) {
	}
}
