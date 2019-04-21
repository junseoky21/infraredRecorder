/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "InfraredIO.h"


void printTime(struct timeval *tv, int curState) {
    if (curState == HIGH) {
        printf("HIGH at %ld\n", tv->tv_usec);
    } else {
        printf("LOW at %ld\n", tv->tv_usec);
    }
}
void writeTime(FILE fp, int curState, long uS) {
    
}

void InfraredReceive(){
    wiringPiSetup () ;
    pinMode (RECV_PIN, INPUT);
    pullUpDnControl (RECV_PIN, PUD_OFF) ;
    int curState = LOW; // Pulled down as default
    long timeEN = 0; 
    struct timeval curTime;
    int captured = 0;
    for (;;)
    {
        gettimeofday(&curTime, NULL);
//        printf("curTime %ld\n", curTime.tv_usec);
        if (timeEN - curTime.tv_sec < 0) {
            if (captured) {
                break;
            }
            if (digitalRead(RECV_PIN) == HIGH) {
                timeEN = curTime.tv_sec + 1; // listen for 1 sec.
                                             // Hopefully we don't get in to the cornercase where uS is really close to the sec
                curState = HIGH;
                printf("**********************START RECORDING!!**********************\n");
                printTime(&curTime, curState);
                captured = 1;   // To ensure we capture one time
            }
        } else {
            int pinState = digitalRead(RECV_PIN);
            if (curState != pinState) {
                printTime(&curTime, pinState);
                curState = pinState;
            }
        }
    }
}