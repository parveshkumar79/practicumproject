#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

char keys[4][3]={
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9};
byte colPin[3]={3,4,5};

String password = "141";  // The Pin Code.
int position = 0;

int wrong = 0; // Variable to calculate the wrong inputs.

int redPin = 10;
int greenPin = 11;
int buzzer = 12;
 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,3);
// MAPPING THE KEYPAD.


int total = 0; // Variable to determine the number of wrong attempts.

void setup()
{
  
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(buzzer, OUTPUT);
 
lcd.init(); //lcd startup
lcd.init();
lcd.backlight();
lcd.print("     Keypad code     ");
lcd.setCursor(0,1);
lcd.print("   Locking System   ");
lcd.setCursor(0,2);
lcd.print("         By:        ");
lcd.setCursor(0,3);
lcd.print("   GROUP11   ");
delay(3000);
lcd.clear();
setLocked(true);
delay(20);
}

void loop()
{
  
  lcd.clear();
  lcd.print(" Enter Unlock Code: ");
  delay(100);
  
 char pressed=keypad.getKey();
 String key[3];
  
 if(pressed)
 {
  lcd.clear();
  lcd.print(" Enter Unlock Code: ");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(500);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }

    else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != password[position] )
      {
          wrong++;
          position ++;
      }

    if(position == 3){
          if( wrong >0)
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.setCursor(0,2);
                lcd.print("    Wrong Code!     ");
                delay(1000);
                setLocked(true);
            }

          else if(position == 3 && wrong == 0)
            {
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.setCursor(0,1);
                lcd.print("      Welcome!     ");
                lcd.setCursor(5,2);
                lcd.print(" Door Open");
                delay(2000);
                setLocked(false);
            }

             if(total ==3)
            {
                total=0;
                buzzer_beep();
                delay(500);
            }

        }

   }

   
}

void setLocked(int locked)
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(1000);
      }
    else
      {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          delay(2000);
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
      }
  }
void buzzer_beep()
{
   lcd.clear();
   lcd.setCursor(0,1);
   lcd.print("    WARNING  !!!!   ");
   lcd.setCursor(0,2);
   lcd.print("   Access Denied");
   for (int i=0;i<10;i++){
   digitalWrite(buzzer,HIGH);
   delay(1000);
   digitalWrite(buzzer,LOW);
   delay(1000);
   }
}
