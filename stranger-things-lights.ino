#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 3
#define TIME_TO_WAIT_MS 1000

String MySentence = "FELIZ NATAL";

// Define the array of leds
CRGB leds[NUM_LEDS];
// 0  1  2  3  4  5  6  7
// a  b  c  d  e  f  g  h
// 16 15 14 13 12 11 10 9  8
// i  j  k  l  m  n  o  p  q
// 17 18 19 20 21 22 23 25 25
// r  s  t  u  v  w  x  y  z

int getCharacterIndex(char& character) {
  switch (character) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    case 'E': return 4;
    case 'F': return 5;
    case 'G': return 6;
    case 'H': return 7;

    case 'I': return 16;
    case 'J': return 15;
    case 'K': return 14;
    case 'L': return 13;
    case 'M': return 12;
    case 'N': return 11;
    case 'O': return 10;
    case 'P': return 9;
    case 'Q': return 8;

    case 'R': return 17;
    case 'S': return 18;
    case 'T': return 19;
    case 'U': return 20;
    case 'V': return 21;
    case 'W': return 22;
    case 'X': return 23;
    case 'Y': return 24;
    case 'Z': return 25;

    case ' ': return -1;
  }
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

int index;
void loop() {
  Serial.println("loop started");

  Serial.print("sentence: ");
  Serial.println(MySentence);
  for (char& c : MySentence) {
    Serial.print("char:");
    Serial.println(c);

    index = getCharacterIndex(c);
    Serial.print("index:");
    Serial.println(index);

    blinkLed(index);
  }
  Serial.println("-- the end --");
  Serial.println();
  delay(3000);
}

void blinkLed(int index) {
  if (index == -1) { // space
    delay(TIME_TO_WAIT_MS);
    return;
  }

  leds[index] = CRGB::White;
  FastLED.show();
  delay(TIME_TO_WAIT_MS);

  leds[index] = CRGB::Black;
  FastLED.show();
  delay(TIME_TO_WAIT_MS);
}
