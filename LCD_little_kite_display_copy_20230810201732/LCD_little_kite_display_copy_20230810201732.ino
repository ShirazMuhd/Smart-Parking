#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  analogWrite(6, 75);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Little kite");
  lcd.setCursor(0, 1);
  lcd.print("KKMHSS cheeckode");
}

void loop() {
}
