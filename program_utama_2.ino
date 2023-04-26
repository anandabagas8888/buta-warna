#include <Wire.h>
//I2C Library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

// Define sensor pins
const int s2 = 4;
const int s3 = 5;
const int out = 6;
const int buzzer = 7;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("PENDETEKSI WARNA");
  
  // Initialize sensor pins
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); // Read red value
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); // Read blue value
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); // Read green value
  
  // Print RGB values to Serial
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" Green: ");
  Serial.print(green);
  Serial.print(" Blue: ");
  Serial.println(blue);

  // Detect color based on RGB values
  String color = "";
  if (red > 5 && green < 50 && blue < 30) {
    color = "Merah";
  } else if (red < 15 && green > 5 && blue < 15) {
    color = "Hijau";
  } else if (red < 35 && green < 25 && blue > 5) {
    color = "Biru";
  } else if (red > 9 && green < 27 && blue > 10) {
    color = "Pink";
  } else if (red > 6 && green > 9 && blue < 12) {
    color = "Kuning";
  } else if (red > 1000 && green > 500 && green < 1000 && blue < 500) {
    color = "Orange";
  }

  // Update LCD display
  lcd.setCursor(7, 1);
  lcd.print("     "); // Clear previous color value
  lcd.setCursor(7, 1);
  lcd.print(color); // Print detected color to LCD

  // Turn on buzzer for 1 second if color is detected
  if (color.length() > 0) {
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }

  delay(500); // Delay for stability
}
