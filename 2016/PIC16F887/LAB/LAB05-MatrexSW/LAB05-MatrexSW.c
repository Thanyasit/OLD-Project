#include "D:\Work T.Pongsak\Microcontroller\Work\LAB05-MatrexSW\LAB05-MatrexSW.h"
#use delay (clock=20M)
int matrixSw(void);
#define COL1 PIN_D2
#define COL2 PIN_D1
#define COL3 PIN_D0
#define ROW1 PIN_D4
#define ROW2 PIN_D5
#define ROW3 PIN_D6
#define ROW4 PIN_D7
void main()
{
   int sw; // local variable
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
   set_tris_d(0b11111000);
   output_b(0x40);
   while(1){
      sw = matrixSw();

      if(sw!=99){

      }
   }
}
int matrixSw(){
   int matsw;
   char segment[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x76,0x36};
   output_low(COL1);
   output_high(COL2);
   output_high(COL3);
   if(!input(ROW1)){
      matsw = 1;
      output_b(segment[1]);
   }else if(!input(ROW2)){
      matsw = 4;
      output_b(segment[4]);
   }else if(!input(ROW3)){
      matsw = 7;
      output_b(segment[7]);
   }else if(!input(ROW4)){   
      matsw = 10;
      output_b(segment[10]);
   }else{
      matsw = 99;
   }
   delay_ms(50);
   
   output_high(COL1);
   output_low(COL2);
   output_high(COL3);
    if(!input(ROW1)){
      matsw = 2;
      output_b(segment[2]);
   }else if(!input(ROW2)){
      matsw = 5;
      output_b(segment[5]);
   }else if(!input(ROW3)){
      matsw = 8;
      output_b(segment[8]);
   }else if(!input(ROW4)){   
      matsw = 0;
      output_b(segment[0]);
   }else{
      matsw = 99;
   }
   delay_ms(50);
   
   output_high(COL1);
   output_high(COL2);
   output_low(COL3);
    if(!input(ROW1)){
      matsw = 3;
      output_b(segment[3]);
   }else if(!input(ROW2)){
      matsw = 6;
      output_b(segment[6]);
   }else if(!input(ROW3)){
      matsw = 9;
      output_b(segment[9]);
   }else if(!input(ROW4)){   
      matsw =11;
      output_b(segment[11]);
   }else{
      matsw = 99;
   }
   delay_ms(50);
   
   return matsw;
}  
