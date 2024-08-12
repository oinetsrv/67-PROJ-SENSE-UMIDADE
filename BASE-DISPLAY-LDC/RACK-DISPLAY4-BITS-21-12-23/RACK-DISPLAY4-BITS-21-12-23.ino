// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pushButton      = 8;
int buttonState     = 0;
int lastButtonState = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor   (0, 0);
  lcd.print       ("0");

  pinMode(pushButton, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(pushButton);
  // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
            lcd.setCursor   (0, 0);
            //lcd.print       (buttonState);
            lastButtonState = buttonState;
            delay(1000);
 
    }
     
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 5000);
}
