void set_velocity(int x) {
  if( x > 1023) {
     set_pwm=1023;
  } 
  else if(x < MIN_PWM)  {
     set_pwm = MIN_PWM;
  }
  else { 
     set_pwm = x;
  }
  motor(GETVAR_1(DIRECTION), set_pwm);
}

void brake() {
  set_pwm = 0;
  motor(0, 1023);
}
