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
        printf("%u\n", AD_ReadADPin(AD_A0)); // AD_A0 is the pin for the pot
    }
}

// Tone out hard-coded Speaker
void toneGen() {
    // Generating a tone
    ToneGeneration_ToneOn();
}

// creating a moving average function
int i, tot, j, arr[2000]; // using 2000 samples

int movingAv() {
    tot = 0;
    // creating an array for all sampled values
    for (i = 0; i <= 2000; i++) {
        arr[i] = AD_ReadADPin(AD_A0);
    }
    // adding together all values in the array
    for (j = 0; j <= 2000; j++) {
        tot = tot + arr[j];
    }
    return tot / 2000; // returns the average
}

//Tone adjust via Pot
void toneAdj(void) {
    ToneGeneration_ToneOn();
    while (1) {
        // implementing the moving average to teh frequency
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
    printf("Hello A/D results: ");
    /***
    UNCOMMENT BELOW FOR PART 3.1
    ***/
    //    printAD();

    printf("Tone out hard-coded Speaker Begin\n");
    // Initializing the Frequency
    /***
    UNCOMMENT BELOW FOR PART 3.2
    ***/
    //    ToneGeneration_SetFrequency(1000);
    //    PWM_SetFrequency(PWM_1KHZ);
    //    ToneGeneration_ToneOn();

    printf("Tone Adjust Via Pot Begin\n");
    /***
    UNCOMMENT BELOW FOR PART 3.3
    ***/
    //        toneAdj();

    printf("Making some Music");
    // Create tone
    ToneGeneration_ToneOn();

    // defining a few useful tools
    float tone;
    int buttonOn = 0;
    while (1) {
        // instance of the Event Checker
        uint8_t c = ButtonsCheckEvents();
        if (c == BUTTON_EVENT_1DOWN) {  // Setting 1st button tone to at least 250 Hz
            tone = 250;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_1UP) { // Turing of the tone 
           tone = 0;
            ToneGeneration_ToneOff();
            buttonOn = 0;
        } else if (c == BUTTON_EVENT_2DOWN) {   // Setting 2nd button tone to at least 350 Hz
            tone = 350;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_2UP) { // Turing of the tone 
            tone = 0;
            ToneGeneration_ToneOff();
            buttonOn = 0;
        } else if (c == BUTTON_EVENT_3DOWN) {   // Setting 3rd button tone to at least 550 Hz
            tone = 550;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_3UP) { // Turing of the tone 
            tone = 0;
            ToneGeneration_ToneOff();
            buttonOn = 0;
        } else if (c == BUTTON_EVENT_4DOWN) {   // Setting 4th button tone to at least 650 Hz
            tone = 650;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_4UP) { // Turing of the tone 
            tone = 0;
            ToneGeneration_ToneOff();
            buttonOn = 0;
        }
        if (buttonOn == 1) {    // Updating the frequency based on the pot values
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
        }
    }

    BOARD_End();
}