#include <Adafruit_NeoPixel.h>

#define PIN 6
#define N_PIXELS 60
#define MIC_PIN A5
#define PEAK_FALL 20
#define SPEED .20

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_HZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, PIN, NEO_GRB + NEO_KHZ800);



//fadeThickness = 0;  // CHANGE THICKNESS (0-10)

int vol = 0;
float total = 0;
int fadeCol = 0;
int val[25];
int volLast = 0;
int fadeAmt = 0;
int counter = 0;

int dotCount;
int peak;
float greenOffset = 30, blueOffset = 150;


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
 Serial.begin(57600); 
}

void loop() {
  fadeCol = 0;
  total = 0;
  int HEIGHT = N_PIXELS / 2;
  int i;

  if(HEIGHT > peak)     peak = HEIGHT; // Keep 'peak' dot at top
  
  for (i = 0; i < N_PIXELS; i++){
    counter = 0;
    do{
      vol = analogRead(MIC_PIN);
 
      counter = counter + 1;
      if (counter > 500){
        rainbowCycle(10);
        
      }
    }while (vol == 0);
    
    total = total + vol;
 
  }
  
  vol = abs((int)total % 256);
 Serial.println(vol);
  
  vol = map(vol,20,255,0,20);
  
  
  if (volLast > vol) {
    vol = volLast - 4;
  }
  
  volLast = vol;
  fadeAmt = 0;
   
// Serial.print(vol);
  for (i = 0; i<strip.numPixels()/2;i++){
    if (i < vol){ 
      strip.setPixelColor((i+strip.numPixels()/2), strip.Color(0,255,vol));
      strip.setPixelColor((strip.numPixels()/2-i), strip.Color(0,255,vol));
    }
    else if (i < (vol + 8)) {
      
      strip.setPixelColor((i+strip.numPixels()/2), strip.Color(255,vol,vol));
      strip.setPixelColor((strip.numPixels()/2-i), strip.Color(255,vol,vol));
    }
    else
    {
      strip.setPixelColor((i+strip.numPixels()/2), strip.Color(0,0,255));
      strip.setPixelColor((strip.numPixels()/2-i), strip.Color(0,0,255));
    }
  }
  greenOffset += SPEED;
  blueOffset += SPEED;
  if (greenOffset >= 255) greenOffset = 0;
  if (blueOffset >= 255) blueOffset = 0;
    
  if(peak > 0 && peak <= HEIGHT-1) {
      strip.setPixelColor(peak,Wheel(map(vol,0,HEIGHT-1,(int)greenOffset, (int)blueOffset))); 
      strip.setPixelColor(HEIGHT-peak,Wheel(map(vol,0,HEIGHT+1,(int)greenOffset, (int)blueOffset)));
  }
  
  
  strip.show();

  if(++dotCount >= (PEAK_FALL)) { // fall rate

    if(peak > 0) peak--;
    dotCount = 0;
  }
  
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
    vol = analogRead(A0);
    if (vol> 10) {
       
      return;
       
    }
    
    
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
