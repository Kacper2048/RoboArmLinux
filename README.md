# RoboArmLinux

### Description

Portfolio and educational project to gain many skills like 3d modeling, writing embedded software or basic of electronics. The main goal of that was creating simple and cheap multipurpose arm for use in many other projects. It use Qt control panel and open-access libraries from linux.

 Here is a link to get a model of arm: https://cults3d.com/en/3d-model/gadget/robo-arm-servo
 Here is a kink to the presentation video: 
   
   
### Requires

 - Linux with desktop environment
 - Qt creator (I used 7.0.2)
 - Pico SDK (default configuration)
 - (for Qt) Your system has to have a global acces to consecutive libraries: stdio.h, string.h, iostream ,
 fcntl.h , errno.h, termios.h, unistd.h, cstdint, stdlib.h
 - (for Pico) Your system has to have a global acces to consecutive libraries: stdlib.h, pico/stdlib.h, stdio.h
 - super user permissions
 - Cmake and make(makefile) buildsystem
  
  
### SetUp

 (PC) Control panel run with Qt creator. It required only default configured Qt.
 
 (Pico-software) In order to save a time I took ready example hello_world from pico and I remodel everything what I needed.
 In order to compile the program you have to go to specified directory and use command `make -j4` and move ready *.uf2 file to rp pico.

 (Pico-hardware) Connect wires according to instruction `instruction.png`. By default 6 gpio pins are used to control the servos. 
 
 
### Warnings

 Raspbery pi pico retrive and send data by usb port, so you have to turn off uart option in your Cmakefile.txt.
 Qt control panel will send data to ttyACM0 by default, the path have to be changed manualy in program in Qt.


### Limits
 Project uses weak servos so in showed model the power of arm is not super enought, so keep in mind it is not good option for real industry usage.
