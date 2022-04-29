#include "BOARD.h"
#include <xc.h>
#include <sys/attribs.h>
#include <PING.h>

typedef enum {
    trigger,
    wait,
} State;

static State curState;
int trig;
int echo;
double dist;
/*******************************************************************************
 * PUBLIC FUNCTIONs                                                 *
 ******************************************************************************/

void runSM(void) {
    switch(curState){
        case(trigger):
            // trigger to 1
            trig = 1;
            // change pr4 for period 10 mus
                // got to wait
            curState = wait;
            break;
        case(wait):
            // trigger to 0
            trig = 0;
            // change pr4 for period 60ms
                // go to trigger
            curState = trigger;
            break
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
    PR4 = 0xFFFF; // this is not the timer value wanted - period 10 mus
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
    curState = trigger;
    echo = PORTDbits.RD4;
}

void __ISR(_CHANGE_NOTICE_VECTOR) ChangeNotice_Handler(void) {
    static char readPort = 0;
    readPort = PORTD; // this read is required to make the interrupt work
    IFS1bits.CNIF = 0;
    //Anything else that needs to occur goes here
}

void __ISR(_TIMER_4_VECTOR) Timer4IntHandler(void) {
    IFS0bits.T4IF = 0;
    //Anything else that needs to occur goes here
    runSM();
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
    dist = (0.5 * 340 * (PING_GetTimeofFlight()));
    return dist;
}

/**
 * @function    PING_GetTimeofFlight(void)
 * @brief       Returns the raw microsecond duration of the echo from the sensor.
 *              NO I/O should be done in this function.
 * @return      time of flight in uSec
 */
unsigned int PING_GetTimeofFlight(void) {
// TIMERS_GetMicroSeconds()/1000000) in seconds 
}