# TPS-Harware

This repository contains the code of TPS's picking face.

To develop the solution pick to light we are using an ESP8266 NodeMCU and flashing it with ESP8266_RTOS_SDK version MASTER (LTS Version is 3.2). It can be found at https://github.com/espressif/ESP8266_RTOS_SDK

### Get Started

1. Get the ESP8266_RTOS_SDK and follow the Espressif tutorial to setup the environment. Make sure that the hello-world example works.
2. Clone this repository. If you are using Windows, then it is important to clone it in the same disk that the SDK is.
3. Compile it using the command "make flash monitor".

### Remarks
1. The makefile used to compile is the one in SDK package, so it is important to follow its structure. All new files are inside the tps_hw/components and it must have the "include" folder with the .h files.
2. Every component folder must have the component.mk file
3. The file "debug.c" is not relevant. The app starts on tps_hw/main/xmain.c

### Have fun!
