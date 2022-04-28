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
    SERIAL_Init();
    PWM_Init();
    QEI_Init();

    // add pins
    PWM_AddPins(PWM_PORTY10);
    PWM_AddPins(PWM_PORTY04);
    PWM_AddPins(PWM_PORTY12);
    
    
    PWM_SetFrequency(PWM_1KHZ);

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
