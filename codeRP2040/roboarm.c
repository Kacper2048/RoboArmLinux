
/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "servo.h"

void init_gpio();
void gpio_update(char *, size_t);

void get_frame(char *, char *);
void print_data(char *, size_t);


int main() 
{
    stdio_init_all();
    init_gpio();

    char str[8];
    char frame[6];

    while (true)
    {
        get_frame(str, frame);
        print_data(frame, sizeof(frame)); 
        printf("\n");
        gpio_update(frame, sizeof(frame));
        
    }
    close_servo();
    return 0;
}

void gpio_update(char * frame, size_t size)
{
    for(int i=10;i<16;i++)
    {
        write_servo(i, (int)frame[i-10]);
    }
    sleep_ms(20);
}

void init_gpio()
{
    for(int i=10;i<16;i++)
    {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
        gpio_put(i, 0); //all pins are turned off
    }
}

void get_frame(char * str, char * converted_frame)
{
    int len = 0;
    int x = 0;
    int q = 0; //position of 255 value

        if( scanf("%8s",str) > 0)
        {
            //find 255 value and 0
            while((int)str[q] != 255)
            {
                q++;
            }

            //sorting
            for(int i=5;i>=0;i--)
            {
                q--;
                if(q<0)
                {
                    q = 7;
                }
                converted_frame[i] = str[q];
            }
        }
}

void print_data(char * frame, size_t size)
{
    int x = 0;
    for(int i = 0; i < size; i++)
    {
        x = (int)frame[i];
        //printf("%c",str[i]);
        printf("%i ",x);
    }
    printf("\n");

}