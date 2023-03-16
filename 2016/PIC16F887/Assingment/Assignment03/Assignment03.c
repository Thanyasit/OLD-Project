#include "D:\Work T.Pongsak\Microcontroller\Work\Assignment03\Assignment03.h"
#use delay (clock=20M)

void main()
{
   char segment[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
   int i,com1,com2,sw,f;
   int data[]={1,2,3,4,5,6};
   int data1[]={6,5,4,3,2,1};
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
   set_tris_d(0x80);
   set_tris_c(0xc0);
   f=0;
   while(1){
      sw = input(PIN_C7);
      delay_ms(1);
      if(sw==0){
         f=~f;
         output_c(0xff);
         do{
            sw = input(PIN_C7);
           }while(sw==0);
      }
      com1 = 0b00000001;
      for(i=0;i<6;i++){
         com2 = ~com1;
         output_c(com2);
         if(f==0){
         output_d(segment[data[i]]);
         }else{
         output_d(segment[data1[i]]);
         }
         delay_ms(1);
         com1 = com1<<1;
      }
   }
}
