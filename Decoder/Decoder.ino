#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

const int colorR = 0;
const int colorG = 100;
const int colorB = 0;
const int pinSound = A1;
const int pinTouch = A2;

const int noise = 250;
int current_offset = 0;
void setup()
{
  pinMode(pinSound, INPUT);
  pinMode(pinTouch, INPUT);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.setRGB(colorR, colorG, colorB);
    current_offset= 0;
    Serial.begin(9600);
}
int letters[26] = {1200, 2111, 2121, 2110, 1000, 1121, 2210, 1111, 1100, 1222, 2120, 1211, 2200, 2100, 2220, 1221, 2212, 1210, 1110, 2000, 1120, 1112, 1220, 2112, 2122, 2211};
int letter_buffer[4];
int final_letter = 0;
unsigned long time_elapsed;
int sensorarray[10];
unsigned long timeatbreak;
unsigned long timesincebreak;
bool space(false);
bool oneinput(false);
void loop() 
{
   if(analogRead(pinTouch) > 250)
     {
       lcd.clear();
     }
  if(current_offset == 4)
   {
      print_letter();
      current_offset = 0;
   }
   int sensorValue = analogRead(pinSound);
  if(sensorValue > noise && current_offset < 4)
    {
      sensorValue = 0;
      analyse();
      current_offset += 1;
      oneinput = true;
      //Serial.print(current_offset);
    }
  else if(sensorValue < noise)
  {
    clockloop();
  }
}

void clockloop()
{
  timesincebreak = millis();
  int shortcut = timesincebreak - timeatbreak;
   if(shortcut > 600 && shortcut < 1500 && oneinput == true)
    {
    current_offset = 0;
    print_letter();
    oneinput = false;
    }
  else if(shortcut > 2000 && space == false)
   {
     current_offset = 0;
     lcd.print(' ');
     space = true;
     oneinput = false;   
   }
} 
void analyse()
{
  space = false;
  int sensorbuffer = 0;
  for(int ppp = 0; ppp <= 10; ++ppp)
  {
    sensorarray[ppp] = analogRead(pinSound);
    if(sensorarray[ppp] > 100)
      sensorbuffer += sensorarray[ppp];
    delay(50);
  }
  timeatbreak = millis();
  int sensorValue = sensorbuffer / 5;
  Serial.print(sensorValue);
  Serial.print(" ");
  if(sensorValue <= 150)
   {
     letter_buffer[current_offset] = 1;
     //Serial.print("Dot");
   }
   else if(sensorValue > 150)
   {
     letter_buffer[current_offset] = 2;
    // Serial.print("Dash");
   }
  sensorValue = 0;
  sensorbuffer = 0;
  for(int qqq = 0; qqq <= 10; ++qqq)
  {
    sensorarray[qqq] = 0;
  } 
  oneinput = true;
}


void print_letter()
{
for(int jjj = 0;jjj < 4;++jjj)
      {
        if(jjj == 0)
          final_letter += (letter_buffer[jjj] * 1000);
        else if(jjj == 1)
          final_letter += (letter_buffer[jjj] *100);
        else if(jjj == 2)
          final_letter += (letter_buffer[jjj] *10);
        else
           final_letter += (letter_buffer[jjj]);
      }
      for(int kkk = 0; kkk<=25;++kkk)
      {
        if(final_letter == letters[kkk])
        {
          lcd.print(static_cast<char>(kkk + 97));
          //Serial.print(static_cast<char>(kkk + 97));
        }
    }
    final_letter = 0;
    for(int lll = 0; lll < 4; ++lll)
    {
     letter_buffer[lll] = 0;
    }
}
