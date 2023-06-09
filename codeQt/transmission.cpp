#include "transmission.h"

transmission::transmission()
{

}

int transmission::qinit(std::string str)
{
    // /dev/ttyACM0
    fd = open(str.c_str(), O_RDWR);
    if(fd < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        status = -1;
        return -1;
    }
    else
    {
        fdstatus = 1;
    }

    termios tty;

    if(tcgetattr(fd, &tty) == 0)
    {
        tty.c_cflag &= ~PARENB;     // Clear parity bit, disabling parity (most common)
        tty.c_cflag &= ~CSTOPB;     // Clear stop field, only one stop bit used in communication (most common)
        tty.c_cflag &= ~CSIZE;      // Clear all bits that set the data size
        tty.c_cflag |= CS8;         // 8 bits per byte (most common)
        tty.c_cflag &= ~CRTSCTS;    // Disable RTS/CTS hardware flow control (most common)
        tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

        tty.c_lflag &= ~ICANON;
        tty.c_lflag &= ~ECHO;                   // Disable echo
        tty.c_lflag &= ~ECHOE;                  // Disable erasure
        tty.c_lflag &= ~ECHONL;                 // Disable new-line echo
        tty.c_lflag &= ~ISIG;                   // Disable interpretation of INTR, QUIT and SUSP

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

        tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
        tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

        tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
        tty.c_cc[VMIN] = 0;

        cfsetispeed(&tty, B1152000);    //set input speed
        cfsetospeed(&tty, B1152000);    //set output speed

        if (tcsetattr(fd, TCSANOW, &tty) != 0)
        {
            printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            status = -1;
            return -1;

        }
        else
        {
            status = 1;
        }
    }
    else
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        status = -1;
        return -1;
    }

    return 1;
}

int transmission::qwrite(char * arr)
{
    return write(fd, arr, sizeof(arr));
}

int transmission::qread(char * arr)
{
    return read(fd, arr, sizeof(arr));
}

