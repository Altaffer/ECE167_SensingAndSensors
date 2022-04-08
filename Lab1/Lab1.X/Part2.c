/* 
 * File:   Part2.c
 * Author: taltaffe
 *
 * Created on April 7, 2022, 4:19 PM
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
void flickTone() {
    // Setting the original tone
    
    int tone = 1000;
    while (1) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            if (AD_ReadADPin(AD_A2) > 300) {
                ToneGeneration_ToneOn();
                ToneGeneration_SetFrequency((tone));
            } else {
                ToneGeneration_ToneOff();
            }
            printf("%u\n\r", AD_ReadADPin(AD_A2));
        }
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

    /**
     * PART 2.1
     **/
    flickTone();

    BOARD_End();
    while (1);


    return (EXIT_SUCCESS);
}
