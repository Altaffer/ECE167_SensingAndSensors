#include <stdio.h>
#include <stdlib.h>

// including common headers
#include "BOARD.h"
#include "serial.h"
#include <xc.h>
#include <sys/attribs.h>
#include <QEI.h>
#include "pwm.h"

/******************
 LOCAL VARIABLES
 ******************/
//static int PinA;
//static int PinB;
int counter;

//typedef enum {
//    Up,
//    Right,
//    Down,
//    Left,
//} State;
//
//static State curState;
//
//int LED_R[] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 213, 148, 89, 55, 46, 0, 0, 0, 0, 0, 0, 0, 42, 168};
//int LED_G[] = {255, 194, 121, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 113, 189, 255, 255, 255, 255, 255, 255, 255};
//int LED_B[] = {0, 0, 0, 0, 0, 32, 121, 193, 255, 255, 255, 255, 255, 255, 255, 255, 255, 191, 118, 7, 0, 0, 0};

/******************
 HELPER FUNCTIONS
 ******************/

//void runSM(void) {
//    switch (curState) {
//        case(Up):
//            if (PinA && !PinB) {
//                curState = Right;
//                counter++;
//            }
//            if (!PinA && PinB) {
//                curState = Left;
//                counter--;
//            }
//            break;
//        case(Right):
//            if (PinA && PinB) {
//                curState = Down;
//                counter++;
//            }
//            if (!PinA && !PinB) {
//                curState = Up;
//                counter--;
//            }
//            break;
//        case(Down):
//            if (!PinA && PinB) {
//                curState = Left;
//                counter++;
//            }
//            if (PinA && !PinB) {
//                curState = Right;
//                counter--;
//            }
//            break;
//        case(Left):
//            if (!PinA && !PinB) {
//                curState = Up;
//                counter++;
//            }
//            if (PinA && PinB) {
//                curState = Down;
//                counter--;
//            }
//            break;
//    }
//}

/**
 * @function QEI_Init(void)
 * @param none
 * @brief  Enables the Change Notify peripheral and sets up the interrupt, anything
 *         else that needs to be done to initialize the module. 
 * @return SUCCESS or ERROR (as defined in BOARD.h)
 */
char QEI_Init(void) {
    // INIT Change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN15 = 1; //enable one phase
    CNENbits.CNEN16 = 1; //enable other phase
    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; //set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify
    
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD7 = 1;
    //    curState = Up;
    //    counter = 0;
    printf("ayy bruh\n");

}

void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
    //anything else that needs to happen goes here
    printf("hello");
    //    PinA = (readPort >> 6)&1;
    //    PinB = (readPort >> 7)&1;
    //    if (counter > 23) {
    //        QEI_ResetPosition();
    //    }
    //    runSM();
    //    PWM_SetDutyCycle(PWM_PORTY10, (LED_R[counter]*1000 / 255));
    //    PWM_SetDutyCycle(PWM_PORTY04, (LED_G[counter]*1000 / 255));
    //    PWM_SetDutyCycle(PWM_PORTY12, (LED_B[counter]*1000 / 255));
    //     printf("%i",QEI_GetPosition());

}

/**
 * @function QEI_GetPosition(void) 
 * @param none
 * @brief This function returns the current count of the Quadrature Encoder in ticks.      
 */
int QEI_GetPosition(void) {
    return counter;
}

/**
 * @Function QEI_ResetPosition(void) 
 * @param  none
 * @return none
 * @brief  Resets the encoder such that it starts counting from 0.
 */
void QEI_ResetPosition() {
    counter = 0;
}
