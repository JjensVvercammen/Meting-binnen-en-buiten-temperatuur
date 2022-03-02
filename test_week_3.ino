#include <SevSeg.h>
SevSeg sevseg;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define address 0x4F
int counter;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A0;
int sensorValue;
int temperature = 0;
int wait = 0; 
unsigned long startTime= 0;
int tempK    = 0;
int tempC    = 0;
long sensor  = 0;

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2, 0);
}

void loop() 
{
  if(millis() > (startTime + wait))
  {
    startTime = millis();
    sensorValue = analogRead(sensorPin);
    float temperature = map(sensorValue, 0, 410, -50, 150);
    temperature =(temperature / 10);
    lcd.setCursor(0, 0);
    lcd.print("TempBinnen: ");
    lcd.setCursor(11, 0);
    lcd.print(temperature);
  }
  Wire.beginTransmission(address);
  Wire.write(0x00);
  Wire.requestFrom(address, 2);
  int temperature;
  if (Wire.available()) {
     //temperature = Wire.read();

         int a = Wire.read();
          int b = Wire.read();
            float temp = a;
  temp=temp+((float)b/1024.0);
  lcd.setCursor(0, 1);
  lcd.print("TempBuiten: ");
  lcd.setCursor(11, 1);
  lcd.print(temp);
  }
 delay(1000);
}
