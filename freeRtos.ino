#include <Arduino.h>

/*
 * Simple example to create and destroy a task by Daniel Carrasco (https://www.electrosoftcloud.com)
 */
#define LED_BUILTIN1 21
#define LED_BUILTIN2 2

bool led_status1 = false;
bool led_status2 = false;
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);

void setup() {
  // Create a new task pinned to core 1.
  xTaskCreatePinnedToCore(
    TaskBlink1,
    "Taskname",
    1024,
    NULL,
    1,
    NULL,
    1);
  xTaskCreatePinnedToCore(
    TaskBlink2,
    "Taskname",
    1024,
    NULL,
    1,
    NULL,
    2
  );
}
void loop() {

}
void TaskBlink1(void *pvParameters) {
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;) { // A Task shall never return or exit.
    digitalWrite(LED_BUILTIN, led_status1);
    led_status1 = !led_status1;
    delay(1000);

  }
}
void TaskBlink2(void *pvParameters) {
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN2, OUTPUT);
  for (;;) { // A Task shall never return or exit.
    digitalWrite(LED_BUILTIN2, led_status2);
    led_status2 = !led_status2;
    delay(2000);

  }
}

