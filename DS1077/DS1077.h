#ifndef __DS1077__
#define __DS1077__

#include "Arduino.h"



#define address 0xB0 >> 1 
#define DIV 0x01
#define MUX 0x02
#define BUS 0x0D
#define WRITE_E2 0x3F


class DS1077
{
  public:
    DS1077 (unsigned long base_freq);
    //DS1077(uint32_t base_freq, int CTRL0, int CTRL1);
    unsigned long set_freq(word N_scale,word P1_scale);
    void reset();
    unsigned long set_closest_freq(unsigned long freq);
    //void kill_CTRL0();
    //void kill_CTRL1();
    //void power_down();
    //void enable_CTRL0();
    //void enable_CTRL1();
    
    
  private:
    void write_to(int data_bytes, byte reg_addr, byte data[]);
    void set_N_divider(word divider);
    void set_P1_divider(word divider);
    //int _CTRL0, _CTRL1;
    unsigned long _base_freq;
    
};

#endif
