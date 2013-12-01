

/*****************************************************************************************************************************************************************************************/
/*
Selecting communication protocol
#define SPICOMM 1
#define I2CCOMM 1


Communication protocol

Query for data-- 
7 bits represent code
Left most bit 0  Read
Left most bit 1  Write


Master
wcode()-Return code write
rcode()-Return code read

Protocol
Read data: Send opcode followed by no of zeroes reqd for reading data
Write data: Send opcode followed by no of 0x80|data



*/

/********************************************************************************************************************************************************************************************/
#define SPICOMM 1               ///////Define SPI comm protocol


// Includes
#include <SPI.h>
#include <TimerOne.h>
#include <PID_v1.h>
#include<WSWire.h>

// Constants
#define DEBUG Serial
#define MSP_LAUNCHPAD Serial

#define MSP_ERROR 0x8FFF

  // Motor Control Pins :
#define MOTOR_PIN_1 7
#define MOTOR_PIN_2 8
#define MOTOR_PIN_PWM 9


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


// Macro functions
#define SETVAR_4(pos, val)\
  Vars[pos] = val;\
  Vars[pos+1] = (val >> 8);\
  Vars[pos+2] = ((uint32_t)val >> 16);\
  Vars[pos+3] = ((uint32_t)val >> 24)
  
#define SETVAR_2(pos, val)\
  Vars[pos] = val;\
  Vars[pos+1] = (val >> 8)
  
#define SETVAR_1(pos, val)\
  Vars[pos] = val

#define GETVAR_4(pos) (Vars[pos] + (Vars[pos+1]<<8) + ((uint32_t)Vars[pos+2]<<16) + ((uint32_t)Vars[pos+3]<<24))
#define GETVAR_2(pos) (Vars[pos] + (Vars[pos+1]<<8))
#define GETVAR_1(pos) Vars[pos]
  
#define motor(motor_direc,motor_pwm) digitalWrite(MOTOR_PIN_1, motor_direc/2);\
                   digitalWrite(MOTOR_PIN_2, motor_direc%2);\
                   Vars[MOTOR_PWM] = char(motor_pwm/4);\
                   Timer1.pwm(MOTOR_PIN_PWM, motor_pwm)
                
// The control objects 
uint8_t Vars[60]={0};


#ifdef SPICOMM                        ////Variables reqd for SPI
byte spi_recd = 0;
boolean spi_type = 1;
uint8_t spi_position = 0, spi_len_left = 0;
int temp_var = 0;
#endif

#ifdef I2CCOMM                         ////Variables reqd for I2c
byte MY_ADD = 2;
byte command;
int flag_i2c = 0;
#endif

// For Sensors:
#define MSP_ERROR 0x8FFF
#define VOLTAGE_SENSOR_1 A5
#define VOLTAGE_SENSOR_2 A4
int32_t motor_encoder;
int32_t motor_encoder_diff = 0;
float set_pwm = 0.0;
float Vref;

// For Control Loop:
double Input, Output, Setpoint, consKp, consKi, consKd, Setpoint_last;
PID pid(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

unsigned long time_last,time_taken,t_start;
boolean vel_flag=0;
uint8_t Dir_last=1;

// SETUP
void setup() {
  Serial.begin(115200);     // debugging & msp
  while(Serial.available()) // flush serial
      Serial.read();
  
  Timer1.initialize(80);
  // Motor Pins init
  pinMode(6,INPUT);
  pinMode(MOTOR_PIN_1, OUTPUT);
  pinMode(MOTOR_PIN_2, OUTPUT);
  //Init voltage sense pins across motor
  pinMode(VOLTAGE_SENSOR_1, INPUT);
  pinMode(VOLTAGE_SENSOR_2, INPUT);
  pinMode(2,INPUT);
  msp_reset();
  
  #ifdef I2CCOMM
  i2c_init();  
  #endif 
  
  pid_set_vel();
  
  // Objects default values
  Vars[HELLO]= 'H' ;
  Vars[RESET] = 'R' ;
  Vars[DIRECTION] = 1;
 
  SETVAR_4(DELAY_PID, 50);
  SETVAR_4(ENCODER_SCALE, (5376));
  SETVAR_4(KP,400);
  SETVAR_4(KI,50);
  SETVAR_4(KD,20); 
}



// LOOP
void loop() {  
calc_vel();
  if(GETVAR_1(RESET)) { // Software reset
    msp_reset();
    calc_vel();
    SETVAR_1(RESET, 0);
  }
  
  consKp=GETVAR_4(KP)/1000.0;
  consKi=GETVAR_4(KI)/1000.0;
  consKd=GETVAR_4(KD)/1000.0;
  pid.SetTunings(consKp,consKi,consKd);
  switch(GETVAR_1(MODE)) {
    case VELOCITY_MODE:
      Setpoint = GETVAR_4(VELOCITY_DEMAND)/100.0;
      if(Setpoint != Setpoint_last) {
        pid.Reset();
        Setpoint_last = Setpoint;
      }
      
      if(Setpoint == 0) {
         brake();
      }
      else if(millis() - t_start > GETVAR_4(DELAY_PID)) {
          Input = GETVAR_4(VELOCITY_ACTUAL)/100.0;
          velocity_pid();
          t_start = millis();
      }
      break;
    case DIAGNOSTIC_MODE:
      set_pwm = GETVAR_4(VELOCITY_DEMAND);
      motor(GETVAR_1(DIRECTION), set_pwm);
      break;
 }   
}
