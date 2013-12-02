// Gets sensor data
void msp_reset() {
  get_pos();
  motor_encoder = 0;
  motor_encoder_diff = 0;
}  
  
void get_pos() {
  while(MSP_LAUNCHPAD.available())
    MSP_LAUNCHPAD.read();
  MSP_LAUNCHPAD.write('S');
  while(!MSP_LAUNCHPAD.available());
  motor_encoder_diff = MSP_LAUNCHPAD.read();
  while(!MSP_LAUNCHPAD.available());
  motor_encoder_diff += (MSP_LAUNCHPAD.read()<<8);
  motor_encoder += motor_encoder_diff;
  SETVAR_4(POSITION_ACTUAL,motor_encoder);
}

void calc_vel() {  
    get_pos();
    time_taken = micros() - time_last;
    time_last = micros();
    if(vel_flag==0) {
      SETVAR_4(VELOCITY_ACTUAL,0);
      vel_flag=1;
    }
    else {
      int32_t velocity = (abs(motor_encoder_diff)*6000)/(GETVAR_4(ENCODER_SCALE))*(1000000/time_taken);
      // 100 for scale, 1000 for micro->milli, 1000 for milli->sec, 60 for sec->min
      SETVAR_4(VELOCITY_ACTUAL, (int32_t) velocity);
    }
}
