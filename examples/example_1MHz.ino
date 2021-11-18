#include "DS1077.h"


DS1077 DS1077(133333000UL,5,3);

void setup() {


  DS1077.reset(); //resets MUX and DIV word to defaults (MUX = 0x1800, DIV = 0x0000)
  toggle_OUT0(OFF); //turn off OUT_0 
  toggle_OUT1(ON); //turn on OUT_1 
  DS1077.set_freq(133,1); //sets freq to around 1MHz
  
  
  
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
