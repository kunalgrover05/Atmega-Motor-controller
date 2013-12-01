int get_len(int c){
 if(c >= LEN_1_MIN && c <= LEN_1_MAX)  return 1;
 else if(c >= LEN_2_MIN && c <= LEN_2_MAX)  return 2;
 if(c >= LEN_4_MIN && c <= LEN_4_MAX)  return 4;
}


const int write_code(int c){
  return (c | 0x80);
}

const int read_code(int c){
  return (c & 0x7F);
}

