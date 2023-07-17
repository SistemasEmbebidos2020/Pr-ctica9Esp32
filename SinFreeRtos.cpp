#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinLED2 32
#define pinLed 33
#define pot 34
#define pinBTN 13

#define COLUMS 16
#define ROWS   2

#define PAGE   ((COLUMS) * (ROWS))

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A00, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);


void setup() {
  // put your setup code here, to run once:
  pinMode(pinLed, OUTPUT);
  pinMode(pinBTN, INPUT_PULLUP);
  pinMode(pinLED2, OUTPUT);
  Serial.begin(9600);

  while (lcd.begin(COLUMS, ROWS) != 1) //colums - 20, rows - 4
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    delay(5000);   
  }

  lcd.print(F("PCF8574 is OK..."));    //(F()) saves string to flash & keeps dynamic memory free
  delay(2000);
  lcd.clear();
  delay(500);

  Serial.println("Programa iniciado");
  lcd.print("Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Usuario");
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinLed, !digitalRead(pinLed));
  delay(100);


  int Vadc = analogRead(pot);
  Vadc = Vadc*0.025;
  // Se coloca limite superior igual a 100
  if(Vadc>100){
    Vadc = 100;
  }
  delay(500);
  lcd.clear();
  lcd.print("Sistema: On");
  lcd.setCursor(0,1);
  lcd.print("Voltaje:");
  lcd.setCursor(11,1);
  lcd.print(Vadc);
  delay(100);


  if(digitalRead(pinBTN)==LOW){
    while(digitalRead(pinBTN)==LOW){};
    if(digitalRead(pinBTN)==HIGH ){
      digitalWrite(pinLED2, !digitalRead(pinLED2));
      }
  }
  delay(10);
  
}
