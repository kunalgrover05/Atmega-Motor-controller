byte transfer_data(byte c)
{
  byte a = SPI.transfer(c);
  delayMicroseconds (20);
  return a; 
} 

void set(int c, uint32_t v,int pin) {
  int len = get_len(c);
  transfer_data(write_code(c));
  transfer_data(v); // 1 byte
  if( c > LEN_2_MIN ) { // 2 bytes
    transfer_data(v >> 8);  
  }
  if( c > LEN_4_MIN) { // 4 bytes
    transfer_data(v >> 16);
    transfer_data(v >> 24);
  }
}

int32_t get(int c) {
  int len = get_len(c);
  uint32_t v= 0;
  transfer_data(c);
  v = (uint8_t)transfer_data(0); // 1 byte
  if( len > 1 ) { // 2 bytes
    v += ((uint16_t)transfer_data(0) << 8);
  }
  if( len > 2) { // 4 bytes
    v += ((uint32_t)transfer_data(0) << 16);  
    v += ((int32_t)transfer_data(0) << 24);  
  }
  return v;
}

