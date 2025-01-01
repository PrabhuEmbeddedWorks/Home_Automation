#include <LiquidCrystal.h> // Include the LiquidCrystal library for LCD

// Initialize the LCD with pin configuration: rs, en, d4, d5, d6, d7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);  

const int LED = 6;      // Define pin for LED
const int IN1 = 5;      // Define pin for motor control IN1
const int IN2 = 4;      // Define pin for motor control IN2
const int PIR = 3;      // Define pin for PIR motion sensor
const int lm35 = A0;    // Define pin for temperature sensor (LM35)
int entry = 0;          // Initialize entry state variable

void setup() {
    Serial.begin(9600); // Start serial communication at 9600 baud rate
    pinMode(LED, OUTPUT); // Set LED pin as OUTPUT
    pinMode(IN1, OUTPUT); // Set IN1 pin as OUTPUT for motor control
    pinMode(IN2, OUTPUT); // Set IN2 pin as OUTPUT for motor control
    pinMode(PIR, INPUT);  // Set PIR pin as INPUT to read motion
    lcd.begin(16, 2);     // Initialize LCD with 16 columns and 2 rows
    lcd.clear();          // Clear the LCD display
}

void loop() {
    float temp = 0;       // Variable to store temperature
    int ppl = 0;          // Variable to store PIR sensor reading

    // Read temperature from LM35 sensor
    temp = analogRead(lm35);  
    temp = temp / 2.62; // Convert analog value to temperature (Celsius)

    lcd.setCursor(0, 0); // Set cursor to the first row
    lcd.print("temp=");   // Display "temp=" on the LCD
    lcd.print(temp);      // Print the temperature value

    // Check if temperature is above or equal to 20°C and entry is 1
    if ((temp >= 20) && (entry == 1)) {
        digitalWrite(IN1, HIGH); // Activate motor IN1
        digitalWrite(IN2, LOW);  // Deactivate motor IN2
    } else {
        digitalWrite(IN1, LOW);  // Deactivate motor IN1
        digitalWrite(IN2, LOW);  // Deactivate motor IN2
    }

    // Read the state of the PIR sensor
    ppl = digitalRead(PIR); 

    // If motion is detected by PIR sensor
    if (ppl == HIGH) {
        digitalWrite(LED, HIGH); // Turn ON the LED
        lcd.setCursor(0, 1);     // Set cursor to the second row
        lcd.print("Light on ");   // Display "Light on" on the LCD
        entry = 1;               // Set entry to 1
        delay(1500);             // Wait for 1.5 seconds
    } else {
        digitalWrite(LED, LOW);  // Turn OFF the LED
        lcd.setCursor(0, 1);     // Set cursor to the second row
        lcd.print("Light off ");  // Display "Light off" on the LCD
        entry = 0;               // Set entry to 0
        delay(1500);             // Wait for 1.5 seconds
    }

    delay(1000); // Wait for 1 second before the next loop iteration
}
