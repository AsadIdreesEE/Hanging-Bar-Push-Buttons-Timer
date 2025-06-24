#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

#define CLK  11
#define OE   9
#define LAT  10
#define A    A0
#define B    A1
#define C    A2
#define D    A3

#define BUTTON_PIN 2
#define LED_PIN 5

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

// Timer states
enum TimerState {
  IDLE,
  RUNNING,
  STOPPED
};

TimerState state = IDLE;

unsigned long startMicros = 0;
unsigned long elapsedMicros = 0;

bool lastButtonState = HIGH;
char lastTimeString[6] = "";

void setup() {
  matrix.begin();
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  displayTime(0); // Show 00:00 on boot
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    delay(50); // debounce
    if (digitalRead(BUTTON_PIN) == LOW) {
      // Handle state changes
      if (state == IDLE) {
        state = RUNNING;
        startMicros = micros();
        elapsedMicros = 0;
        digitalWrite(LED_PIN, HIGH);
      } else if (state == RUNNING) {
        elapsedMicros += micros() - startMicros;
        state = STOPPED;
        digitalWrite(LED_PIN, LOW);
      } else if (state == STOPPED) {
        state = IDLE;
        elapsedMicros = 0;
        displayTime(0); // Reset to 00:00
        strcpy(lastTimeString, ""); // Clear buffer
      }
    }
  }

  lastButtonState = currentButtonState;

  if (state == RUNNING) {
    unsigned long currentMicros = elapsedMicros + micros() - startMicros;
    displayTime(currentMicros);
  } else if (state == STOPPED) {
    displayTime(elapsedMicros);
  }

  delay(50);
}

void displayTime(unsigned long totalMicros) {
  unsigned int sec = (totalMicros / 1000000UL) % 100;
  unsigned int usec = (totalMicros % 1000000UL) / 10000;

  char timeString[6];
  sprintf(timeString, "%02d:%02d", sec, usec);

  if (strcmp(timeString, lastTimeString) != 0) {
    strcpy(lastTimeString, timeString);

    matrix.fillScreen(matrix.Color333(0, 0, 0)); // Clear screen
    matrix.setTextSize(2);
    matrix.setCursor(3, 9); // Position (3, 9) as requested
    matrix.setTextColor(matrix.Color333(7, 7, 7)); // White
    matrix.print(timeString);
  }
}
