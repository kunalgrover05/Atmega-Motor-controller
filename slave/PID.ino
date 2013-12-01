void pid_set_vel() {
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-1000,1000);
  pid.SetSampleTime(50);
  pid.SetTunings(consKp,consKi,consKd);
}      

void pid_set_voltage() {
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-1000,1000);
  pid.SetSampleTime(50);
  pid.SetTunings(consKp,consKi,consKd);
}      


void velocity_pid() {
  pid.Compute();
  if(Output+set_pwm > 1023) {
    set_pwm=1023;
  } 
  else if(set_pwm+Output < MIN_PWM)  {
    set_pwm = MIN_PWM;
  }
  else { 
    set_pwm += Output;
  }
  motor(GETVAR_1(DIRECTION), set_pwm);
}

void voltage_pid() {
  pid.Compute();
  if(Output+set_pwm > 1023) {
    set_pwm=1023;
  } 
  else if(set_pwm+Output < MIN_PWM)  {
    set_pwm = MIN_PWM;
  }
  else { 
    set_pwm += Output;
  }
  motor(GETVAR_1(DIRECTION), set_pwm);
}
