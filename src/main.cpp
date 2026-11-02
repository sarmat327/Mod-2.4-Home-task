/*
Завдання 4: Polling + debounce (без interrupts)
Прибрати interrupt повністю
Опитувати кнопку кожні 5–10 мс
Реалізувати debounce як машину станів
Очікуваний результат

Найстабільніша поведінка
Трохи більша затримка реакції
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