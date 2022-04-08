/* 
 * File:   Part3.c
 * Author: taltaffe
 *
 * Created on April 7, 2022, 6:13 PM
 */

#include <stdio.h>
#include <stdlib.h>

// including common headers
#include "BOARD.h"
#include "serial.h"
#include "AD.h"
#include "ToneGeneration.h"
#include "pwm.h"
#include "timers.h"

/******************
 HELPER FUNCTIONS
 ******************/
//int tone = 1000;
int tone2;

void flexTone(void) {
    // Setting the original tone
    ToneGeneration_ToneOn();
    while (1) { // Updates the Frequency every 50 milliseconds
        if (TIMERS_GetMilliSeconds() % 50 == 0) {
            tone2 = AD_ReadADPin(AD_A1);
            ToneGeneration_SetFrequency((tone2));
        }
    }
}

void flickTone() {
    // Setting the original tone
    while (1) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            if (AD_ReadADPin(AD_A2) > 300) {
                ToneGeneration_ToneOn();
                ToneGeneration_SetFrequency((tone2));
            } else {
                ToneGeneration_ToneOff();
            }
            printf("%u\n\r", AD_ReadADPin(AD_A2));
        }
    }
}

void tone() {
    while (1) { // Updates the Frequency every 50 milliseconds
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            tone2 = AD_ReadADPin(AD_A1);
            if (AD_ReadADPin(AD_A2) > 300) {
                ToneGeneration_SetFrequency((tone2));
                ToneGeneration_ToneOn();
                for(int i=0; i<150000;i++){
                    int x = 0;
                    x += 1;
                    x -=1;
                }
            } else {
                ToneGeneration_ToneOff();
            }
        }
        printf("%u\n\r", AD_ReadADPin(AD_A1));
    }
}

int printAD(void) {
    // Creating a loop for continuously printing the output value
    while (1) {
        if (TIMERS_GetMilliSeconds() % 100 == 0) {
            printf("%u\n\r", AD_ReadADPin(AD_A2)); // AD_A1 is the FS output pin
        }
    }
}

int main(void) {
    // initializing libraries
    BOARD_Init();
    AD_Init();
    ToneGeneration_Init();
    PWM_Init();
    TIMERS_Init();

    // initializing pins
    AD_AddPins(AD_A2);
    AD_AddPins(AD_A1);

    /**
     * PART 2.1
     **/
    tone();

    BOARD_End();
    while (1);


    return (EXIT_SUCCESS);
}
