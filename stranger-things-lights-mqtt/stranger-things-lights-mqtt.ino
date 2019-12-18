#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define NUM_LEDS 26
#define DATA_PIN 3
#define TIME_TO_WAIT_MS 800
#define A_CHARCODE 65

#define NETWORK_SSID "RESIDENCIAL2"
#define NETWORK_PASSWORD "FLORIPA17"
#define MQTT_SERVER "tailor.cloudmqtt.com"
#define MQTT_SERVER_PORT 13415
#define MQTT_USER "oqkathdv"
#define MQTT_PASS "LVN8i1VW8xVk"

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

String MySentence = "FELIZ NATAL";

// Define the array of leds
CRGB leds[NUM_LEDS];
// 0  1  2  3  4  5  6  7
// a  b  c  d  e  f  g  h

// 16 15 14 13 12 11 10 9  8
// i  j  k  l  m  n  o  p  q

// 17 18 19 20 21 22 23 25 25
// r  s  t  u  v  w  x  y  z

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String fraseRecebida;
  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    fraseRecebida += c;
    Serial.print(c);
  }
  Serial.println("-----");
  Serial.print("Frase recebida: ");
  Serial.println(fraseRecebida);
  printMessage(fraseRecebida);
  
  Serial.println();
  if ((char)payload[0] == 'L') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(NETWORK_SSID);

  WiFi.begin(NETWORK_SSID, NETWORK_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
      Serial.println("connected");
      //client.publish("outTopic", "hello world");
      client.subscribe("b805ce7a-88fe-4a3d-991b-6ca8c45d08b6");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

int getCharacterIndex(char& character) {

  // return ((int)character) - A_CHARCODE;

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
  pinMode(BUILTIN_LED, OUTPUT);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_SERVER_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  /*
    int index;
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
  */
}

void printMessage(String message) {
  for (char& c : message) {
    Serial.print("char:");
    Serial.println(c);

    int index = getCharacterIndex(c);
    Serial.print("index:");
    Serial.println(index);

    blinkLed(index);
  }
}

void blinkLed(int charIndex) {
  if (charIndex == -1) { // space
    delay(TIME_TO_WAIT_MS);
    return;
  }

  leds[charIndex] = CRGB::White;
  FastLED.show();
  delay(TIME_TO_WAIT_MS);

  leds[charIndex] = CRGB::Black;
  FastLED.show();
  delay(TIME_TO_WAIT_MS);
}
