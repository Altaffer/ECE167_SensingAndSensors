/* 
 * File:   helloworld.c
 * Author: taltaffe
 *
 * Created on March 29, 2022, 8:13 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "serial.h"

int main(void) {
    BOARD_Init();
    printf("Hello World!\n");
    BOARD_End();

    while(1);
}

