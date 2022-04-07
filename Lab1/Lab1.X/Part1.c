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


/*
 * 
 */
int main(void){
    BOARD_Init();
    
    BOARD_End();
    while(1);
    

    return (EXIT_SUCCESS);
}

