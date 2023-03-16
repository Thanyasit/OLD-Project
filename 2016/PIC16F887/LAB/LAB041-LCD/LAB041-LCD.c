#include "D:\Work T.Pongsak\Microcontroller\Work\LAB041-LCD\LAB041-LCD.h"
#use delay (clock=20M)
#include <lcd.c>

void main()
{
   char msg[]={'T','h','a','n','y','a','s','i','t'};
   char msa[]={'A','k','k','a','r','a','n','a','r','a','t','h','i','w','a','t'};
   char msb[]={'5','8','3','1','0','5','0','0','2','4'};
   char mse[]={'I','n','d','u','s','t','r','i','a','l',' ','E','l','e','c','.'};
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
   while(1){
            lcd_init();
            lcd_gotoxy(5,1);
            for(i=0;i<9;i++){
                  delay_ms(250);
                  lcd_putc(msg[i]);
            }
            lcd_gotoxy(1,2);
            for(i=0;i<16;i++){
                  delay_ms(250);
                  lcd_putc(msa[i]);
            }
            delay_ms(2000);
            lcd_putc('\f');
            lcd_gotoxy(4,1);
            for(i=0;i<10;i++){
                  delay_ms(250);
                  lcd_putc(msb[i]);
            }
            lcd_gotoxy(1,2);
            for(i=0;i<16;i++){
                  delay_ms(250);
                  lcd_putc(mse[i]);
            }
            delay_ms(2000);
   }
}
