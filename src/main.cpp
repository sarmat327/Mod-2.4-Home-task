#include <Arduino.h>

#define PIN_IN         15
#define PERIOD_MS      50

volatile u32_t lastTimeChanged = 0;
volatile bool interruptFlag = false;

void IRAM_ATTR buttonISR()
{
    if(millis()-lastTimeChanged >= PERIOD_MS){
      interruptFlag = true;
      lastTimeChanged = millis();
    } 
}

void setup(){
  Serial.begin(115200);
  pinMode(PIN_IN, PULLUP);

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
    Serial.println("BUTTON was PRESSED");
  } 
}