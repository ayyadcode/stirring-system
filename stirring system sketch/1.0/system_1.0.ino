#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <AccelStepper.h>

// Define the pins for the TB6600 driver
#define PUL_PIN 2
#define DIR_PIN 3

// Define the keypad layout
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {8, 9, 10, 11};
byte colPins[COLS] = {4, 5, 6, 7};

// Initialize the keypad and display
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Motor parameters
int speed = 100;            // Default speed in RPM
int acceleration = 20;      // Default acceleration in RPM
int runTime = 60;           // Default run time in seconds
bool clockwise = true;      // Default rotation direction

// Variables for timing
unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;

// Create an instance of AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, PUL_PIN, DIR_PIN);

// Function prototypes
void updateDisplay();
void startMotor();
void stopMotor();
void resetSettings();

void setup() {
  stepper.setMaxSpeed(speed);
  stepper.setAcceleration(acceleration);
  
  pinMode(PUL_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Stirring System");
  display.setTextSize(1);
  display.println("V1.0.0");
  display.display();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
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
        speed = speedStr.toInt();
        stepper.setMaxSpeed(speed);
        updateDisplay();
        break;
        
      case 'B':
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Set run time:");
        display.println("1) Minutes");
        display.println("2) Seconds");
        display.display();
        delay(100);
        key = keypad.getKey();
        if (key == '1') {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Set run time (min): ");
          display.display();
          delay(100);
          String timeStr = "";
          while (key != '#') {
            key = keypad.getKey();
            if (key >= '0' && key <= '9') {
              timeStr += key;
              display.setCursor(0, 20);
              display.print("                ");  // Clear the previous value
              display.setCursor(0, 20);
              display.print(timeStr);
              display.display();
            }
          }
          runTime = timeStr.toInt() * 60;
        } else if (key == '2') {
          display.clearDisplay();
          display.setCursor(0, 0);
          display.print("Set run time (sec): ");
          display.display();
          delay(100);
          String timeStr = "";
          while (key != '#') {
            key = keypad.getKey();
            if (key >= '0' && key <= '9') {
              timeStr += key;
              display.setCursor(0, 20);
              display.print("                ");  // Clear the previous value
              display.setCursor(0, 20);
              display.print(timeStr);
              display.display();
            }
          }
          runTime = timeStr.toInt();
        }
        updateDisplay();
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
        acceleration = accelStr.toInt();
        stepper.setAcceleration(acceleration);
        updateDisplay();
        break;
        
      case 'D':
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Rotation:");
        display.println("1) Clockwise");
        display.println("2) Counter-Clockwise");
        display.display();
        delay(100);
        key = keypad.getKey();
        if (key == '1') {
          clockwise = true;
        } else if (key == '2') {
          clockwise = false;
        }
        digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
        updateDisplay();
        break;
        
      case '#':
        startMotor();
        break;
        
      case '*':
        stopMotor();
        resetSettings();
        updateDisplay();
        break;
    }
  }
  
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  
  if (elapsedTime >= runTime * 1000) {
    stopMotor();
  }
  
  stepper.run();
  updateDisplay();
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Speed: ");
  display.print(speed);
  display.println(" RPM");
  display.print("Acceleration: ");
  display.print(acceleration);
  display.println(" RPM");
  display.print("Run Time: ");
  display.print(runTime / 60);
  display.println(" min");
  display.print("Direction: ");
  display.println(clockwise ? "Clockwise" : "Counter-Clockwise");
  display.print("Current Speed: ");
  display.print(elapsedTime < runTime * 1000 ? speed : 0);
  display.println(" RPM");
  display.print("Time Remaining: ");
  display.print((runTime * 1000 - elapsedTime) / 1000);
  display.println(" sec");
  display.display();
}

void startMotor() {
  startTime = millis();
  stepper.setSpeed(speed * (clockwise ? 1 : -1));
  stepper.runSpeedToPosition();
}

void stopMotor() {
  stepper.stop();
  stepper.setSpeed(0);
}

void resetSettings() {
  speed = 100;
  acceleration = 20;
  runTime = 60;
  clockwise = true;
}
