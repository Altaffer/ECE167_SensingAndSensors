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
#include "timers.h"

// defines for different parts 
//#define PART1
//#define PART2
#define PART3

/******************
 LOCAL VARIABLES
 ******************/
int tone2;  // frequency for part 3
int tone1;  // frequency for part 1
int ptone;  // frequency for part 2

/******************
 HELPER FUNCTIONS
 ******************/

void toneAdj(void) {    // Adjusting tone for the flex sensor
    // Setting the original tone
    ToneGeneration_ToneOn();
    while (1) {     // Updates the Frequency every 50 milliseconds
        if (TIMERS_GetMilliSeconds() % 50 == 0) {
            // getting and setting the tone every time sampled
            tone1 = AD_ReadADPin(AD_A1);
            ToneGeneration_SetFrequency((tone1));
        }
    }
}

void flickTone() {  // Creating a tone using the Piezo sensor
    ptone = 1000;
    while (1) { // while loop for continuous flicking
        if (TIMERS_GetMilliSeconds() % 20 == 0) {   // sampling evert 20 ms
            if (AD_ReadADPin(AD_A2) > 100) {    // giving a 100v threshold to play
                // turning on and setting frequency
                ToneGeneration_ToneOn();
                ToneGeneration_SetFrequency((ptone));
            } else { // turning off when tone is played
                ToneGeneration_ToneOff();
            }
        }
    }
}

void tone() {
    while (1) { // Updates the Frequency every 40 milliseconds
        if (TIMERS_GetMilliSeconds() % 40 == 0) {
            // get and set the frequency after starting the next sample
            tone2 = AD_ReadADPin(AD_A1);
            ToneGeneration_SetFrequency((tone2));
            // loop to play the tone only after surpassing the 100v threshold,
            while (AD_ReadADPin(AD_A2) > 100) {
                ToneGeneration_ToneOn();
                // for loop to stall the code and play the tone for a longer period
                for (int i = 0; i < 150000; i++) {
                    int x = 0;
                    x += 1;
                    x -= 1;
                }
            }
        }
        // stop the tone after the loop is done
        ToneGeneration_ToneOff();
    }

}

int printAD2(void) {
    // Creating a loop for continuously printing the output value
    while (1) {
        if (TIMERS_GetMilliSeconds() % 100 == 0) { // print only after 100 ms
            printf("%u\n\r", AD_ReadADPin(AD_A2)); // AD_A1 is the FS output pin
        }
    }
}

int main(void) {
    // initializing libraries
    BOARD_Init();
    AD_Init();
    ToneGeneration_Init();
    TIMERS_Init();

    // initializing pins
    AD_AddPins(AD_A2);
    AD_AddPins(AD_A1);
    
    /*****
     Part1
     *****/
    #ifdef PART1
    toneAdj();
    #endif
    
    /*****
     Part2
     *****/
    #ifdef PART2
    tone();
    #endif

    /*****
     Part3
     *****/
    #ifdef PART3
    tone();
    #endif

    BOARD_End();
    while (1);


    return (EXIT_SUCCESS);
}
