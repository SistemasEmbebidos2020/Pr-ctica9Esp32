#include <Arduino.h>

/*
 * Simple example to create and destroy a task by Daniel Carrasco (https://www.electrosoftcloud.com)
 */
#define LED_BUILTIN1 21
#define LED_BUILTIN2 19
bool led_status1 = false;
bool led_status2 = false;
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void setup() {
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
    1
  );
}
void loop() {

}
void TaskBlink1(void *pvParameters) {
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN1, OUTPUT);
  for (;;) { // A Task shall never return or exit.
    digitalWrite(LED_BUILTIN1, led_status1);
    led_status1 = !led_status1;
    // Wait exactly 1500ms from execution start
    vTaskDelay(1500 / portTICK_PERIOD_MS );
    // Delete the task
    //vTaskDelete(NULL);
  }
}
void TaskBlink2(void *pvParameters) {
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN2, OUTPUT);
  for (;;) { // A Task shall never return or exit.
    digitalWrite(LED_BUILTIN2, led_status2);
    led_status2 = !led_status2;
    // Wait exactly 500ms from execution start
    vTaskDelay(500 / portTICK_PERIOD_MS );
    // Delete the task
    //vTaskDelete(NULL);
  }
}

