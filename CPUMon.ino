// This uses the Ethercard library and Neopixels to display the LED status, you can change values in the setup //
#include <Adafruit_NeoPixel.h>
#define PIN A0
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

#include <UIPEthernet.h>
EthernetClient client;
int cpu = 0;
int debug = 0;

void setup() {
  strip.begin();
  strip.setBrightness(30); 
  light(strip.Color(255, 255, 255), 0, 8);
  strip.show();
  
  if (debug = 1) {
    Serial.begin(9600);
    Serial.println("init");
  }

  uint8_t mac[6] = {0x74,0x69,0x69,0x2D,0x30,0x31};
  Ethernet.begin(mac);

  if (debug = 1) {
    Serial.println(Ethernet.localIP());
  }

  if (client.connect({ 192, 168, 1, 10 }, 8888)) {
      Serial.println("1");
  } else {
      Serial.println("0");
      light(strip.Color(0, 0, 255), 0, 8);
      strip.show();
  }
  
}

void loop() {
        char buffer[] = {' ',' ',' '};
        while (!client.available());
            client.readBytesUntil('n', buffer, 3);
            int incomingValue = atoi(buffer);
            Serial.println(incomingValue);
            int led = 0;
        
        if (incomingValue >= 11) { led = 1; clearLED(led); }
        if (incomingValue >= 22) { led = 2; clearLED(led); }
        if (incomingValue >= 33) { led = 3; clearLED(led); }
        if (incomingValue >= 45) { led = 4; clearLED(led); }
        if (incomingValue >= 56) { led = 5; clearLED(led); }
        if (incomingValue >= 67) { led = 6; clearLED(led); }
        if (incomingValue >= 78) { led = 7; clearLED(led); }
        if (incomingValue >= 90) { led = 8; clearLED(led); }

        if (incomingValue <= 33) { light(strip.Color(0, 255, 0), 50, led); } //green
        else if (incomingValue <= 66) { light(strip.Color(255, 255, 0), 50, led); } //yellow
        else { light(strip.Color(255, 0, 0), 50, led); } //red

      if (!client.connected()) {
        //Serial.println("OK");
        client.connect({ 192, 168, 1, 10 }, 8888);
        delay(200);
      }
}

void light(uint32_t c, uint8_t wait, uint8_t t) {
  for(uint16_t i=0; i<t; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void clearLED(uint32_t c) {
  if (c == 1) {
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0);
    strip.setPixelColor(2, 0, 0, 0);
  }
  if (c == 2) {
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0);
  }
  if (c == 3) {
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0);
  }
  if (c == 4) {
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
  }
  if (c == 5) {
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
  }
  if (c == 6) {
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
  }
  if (c == 7) {
    strip.setPixelColor(7, 0, 0, 0);
  }
  strip.show();
}
