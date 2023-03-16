// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        15 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 14 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
int val = 0;
int i = 1;
// Variables will change:
//int ledState = HIGH;         // the current state of the output pin
//int buttonState;             // the current reading from the input pin
//int lastButtonState = LOW;   // the previous reading from the input pin
//
//// the following variables are unsigned longs because the time, measured in
//// milliseconds, will quickly become a bigger number than can be stored in an int.
//unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
//unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT);
  Serial.begin(9600);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  //potValue = analogRead(4); // อ่านค่า Analog จากขา 4
  Serial.print("I : ");
  Serial.println(i);
  Serial.print("Push : ");
  int reading = digitalRead(5);
  delay(400);
//  if (reading != lastButtonState) {
//    // reset the debouncing timer
//    lastDebounceTime = millis();
//  }
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    // whatever the reading is at, it's been there for longer than the debounce
//    // delay, so take it as the actual current state:
//
//    // if the button state has changed:
//    if (reading != buttonState) {
//      buttonState = reading;
//
//      // only toggle the LED if the new button state is HIGH
//      if (buttonState == HIGH) {
//        ledState = !ledState;
//      }
//    }
//  }
  if (reading == 0) {
    i++;
    if (i == 8) {
      i = 0;
    }
  }
  Serial.println(reading);
  if (i == 1) {
    int val = map(analogRead(4), 30, 4095, 1000, 1);
    Serial.print("analog : ");
    Serial.println(analogRead(4));
    Serial.print("Val : ");
    Serial.println(val);
    if (analogRead(4) > 30) {
      pixels.setPixelColor(1, pixels.Color(150, 0, 0));
      pixels.setPixelColor(2, pixels.Color(76, 0, 150));
      pixels.setPixelColor(3, pixels.Color(0, 0, 150));
      pixels.setPixelColor(4, pixels.Color(0, 150, 0));
      pixels.setPixelColor(5, pixels.Color(150, 76, 0));
      pixels.setPixelColor(6, pixels.Color(150, 150, 0));
      pixels.setPixelColor(8, pixels.Color(150, 0, 0));
      pixels.setPixelColor(9, pixels.Color(76, 0, 150));
      pixels.setPixelColor(10, pixels.Color(0, 0, 150));
      pixels.setPixelColor(11, pixels.Color(0, 150, 0));
      pixels.setPixelColor(12, pixels.Color(150, 76, 0));
      pixels.setPixelColor(13, pixels.Color(150, 150, 0));
      pixels.show();
      delay(val);
      for (int a = 0; a < 15; a++) {
        pixels.setPixelColor(a, pixels.Color(0, 0, 0));
      }
      pixels.show();
      delay(val);
    } else {
      pixels.setPixelColor(1, pixels.Color(150, 0, 0));
      pixels.setPixelColor(2, pixels.Color(76, 0, 150));
      pixels.setPixelColor(3, pixels.Color(0, 0, 150));
      pixels.setPixelColor(4, pixels.Color(0, 150, 0));
      pixels.setPixelColor(5, pixels.Color(150, 76, 0));
      pixels.setPixelColor(6, pixels.Color(150, 150, 0));
      pixels.setPixelColor(8, pixels.Color(150, 0, 0));
      pixels.setPixelColor(9, pixels.Color(76, 0, 150));
      pixels.setPixelColor(10, pixels.Color(0, 0, 150));
      pixels.setPixelColor(11, pixels.Color(0, 150, 0));
      pixels.setPixelColor(12, pixels.Color(150, 76, 0));
      pixels.setPixelColor(13, pixels.Color(150, 150, 0));
      pixels.show();
    }
  } else if (i == 2) {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(150, 0, 0));
    }
    pixels.show();
  } else if (i == 3) {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(76, 0, 150));
    }
    pixels.show();
  } else if (i == 4) {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(0, 0, 150));
    }
    pixels.show();
  } else if (i == 5) {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(0, 150, 0));
    }
    pixels.show();
  } else if (i == 6) {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(150, 76, 0));
    }
    pixels.show();
  } else if (i == 7) {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(150, 150, 0));
    }
    pixels.show();
  } else {
    for (int a = 0; a < 15; a++) {
      pixels.setPixelColor(a, pixels.Color(0, 0, 0));
    }
    pixels.show();
  }
  //  pixels.clear(); // Set all pixel colors to 'off'
  //  // The first NeoPixel in a strand is #0, second is 1, all the way up
  //  // to the count of pixels minus one.
  //  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
  //
  //    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
  //    // Here we're using a moderately bright green color:
  //    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
  //
  //    pixels.show();   // Send the updated pixel colors to the hardware.
  //
  //    delay(DELAYVAL); // Pause before next pass through loop
}
