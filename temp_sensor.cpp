#include <Adafruit_LiquidCrystal.h>

// Initialize the LCD. '32' is the I2C address for the Tinkercad simulation.
Adafruit_LiquidCrystal lcd(32);

int sensorPin = A0;  // TMP36 connected to Analog Pin 0
int threshold = 30;  // Alert threshold in Celsius

void setup() {
  lcd.begin(16, 2);      // Initialize a 16x2 LCD
  lcd.setBacklight(1);   // Turn on the display backlight
  Serial.begin(9600);    // Start serial communication for background debugging
}

void loop() {
  // Read the raw analog sensor value (0-1023)
  int sensorVal = analogRead(sensorPin);
  
  // Convert ADC reading to voltage, then calculate Celsius
  // TMP36 spec: 10mV per degree, with a 500mV offset
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;
  
  // Clear the screen for the new data frame
  lcd.clear();
  // --- ROW 1: Display Live Temperature ---
  lcd.setCursor(0, 0); // Start at Column 0, Row 0
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  // --- ROW 2: Display Status/Alert Logic ---
  lcd.setCursor(0, 1); // Start at Column 0, Row 1  
  // Conditional logic to check against threshold
  if (temperature > threshold) {
    lcd.print("!! ALERT HIGH !!"); // Triggered when too hot
  } else {
    lcd.print("Status: Normal");   // Triggered when safe
  }
  // Delay 1 second before the next loop to stabilize the display
  delay(1000); 
}
