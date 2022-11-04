#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define oled_i2c_Address 0x3c //Defines the I2C address used by the display

#define SCREEN_WIDTH 128      //OLED display width, in pixels
#define SCREEN_HEIGHT 64      //OLED display height, in pixels
#define OLED_RESET -1         //From the Adafruit example library

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Sets the 3 defines above into the Adafruit_SH1106G object

void setup(){
  Serial.begin(9600);                  //Sets speed of display draw. Recommanded 9600 but 38400 should work.
  delay(250);                           //Wait for the display to start up.
  display.begin(SSD1306_SWITCHCAPVCC, oled_i2c_Address); //Sets the I2C address used by the display
  display.display();                    //From the Adafruit example library
  delay(2000);                          //From the Adafruit example library

  //Clears display 
  display.clearDisplay();
  display.display();
}

/*
Char index for a clock
#0=42+6
#1=42+7
#2=42+8
#3=42+9
#4=42+10
#5=42+11
#6=42+12
#7=42+13
#8=42+14
#9=42+15
:=42+16
*/

int clock[6]={0,0,0,0,0,-1};

void loop(){
  clock[5]++;

  if(clock[5]>9){
    clock[5]=0;
    clock[4]++;
  }

  if(clock[4]>5){
    clock[4]=0;
    clock[3]++;
  }

  if(clock[3]>9){
    clock[3]=0;
    clock[2]++;
  }

  if(clock[2]>5){
    clock[2]=0;
    clock[1]++;
  }

  if(clock[1]>9){
    clock[1]=0;
    clock[0]++;
  }

  if(clock[0]>1 && clock[1]>23){
    clock[0]=0;
    clock[1]=0;
  }

  display.clearDisplay();
  display.fillCircle(63, 50, 3+clock[5]%2*3, SSD1306_WHITE);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(17,25);
  display.write(numTranslate(clock[0]));
  display.write(numTranslate(clock[1]));
  display.write(58);
  display.write(numTranslate(clock[2]));
  display.write(numTranslate(clock[3]));
  display.write(58);
  display.write(numTranslate(clock[4]));
  display.write(numTranslate(clock[5]));
  display.display();
  delay(250);
}

int numTranslate(int aNum){
  int tVal=0;
  switch (aNum){
    case 1:
      tVal=49;
      break;
    case 2:
      tVal=50;
      break;
    case 3:
      tVal=51;
      break;
    case 4:
      tVal=52;
      break;
    case 5:
      tVal=53;
      break;
    case 6:
      tVal=54;
      break;
    case 7:
      tVal=55;
      break;
    case 8:
      tVal=56;
      break;
    case 9:
      tVal=57;
      break;
    default:
      tVal=48;
      break;
  }
  return tVal;
}