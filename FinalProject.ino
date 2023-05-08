#include "FastLED.h"

// Connect the port of the stepper motor driver
int outPorts[] = {27, 26, 25, 33};
const int joyThreshold = 500;
// int joyX, joyY;
// int count = 0;

//defines pins numbers for distance sensor
const int trigPin = 15;
const int echoPin = 2;
//defines variables
long duration;
int distance;
uint8_t current_color_index = 0;

#define LED_PIN     17
#define NUM_LEDS    30
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

CRGB colors[] = {
  CRGB(0, 255, 0),      // Green
  CRGB(50, 205, 50),    // Light Green
  CRGB(150, 255, 0),    // Lime Green
  CRGB(255, 255, 0),    // Yellow
  CRGB(255, 140, 0),    // Dark Orange
  CRGB(255, 69, 0),     // Orange-Red
  CRGB(255, 0, 0)       // Red
};

void setup() {
  //distance sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication

  // set pins to output for stepper motor 
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }

  // for LED
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
}
void loop(){
   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  static uint32_t last_color_change_time = 0;

  // Check if it's time to change the color
  if (millis() - last_color_change_time >= 5000) {
    last_color_change_time = millis();

    if (distance<40){
      for (int i = 0; i < 3; i++) {
        // Rotate left 60 degrees
        move60Degrees(true, 3);
        delay(100);

        // Rotate right 60 degrees
        move60Degrees(false, 3);
        delay(100);
        current_color_index = 0;
      }
    }
    else{
      // Get the next color in the palette
      current_color_index++;
    }

    if (current_color_index >= 7) {
      // We've reached the end of the palette, so stop iterating
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      return;
    }

    // Set all the LEDs to the current color
    fill_solid(leds, NUM_LEDS, colors[current_color_index]);
    FastLED.show();

  }
}

//the motor turns precisely when the ms range is between 3 and 20
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms,3,20));        // Control the speed
  }
}

void moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port 
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) { // ring shift left
    out!=0x08? out=out<<1:out=0x01; 
  }
  else {      // ring shift right
    out!=0x01? out=out>>1:out=0x08; 
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }

}

void moveAround(bool dir, int turns, byte ms){ for(int i=0;i<turns;i++)
    moveSteps(dir,32*64,ms);
}

// want to move left and right for certian angel
// 32 * 64 is used to calculate the number of steps to rotate the stepper motor
// 200 steps to complete a full 360 rotation 
// Rotate the motor a certain angle at a certain speed
void moveAngle(bool dir, int angle, byte ms) {
  moveSteps(dir, (angle * 32 * 64 / 360), ms);
}

// Rotate the motor 60 degrees at a certain speed
void move60Degrees(bool dir, byte ms) {
  moveAngle(dir, 60, ms);
}

