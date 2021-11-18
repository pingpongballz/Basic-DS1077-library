#ifndef __DS1077__
#define __DS1077__

#include "Arduino.h"


#define DIV 0x01
#define MUX 0x02
#define BUS 0x0D
#define WRITE_E2 0x3F

#define ON 1 
#define OFF 0


class DS1077
{
  public:
    DS1077(uint32_t base_freq, int CTRL0, int CTRL1);
    unsigned long set_freq(word N_scale,word P1_scale);
    unsigned long set_OUT0_div(byte P0_scale);
    void reset();
    unsigned long set_closest_freq(unsigned long freq);
    void toggle_OUT0(bool condition);
    void toggle_OUT1(bool condition);
    //void power_down();

    
    
  private:
    void write_to(int data_bytes, byte reg_addr, byte data[]);
    void set_N_divider(word divider);
    void set_P1_divider(word divider);
    unsigned long _base_freq;
    int _CTRL0, _CTRL1;
    
   
    
};

#endif
