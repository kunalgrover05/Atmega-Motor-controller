#include<SPI.h>

 // Comm guide 
#define LEN_1_MIN 1
#define HELLO 1
#define RESET 2
#define MODE 3
#define DIRECTION 4
#define MOTOR_PWM 5
#define LEN_1_MAX 5
#define LEN_2_MIN 6
#define VOLTAGE_ACTUAL 6
#define VOLTAGE_DEMAND 8
#define LEN_2_MAX 9
#define LEN_4_MIN 10
#define ENCODER_SCALE 10
#define DELAY_PID 14
#define POSITION_ACTUAL 22
#define POSITION_DEMAND 26
#define VELOCITY_ACTUAL 30
#define VELOCITY_DEMAND 34
#define KP 38
#define KI 42
#define KD 46
#define LEN_4_MAX 50
 
#define POSITION_MODE 1              //position control using encoder
#define VELOCITY_MODE 2              //Velocity control using encoder
#define DIAGNOSTIC_MODE 3            //give it a PWM to go at
#define VOLTAGE_MODE 4               //Velocity control using voltage

void setup() {
  Serial.begin(115200);
  while(Serial.available())
    Serial.read();
  SPI.begin ();
  digitalWrite(SS,LOW);
  Serial.println("Initialized");
}

void loop() {
}
