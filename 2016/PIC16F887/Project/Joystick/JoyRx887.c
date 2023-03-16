#include "D:\Work T.Pongsak\Microcontroller\Work\Joystick\JoyRx887.h"
#use delay (clock=20m)
#define M1  PIN_D0  // PWN Moter1
#define M1R PIN_D1  // Moter1 Reves
#define M2  PIN_D2  // PWN Moter2
#define M2R PIN_D3  // Moter2 Reves
#define M3  PIN_D4  // PWN Moter3
#define M3R PIN_D5  // Moter3 Reves
#define M4  PIN_D6  // PWN Moter4
#define M4R PIN_D7  // Moter4 Reves
void delay(void);//delay
void checkjoystick(void); // check joy
void moter_wheel(void);
void limitsw(void);
void ButtonLR(void);
void right(void);
void upleft(void);
void upright(void);
void downleft(void);
void downright(void);
//#include <lcd.c>
char save[];
int x=0,b=0,f=0,count=0,s=0,s1=0,d=0,sum=127,sum2=127,M;
#INT_RDA
void rs232_isr(){
   x=getc();
//   lcd_putc(x);
   if(b==0){
      if(x=='W'){//"Q"
         b=1;
      }else{
         d=x;
         m=x;
      }
   }else if(b==1){
      if(x==0x0d){
         b=0;
         f=1;
         s1=count;
      }else{
         if(x=='P'){//'S'
            s=count;
         }
         save[count]=x;
         count++;
      }
   }
}
void main()
{
   int start=0,level=0,mag=0;
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);// This device COMP currently not supported by the PICWizard
//Setup_Oscillator parameter not selected from Intr Oscillotar Config tab

   // TODO: USER CODE!!
   set_tris_d(0x00);
   set_tris_c(0x00);//80
   set_tris_b(0x00);
   Set_tris_a(0x00);
   output_c(0x00);
   output_b(0x00);
   output_a(0x00);
   output_d(0x00);
   enable_interrupts(GLOBAL);
 //  lcd_init();
   do{
      x = getc();
   }while(x!='1');
   x=0;
   output_high(PIN_A0); //C0
   enable_interrupts(INT_RDA);
   while(1){
  //    lcd_gotoxy(1,1);
      if(f==1){
         checkjoystick();
      }
      moter_wheel();
      if(d=='K'){ //shoot Sorenal*****************
         output_high(PIN_C0);//A4
       //  delay();
         output_low(PIN_A4);
      }else if(d=='I'){//Roll mag
         output_high(PIN_C3);
         mag=1;
      }else if(d=='H'){
         start=!start; //Start,Stop roll shoot
      }else if(d=='L'){//Up speed roll shoot*******
         level++;
         if(level==8){
            level--;
         }
      }else if(d=='J'){//Down speed roll shoot*****
         level--;
         if(level==10){
            level++;
         }
      }else{
         d=0;
      }
      ButtonLR();
      if(mag==1){
         if(!input(PIN_A3)){// limit position
            output_low(PIN_C3); //Stop mag
            mag=0;
         }
      }
      if(start==1){ //Level roll speed shoot*****************
         if(level==1){
            set_pwm1_duty(22);
            output_e(0x01);
         }else if(level==2){
            set_pwm1_duty(44);
            output_e(0x02);
         }else if(level==3){
            set_pwm1_duty(67);
            output_e(0x03);
         }else if(level==4){
            set_pwm1_duty(89);
            output_e(0x04);
         }else if(level==5){
            set_pwm1_duty(111);
            output_e(0x05);
         }else if(level==6){
            set_pwm1_duty(134);
            output_e(0x06);
         }else if(level==7){
            set_pwm1_duty(156);
            output_e(0x07);
         }
      }else{
         set_pwm1_duty(0);
      }
/*
         if(sum==0){
            if(sum2==127){
               printf(lcd_putc,"Up");
            }   
         }else if(sum==127){
            if(sum2==0){
               printf(lcd_putc,"Left");           
            }else if(sum2==127){
               printf(lcd_putc,"Center");
            }else if(sum2==255){
               printf(lcd_putc,"Right");
            }  
         }else if(sum==255){
            if(sum2==127){
               printf(lcd_putc,"Down");
            }
         }
         */
   }
}
//***************************************************************************
void delay(){
   delay_ms(50);
}
//****************************************************************************
void checkjoystick(){
int i,sc=0,a=0;
   sum=0;
   sum2=0;
   s1=s1-s;
   for(i=0;i<count;i++){
      if(save[i]=='S'||save[i]=='P'){
         i++;
         sc=1;
      }
      save[i]=save[i]&0x0f;
      if(sc==1){
         if(s1==4){
            if(a==0){
               save[i]=save[i]*100;
               a++;
            }else if(a==1){
               save[i]=save[i]*10;
               a++;
            }
         }else if(s1==3){
            if(a==0){
               save[i]=save[i]*10;
               a++;
            }
         }
         sum2=sum2+save[i];
      }else{
         if(s==3){
            if(i==0){
               save[i]=save[i]*100;
            }else if(i==1){
               save[i]=save[i]*10;
            }
         }else if(s==2||s==4){
            if(i==0){
               save[i]=save[i]*10;
            }
         }
         sum=sum+save[i];
      }
   }
   //output_b(sum);
   //output_high(PIN_C1);
   //output_b(sum2);
   f=0;
   a=0;
   sc=0;
   count=0;
   //lcd_putc('\f');
}
//***************************************************************************
void moter_wheel(){
 int data;
      data=d;
      if(sum<=59&&sum2<=59){//Left Up
         output_low(M1);  //Stop
         output_low(M1R);
         output_high(M2); //REV
         output_high(M2R);
         output_high(M3); //REV
         output_high(M3R); 
         output_low(M4); //Stop
         output_low(M4R); 
      }else if(sum==0&&sum2>=68&&sum2<=187){ //Up
         output_high(M1); //FWD
         output_low(M1R);
         output_high(M2); //REV
         output_high(M2R);
         output_high(M3); //REV
         output_high(M3R); 
         output_high(M4); //FWD
         output_low(M4R); 
      }else if(sum<=59&&sum2>=196){//Right Up
         output_high(M1); //FWD
         output_low(M1R);
         output_low(M2);  //Stop
         output_low(M2R);
         output_low(M3);  //Stop
         output_low(M3R); 
         output_high(M4); //FWD
         output_low(M4R); 
      }else if(sum>=68&&sum<=187&&sum2==255){//Right
         output_high(M1); //FWD
         output_low(M1R);
         output_high(M2); //FWD
         output_low(M2R);
         output_high(M3); //FWD
         output_low(M3R); 
         output_high(M4); //FWD
         output_low(M4R); 
      }else if(sum>=196&&sum2>=196){//Right Down
         output_low(M1);  //Stop
         output_low(M1R);
         output_high(M2); //FWD
         output_low(M2R);
         output_high(M3); //FWD
         output_low(M3R); 
         output_low(M4);  //Stop
         output_low(M4R); 
      }else if(sum==255&&sum2>=68&&sum2<=187){// Down
         output_high(M1); //REV
         output_high(M1R);
         output_high(M2); //FWD
         output_low(M2R);
         output_high(M3); //FWD
         output_low(M3R); 
         output_high(M4); //REV
         output_high(M4R); 
      }else if(sum>=196&&sum2<=59){//Left Down
         output_high(M1); //REV
         output_high(M1R);
         output_low(M2);  //Stop
         output_low(M2R);
         output_low(M3);  //Stop
         output_low(M3R); 
         output_high(M4); //REV
         output_high(M4R); 
      }else if(sum>=68&&sum<=187&&sum2==0){//Left
         output_high(M1); //REV
         output_high(M1R);
         output_high(M2); //REV
         output_high(M2R);
         output_high(M3); //REV
         output_high(M3R); 
         output_high(M4); //REV
         output_high(M4R);
      }else if(data=='A'){//Up Right 
         output_low(M1);  //Stop
         output_low(M1R);
         output_high(M2); //REV
         output_high(M2R);
         output_high(M3); //FWD
         output_low(M3R); 
         output_high(M4); //FWD
         output_low(M4R); 
         data=0;
         delay();
      }else if(data=='D'){//Down Right
         output_low(M1);  //Stop
         output_low(M1R);
         output_high(M2); //FWD
         output_low(M2R);
         output_high(M3); //REV
         output_high(M3R); 
         output_high(M4); //REV
         output_high(M4R); 
         data=0;
         delay();
      }else if(data=='C'){//Up Left
         output_high(M1); //FWD
         output_low(M1R);
         output_low(M2);  //Stop
         output_low(M2R);
         output_high(M3); //REV
         output_high(M3R); 
         output_high(M4); //REV
         output_high(M4R); 
         data=0;
         delay();
      }else if(data=='B'){//Down Left
         output_high(M1); //REV
         output_high(M1R);
         output_low(M2);  //Stop
         output_low(M2R);
         output_high(M3); //FWD
         output_low(M3R); 
         output_high(M4); //FWD
         output_low(M4R); 
         data=0;
         delay(); 
      }else{
         output_low(M1); //Stop
         output_low(M1R);
         output_low(M2); //Stop
         output_low(M2R);
         output_low(M3); //Stop
         output_low(M3R); 
         output_low(M4); //Stop
         output_low(M4R); 
      }   
}
//***************************************************************************
void limitsw(){
}
//*****************************************************************************
void ButtonLR(){
int tarry=0;
      if(tarry==0){
         if(d=='N'){ //Up Lift
            output_high(PIN_C4);//FWD
            output_low(PIN_C5);
            tarry=1;
         }else if(d=='F'){ // Down Lift
            output_high(PIN_C4); //REV
            output_high(PIN_C5);
            tarry=1;
         }else if(M=='M'){ // Up
            output_high(PIN_C0);//FWD
            output_low(PIN_C1);
            tarry=1;
         }else if(M=='E'){ //return
            output_high(PIN_C0);//REV
            output_high(PIN_C1);
            tarry=1;
         }
      }else if(tarry=1){
         if(M=='N'||M=='F'||M=='M'||M=='E'){
            if(!input(PIN_A1)){ // limit Up  
               output_low(PIN_C4);
               tarry=0;
            }else if(!input(PIN_A2)){// limit Down 
               output_low(PIN_C4);
               tarry=0;
            }else if(!input(PIN_A5)){// limit Up  
               output_low(PIN_C0); 
               tarry=0;
            }else if(!input(PIN_A6)){// limit return
               output_low(PIN_C0); 
               tarry=0;   
            }
         }else{
            output_low(PIN_C4);
            output_low(PIN_C0);
            tarry=0;
         }
      }
}
//**************************************************************************
void right(){
}
void upleft(){
}
void upright(){
}
void downleft(){
}
void downright(){
}

