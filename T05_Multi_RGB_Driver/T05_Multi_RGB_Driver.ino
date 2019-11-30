
int tDelay = 200;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

byte leds = 0;
bool up = true;

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  delay(tDelay);
}

void loop() 
{
  leds = 0; 
  updateShiftRegister();
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
  for (int i = 0; up && i < 8; i++)
  {
    bitClear(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
  for (int i = 8; !up && i > -1; i--)
  {
    bitClear(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }

  up = !up;
  
}
