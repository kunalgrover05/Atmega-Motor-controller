
const int code_type(int c){
 return (c&0x80)?1:0 ;
}

const int write_code(int c){
  return (c | 0x80);
}

const int read_code(int c){
  return (c & 0x7F);
}

int get_len(int c){
 if(c >= LEN_1_MIN && c <= LEN_1_MAX)  return 1;
 else if(c >= LEN_2_MIN && c <= LEN_2_MAX)  return 2;
 if(c >= LEN_4_MIN && c <= LEN_4_MAX)  return 4;
}

int voltage_to_pwm(int a) {
  float b = ( (a *255.0) / MAX_VOLTAGE_BATTERY  );
  if( b > 255)
    b = 255;
  else if( b < -255)
    b = -255;
  return (int)b;
}

int pwm_to_voltage(int a) {
  return ( a / 1023.0 * MAX_VOLTAGE_BATTERY );
}

int adc_to_voltage(int a) {
  return ( (float(a) * MAX_VOLTAGE_BATTERY) / Vref );
}

int adc_to_pwm(int a) {
  return  ((float)a / Vref * 1023.0 )  ;
}
