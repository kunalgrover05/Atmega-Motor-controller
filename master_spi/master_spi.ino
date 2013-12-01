
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
#define DELAY_PID 10
#define ENCODER_SCALE 14
#define POSITION_ACTUAL 28
#define POSITION_DEMAND 22
#define VELOCITY_ACTUAL 26
#define VELOCITY_DEMAND 30
#define KP 34
#define KI 38
#define KD 42
#define MAX_VOLTAGE_BATTERY 46
#define LEN_4_MAX 50
 
#define POSITION_MODE 1
#define VELOCITY_MODE 2
#define DIAGNOSTIC_MODE 3
#define MAX_RPM 300
#define MIN_PWM 0


  // Extra consts for spi comm           
 // ---- voltage -- set pwm.
 // ---- vel --does pid velocity -- NO ACC
 // ---- pos --does pid position -- NO ACC
 // ---- profile_vel --does pid vel + trajectory
 // ---- profile_pos --does pid pos + trajectory  -----------
 
     

void setup() {
  Serial.begin(115200);
  while(Serial.available())
    Serial.read();
  SPI.begin ();
  Serial.println("Initialized");
}

void loop() {
}
