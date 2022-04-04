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
    ToneGeneration_ToneOn();
}

// creating a moving average function
int i, tot, j, arr[2000]; // using 2000 samples

int movingAv() {
    tot = 0;
    for (i = 0; i <= 2000; i++) {
        arr[i] = AD_ReadADPin(AD_A0);
    }
    for (j = 0; j <= 2000; j++) {
        tot = tot + arr[j];
    }
    return tot / 2000;
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

    float tone;
    int buttonOn = 0;
    while (1) {
        uint8_t c = ButtonsCheckEvents();
        if (c == BUTTON_EVENT_1DOWN) {
            tone = 250;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_1UP) {
            tone = 0;
            ToneGeneration_ToneOff();
            buttonOn = 0;
        } else if (c == BUTTON_EVENT_2DOWN) {
            tone = 350;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_2UP) {
            tone = 0;
           ToneGeneration_ToneOff();
            buttonOn = 0;
        } else if (c == BUTTON_EVENT_3DOWN) {
            tone = 550;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_3UP) {
            tone = 0;
           ToneGeneration_ToneOff();
            buttonOn = 0;
        } else if (c == BUTTON_EVENT_4DOWN) {
            tone = 650;
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
            buttonOn = 1;
        } else if (c == BUTTON_EVENT_4UP) {
            tone = 0;
            ToneGeneration_ToneOff();
            buttonOn = 0;
        }
        if (buttonOn == 1){
            ToneGeneration_SetFrequency((tone + (movingAv() / 5)));
        }
    }

    BOARD_End();
}