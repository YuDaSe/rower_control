
#include "ZumoMotors.h"

#define LED_PIN 13

ZumoMotors motors;

struct tracks_t {
  int padding;
  int left;
  int right;
};

void initTracks(tracks_t* tracks, int leftSpeed, int rightSpeed);
void parseControl(String control, tracks_t* tracks);

tracks_t* tracks;
// left:3;right:5
String control;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  Serial.begin(9600);

  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available()) {
    control = Serial.readString();

    parseControl(control, tracks);

    motors.setLeftSpeed((tracks->left - 5) * 100);
    motors.setRightSpeed((tracks->right - 5) * 100);
  }
}

void initTracks(tracks_t* tracks, int leftSpeed, int rightSpeed) {
  tracks->left = leftSpeed;
  tracks->right = rightSpeed;
  
  return;  
}

void parseControl(String control, tracks_t* tracks) {
  String leftSpeed = control.substring(5, 6);
  String rightSpeed = control.substring(13, 14);
 
  initTracks(tracks, leftSpeed.toInt(), rightSpeed.toInt());

  return;
}
