#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define PRO_CPU 0
#define APP_CPU 1
#define NOAFF_CPU tskNO_AFFINITY
#define pinLED2 32
#define pinLed 33
#define pot 34
#define pinBTN 13

#define COLUMS 16
#define ROWS   2

#define PAGE   ((COLUMS) * (ROWS))

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A00, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);


void TestHwm(char *taskName);
void TaskLed(void *pvParameters);
void Taskpot(void *pvParameters);
void TaskLED2(void *pvParameters);

void setup() {
  // put your setup code here, to run once:

  // xTaskCreatePinnedToCore(TaskLed, "TaskLed",1024,NULL,3,NULL,APP_CPU);
  // TaskLed: Nombre de la funcion 
  // "TaskLed": Nombre de la tarea
  // 3: prioridad que puede ser hasta 27 
  // APP_CPU: es el nucleo seleccionado
  xTaskCreatePinnedToCore(Taskpot, "Taskpot",4096,NULL,1,NULL,APP_CPU);
  xTaskCreatePinnedToCore(TaskLed, "TaskLed",4096,NULL,1,NULL,APP_CPU);
  xTaskCreatePinnedToCore(TaskLED2, "TaskLED2",4096,NULL,1,NULL,APP_CPU);
}
void loop() {}





// Tester: permite saber cuanta RAM no se esta usando una tarea y considerar el valor mas cercano mayor con 2^n
// Considerar que el maximo de RAM es 2^12 = 4096 bytes
// Esta funcion ocupa 512 bytes
void TestHwm(char *taskName){
  static int stack_hwm, stack_hwm_temp;

  stack_hwm_temp = uxTaskGetStackHighWaterMark(nullptr);
  if(!stack_hwm || (stack_hwm_temp < stack_hwm)){
    stack_hwm=stack_hwm_temp;
    Serial.printf("%s has stack hwm %u\n",taskName,stack_hwm);
  }
} 


void TaskLed(void *pvParameters){
  (void) pvParameters;
  pinMode(pinLed, OUTPUT);
  while(1){
    digitalWrite(pinLed, !digitalRead(pinLed));
    vTaskDelay(100);
    //TestHwm("TaskLed"); Si se quiere activar se debe sumar 512 bytes 
    // En ese caso se recomienda usar 2^11 = 2048 al tamaño en bytes de la tarea
  }
}


void Taskpot(void *pvParameters){
  (void) pvParameters;
  Serial.begin(9600);

  while (lcd.begin(COLUMS, ROWS) != 1) //colums - 20, rows - 4
  {
    Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
    vTaskDelay(5000);   
  }

  lcd.print(F("PCF8574 is OK..."));    //(F()) saves string to flash & keeps dynamic memory free
  vTaskDelay(2000);
  lcd.clear();
  vTaskDelay(500);

  Serial.println("Programa iniciado");
  lcd.print("Bienvenido");
  lcd.setCursor(0,1);
  lcd.print("Usuario");
  lcd.clear();
  while(1){
    
    int Vadc = analogRead(pot);
    int valor = map(Vadc,0,4095,0,100);
   
    vTaskDelay(500);
    lcd.clear();
    lcd.print("Sistema: On");
    lcd.setCursor(0,1);
    lcd.print("Voltaje:");
    lcd.setCursor(11,1);
    lcd.print(valor);
    vTaskDelay(100);
    //TestHwm("Taskpot");
  }
}



void TaskLED2(void *pvParameters){
  (void) pvParameters;
  Serial.begin(9600);
  pinMode(pinBTN, INPUT_PULLUP);
  pinMode(pinLED2, OUTPUT);
  while(1){
    if(digitalRead(pinBTN)==LOW){
      while(digitalRead(pinBTN)==LOW){};
      if(digitalRead(pinBTN)==HIGH ){
        digitalWrite(pinLED2, !digitalRead(pinLED2));
      }
      }
      vTaskDelay(10);
      //TestHwm("TaskLED2");
}
}
