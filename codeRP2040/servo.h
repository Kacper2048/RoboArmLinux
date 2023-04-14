/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdlib.h>
#include "pico/stdlib.h"

int const min_time = 550; //550us
int const min_time_org = 1000; //550us
int const max_time = 2500;//2500us
int const max_time_org = 2000;//2500us
int const one_cycle_time = 20000; //20ms = 20000us
float const one_degree = (max_time - min_time)/180; //to make one degree we need 5.55us
float const one_degree_org = (max_time_org - min_time_org)/180; //to make one degree we need 5.55us

struct ServoPin
{
    int * pin_list;
    int * degs;
    int qsize;
};

struct ServoPin Servo;

void add_servo(int pin)
{
    Servo.qsize++;
    //copy from old
    int * temp_pin = NULL;
    int * temp_deg = NULL;
    
    temp_pin = calloc(Servo.qsize, sizeof(char));
    temp_deg = calloc(Servo.qsize, sizeof(char));

    for(int i=0;i<Servo.qsize-1;i++)
    {
        temp_pin[i] = Servo.pin_list[i];
        temp_deg[i] = Servo.degs[i];
    }

    temp_pin[Servo.qsize-1] = pin;
    temp_deg[Servo.qsize-1] = 0;

    free(Servo.pin_list);
    free(Servo.degs);

    Servo.pin_list = temp_pin;
    Servo.degs = temp_deg;
}

void close_servo()
{
    free(Servo.pin_list);
    free(Servo.degs);
}

void delete_servo(int pin)
{
    Servo.qsize--;
    //copy from old
    int * temp_pin = NULL;
    int * temp_deg = NULL;
    int x = 0;
    temp_pin = calloc(Servo.qsize, sizeof(char));
    temp_deg = calloc(Servo.qsize, sizeof(char));

    for(int i=0;i<Servo.qsize;i++)
    {
        if(Servo.pin_list[i] != pin)
        {
            temp_pin[i] = Servo.pin_list[i+x];
            temp_deg[i] = Servo.degs[i+x];
        }
        else
        {
            x++;
        }
        
    }

    free(Servo.pin_list);
    free(Servo.degs);

    Servo.pin_list = temp_pin;
    Servo.degs = temp_deg;
}

void write_servo(int pin, int degrees)
{
    int pwn_duty = 0; //us
    int rest = 0;

    pwn_duty = (degrees * one_degree) + min_time;
    rest  = one_cycle_time - pwn_duty;

    gpio_put(pin, 0);
    gpio_put(pin, 1);
    sleep_us(pwn_duty);
    gpio_put(pin, 0);
    //sleep_us(rest);
    //sleep_ms(5); //time to gain position by servo        
}

void write_servo_org(int pin, int degrees)
{
    int pwn_duty = 0; //us
    int rest = 0;

    pwn_duty = (degrees * one_degree_org) + min_time_org;
    rest  = one_cycle_time - pwn_duty;

    gpio_put(pin, 0);
    gpio_put(pin, 1);
    sleep_us(pwn_duty);
    gpio_put(pin, 0);
    sleep_us(rest);
    sleep_ms(5); //time to gain position by servo        
}

void update_servo()
{
    for(int i=0;i<Servo.qsize;i++)
    {
        write_servo(Servo.pin_list[i], Servo.degs[i]);
    }
    sleep_ms(20);
}