# Basic DS1077 library for arduino
A very basic DS1077 library for arduino. More features to be added in time to come.


How to use:

3 functions are available for use:
```c++
1. unsigned long set_freq(word N_scale,word P1_scale);
2. void reset();
3. unsigned long set_closest_freq(unsigned long freq);
```
1. As the name suggests, ```set_freq(word N_scale,word P1_scale)``` has 2 inputs, the N divider(1-1025) and the P1 divider(1,2,4,8).
  The N divider's range is actually from 2-1025. When you set the N  divider as 1, the second bit of the second data byte of the MUX register is turned on,
  bypassing the N divider.
  
2. ```reset()``` sets the DIV and MUX registers to DIV = 0x1800 and MUX = 0x0000. Resetting the WC register hasn't been done yet.


3. ```set_closest_freq(unsigned long freq)``` has 1 input, the desired freq. The program will try to attain the closest frequency permissible by the frequency dividers
  (Note: I'm actually not sure if the current implementation is the best)
  
  
This library was made as a very quick excercise in arduino porgramming, and the implementation is definitely not the fastest. Apologies! :sweat_smile:

Further reading and reference: DS1077 datasheet, Maxim Integrated. https://datasheets.maximintegrated.com/en/ds/DS1077.pdf
