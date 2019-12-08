#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
String myWord;
// 0  1  2  3  4  5  6  7
// a  b  c  d  e  f  g  h
// 16 15 14 13 12 11 10 9  8
// i  j  k  l  m  n  o  p  q
// 17 18 19 20 21 22 23 25 25
// r  s  t  u  v  w  x  y  z

int getCharacterIndex(char& character) {
  Serial.print("char inside function:");
  Serial.println(character);
  int charIndex;
  switch (character) {
    case 'A': charIndex = 0; break;
    case 'B': charIndex = 1; break;
    case 'C': charIndex = 2; break;
    case 'D': charIndex = 3; break;
    case 'E': charIndex = 4; break;
    case 'F': charIndex = 5; break;
    case 'G': charIndex = 6; break;
    case 'H': charIndex = 7; break;

    case 'I': charIndex = 16; break;
    case 'J': charIndex = 15; break;
    case 'K': charIndex = 14; break;
    case 'L': charIndex = 13; break;
    case 'M': charIndex = 12; break;
    case 'N': charIndex = 11; break;
    case 'O': charIndex = 10; break;
    case 'P': charIndex = 9; break;
    case 'Q': charIndex = 8; break;

    case 'R': charIndex = 17; break;
    case 'S': charIndex = 18; break;
    case 'T': charIndex = 19; break;
    case 'U': charIndex = 20; break;
    case 'V': charIndex = 21; break;
    case 'W': charIndex = 22; break;
    case 'X': charIndex = 23; break;
    case 'Y': charIndex = 24; break;
    case 'Z': charIndex = 25; break;
  }
  Serial.print("charIndex:");
  Serial.println(charIndex);
  return charIndex;
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  myWord = "HELLO WORLD";
}
int index;
int timeToWait = 1000;
void loop() {
  Serial.println("loop started");
  Serial.println("word: " + myWord);
  for (char& c : myWord) {
    Serial.print("char:");
    Serial.println(c);
    
    index = getCharacterIndex(c);
    Serial.print("index:");
    Serial.println(index);
    
    blinkLed(index);
    Serial.println("-- the end --");
  }
  delay(3000);
}

void blinkLed(int index){
  leds[index] = CRGB::White;
    FastLED.show();
    delay(timeToWait);
    leds[index] = CRGB::Black;
    FastLED.show();
    delay(timeToWait);
}
