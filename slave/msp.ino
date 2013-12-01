void msp_reset() {
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
    if(vel_flag==0) {                                       /// initial velocity=0
      SETVAR_4(VELOCITY_ACTUAL,0);
      vel_flag=1;
    }
    else {
      uint32_t mdiff = (600000)/(GETVAR_4(ENCODER_SCALE)) * (10000*abs(motor_encoder_diff))/(time_taken) ; 
      SETVAR_4(VELOCITY_ACTUAL, mdiff);
   }
}
