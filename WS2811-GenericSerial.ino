/*
Vixen to Arduino based Generic Serial interface for Addressable Pixels, prefix = 'x'
*/

#include <FastLED.h>
#define NUM_LEDS 100
#define DATA_PIN 9
#define LED_TYPE WS2811
#define COLOR_ORDER RGB

CRGB leds[NUM_LEDS];

bool reset = false;
int currentMillis = millis();
int lastMillis = currentMillis;

void setup() {
  delay(3000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  delay(500);
  error();

  delay(500);
  Serial.begin(230400);

  waitSerial();
}

void loop() {
  int cnt;

  while(true){
    cnt = 0;

    while(!Serial.available()){}

    if(Serial.read() != 'x'){
      continue;
    }
    
    while(true){
      if(cnt >= NUM_LEDS){
        break;
      }

      while(!Serial.available()){}
      leds[cnt].r = Serial.read();

      while(!Serial.available()){}
      leds[cnt].g = Serial.read();

      while(!Serial.available()){}
      leds[cnt].b = Serial.read();

      cnt++;
    }
    FastLED.show();
  }
}

void error(){
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  FastLED.show();
}
void waiting(){
  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  FastLED.show();
}
void warning(){
  leds[0] = CRGB::Orange;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  FastLED.show();
}
void success(){
  leds[0] = CRGB::Green;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  FastLED.show();
}
void clear(){
  FastLED.clear();
  FastLED.show();
}
void waitSerial(){
  while(true){
    if(Serial.available()){
      success();
      delay(500);
      break;
    }
    else{
      waiting();
      delay(500);
    }
  }
  clear();
}