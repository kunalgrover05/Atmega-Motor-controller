// Contains all functions that handle SPI communication
// i.e. Communication with MASTER

void spi_init() {
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // now turn on interrupts
  SPI.attachInterrupt();
  // SPCR |= _BV(SPIE); // atmega way to attach interrupt
  
}

ISR (SPI_STC_vect) {                                  // interrupt for SPI
  spi_recd = SPDR;                                    // take input -- this is supposed to be a Object
  if(!(spi_len_left>0 && spi_type)) {
    spi_type = code_type(spi_recd);                       // Check whether code is read or write or check if some data has to come in
    spi_recd = read_code(spi_recd);                   //Converting it into a code ignoring case when recieving data
  }        
  
  switch(spi_type) {
    case 0:  
      if(spi_recd != 0) {   //New Command is recieved 
        spi_position = spi_recd;
        spi_len_left = get_len(spi_recd) - 1;
        SPDR = Vars[spi_position++];
      } else if(spi_recd == 0 && spi_len_left) {              //Returning output to master based on command
        SPDR = Vars[spi_position++];
        spi_len_left--;
      } 
        /*    else if(spi_len_left==0 || (spi_recd+last_code==0)) { //Communication went wrong tell master
         SPDR=0;            
      }         */
    break; 
             
    case 1:  
      if(spi_recd != 0 && spi_len_left == 0) {                // getting a new command
        spi_position = spi_recd;
        spi_len_left = get_len(spi_recd);
      } else if(spi_len_left) {                       //Reject everything else until completely read the value
        Vars[spi_position++] = spi_recd ;
        spi_len_left--;                 
        SPDR = 1;                                     //Tell master that data is recieved
      }
  /*else if(spi_len_left==0 || (spi_recd+last_code==0))  //Communication went wrong ask master to reset once
          {
         SPDR=0;           
         }*/
    break;
  }
}
