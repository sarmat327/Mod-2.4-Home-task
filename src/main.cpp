
#include <Arduino.h>

// Hardware configuration
#define BUTTON_PIN       15

// Timing configuration
#define POLLING_INTERVAL 5
#define DEBOUNCE_TIME    50

// Button states
enum ButtonState : uint8_t
{
    RELEASED,
    PRESSED
};

// Button variables
ButtonState buttonState = RELEASED;

uint32_t lastPollingTime = 0;
uint32_t lastDebounceTime = 0;

uint32_t counter = 0;

bool rawState = HIGH;
bool lastRawState = HIGH;


void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.println("SETUP DONE");
}

void buttonTask(uint32_t now)
{
    // Read physical button state
    rawState = digitalRead(BUTTON_PIN);

    // Detect raw state change
    if (rawState != lastRawState)
    {
        lastDebounceTime = now;
        lastRawState = rawState;
    }

    // Check if state is stable
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

                    Serial.printf(
                        "COUNTER: %lu\n",
                        (unsigned long)counter
                    );
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
    uint32_t now = millis();

    // Polling every 5 ms
    if (now - lastPollingTime >= POLLING_INTERVAL)
    {
        lastPollingTime = now;

        buttonTask(now);
    }
}



