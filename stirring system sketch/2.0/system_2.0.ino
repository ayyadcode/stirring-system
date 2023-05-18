#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <AccelStepper.h>

// OLED display configuration
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(128, 32, &Wire, -1);

// Keypad configuration
const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pin_rows[ROWS] = {8, 9, 10, 11};    // connect to the row pinouts of the keypad
byte pin_column[COLS] = {4, 5, 6, 7};    // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROWS, COLS);

// Motor configuration
AccelStepper stepper(AccelStepper::DRIVER, 2, 3);  // Step pin, Direction pin

// Speed, acceleration, run time, and rotation variables
int speed = 100;           // Default speed in RPM
int acceleration = 20;     // Default acceleration in RPM
int runTime = 60;          // Default run time in seconds
bool clockwise = true;     // Default rotation direction (clockwise)

// Constants
const int MIN_SPEED = 0;          // Minimum speed value
const int MAX_SPEED = 500;        // Maximum speed value
const int MIN_ACCELERATION = 0;   // Minimum acceleration value
const int MAX_ACCELERATION = 100; // Maximum acceleration value
const int MIN_RUN_TIME = 0;       // Minimum run time value
const int MAX_RUN_TIME = 600;     // Maximum run time value

// Time variables
unsigned long startTime;
unsigned long elapsedTime;

// Function prototypes
void updateDisplay();
void startMotor();
void stopMotor();
void resetSettings();

void setup() {
  // Initialize the OLED display
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Stirring System");
  display.println("V2.0.0");
  display.println("Designed By");
  display.println("Amr Ayyad");
  display.display();
  delay(1000);

  // Set up motor
  stepper.setMaxSpeed(speed);
  stepper.setAcceleration(acceleration);

  // Set initial display
  updateDisplay();
}

void loop() {
  char key = keypad.getKey();

  switch (key) {
    case 'A':
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Set speed (RPM): ");
      display.display();
      delay(100);
      String speedStr = "";
      while (key != '#') {
        key = keypad.getKey();
        if (key >= '0' && key <= '9') {
          speedStr += key;
          display.setCursor(0, 20);
          display.print("                ");  // Clear the previous value
          display.setCursor(0, 20);
          display.print(speedStr);
          display.display();
        }
      }
      int newSpeed = speedStr.toInt();
      if (newSpeed >= MIN_SPEED && newSpeed <= MAX_SPEED) {
        speed = newSpeed;
        updateDisplay();
      } else {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Invalid speed!");
        display.display();
        delay(2000);
        updateDisplay();
      }
      break;

    case 'C':
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Set acceleration (RPM): ");
      display.display();
      delay(100);
      String accelStr = "";
      while (key != '#') {
        key = keypad.getKey();
        if (key >= '0' && key <= '9') {
          accelStr += key;
          display.setCursor(0, 20);
          display.print("                ");  // Clear the previous value
          display.setCursor(0, 20);
          display.print(accelStr);
          display.display();
        }
      }
      int newAccel = accelStr.toInt();
      if (newAccel >= MIN_ACCELERATION && newAccel <= MAX_ACCELERATION) {
        acceleration = newAccel;
        updateDisplay();
      } else {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Invalid acceleration!");
        display.display();
        delay(2000);
        updateDisplay();
      }
      break;

    case 'B':
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Set run time:");
      display.println("1 - Minutes");
      display.println("2 - Seconds");
      display.display();
      delay(100);
      char timeChoice = keypad.getKey();
      if (timeChoice == '1') {
        display.setCursor(0, 20);
        display.println("Enter minutes: ");
        display.display();
        delay(100);
        String minutesStr = "";
        while (key != '#') {
          key = keypad.getKey();
          if (key >= '0' && key <= '9') {
            minutesStr += key;
            display.setCursor(0, 30);
            display.print("                ");  // Clear the previous value
            display.setCursor(0, 30);
            display.print(minutesStr);
            display.display();
          }
        }
        int newMinutes = minutesStr.toInt();
        if (newMinutes >= MIN_RUN_TIME && newMinutes <= MAX_RUN_TIME) {
          runTime = newMinutes * 60;
          updateDisplay();
        } else {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Invalid run time!");
          display.display();
          delay(2000);
          updateDisplay();
        }
      } else if (timeChoice == '2') {
        display.setCursor(0, 20);
        display.println("Enter seconds: ");
        display.display();
        delay(100);
        String secondsStr = "";
        while (key != '#') {
          key = keypad.getKey();
          if (key >= '0' && key <= '9') {
            secondsStr += key;
            display.setCursor(0, 30);
            display.print("                ");  // Clear the previous value
            display.setCursor(0, 30);
            display.print(secondsStr);
            display.display();
          }
        }
        int newSeconds = secondsStr.toInt();
        if (newSeconds >= MIN_RUN_TIME && newSeconds <= MAX_RUN_TIME) {
          runTime = newSeconds;
          updateDisplay();
        } else {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Invalid run time!");
          display.display();
          delay(2000);
          updateDisplay();
        }
      }
      break;

    case 'D':
      clockwise = !clockwise;
      updateDisplay();
      break;

    case '#':
      startMotor();
      break;

    case '*':
      stopMotor();
      resetSettings();
      break;
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Speed: ");
  display.println(speed);
  display.print("Acceleration: ");
  display.println(acceleration);
  display.print("Run Time: ");
  display.println(runTime);
  display.print("Direction: ");
  display.println(clockwise ? "Clockwise" : "Counterclockwise");
  display.display();
}

void startMotor() {
  updateDisplay();

  // Start the motor
  stepper.setMaxSpeed(speed);
  stepper.setAcceleration(acceleration);
  stepper.moveTo(clockwise ? 360 : -360);  // Example: Rotate 360 degrees

  // Set the start time
  startTime = millis();

  // Run the motor until the run time is reached
  while (elapsedTime < runTime * 1000) {
    stepper.run();
    elapsedTime = millis() - startTime;
    // Update the display with current speed and remaining time
    display.setCursor(0, 20);
    display.print("Speed: ");
    display.print(stepper.speed());
    display.print("     ");
    display.setCursor(0, 30);
    display.print("Time: ");
    display.print(runTime - (elapsedTime / 1000));
    display.print(" s     ");
    display.display();
  }

  stopMotor();
}

void stopMotor() {
  stepper.stop();
  stepper.setCurrentPosition(0);
  updateDisplay();
}

void resetSettings() {
  speed = 100;
  acceleration = 20;
  runTime = 60;
  clockwise = true;
  updateDisplay();
}
