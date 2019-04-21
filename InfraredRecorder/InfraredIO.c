/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "InfraredIO.h"

#define MAX_SIG_BUF_LEN 512

void printTime(struct timeval *tv, int curState) {
    if (curState == HIGH) {
        printf("HIGH at %ld\n", tv->tv_usec);
    } else {
        printf("LOW at %ld\n", tv->tv_usec);
    }
}
void writeTime(FILE fp, int curState, long uS) {
    
}
/**
 * 
 * @param pinnum wiringPI pinnumber. Check to pin using `gpio readall`
 * @param timeoutuS timeout value in microseconds. Timeout value should not exceed 100 seconds.
 * @param opt options available in InfraredReceiveOption at the header file
 * @return 
 */
int InfraredReceive(int pinnum, int timeoutuS, int opt, FILE* fp=NULL){
    wiringPiSetup ();
    pinMode (RECV_PIN, INPUT);
    pullUpDnControl (RECV_PIN, PUD_OFF) ;
    int curState = LOW; // Pulled down as default
    long timeEN = 0; 
    struct timeval curTime;
    int captured = 0, signalTraverse;
    long signal[MAX_SIG_BUF_LEN];
    
    // Listening for signal
    for (;;)
    {
        gettimeofday(&curTime, NULL);
        if (timeEN - curTime.tv_sec < 0) {
            if (captured) {
                break;
            }
            if (digitalRead(RECV_PIN) == HIGH) {
                timeEN = curTime.tv_sec + 1; // listen for 1 sec.
                                             // Hopefully we don't get in to the cornercase where uS is really close to the sec
                curState = HIGH;
                printf("**********************START RECORDING!!**********************\n");
                captured = 1;   // To ensure we capture one time
                signalTraverse = 0;
                signal[signalTraverse++] = curTime.tv_usec;
            }
        } else {
            int pinState = digitalRead(RECV_PIN);
            if (curState != pinState) {
                curState = pinState;
                if (signalTraverse >= MAX_SIG_BUF_LEN - 1)
                {
                    return -1;
                }
                signal[signalTraverse++] = curTime.tv_usec;
            }
        }
    }
    // Option Processing
    for (int i = 0; i < signalTraverse; i++) {
        if (opt & InfraredReceiveOption.Print) {
            printf("%ld,%ld\n", (!(fp % 2) ? "HIGH":"LOW"), signal[i]);
        }
        if (opt & InfraredReceiveOption.File) {
            if (fp == NULL) {
                return -1;
            }
            char lineBuf[64];
            int charnum = sprintf(lineBuf, "%ld,%ld\n", (!(fp % 2) ? "HIGH":"LOW"), signal[i]);
            fwrite(lineBuf, sizeof(char), charnum, fp);
        }
    }
    return 0;   // return on success
}