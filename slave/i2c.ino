#ifdef I2CCOMM
void i2c_init() {
   Wire.begin (MY_ADD);
   Wire.onReceive (receiveEvent);
   Wire.onRequest (requestEvent);
}


void receiveEvent(int sz) {
  if( flag_i2c == 0) {
    command = Wire.read();
    flag_i2c = 1;
  }
    
  else {
    byte i2c_position = read_code(command);
    for (int i=0; i<sz; i++) {
        uint8_t c = Wire.read();
        Vars[i2c_position+i] = c;
    }
    flag_i2c = 0;  
  }
}

void requestEvent() {
  uint8_t buff,buff2[2],buff4[4];
  int len_buff = get_len(command);
  byte i2c_position = read_code(command);
  switch(len_buff) {
    case 1:  buff = Vars[i2c_position];
             Wire.write(buff);
             break;
    case 2:  buff2[0] = Vars[i2c_position];
             buff2[1] = Vars[i2c_position+1];
             Wire.write(buff2,2);   
             break;
    case 4:  buff4[0] = Vars[i2c_position];
             buff4[1] = Vars[i2c_position+1];
             buff4[2] = Vars[i2c_position+2];
             buff4[3] = Vars[i2c_position+3];
             Wire.write(buff4,4);   
             break;
  }
}
#endif
