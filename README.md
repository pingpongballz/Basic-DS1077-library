# Basic DS1077 library for arduino
A very basic DS1077 library for arduino. More features to be added in time to come.

# Installation

Copy the contents of the **DS1077** folder and place it in your arduino libraries folder. 
Usually you can find the folder in **C:\Users\USERNAME\Documents\Arduino\libraries**.

# Hooking up:

You can connect the DS1077 in a barebone configuration, as such:
![image](https://user-images.githubusercontent.com/74599812/142455865-af7c5d78-7176-41c6-a208-eb04f610d46c.png)
Credit goes to EasyEDA for their online EDA software: https://easyeda.com/

If desired, a buffer can be placed as such too, using an opamp:
![image](https://user-images.githubusercontent.com/74599812/142459135-0a200b42-09af-4623-80d2-44bae9a1f3ff.png)
V- can be shorted to ground as Vout(Low) = 0.4V and Vout(High) = 2.4V, from the DS1077 datasheet.

Or a dedicated buffer, such as the BUF602:
![image](https://user-images.githubusercontent.com/74599812/142460170-b5dce3a5-3bba-495a-81bd-4ac7c1698a97.png)



# Programming:

First initialise the DS1077 module: ```DS1077(Base frequency, pin connected to CTRL_0, pin connected to CTRL1)```

So for example, if you are  using the 133.333MHz version of the module, and have CTRL_0 connected to pin 6, and CTRL_1 connected to pin 7:
```c++
#include "DS1077.h"

DS1077 DS1077(133333000UL, 6, 7);
```

6 functions are available for use:
```c++
1. unsigned long set_freq(word N_scale,word P1_scale);
2. void reset();
3. unsigned long set_closest_freq(unsigned long freq);
4. unsigned long set_OUT0_div(byte P0_scale);
5. void toggle_OUT0(bool condition);
6. void toggle_OUT1(bool condition);

```
1. As the name suggests, **```set_freq(word N_scale,word P1_scale)```** has 2 inputs, the N divider(1-1025) and the P1 divider(ONLY 1,2,4,8).

   The N divider's range is actually from 2-1025. When you set the N  divider as 1, the second bit of the second data byte of the MUX register is turned on,
   bypassing the N divider. 
  
   **This sets the clock on OUT_1 to ``` f = (base frequency)/(P1_scale*N_scale)```**
  
   **Returns the set frequency on OUT_1.**
  
2. **```reset()```** sets the DIV and MUX registers to **DIV = 0x1800 and MUX = 0x0000**. 

   Resetting the WC register hasn't been done yet.


3. **```set_closest_freq(unsigned long freq)```** has 1 input, the desired freq. 

   The program will try to attain the closest frequency permissible by the frequency dividers
   (Note: I'm actually not sure if the current implementation is the best).
  
   **This sets the clock on OUT_1 to the closest desire frequency**
  
   **Returns the closest frequency attained onto OUT_1.**
  
4. **```unsigned long set_OUT0_div(byte P0_scale)```** has 1 input, P0_scale(ONLY 1,2,4,8). 

   **This sets the clock on OUT_0 to ``` f = (base frequency)/(P0_scale)```**
   
   **Returns the set frequency on OUT_0.**
   
5. **```void toggle_OUT0(bool condition)```** toggles the OUT_0 pin off(False) or on(True). 
 
   **```toggle_OUT0(ON)``` or ```toggle_OUT0(true)``` turns OUT_0 on.**
   
   **```toggle_OUT0(OFF)``` or ```toggle_OUT0(false)``` turns OUT_0 off.**
   
6. **```void toggle_OUT1(bool condition)```** toggles the OUT_1 pin off(False) or on(True). 
 
   **```toggle_OUT1(ON)``` or ```toggle_OUT1(true)``` turns OUT_1 on.**
   
   **```toggle_OUT1(OFF)``` or ```toggle_OUT1(false)``` turns OUT_1 off.**
  
  
This library was made as a very quick excercise in arduino porgramming, and the implementation is definitely not the fastest. Apologies! :sweat_smile:

Further reading and reference: DS1077 datasheet, Maxim Integrated. https://datasheets.maximintegrated.com/en/ds/DS1077.pdf
