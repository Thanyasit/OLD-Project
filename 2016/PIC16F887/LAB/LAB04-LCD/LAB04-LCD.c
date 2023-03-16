#include "D:\Work T.Pongsak\Microcontroller\Work\LAB04-LCD\LAB04-LCD.h"
#use delay (clock=20M)
#include <lcd.c>

void main()
{
   char msg[]={'T','H','A','N','Y','A','S','I','T'};
   int i;
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   // TODO: USER CODE!!
   lcd_init();
   lcd_putc(0x41);
   lcd_putc(0x30);
   lcd_putc('A');
   lcd_putc('0');
   lcd_gotoxy(15,2);
   lcd_putc('Z');
   delay_ms(500);
   lcd_putc('\f');
   lcd_gotoxy(4,1);
   printf(lcd_putc,"THANYASIT");
   lcd_gotoxy(4,2);
   for(i=0;i<9;i++){
      delay_ms(500);
      lcd_putc(msg[i]);
   }
   while(1);
}
