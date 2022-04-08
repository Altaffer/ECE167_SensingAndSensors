/* 
 * File:   Part1.c
 * Author: Luca Altaffer
 *
 * Created on April 6, 2022, 7:21 PM
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
// printing the A/D values of flex sensor 

int printAD(void) {
    // Creating a loop for continuously printing the output value
    while (1) {
        if (TIMERS_GetMilliSeconds() % 100 == 0) {
            printf("%u\n\r", AD_ReadADPin(AD_A1)); // AD_A1 is the FS output pin
        }
    }
}

//// Function for adjusting the tone using the flex sensor
//int i, j, k, tot, average, arr[50]; // using 50 samples

//void toneAdj(void) {
//    // Turing the tone on
//    //    ToneGeneration_ToneOn();
//
//    // Creating the first sample of 50
//    //    for (i = 0; i <= 50; i++) {
//    //        arr[i] = AD_ReadADPin(AD_A1);
//    //    }
//    while (1) { // implementing a loop to keep the averaging going
//        // summing the values in the array
////        tot = 0;
//        for (i = 0; i <= 50; i++) {
//            arr[i] = AD_ReadADPin(AD_A1);
//        }
//
//        for (j = 0; j <= 50; j++) {
//            tot = tot + arr[j];
//        }
//        average = (tot / 50);
//        printf("%i\n\r", average);
//        // setting the frequency to the average 
//        //        ToneGeneration_SetFrequency((average));
//
//        // removing the last item in the array and adding an new item in front
//        //        for (k = 50; k >= 0; k--) {
//        //            if (k != 0) {
//        //                arr[k] = arr[k - 1];
//        //            } else if (k == 0) {
//        //                arr[k] = AD_ReadADPin(AD_A1);
//        //            }
//        //        }
//
//    }
//}

int tone;
void toneAdj(void) {
    // Setting the original tone
    ToneGeneration_ToneOn();
    while (1) {     // Updates the Frequency every 50 milliseconds
        if (TIMERS_GetMilliSeconds() % 50 == 0) {
            tone = AD_ReadADPin(AD_A1);
            ToneGeneration_SetFrequency((tone));
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
    AD_AddPins(AD_A1);

    /**
     * PART 1.3
     **/
    toneAdj();

    BOARD_End();
    while (1);


    return (EXIT_SUCCESS);
}

