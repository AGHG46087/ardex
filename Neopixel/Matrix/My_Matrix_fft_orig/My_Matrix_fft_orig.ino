/*
 * Multi alternating FFT
 * changes from a 6x10 graph to a 10x6 graph - bottom up and top down
 * FFT for LED sequrntial Strip, that could be used in horizonal or even vertical plane
 * by Hans-Jurgen Greiner
 * June 2019
 * 
 * based on FFT library and code from the Arduino forums
 * 
 */
#include <Adafruit_NeoPixel.h>
#include <fix_fft.h>

#define AUDIOPIN A5
#define N_PIXELS 60
#define LED_PIN  6
#define NUM_FREQS 13
#define HUE_STEP_INCREMENT 20
#define HUE_MAX 255

int HEIGHT = N_PIXELS/10;
int SEG = N_PIXELS/6;

// multiAlternatingFFT

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


int freqCounter = 0;
int rotateFreqs = NUM_FREQS;
char im[128], data[128]; // FFT requires an IM-aginary part and DATA part. 
char data_avgs[14];
int i=0,val;
bool reverse = false;

int offsetGreenHue = 30;
int offsetBlueHue = 150;


void setup() {
  
  strip.begin();
  strip.show(); // all pixels to 'off'
  Serial.begin(57600); // We all know the drill on the log stuff.
  
  delay(3000);   // SPOOL UP TIME 
}


void loop() {
  int ledIndex = 0;
  int lclVal = 0;
  bool reverse = true;

  // Rotate the frequency,  so it is a different position every so many cycles
  if ( ++freqCounter > 1024 ) { rotateFreqs--;  }
  // Every so many cycles, change the graph from a 6x10 to a 10x6 display
  if( freqCounter > 512 ) {
    HEIGHT = N_PIXELS/6;
    SEG = N_PIXELS/10;
    reverse = !reverse; // Lets look at a protothread to change this.
  }
  // Reset the graph to a 6x10, counters, and 
  if (rotateFreqs <= 0 ) {
    rotateFreqs = NUM_FREQS;
    freqCounter = 0;
    HEIGHT = N_PIXELS/10;
    SEG = N_PIXELS/6;
  }


  for (i=0; i < 128; i++){ 
    lclVal = 5000 * analogRead(AUDIOPIN); //shin: analog sig not detected from laptop audio out. scale to 5000  
    lclVal = abs((int)lclVal % 128);
    data[i] = lclVal;
    im[i] = 0;
  };

  /* 
   *  Frequency Sprectum this bad boy
   * 1. data array
   * 2. imaginary number array
   * 3. FFT requires samples in power of two, we have a 128 so in our case (2^7 == 128)
   * 4. Invert, We will always say false here
   */ 
  fix_fft(data,im,7,0);  

  for (i=0; i< 64;i++){                                      
    data[i] = sqrt(data[i] * data[i] + im[i] * im[i]);  // this gets the absolute value of the values in the array, so we're only dealing with positive numbers
  };     
  
  
  // average bars together
  for (i=0; i<14; i++) {
    data_avgs[i] = data[i*4] + data[i*4 + 1] + data[i*4 + 2] + data[i*4 + 3];   // average together 
    data_avgs[i] = map(data_avgs[i], 0, 30, 0, HEIGHT);                         // remap values
  }
  
  
  
  // set LoLShield
  offsetGreenHue += HUE_STEP_INCREMENT;
  offsetBlueHue += HUE_STEP_INCREMENT;
  if (offsetGreenHue >= HUE_MAX) offsetGreenHue = 0;
  if (offsetBlueHue >= HUE_MAX) offsetBlueHue = 0;

  for (int x=0; x < SEG; x++) {
    for (int y=0; y < HEIGHT; y++) {
      ledIndex = (x * HEIGHT) + y; 
      if(reverse) { 
        // Bump it a segment higher and take off the height
        ledIndex = ((x+1) * HEIGHT) - y; 
      }
//      if (y < data_avgs[13-x]) { // 13-x reverses the bars so low to high frequences are represented from left to right.
      if (y < data_avgs[rotateFreqs-x]) { // 13-x reverses the bars so low to high frequences are represented from left to right.
        strip.setPixelColor(ledIndex, Wheel(map(data_avgs[y],0,HEIGHT,(int)offsetGreenHue, (int)offsetBlueHue)));
      } else {
        strip.setPixelColor(ledIndex, strip.Color(0,0,0));
      }
    } 
  }

  strip.show();
}

// Input a value 0 to HUE_MAX, returns color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
