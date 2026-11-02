/*
Завдання 2: Software debounce через таймер (time-based)
Додати debounce на основі часу:
ігнорувати interrupt, якщо з моменту попереднього пройшло < 50 мс
Реалізувати поза ISR
Очікуваний результат

Менше хибних спрацювань
Все ще можливі спрацювання при відпусканні
*/

#include <Arduino.h>

#define PIN_IN         15
#define PERIOD_MS      50

volatile u32_t counter = 0;
volatile u32_t lastTimeChanged = 0;
volatile bool interruptFlag = false;

void IRAM_ATTR buttonISR()
{
    if(esp_timer_get_time()-lastTimeChanged >= PERIOD_MS && !interruptFlag){
      interruptFlag = true;
      lastTimeChanged = esp_timer_get_time();
    } 
}

void setup(){
  Serial.begin(115200);
  pinMode(PIN_IN, INPUT_PULLUP);
  Serial.println(digitalRead(PIN_IN));
  Serial.println("SETUP DONE");
  attachInterrupt(
        digitalPinToInterrupt(PIN_IN),
        buttonISR,
        FALLING
    );
}



void loop(){
  if(interruptFlag){
    interruptFlag = false;
    counter++;
    Serial.println("BUTTON was PRESSED");
    Serial.printf("COUNTER is: %d \n", counter);
  } 
}