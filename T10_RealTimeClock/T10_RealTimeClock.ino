
#include <Wire.h>
#include <DS3231.h>

DS3231 clock;
RTCDateTime dt;

void setup()
{
  Serial.begin(9600);

  // Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();

  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);

  // Set from UNIX timestamp
  // clock.setDateTime(1397408400);

  // Manual (YYYY, MM, DD, HH, II, SS
  //clock.setDateTime(2016, 12, 9, 11, 46, 00);
}

void loop()
{
  dt = clock.getDateTime();
  char sz[255];

  Serial.print("Long number format:          ");
  clock.dateFormat("d-m-Y H:i:s", dt, sz);
  Serial.println(sz); 

  Serial.print("Long format with month name: ");
  clock.dateFormat("d F Y H:i:s",  dt, sz);
  Serial.println(sz); 

  Serial.print("Short format with 12h mode: ");
  clock.dateFormat("jS M y, h:ia", dt, sz);
  Serial.println(sz);

  Serial.print("Today is:                    ");
  clock.dateFormat("l, z", dt, sz);
  Serial.print(sz);
  Serial.println(" days of the year.");

  Serial.print("Actual month has:            ");
  clock.dateFormat("t", dt, sz);
  Serial.print(sz);
  Serial.println(" days.");

  Serial.print("Unixtime:                    ");
  clock.dateFormat("U", dt, sz);
  Serial.println(sz);

  Serial.println();
  Serial.println("Individual values Here");
  Serial.print(dt.year); Serial.print("-");
  Serial.print(dt.month); Serial.print("-");
  Serial.print(dt.day); Serial.print("-");
  Serial.print(dt.hour); Serial.print("-");
  Serial.print(dt.minute); Serial.print("-");
  Serial.print(dt.second); Serial.println("");
  Serial.println();
  

  delay(1000);
}
