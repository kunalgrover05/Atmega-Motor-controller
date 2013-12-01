/****************************************
Define communication protocol using 


How to use:
SPI 
  Set required SS pin to low
  Functions:
    set(COMMAND,VALUE);
    int32_t var = get(COMMAND);
    
    
  eg:
  VELOCITY MODE : Set using Set(MODE,VELOCITY_MODE)
  Set velocity using Set(VELOCITY_DEMAND,/reqd vel/)
  reqd_vel = velocity*100 (integer only)
  See current velocity using Get(VELOCITY_ACTUAL)

  Directions:
  1,2
  
I2C
  Functions:
    set(COMMAND,VALUE,SLAVE_ADD);
    int32_t var = get(COMMAND,SLAVE_ADD);
    
    


***************************************/
