#ifndef TRANSMISSION_H
#define TRANSMISSION_H

// C library headers
#include <stdio.h>
#include <string.h>
#include <iostream>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <cstdint>

#endif // TRANSMISSION_H

/*
struct termios
{
    tcflag_t c_iflag;       // input modes
    tcflag_t c_oflag;       // output modes
    tcflag_t c_cflag;       // control modes
    tcflag_t c_lflag;       // local modes
    cc_t c_cc[NCCS];        // special characters
    cc_t c_line;		    // line discipline
}
*/

class transmission
{

public:
    transmission();
    ~transmission(){ close(fd); };

    int qinit(std::string);
    int qwrite(char *); //pointer to char array and its size
    int qread(char *);
    short int returnStatus(){return status;};
    short int returnFdStatus(){return fdstatus;};

private:
    short int fd = 0;
    termios tty;
    short int status = 0;
    short int fdstatus = 0;
};
