
## Connecting and Using the System
To connect and use the system with a 12V 20A PSU, follow these steps:

1. Connect the TB6600 driver:
   - Connect the VCC pin of the TB6600 driver to the 12V output of the PSU.
   - Connect the GND pin of the TB6600 driver to the GND of the PSU.
   - Connect the A+ and A- pins of the TB6600 driver to one coil of the NEMA 17 motor.
   - Connect the B+ and B- pins of the TB6600 driver to the other coil of the NEMA 17 motor.
   - Connect the STEP pin of the TB6600 driver to pin 2 of the Arduino Uno.
   - Connect the DIR pin of the TB6600 driver to pin 3 of the Arduino Uno.

2. Connect the I2C OLED display:
   - Connect the VCC pin of the OLED display to the 5V output of the Arduino Uno.
   - Connect the GND pin of the OLED display to the GND of the Arduino Uno.
   - Connect the SDA pin of the OLED display to the SDA pin (A4) of the Arduino Uno.
   - Connect the SCL pin of the OLED display to the SCL pin (A5) of the Arduino Uno.

3. Connect the 16-key membrane keypad:
   - Connect the ROW pins of the keypad to digital pins 8, 9, 10, and 11 of the Arduino Uno.
   - Connect the COLUMN pins of the keypad to digital pins 4, 5, 6, and 7 of the Arduino Uno.

4. Connect the 12V 20A PSU:
   - Connect the positive terminal of the PSU to the VIN pin of the Arduino Uno.
   - Connect the negative terminal of the PSU to the GND pin of the Arduino Uno.

5. Upload the sketch to the Arduino Uno using the Arduino IDE.

## How to Use the System
Once everything is connected, you can use the system as follows:

1. Power on the system by connecting the 12V 20A PSU.

2. The OLED display will show the message "Stirring System V0.0.0" briefly.

3. **Adjust the speed:**
   - Press the "A" button on the keypad.
   - Enter the desired speed in RPM using the keypad.
   - Press "#" to confirm the speed setting.
   - The OLED display will update with the new speed.

4. **Adjust the acceleration:**
   - Press the "C" button on the keypad.
   - Enter the desired acceleration in RPM using the keypad.
   - Press "#" to confirm the acceleration setting.
   - The OLED display will update with the new acceleration.

5. **Set the run time:**
   - Press the "B" button once for minutes or twice for seconds.
   - Enter the desired run time using the keypad.
   - Press "#" to confirm the run time setting.
   - The OLED display will update with the new run time.

6. **Set the rotation direction:**
   - Press the "D" button on the keypad.
   - The OLED display will update with the current rotation direction.

7. **Start the motor:**
   - Press "#" to confirm the settings and start the motor.
   - The motor will start rotating at the specified speed and acceleration.
   - The OLED display will show the current speed and remaining run time.

8. **Stop the motor:**
   - Press "*" on the keypad to stop the motor.
   - The motor will stop rotating.
   - The OLED

 display will update with the stopped state.

9. **Reset the settings:**
   - Press "*" on the keypad to reset the settings to their defaults (100 RPM speed, 20 RPM/s acceleration, 60 seconds run time, clockwise rotation).
   - The OLED display will update with the default settings.

10. **Adjust and repeat:** Adjust the settings using the keypad as needed and repeat steps 7 to 9.


> **Notes:** 
1. The 12V 20A PSU should provide sufficient power for the NEMA 17 motor and the Arduino Uno. Ensure proper wiring, connect the ground of the PSU to the Arduino Uno, and use adequate heat sinks for the TB6600 driver if required. Take necessary safety measures while working with high currents.

2. you can use the system for shorter durations such as 10, 20, or 30 seconds. The run time setting allows you to specify the duration for which the motor will run 

   To set a shorter run time:

   - Press the "B" button on the keypad.
   - Enter the desired run time using the keypad (e.g., 10 for 10 seconds).
   - Press "#" to confirm the run time setting.

   The motor will then run for the specified duration and stop automatically. The OLED display will show the remaining run time during the operation.

   You can repeat the same steps to set different run times for shorter durations as needed.
