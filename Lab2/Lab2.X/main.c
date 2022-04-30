/* 
 * File:   main.c
 * Author: taltaffe
 *
 * Created on April 26, 2022, 12:57 PM
 */

#include <stdio.h>
#include <stdlib.h>

// including common headers
#include "BOARD.h"
#include "serial.h"
#include "pwm.h"
#include "QEI.h"
#include "PING.h"
#include "timers.h"
#include <xc.h>
#include "AD.h"
#include "ToneGeneration.h"

// defines for different parts 
//#define PART1
//#define PART2
#define PART3

/******************
 VARIABLES 
 ******************/
int out;    // variable for output in PART3
int tone;   // tone variable for music function in PART2

/******************
 HELPER FUNCTIONS
 ******************/
void makeMusic(void){   // Part 2.3 function
     while (1) { // Updates the Frequency every 40 milliseconds
        if (TIMERS_GetMilliSeconds() % 40 == 0) {
            // setting the tone using the distance
            tone = PING_GetDistance()/10; 
            // setting the tone on PIN3 - incompatible with PART1 due to PWM pin
            ToneGeneration_SetFrequency((DEFAULT_TONE + tone));
            // creating threshold for tone on
            if ((tone > 40) && (tone < 500)){
                ToneGeneration_ToneOn();
            }
            else{
                ToneGeneration_ToneOff();
            }
        }
    }
}

int main(void) {
    // initializing libraries
    BOARD_Init();
    SERIAL_Init();
    PWM_Init();
    ToneGeneration_Init();
    AD_Init();

    /*****
    Part1
     *****/
#ifdef PART1
    // make sure QEI.c is included in the project and PING.c is not
    QEI_Init();
#endif

    /*****
     Part2
     *****/
#ifdef PART2
    // make sure PING.c is included in the project and QEI.c is not
    PING_Init();
    makeMusic();
#endif

    /*****
     Part3
     *****/
#ifdef PART3
    AD_AddPins(AD_A0);
    
    int i = 0;
    int average = 0;
    while(1){
        average += AD_ReadADPin(AD_A0);
        if(i>5000){
            if(abs(average/5000) < 7){
                printf("%i\n\r", abs(average/5000));
            }
            //out = average/5000;
            //printf("%i\n\r", out);
            average = 0;
            i = 0;
        }
        i++;
    }
#endif



    while (1);
    BOARD_End();
}