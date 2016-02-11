#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

const int colorR = 0;
const int colorG = 0;
const int colorB = 0;
const int pinSound = A1;
const int pinButton = 2;

const int noise = 250;
int current_offset = 0;
void setup()
{
  //Sets up pins for input
  pinMode(pinSound, INPUT);
  pinMode(pinButton, INPUT);
  //Sets up the lcd
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  current_offset= 0;
  Serial.begin(9600);
}
//Important variables
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
   if(digitalRead(pinButton) == HIGH)
    {
      lcd.clear(); //Clears the lcd when the button is pressed
    }
  if(current_offset == 4)
   {
      print_letter();//prints the letter if the letter buffer is full
      current_offset = 0;
   }
   int sensorValue = analogRead(pinSound);//Gets sound reading and puts it in sensorValue
  if(sensorValue > noise && current_offset < 4)//If sound reading is greater than threshold alnalyse it as a dot or a dash
    {
      sensorValue = 0;
      analyse();
      current_offset += 1;
      oneinput = true;
      //Serial.print(current_offset);
    }
  else if(sensorValue < noise)
  {
    clockloop();//If sound < threshold got to clockloop()
  }
}

void clockloop()
{
  timesincebreak = millis();//Get timestamp
  int shortcut = timesincebreak - timeatbreak;//timesincebreak - timeatbreak = timewithoutsound
   if(shortcut > 600 && shortcut < 1500 && oneinput == true)//If the time wihtout sound > 600 and < 1500 print the current letter and start a new one
    {
    current_offset = 0;
    print_letter();
    oneinput = false;
    }
  else if(shortcut > 2000 && space == true)//if the time withoutsound > 2000 print a space
   {
     current_offset = 0;
     lcd.print(' ');
     space = false;
     oneinput = false;   
   }
} 
void analyse()
{
  space = true; // set the ability for a new space to be printed
  int sensorbuffer = 0;
  for(int ppp = 0; ppp <= 10; ++ppp)//take ten readings and if they are greater than 100 add them to the variable sensorbuffer
  {
    sensorarray[ppp] = analogRead(pinSound);
    if(sensorarray[ppp] > 100)
      sensorbuffer += sensorarray[ppp];
    delay(50);
  }
  timeatbreak = millis();//get timeatbreak for use when calculating timewithoutsound
  int sensorValue = sensorbuffer / 5; //divide the sensorbuffer variable by 5
  //Serial.print(sensorValue);
  //Serial.print(" ");
  if(sensorValue <= 150)//If the value is less than 150 it is a dot
   {
     letter_buffer[current_offset] = 1;
     //Serial.print("Dot");
   }
   else if(sensorValue > 150)//If the value is greater than 150 it is a dash
   {
     letter_buffer[current_offset] = 2;
    // Serial.print("Dash");
   }
  //Set all variables back to 0
  sensorValue = 0;
  sensorbuffer = 0;
  for(int qqq = 0; qqq <= 10; ++qqq)
  {
    sensorarray[qqq] = 0;
  } 
  //Set oneinput to true to allow for the letter/space to be printed
  oneinput = true;
}


void print_letter()//print letter function
{
//converts dots and dashes to a single value i.e if it was a the inpput would be 2,1,0,0. To compare it against the letters array we need it as 2100.
for(int jjj = 0;jjj < 4;++jjj)
      {
        if(jjj == 0)
          final_letter += (letter_buffer[jjj] * 1000);//Creates the thousand
        else if(jjj == 1)
          final_letter += (letter_buffer[jjj] *100);//Creates the hundred
        else if(jjj == 2)
          final_letter += (letter_buffer[jjj] *10);//Creates the ten
        else
           final_letter += (letter_buffer[jjj]);//The unit
      }
      for(int kkk = 0; kkk<=25;++kkk)//Compares the new value e.g 2100 against letters array.
      {
//If we have the latter 'a' the program will find a match the 2100 in the first place of the letters array-slot 0.       
        if(final_letter == letters[kkk])
        {  
          lcd.print(static_cast<char>(kkk + 97)); //Adds 97 to how far into the for loop we are to get the ASCII value. It converts and prints this value
          //Serial.print(static_cast<char>(kkk + 97));
        }
    }
//Sets all variables back to 0    
    final_letter = 0;
    for(int lll = 0; lll < 4; ++lll)
    {
     letter_buffer[lll] = 0;
    }
}
