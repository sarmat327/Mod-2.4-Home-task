/*
Завдання 3: Debounce через перевірку рівня (state-based)
Interrupt лише сигналізує “подія”
У loop() / task:
приймати подію лише якщо кнопка досі натиснута
ігнорувати події при відпусканні
Очікуваний результат

Рівно 1 реакція на 1 натискання
Release не викликає дії
*/

#include <Arduino.h>

#define PIN_IN         15
#define PERIOD_MS      50

volatile u32_t counter = 0;
volatile u32_t lastTimeChanged = 0;
volatile bool interruptFlag = false;

void IRAM_ATTR buttonISR()
{
    interruptFlag = true;
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
  if(interruptFlag && digitalRead(PIN_IN)){
    interruptFlag = false;
    counter++;
    Serial.println("BUTTON was PRESSED");
    Serial.printf("COUNTER is: %d \n", counter);
  } 
}