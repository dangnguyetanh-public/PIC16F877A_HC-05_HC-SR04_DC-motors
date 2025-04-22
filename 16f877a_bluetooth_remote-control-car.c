#include <16f877a_bluetooth_remote-control-car.h>
#include "config.h"

#use rs232(baud=9600,xmit = pin_C6,rcv=pin_C7,BITS=8,PARITY=N,STOP=1)

#use i2c(Master,Fast=100000,sda=PIN_C4,scl=PIN_C3,force_sw)
#include <lcd_i2c.c>
#include <string.h>
#include <math.h>



char c;
#INT_RDA
void  RDA_isr(void) 
{
   c = getch();   
}

float distance,time;
float measure_distance()
{
   output_high(TRIGGER);   //Bat Triger output_high(pin_b0)
   delay_ms(50);
   output_low(TRIGGER);    //Tat Triger output_low(pin_b0)
   
   while(ECHO==0) {}// Doi cho chan echo len muc cao input(PIN_B1)
   //Su dung Timer1
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   set_timer1(0);
   while(ECHO==1) {}// Doi cho chan echo xuong muc thap
   setup_timer_1(T1_DISABLED);
   //Lay so xung song sieu am phan lai tu vat
   time = get_timer1() * 1.6f;
   //Thoi gian = so xung * 1.6 
   distance = (float)time/58.0f; 
   //Khoang cach = thoi gian /58
   return distance;
}

void distance_display()
{
   distance=measure_distance();
//!   lcd_gotoxy(12,1);  printf(lcd_putc,"%.0fcm ",distance+1);
}

int16 speed=400;
void forward()
{
   output_high(pin_D0);   output_high(pin_D2); 
   set_pwm1_duty(speed);  set_pwm2_duty(speed);
}
void back()
{
   output_high(pin_D1);   output_high(pin_D3); 
   set_pwm1_duty(speed);  set_pwm2_duty(speed);
}

void left()
{
   output_high(pin_D0);   output_high(pin_D3);
   set_pwm1_duty(speed);  set_pwm2_duty(speed);
}

void right()
{
   output_high(pin_D1);   output_high(pin_D2);
   set_pwm1_duty(speed);  set_pwm2_duty(speed);
}


void stop()
{
   output_low(pin_D0); output_low(pin_D1); 
   output_low(pin_D2); output_low(pin_D3);
}

int16 speed_up()
{
   if(input(pin_B4)==0)
   {
      while(input(pin_B4)==0) {}
      speed+=300;
      if(speed>1000)   speed=1000;
   }
   return speed;
}

int16 speed_dw()
{
   if(input(pin_B5)==0)
   {
      while(input(pin_B5)==0) {}
      speed-=300;
      if(speed<400)   speed=400;
   }
   return speed;
}

void speed_display()
{
   if(speed==400) 
   {
      lcd_gotoxy(1,1);  printf(lcd_putc,"SPEED:SLOW  ");
   }
   if(speed==700) 
   {
      lcd_gotoxy(1,1);  printf(lcd_putc,"SPEED:NORMAL");
   }
   if(speed==1000) 
   {
      lcd_gotoxy(1,1);  printf(lcd_putc,"SPEED:HIGH  ");
   }
}

void warning()
{
   distance=measure_distance();
   if(distance<30)
   {
      output_high(pin_C5);
      delay_ms(200);
      output_low(pin_C5);
      delay_ms(200);
   }
   else  output_low(pin_C5);
}

void app_speed()
{
   if(c=='3')  speed=1000;
   if(c=='2')  speed=700;
   if(c=='1')  speed=400;
}

void main()
{
   lcd_init();
   lcd_clear();

   setup_timer_2(T2_DIV_BY_16,249,1);
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);

   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   lcd_gotoxy(5,1);  printf(lcd_putc,"42101280");
   lcd_gotoxy(1,2);  printf(lcd_putc,"DANG NGUYET ANH");
   delay_ms(3000);
   
   output_low(pin_D0); output_low(pin_D1); output_low(pin_D2);    output_low(pin_D3); 
   while(TRUE)
   {   
      speed_up();
      speed_dw();
      app_speed();
      measure_distance();
      distance_display();
      speed_display();
      warning();
      if(c=='F')
      {
         forward();
         lcd_gotoxy(1,2);  printf(lcd_putc,"STATUS:FORWARD     ");
      }
      else if(c=='B')   
      {
         back();
         lcd_gotoxy(1,2);  printf(lcd_putc,"STATUS:BACK     ");
      }
      else if(c=='L')   
      {
         left();
         lcd_gotoxy(1,2);  printf(lcd_putc,"STATUS:LEFT     ");
      }
      else if(c=='R')
      {
         right();
         lcd_gotoxy(1,2);  printf(lcd_putc,"STATUS:RIGHT     ");
      }
      else
      {
         stop();
         lcd_gotoxy(1,2);  printf(lcd_putc,"STATUS:STOP     ");
      }
   }  
} 










