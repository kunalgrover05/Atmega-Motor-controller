void i2c_init() {
  Wire.begin();
}

int set(int c, uint32_t v, uint8_t slave) {
  Wire.beginTransmission (slave);
  Wire.write(write_code(c));
  Wire.endTransmission();
  Wire.beginTransmission(slave);
 
             
  uint8_t buff,buff2[2],buff4[4];
  int len_buff = get_len(c);
  switch(len_buff) {
    case 1:  buff = v;
             Wire.write(buff);   
             break;
    case 2:  buff2[0] = v;
             buff2[1] = v>>8;
             Wire.write(buff2,2);   
             break;
    case 4:  buff4[0] = v;
             buff4[1] = v>>8;
             buff4[2] = v>>16;
             buff4[3] = v>>24;
             Wire.write(buff4,4);   
             break;
  }
  if (Wire.endTransmission() == 0) {
    return 1;
  }
 return -1  ; 
}


int32_t get(int c,uint8_t slave) {
  Wire.beginTransmission(slave);
  Wire.write(read_code(c));
  Wire.endTransmission();
  Wire.beginTransmission(slave);
  uint8_t len_buff = get_len(c); 
  int32_t buff;
  if (Wire.requestFrom ((uint8_t)slave, len_buff) == len_buff) {
    buff = (uint8_t)Wire.read();
    if( len_buff > 1 ) { // 2 bytes
      buff += ((uint16_t)Wire.read() << 8);
    }
    if( len_buff > 2) { // 4 bytes
      buff += ((uint32_t)Wire.read() << 16);  
      buff += ((int32_t)Wire.read() << 24);  
     }
   }
  if (Wire.endTransmission() == 0) {
    return buff;
  }
  return -1;
}
