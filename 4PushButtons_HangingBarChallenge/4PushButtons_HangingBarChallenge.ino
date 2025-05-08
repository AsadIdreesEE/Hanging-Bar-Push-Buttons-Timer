// Define push button pins
#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUTTON3_PIN 4
#define BUTTON4_PIN 5

// Debounce delay
const unsigned long debounceDelay = 50; // in milliseconds

// Variables to store the last debounce time
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;

// Variables to store the last state of the buttons
bool lastButtonState1 = HIGH;
bool lastButtonState2 = HIGH;
bool lastButtonState3 = HIGH;
bool lastButtonState4 = HIGH;

// Variables to store the current state of the timer
bool timerRunning = false;

void setup() {
  // Initialize button pins as input with internal pull-up resistors
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the state of each button
  int reading1 = digitalRead(BUTTON1_PIN);
  int reading2 = digitalRead(BUTTON2_PIN);
  int reading3 = digitalRead(BUTTON3_PIN);
  int reading4 = digitalRead(BUTTON4_PIN);

  // Check if any button is pressed
  if ((reading1 == LOW || reading2 == LOW || reading3 == LOW || reading4 == LOW) && !timerRunning) {
    startTimer();
    timerRunning = true;
  }

  // Check if all buttons are released
  if ((reading1 == HIGH && reading2 == HIGH && reading3 == HIGH && reading4 == HIGH) && timerRunning) {
    stopTimer();
    timerRunning = false;
  }

  // Update the last button states
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
  lastButtonState4 = reading4;

  // Delay to prevent flooding the serial output
  delay(50);
}

void startTimer() {
  // Send command to start timer
  Serial.println("Zano Excited");
}

void stopTimer() {
  // Send command to stop timer
  Serial.println("Zano Slept");
}
