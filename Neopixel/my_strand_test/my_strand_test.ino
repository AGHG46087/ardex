// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

// include the library code:
#include <LiquidCrystal.h>

#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
// #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

#define DELAYTIME 10
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 120
// BRIGHTNESS to about 1/5 (max = 255)
#define TWENTY_PERCENT_BRIGHT 50
#define BRIGHTNESS_INCREMENT 50

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------


int brightness = TWENTY_PERCENT_BRIGHT;
char buffer[50];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup My Strand Test"); 
  lcd.begin(16, 2);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(brightness); // Set BRIGHTNESS to about 1/5 (max = 255)
}
void red_to_green() {
  int redValue = 255; // choose a value between 1 and 255 to change the color.
  int greenValue = 0;
  int blueValue = 0;

  for (int i = 0; i < 255; i += 1)  { // fades out red bring green full when i=255
    redValue -= 1;
    greenValue += 1;
    strip.fill(strip.Color(redValue,   greenValue,   blueValue), 0, LED_COUNT);
    strip.show();
    delay(DELAYTIME);
  }
}

void green_to_blue() {
  int redValue = 0;
  int greenValue = 255;
  int blueValue = 0;

  for (int i = 0; i < 255; i += 1) { // fades out green bring blue full when i=255
    greenValue -= 1;
    blueValue += 1;
    strip.fill(strip.Color(redValue,   greenValue,   blueValue), 0, LED_COUNT);
    strip.show(); 
    delay(DELAYTIME);
  }
}

void blue_to_red() {
  int redValue = 0;
  int greenValue = 0;
  int blueValue = 255;

  for (int i = 0; i < 255; i += 1) { // fades out blue bring red full when i=255
    // The following code has been rearranged to match the other two similar sections
    blueValue -= 1;
    redValue += 1;
    strip.fill(strip.Color(redValue,   greenValue,   blueValue), 0, LED_COUNT);
    strip.show(); 
    delay(DELAYTIME);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
void writeText(const char* text) {
  sprintf(buffer,"Brightness=%d", brightness);
  Serial.print(text); Serial.print( " : " );  Serial.println(buffer);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
  lcd.setCursor(0, 1);
  lcd.print(buffer);
}
void loop() {
  // put your main code here, to run repeatedly:
  writeText("Color Rotators");
  red_to_green();
  green_to_blue();
  blue_to_red();
  
  writeText("Color wipes");
  colorWipe(strip.Color(  255,   0, 0), 10); // Red
  colorWipe(strip.Color(  0,   255, 0), 10); // Green
  colorWipe(strip.Color(  0,   0, 255), 10); // Blue
  colorWipe(strip.Color(  0,   0, 0), 10); // off

  writeText("Theater Color Chase");
  theaterChaseRainbow(50);

  brightness += BRIGHTNESS_INCREMENT;
  if (brightness >= 255 ) {
    brightness = TWENTY_PERCENT_BRIGHT;
  }
  strip.setBrightness(brightness);

}
