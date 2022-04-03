/* 
 * File:   part3.c
 * Author: taltaffe
 *
 * Created on April 1, 2022, 3:17 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "serial.h"
#include "AD.h"
#include "ToneGeneration.h"
#include "pwm.h"
#include "Buttons.h"

// Hello A/D
int printAD(void) {
    // Creating a loop for continuously printing the pot value
    while (1) {
        printf("%u\n", AD_ReadADPin(AD_A0));    // AD_A0 is the pin for the pot
    }
}

// Tone out hard-coded Speaker
void toneGen() {
    ToneGeneration_ToneOn();
}

// creating a moving average function
int i, tot, j, arr[2000];   // using 2000 samples
int movingAv(){
    tot = 0;
    for(i = 0;i <= 2000; i++){
        arr[i] = AD_ReadADPin(AD_A0);
    }
    for(j=0;j <=2000; j++){
        tot = tot + arr[j];
    }
    return tot/2000;
}

//Tone adjust via Pot
void toneAdj(void) {
    ToneGeneration_ToneOn();
    
    while (1) {
        // implementing the moving average
        ToneGeneration_SetFrequency((movingAv()));
    }
}

int main(void) {
    // initializing the components for test
    BOARD_Init();
    AD_Init();
    ToneGeneration_Init();
    PWM_Init();
    ButtonsInit();
    // Initializing the pot pin
    AD_AddPins(AD_A0);
    
    printf("Testing the Hardware begin\n");

    printf("*************************\n");
    //    printf("Hello A/D results: ");
    //    printAD();

//    printf("Tone out hard-coded Speaker Begin\n");
    // Initializing the Frequency
//    ToneGeneration_SetFrequency(1000);
//    PWM_SetFrequency(PWM_1KHZ);
//    ToneGeneration_ToneOn();
    
//        printf("Tone Adjust Via Pot Begin\n");
//        toneAdj();
        
        printf("Making some Music");
        ToneGeneration_ToneOn();
        while(1){
            if (BUTTON_STATES = BUTTON_EVENT_1UP){
                ToneGeneration_SetFrequency((500 + movingAv()));
            }
            else if (BUTTON_STATES == BUTTON_EVENT_2UP){
                ToneGeneration_SetFrequency((1000 + movingAv()));
            }
            else if (BUTTON_STATES == BUTTON_EVENT_3UP){
                ToneGeneration_SetFrequency((1500 + movingAv()));
            }
            else if (BUTTON_STATES == BUTTON_EVENT_4UP){
                ToneGeneration_SetFrequency((2000 + movingAv()));
            }
            else if(BUTTON_EVENT_NONE){
                ToneGeneration_SetFrequency((movingAv()));
            }
        }

    BOARD_End();
}