/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Comment out above, uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);
*/


int ran;
int can1=5;
int can2=6;
int can3=7;
int silah1=2;
int silah2=3;
int silah3=4;
int buton=8;
void setup() {
  Serial.begin(9600);
  pinMode(can1,OUTPUT);
  pinMode(can2,OUTPUT);
  pinMode(can3,OUTPUT);
  
  pinMode(buton,INPUT);
  pinMode(silah1,OUTPUT);
  pinMode(silah2,OUTPUT);
  pinMode(silah3,OUTPUT);
  

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  


}
int matrix[8][16] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int konum=3;
int can=3;
int silah=3;
int butondurum=0;
void loop() {
  
  
  int sensorValue = analogRead(A0);
  butondurum=digitalRead(buton);
  Serial.println(butondurum);
  Serial.println(sensorValue);
  
  
  

  display.clearDisplay(); // Clear the screen
  display.setTextColor(SSD1306_WHITE); // Set the text color to white
  if(can==3)
  {
    digitalWrite(can1,HIGH);
    digitalWrite(can2,HIGH);
    digitalWrite(can3,HIGH);
  }
  if(can==2)
  {
    digitalWrite(can1,HIGH);
    digitalWrite(can2,HIGH);
    digitalWrite(can3,LOW);
  }
  if(can==1)
  {
    digitalWrite(can1,HIGH);
    digitalWrite(can2,LOW);
    digitalWrite(can3,LOW);
  }
  if(can==0)
  {
    digitalWrite(can1,LOW);
    digitalWrite(can2,LOW);
    digitalWrite(can3,LOW);
  }
  if(silah==3)
  {
    digitalWrite(silah1,HIGH);
    digitalWrite(silah2,HIGH);
    digitalWrite(silah3,HIGH);
  }
  if(silah==2)
  {
    digitalWrite(silah1,HIGH);
    digitalWrite(silah2,HIGH);
    digitalWrite(silah3,LOW);
  }
  if(silah==1)
  {
    digitalWrite(silah1,HIGH);
    digitalWrite(silah2,LOW);
    digitalWrite(silah3,LOW);
  }
  if(silah==0)
  {
    digitalWrite(silah1,LOW);
    digitalWrite(silah2,LOW);
    digitalWrite(silah3,LOW);
  }

  
  // Loop through the matrix and print each value
  
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<16;j++)
    {
      display.setCursor(j * 8, i * 8); 
      if(matrix[i][j]==0)
      {
      display.print(" ");        
      }
      if(matrix[i][j]==7)
      {
      display.print("E");
      }
      if(matrix[i][j]==1)
      {
      display.print("o");
      }
      if(matrix[i][j]==2)
      {
      display.print("Q");
      }
      
      
      
    }
    
  }
  if(sensorValue>512)
  {
    if(konum!=0)
    {
      if(matrix[konum-1][0]==0)
    {
       matrix[konum-1][0]=matrix[konum][0];
       matrix[konum][0]=0;
       konum=konum-1;
    }
    }
    
     
  }
  if(sensorValue<512)
  {
    if(konum!=7)
    {
      if(matrix[konum+1][0]==0)
    {
       matrix[konum+1][0]=matrix[konum][0];
       matrix[konum][0]=0;
       konum=konum+1;
    }
    }    
    
     
  }
  
  if(butondurum==1)
  {
    
    silah--;
    if(silah==-1)
    {
      silah=0;
    }
    butondurum=0;

    
  }
 
  Serial.println(can);
  
  Serial.println(silah);
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<16;j++)
    {
      
      matrix[i][j]=matrix[i][j+1];
      if(matrix[konum][0]==1 || matrix[konum][0]==2)
      {
        can--;
        if(can==-1)
        {
          can=0;
        }
      }
      matrix[konum][0]=7;
      if(j==15)
      {
       ran=random(0,10);
       
       if(ran==0)
       {
         matrix[i][j]=0;
       } 
       if(ran==1)
       {
         matrix[i][j]=1;
       } 
       if(ran==2)
       {
         matrix[i][j]=2;
       } 
       if(ran==3)
       {
         matrix[i][j]=0;
       } 
       if(ran==4)
       {
         matrix[i][j]=0;
       } 
       if(ran==5)
       {
         matrix[i][j]=0;
       } 
       if(ran==6)
       {
         matrix[i][j]=0;
       } 
       if(ran==7)
       {
         matrix[i][j]=0;
       } 
       if(ran==8)
       {
         matrix[i][j]=0;
       } 
       if(ran==9)
       {
         matrix[i][j]=0;
       } 
       

        
      }
      
    }
    
  }
  
  display.display(); // Display the content on the screen
  delay(500); 

}


