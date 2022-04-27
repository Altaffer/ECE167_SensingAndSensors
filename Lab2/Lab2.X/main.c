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
#include "AD.h"
#include "ToneGeneration.h"
#include "timers.h"

// definitions for ifdef
#define PART1
//#define PART2
//#define PART3

/******************
 LOCAL VARIABLES
 ******************/

/******************
 HELPER FUNCTIONS
 ******************/


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

#endif

    /*****
     Part2
     *****/
#ifdef PART2

#endif

    /*****
     Part3
     *****/
#ifdef PART3

#endif

    BOARD_End();
    while (1);


    return (EXIT_SUCCESS);
}
