To connect all the components together, follow these steps:

1. Connect the 12V power supply (PSU) to the TB6600 driver:
   - Connect the positive terminal of the PSU to the "+" terminal of the TB6600 driver.
   - Connect the negative terminal of the PSU to the "-" terminal of the TB6600 driver.

2. Connect the TB6600 driver to the NEMA 17 motor:
   - Connect the "A+" and "A-" terminals of the TB6600 driver to the corresponding wires of one coil of the NEMA 17 motor.
   - Connect the "B+" and "B-" terminals of the TB6600 driver to the corresponding wires of the other coil of the NEMA 17 motor.

3. Connect the Arduino Uno to the TB6600 driver and the keypad:
   - Connect the digital pin 2 of the Arduino Uno to the "PUL+" terminal of the TB6600 driver.
   - Connect the digital pin 3 of the Arduino Uno to the "DIR+" terminal of the TB6600 driver.
   - Connect the row pins (8, 9, 10, 11) of the Arduino Uno to the respective row pins of the keypad.
   - Connect the column pins (4, 5, 6, 7) of the Arduino Uno to the respective column pins of the keypad.

4. Connect the Arduino Uno to the I2C OLED display:
   - Connect the SDA pin of the Arduino Uno to the SDA pin of the OLED display.
   - Connect the SCL pin of the Arduino Uno to the SCL pin of the OLED display.
   - Connect the VCC pin of the OLED display to the 5V pin of the Arduino Uno.
   - Connect the GND pin of the OLED display to the GND pin of the Arduino Uno.

5. Connect the GND pin of the Arduino Uno to the GND terminal of the TB6600 driver and the GND terminal of the PSU.

6. Connect the 12V positive terminal of the PSU to the "+" terminal of the NEMA 17 motor.

Once all the connections are made, upload the Arduino sketch to the Arduino Uno using the Arduino IDE. After uploading, power on the PSU, and you should see the "Stirring System" message on the OLED display. You can then use the keypad to adjust the speed, acceleration, run time, and rotation direction of the motor.

Please note that when working with high-power motors, like the NEMA 17, make sure to use appropriate precautions to handle the power supply and ensure the connections are secure. Also, be cautious with the current limits of your power supply (20A) and the power requirements of your motor to avoid any issues.

To use the system, follow these steps with an example scenario:

1. Power on the system by connecting the 12V power supply.

2. The OLED display will show the "Stirring System" message along with the version number.

3. Adjusting the Speed:
   - Press the "A" button on the keypad.
   - Enter the desired speed in RPM using the keypad (e.g., 150).
   - Press "#" to confirm.
   - The OLED display will show the updated speed value.

4. Adjusting the Run Time:
   - Press the "B" button on the keypad.
   - Press "1" for minutes or "2" for seconds.
   - Enter the desired run time (e.g., 5 for 5 minutes or 30 for 30 seconds).
   - Press "#" to confirm.
   - The OLED display will show the updated run time value.

5. Adjusting the Acceleration:
   - Press the "C" button on the keypad.
   - Enter the desired acceleration value in RPM using the keypad (e.g., 25).
   - Press "#" to confirm.
   - The OLED display will show the updated acceleration value.

6. Adjusting the Rotation Direction:
   - Press the "D" button on the keypad.
   - Press "1" for clockwise or "2" for counterclockwise rotation.
   - The OLED display will show the selected rotation direction.

7. Start the Motor:
   - Press "#" to confirm the settings and start the motor.
   - The motor will start running at the specified speed and rotation direction.
   - The OLED display will show the current speed and the remaining run time.

8. Stop the Motor:
   - Press "*" to stop the motor at any time.
   - The motor will stop, and the OLED display will show the speed as 0.

9. Reset the Settings:
   - Press "*" to reset the settings to their defaults (100 RPM speed, 20 RPM acceleration, 60 seconds run time, clockwise rotation).
   - The OLED display will show the default settings.

Remember to thoroughly test and validate the system before integrating it into your project to ensure it meets your specific requirements and functions reliably.
