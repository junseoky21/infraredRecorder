/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: junse
 *
 * Created on April 20, 2019, 11:59 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

void printTime(struct timeval *tv, int curState) {
    if (curState == HIGH) {
        printf("HIGH at %ld\n", tv->tv_usec);
    } else {
        printf("LOW at %ld\n", tv->tv_usec);
    }
}
#define RECV_PIN 21
/*
 * 
 */
int main(int argc, char** argv) {
    wiringPiSetup () ;
    pinMode (RECV_PIN, INPUT);
    pullUpDnControl (RECV_PIN, PUD_OFF) ;
    int curState = LOW; // Pulled down as default
    long timeEN = 0; 
    struct timeval curTime;
    for (;;)
    {
        gettimeofday(&curTime, NULL);
//        printf("curTime %ld\n", curTime.tv_usec);
        if ((digitalRead(RECV_PIN) == HIGH) && ((timeEN - curTime.tv_sec) < 0)) {
            timeEN = curTime.tv_sec + 1; // listen for 1 sec 
            curState = HIGH;
            printf("**********************START RECORDING!!**********************\n");
            printTime(&curTime, curState);
        } else if (timeEN - curTime.tv_sec > 0) {
            int pinState = digitalRead(RECV_PIN);
            if (curState != pinState) {
                printTime(&curTime, pinState);
                curState = pinState;
            }
        }
//        delay (1) ;
    }

    return (EXIT_SUCCESS);
}

