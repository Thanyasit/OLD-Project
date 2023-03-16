#include "D:\Work T.Pongsak\Microcontroller\Work\LAB02-flowCon2\LAB02-flowCon2.h"
#use delay (clock=20M)

void main()
{
   int i;
   char segment[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
   char y;
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
   set_tris_b(0x00);
/*
   y = segment[9]; //Data come save y
   output_b(y);//sent out port B
   output_b(segment[9]);
*/
/*   while(1){ 
      for(i=0;i<10;i++){  //i++ : i=i+1
         output_b(segment[i]);
         delay_ms(1000);
      }
*/
   y = 10;
   switch(y){
      case 0:
         output_b(segment[0]);
         break;
      case 1:
         output_b(segment[1]);
         break;
      case 2:
         output_b(segment[2]);
         break;
      case 3:
         output_b(segment[3]);
         break;
      case 4:
         output_b(segment[4]);
         break;
      case 5:
         output_b(segment[5]);
         break;
      case 6:
         output_b(segment[6]);
         break;
      case 7:
         output_b(segment[7]);
         break;
      case 8:
         output_b(segment[8]);
         break;
      case 9:
         output_b(segment[9]);
         break;
      default:
         output_b(0x40);
         break;
   }
   
}
