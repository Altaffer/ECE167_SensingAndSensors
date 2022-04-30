#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "serial.h"
#include <xc.h>
#include <sys/attribs.h>
#include "PING.h"
#include "timers.h"
#include "pwm.h"
#include "AD.h"

/*******************************************************************************
 * VARIABLES                                                 *
 ******************************************************************************/

// states for SM

typedef enum {
    trigger,
    wait,
} State;

static State curState; // defining the initial state
int echo; // defining the echo
double dist; // defining the distance

int timer1; // first timer for time of flight
int timer2; // second timer for time of flight
int TOF; // Time of Flight (timer1-timer2), see function

int ms60 = 0x9500; // timer for PR4 -> 60 ms
int mus10 = 0x0090; // timer for PR4 -> 10 mus

//int tone;

/*******************************************************************************
 * PUBLIC FUNCTIONs                                                 *
 ******************************************************************************/

void runSM2(void) { // state machine for trigger and waiting
    switch (curState) {
        case(trigger): // the trigger state
            // set trigger high
            LATDbits.LATD1 = 1;
            // set timer
            PR4 = mus10;
            curState = wait;
            break;
        case(wait): // waiting state 
            // set trigger low
            LATDbits.LATD1 = 0;
            // set timer
            PR4 = ms60;
            curState = trigger;
            break;
    }
}

/**
 * @function    PING_Init(void)
 * @brief       Sets up both the timer and Change notify peripherals along with their
 *              respective interrupts.  Also handles any other tasks needed such as pin 
 *              I/O directions, and any other things you need to initialize the sensor.
 *              TIMERS library must be inited before this library.
 * @return      SUCCESS or ERROR (as defined in BOARD.h)
 */
char PING_Init(void) {
    // following block inits the timer
    T4CON = 0;
    T4CONbits.TCKPS = 0b110;
    PR4 = mus10; // this is not the timer value wanted - period 10 mus
    T4CONbits.ON = 1;
    IFS0bits.T4IF = 0;
    IPC4bits.T4IP = 3;
    IEC0bits.T4IE = 1;

    // following block inits change notify
    CNCONbits.ON = 1; // Change Notify On
    CNENbits.CNEN14 = 1;
    int temp = PORTD; // this is intentional to ensure a interrupt occur immediately upon enabling
    IFS1bits.CNIF = 0; // clear interrupt flag
    IPC6bits.CNIP = 1; //set priority
    IPC6bits.CNIS = 3; // and sub priority
    IEC1bits.CNIE = 1; // enable change notify

    //Anything else that needs to occur goes here
    TIMERS_Init();
    TRISDbits.TRISD1 = 0;   // setting pin 3 to output
    LATDbits.LATD1 = 0; // initializing pin 3 trigger
    curState = trigger; // initializing the initial state
    echo = PORTDbits.RD5; // initializing the echo pin 34. 
}

void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
  
    //Anything else that needs to occur goes here
    echo = PORTDbits.RD5;
    if (echo == 1) {
        timer1 = TIMERS_GetMicroSeconds();
    }
    if (echo == 0) {
        timer2 = TIMERS_GetMicroSeconds(); // second timer for TOF
        TOF = timer2 - timer1;
        printf("dist: %u\n\r", PING_GetDistance()); // calling function to get TOF
    }
}

void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void) {
    IFS0bits.T4IF = 0;

    //Anything else that needs to occur goes here
    runSM2(); // running the SM 
    //    PWM_SetFrequency();   // cheese
}

/**
 * @function    PING_GetDistance(void)
 * @brief       Returns the calculated distance in mm using the sensor model determined
 *              experimentally. 
 *              No I/O should be done in this function
 * @return      distance in mm
 */
unsigned int PING_GetDistance(void) {
    // d = 0.5 * v * t; 
    dist = ((10 * 10 *PING_GetTimeofFlight()) / 58)/10; // in meters
    return dist;
}

/**
 * @function    PING_GetTimeofFlight(void)
 * @brief       Returns the raw microsecond duration of the echo from the sensor.
 *              NO I/O should be done in this function.
 * @return      time of flight in uSec
 */
unsigned int PING_GetTimeofFlight(void) {
    return TOF;
    // TIMERS_GetMicroSeconds()) in seconds 
}

//void makeMusic(void){
////     while (1) { // Updates the Frequency every 40 milliseconds
//        if (TIMERS_GetMilliSeconds() % 40 == 0) {
//            // get and set the frequency after starting the next sample
//            tone = PING_GetDistance();
////            AD_ReadADPin(AD_A1);
//            ToneGeneration_SetFrequency((tone*10));
//            if ((tone > 400) && (tone < 5000)){
//                ToneGeneration_ToneOn();
//            }
//            else{
//                ToneGeneration_ToneOff();
//            }
//        }
//    }
