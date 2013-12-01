/*
PARTS :
//  Comm layer with *MASTER* 
  -> Set parameters mode  ( Manual config of various variables )
//  -> Get Sensor data always in BG
  -> Enable controlling of motor with MC
  -> Apply PID control loop (depending on control word by MASTER)
  -> Throughout, all commands from MASTER are heard. (for quick stop, etc.)


Com with master :
if 0x80 (BIT7) is high => WRITE
if 0x80 (BIT7) is low => READ
Other 6 bits are for information
Each comm WILL output 1 byte minimum. More will depend on dictionary

Encoder values will be queried at all times

On comm with MASTER, values will be set/got





ARRAY uint32_t -- 256
# define POSITION 4
read => ARRAY[CODE_RECD] = 

ARRAY[POSITION]


DIRECTION :  2-Forward
             1-Backward





*/


