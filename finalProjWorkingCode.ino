// include libraries
#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

// define vars
RTC_DS1307 rtc;
//                  pixels, PIN
Adafruit_NeoPixel strip(60, 12);
Adafruit_NeoPixel strip2(60, 11);
Adafruit_NeoPixel strip3(120, 13);

int seconds = 0;
int minutes = 0;
int hours = 0; 
int hoursAM = 0; 
int hoursPM = 0;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

void setup () {
  Serial.begin(9600);
  // led strip 1 
  strip.begin();
  strip.setBrightness(80);
  strip.clear();
  strip.show();
  //led strip 2 
  strip2.begin();
  strip2.setBrightness(80);
  strip2.clear();
  strip2.show();
  // led strip 3 
  strip3.begin();
  strip3.setBrightness(80);
  strip3.clear();
  strip3.show();

  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop () {
  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);

   //                         leds / seconds 
   seconds = (now.second()) * 82 / 60;
   //Serial.println(seconds);

   minutes = (now.minute());
   //Serial.println(minutes);
                   
  hours = (now.hour());
  //Serial.println(now.hour());


// this value assumes there are 120 LEDs for the hour part
// that means each hour is 10 LEDs. To account for the minutes that 
// move the hour hand, I'm adding the minute value/the minute total LEDs * 10 (or 1 hour)
// this gets me the hour plus the ratio of the minutes accounted for 
  hoursAM = (hours * 3.667 + ((minutes/60)*3.667));
  //Serial.println(hoursAM);

  hoursPM = ((hours - 12) * 3.667 + ((minutes/60)*3.667));
  //Serial.println(hoursPM);

// call the functions
setSeconds();
setMinutes();
hourSwitch();
}

// function that works off of seconds 
void setSeconds () {
  ////////////////////// AM ////////////////////////////
  DateTime now = rtc.now();
  if (now.hour() < 12 || now.hour() == 24 ){
 
 //             80 LEDs
  if (seconds < 80){
    // for loop to light up all the lights up until the time
   for (int i = 0; i <= (seconds); i++){
    strip3.setPixelColor (i, strip3.Color(255, 160, 30));
    strip3.show();
}
  }
  // clears the strip 
  else if (seconds  >= 80){
    strip3.clear();
    strip3.show();
    }
}

////////////////////// PM ////////////////////////////
  if (now.hour() >= 12 && now.hour() < 24){
  if (seconds < 80){
   for (int i = 0; i <= (seconds) ; i++){
    strip3.setPixelColor (i, strip3.Color(128,0,128));
    strip3.show();
}
  }
  else if (seconds  >= 80){
    strip3.clear();
    strip3.show();
    }
}
}

// function for the minutes 
void setMinutes () {
  ////////////////////// AM ////////////////////////////
  DateTime now = rtc.now();
if (now.hour() < 12 || now.hour() == 24 ){
// 46 LEDs
if (minutes < 59){
for (int i = 0; i <= minutes; i++){
  strip.setPixelColor (i, strip.Color(219,150,15));
    strip.show();
}
}
  else if (minutes >= 59){
    strip.clear();
    strip.show();
    }
}

////////////////////// PM ////////////////////////////
else if (now.hour() >= 12 && now.hour() < 24) {
if (minutes < 59){
for (int i = 0; i <= minutes; i++){
  strip.setPixelColor (i, strip.Color(173,216,230));
    strip.show();
}
}
  else if (minutes >= 59){
    strip.clear();
    strip.show();
    }
}
}

// hours function for the AMs
void setHoursAM () {
// num of LEDs
if (hoursAM < 44){
for (int i = 0; i <= hoursAM; i++){
  strip2.setPixelColor (i, strip3.Color(255,0,0));
    strip2.show();
}
}
  else if (hoursAM >= 44){
    strip2.clear();
    strip2.show();
    }
}

// hours function for the PMs
void setHoursPM () {
if (hoursPM < 44){
for (int i = 0; i <= hoursPM; i++){
  strip2.setPixelColor (i, strip3.Color(0,0,255));
    strip2.show();
}
}
  else if (hoursPM >= 44){
    strip2.clear();
    strip2.show();
    }
}

// switches between AM and PM 
void hourSwitch () {
if (hours < 12 || hours == 24 ){
  setHoursAM();
}
else if (hours >= 12 && hours < 24) {
  setHoursPM();
}
}

