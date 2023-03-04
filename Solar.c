#include <pic.h>
#include <math.h>
#include "lcd.h"
#define charge_Batt_1_Solar 0x15
#define charge_Batt_2_Solar 0x0E
#define Batt_Low_Solar 0x07
#define charge_over 0x08
#define charge_Batt_1_AC 0x11
#define charge_Batt_2_AC 0x0A
#define Batt_Low_AC 0x03

void delay(unsigned int time) // Delay 
{
	unsigned int i, j;
	for(i=0;i<time;i++)
	   for(j=0;j<time;j++); 
}
void ADC_Init() // Intialise ADC 
{
  ADCON0 = 0x01;	
  ADCON1 = 0xC4;	//Right justified,AN0,AN1,AN3 are analog input.
  ADRESH = 0;
  ADRESL = 0;
}
unsigned int ADC_Read(unsigned char channel)
{
  ADCON0 &= 0xC7; 		//Clearing the Channel Selection Bits
  ADCON0 |= channel<<3; //Setting the required Bits
  delay(10); 		    //Acquisition time to charge hold capacitor
  ADGO = 1; 			//Initializes A/D Conversion
  while(ADGO == 1); 	//Wait for A/D Conversion to complete
  return (256 * ADRESH + ADRESL); //Returns Result
}
void main(void)
{	unsigned int Solar,Batt_1,Batt_2,temp,unit,a,b,c,d,x,y,z;
	TRISA = 0x0F;		//
	TRISB = 0x00;			// port B as output
	TRISC = 0x00;			// port C as output
	TRISD = 0x00;			// port D as output
   	lcdint();			// intialised LCD
	cmm(0x01);			// clear display
	cmm(0x80);			// 1'st line of LCD
   	data_str("SOLAR CHARGER");
	delay(100);
	ADC_Init(); 		// Initialise ADC
while(1)
		{
		  Solar = ADC_Read(0);
		  unit = Solar; // Temperature is conveted to ASCII
		if(unit > 900)
				{ 	Batt_1 = ADC_Read(1);
					Batt_2 = ADC_Read(3);	
			 
			if((Batt_1 < 650)&&(Batt_2 > 850))
				{
				 cmm(0x80);			// 2nd line of LCD
				 data_str("BATT-1  CHARGING");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("BATT-2 FULL SOL.");
				 PORTC = charge_Batt_1_Solar;
				 delay(100);
				}
        	if((Batt_2 < 650)&&(Batt_1 > 850))
				{
				 cmm(0x80);			// 2nd line of LCD
				 data_str("BATT-2  CHARGING");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("BATT-1 FULL SOL.");
				 PORTC = charge_Batt_2_Solar;
				 delay(100);
				}
			
			
			 if((Batt_1 > 850)&&(Batt_2 > 850))
				{
				 cmm(0x80);			// 2nd line of LCD
				 data_str("BATT-2      FULL");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("BATT-1      FULL");
				 PORTC = charge_over;
				 delay(100);
				}
			if((Batt_1 < 650)&&(Batt_2 < 650))
				{
				 cmm(0x80);			// 1st line of LCD
				 data_str("BATT-1    BATT-2");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("CHARGING    SOL.");
				 PORTC = Batt_Low_Solar;
				 delay(100);
				}
		
			}
			else
			{	 Batt_1 = ADC_Read(1);
				 Batt_2 = ADC_Read(3);	
			 
			 if((Batt_1 < 650)&&(Batt_2 > 850))
				{
				 cmm(0x80);			// 2nd line of LCD
				 data_str("BATT-1  CHARGING");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("BATT-2 FULL   AC");
				 PORTC = charge_Batt_1_AC;
				 delay(100);
				}
        	if((Batt_2 < 650)&&(Batt_1 > 850))
				{
				 cmm(0x80);			// 2nd line of LCD
				 data_str("BATT-2  CHARGING");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("BATT-1 FULL   AC");
				 PORTC = charge_Batt_2_AC;
				 delay(100);
				}
			
			
			 if((Batt_1 > 650)&&(Batt_2 > 850))
				{
				 cmm(0x80);			// 2nd line of LCD
				 data_str("BATT-2      FULL");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("BATT-1      FULL");
				 PORTC = charge_over;
				 delay(100);
				}
			if((Batt_1 < 650)&&(Batt_2 < 650))
				{
				 cmm(0x80);			// 1st line of LCD
				 data_str("BATT-1    BATT-2");
				 cmm(0xC0);			// 2nd line of LCD
				 data_str("CHARGING      AC");
				 PORTC = Batt_Low_AC;
				 delay(100);
				}
			}
	} 	
}



						


