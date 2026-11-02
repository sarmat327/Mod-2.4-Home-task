
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

#define PIN_IN       15

#define POLLING_INTERVAL 5
#define DEBOUNCE_TIME    50

// Button states machine
enum ButtonState : uint8_t
{
    RELEASED,
    PRESSED
};

ButtonState buttonState = RELEASED;

uint32_t lastPollingTime = 0;
uint32_t lastDebounceTime = 0;

uint32_t counter = 0;

bool rawState = HIGH;
bool lastRawState = HIGH;


void setup()
{
    Serial.begin(115200);

    pinMode(PIN_IN, INPUT_PULLUP);
    Serial.println(digitalRead(PIN_IN));

    Serial.println("SETUP DONE");
}

void buttonTask(uint32_t now)
{
    rawState = digitalRead(PIN_IN);

    if (rawState != lastRawState)
    {
        lastDebounceTime = now;
        lastRawState = rawState;
    }

    if (now - lastDebounceTime >= DEBOUNCE_TIME)
    {
        // State machine
        switch (buttonState)
        {
            case RELEASED:

                if (rawState == LOW)
                {
                    buttonState = PRESSED;
                    counter++;
                    Serial.println("BUTTON PRESSED");
                    Serial.printf("COUNTER: %d \n", counter);
                }

                break;


            case PRESSED:

                if (rawState == HIGH)
                {
                    buttonState = RELEASED;
                    Serial.println("BUTTON RELEASED");
                }

                break;
        }
    }
}

void loop()
{
    uint32_t now = esp_timer_get_time();

    // Polling every 5 ms
    if (now - lastPollingTime >= POLLING_INTERVAL)
    {
        lastPollingTime = now;

        buttonTask(now);
    }
}



