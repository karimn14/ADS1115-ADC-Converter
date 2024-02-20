#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold9pt7b.h>

#include <Adafruit_ADS1X15.h>
#define ADS1115_ADDR_SDA 0x4A
Adafruit_ADS1115 ads;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.println("START MEASURE!");

  ads.setGain(GAIN_TWO);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV

  while (!ads.begin(0x4A)) {
    Serial.println("Failed to initialize ADS.");
  }
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop(){
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3; 
  
  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);
  adc1 = ads.readADC_SingleEnded(1);
  volts1 = ads.computeVolts(adc1);
  adc2 = ads.readADC_SingleEnded(2);
  volts2 = ads.computeVolts(adc2);
  adc3 = ads.readADC_SingleEnded(3);
  volts3 = ads.computeVolts(adc3);

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("V0: "); Serial.println(volts0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("V1: "); Serial.println(volts1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("V2: "); Serial.println(volts2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.print("V3: "); Serial.println(volts3);

  display.clearDisplay();
  display.setCursor(0,5); display.print("A0:");display.println(volts0);display.println("V ");
  display.setCursor(0,15);display.println(adc0); 
  display.setCursor(0,35); display.print("A1:");display.println(volts1);display.println("V ");
  display.setCursor(0,45);display.println(adc1); 
  
  display.setCursor(60,5); display.print("A2:");display.println(volts2);display.println("V ");
  display.setCursor(60,15);display.println(adc2); 
  display.setCursor(60,35); display.print("A3:");display.println(volts3);display.println("V ");
  display.setCursor(60,45);display.println(adc3); 

  display.display();
  
  delay(500);
}
