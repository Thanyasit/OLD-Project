#include "D:\Work T.Pongsak\Microcontroller\Work\Assignment09\Assignment09-2\Assignment09-2.h"
#use delay (clock=20M)
#include <lcd.c>
#INT_RDA
int x;
void rs232_isr(){
   x=getc();
}
void main()
{
   char save[];
//   int1 recv;
   int i,A=0;
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);// This device COMP currently not supported by the PICWizard
//Setup_Oscillator parameter not selected from Intr Oscillotar Config tab

   // TODO: USER CODE!!
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);
   lcd_init();
   lcd_gotoxy(5,1);
   printf(lcd_putc,"LAB-092");
   lcd_gotoxy(1,2);
   x=getc();
   if(x==0x30){
      output_high(PIN_C1);
/*
      if(x==0x31){
            do{
               save[i] = x;
               i++;
            }while(0x32!= x);
            x = getc();
            if(x==0x33){
               A=1;
            }
         }
      if(A==0){
         output_high(PIN_C0);
      }else if(A==1){
         output_high(PIN_C1);
         for(i;i>1;i--){
            lcd_putc(save[i]);
         }
      }
*/
   }
   while(1);
}
     
/*
   while(0){
      recv = kbhit();
      if(recv){
         x = getc();
         lcd_putc(x);
      }
   }
*/

