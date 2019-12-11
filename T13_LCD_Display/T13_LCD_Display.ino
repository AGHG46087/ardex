
/*
  LiquidCrystal Library - Hello World
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hola Mapi Mia!");
}
int column = 16;
char* text = "Te amo";

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  delay(1000);

  //column = (column < 0 ) ? 17 : column-1;
  lcd.setCursor(column, 1);
  lcd.scrollDisplayLeft();
  lcd.print(text);
}
