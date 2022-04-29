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


int main(void) {
    // initializing libraries
    BOARD_Init();
    SERIAL_Init();
    PWM_Init();
    QEI_Init();
    TIMERS_Init();
    PING_Init();

    // add pins
    PWM_AddPins(PWM_PORTY10);
    PWM_AddPins(PWM_PORTY04);
    PWM_AddPins(PWM_PORTY12);
    
    PWM_AddPins(PWM_PORTZ06);
    
    
    PWM_SetFrequency(PWM_1KHZ);


    while (1);
    BOARD_End();
}