/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InfraredIO.h
 * Author: junse
 *
 * Created on April 21, 2019, 1:18 PM
 */

#ifndef INFRAREDIO_H
#define INFRAREDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif

    

#define RECV_PIN 21 // Listen for changes at the pin 21



int InfraredReceive(int pinnum, int timeoutuS, int opt, FILE* fp);


#define INFRA_RECV_FILE     0x1
#define INFRA_RECV_PRINT    0x2



#ifdef __cplusplus
}
#endif

#endif /* INFRAREDIO_H */

