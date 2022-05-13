/* 
 * File:   main.c
 * Author: taltaffe
 *
 * Created on May 12, 2022, 12:54 PM
 */

#include <stdio.h>
#include <stdlib.h>

// including common headers
#include "BOARD.h"
#include "serial.h"
#include "pwm.h"
#include <xc.h>
#include <I2C.h>
#include <stdio.h>
#include "AD.h"
#include "BNO055.h"
#include "timers.h"

// defines for different parts 
//#define PART2
#define PART3
//#define PART4

/******************
 VARIABLES 
 ******************/
// z-axis variables
int zAccel; // the z axis acceleration value
int zMag; // the z axis magnetic field value
int z_arr[100]; // array to calculate the average of all the z acceleration values
double z_ave; // average of all the z axis acceleration values
double z_Gave; // average for gyro

// y-axis variables
int yAccel; // the y axis acceleration value
int yMag; // the y axis magnetic field value
int y_arr[100]; // array to calculate the average of all the y acceleration values
double y_ave; // average of all the x axis acceleration values
double y_Gave; // average for gyro

// x-axis variables
int xAccel; // the x axis acceleration value
int xMag; // the x axis magnetic field value
int x_arr[100]; // array to calculate the average of all the0 x acceleration values
double x_ave; // average of all the x axis acceleration values
double x_Gave; // average for gyro

// loop helper variables
int i = 0; // loop to add components to array
int j = 0; // loop to sum for average
int sum; // holder for the sum

/******************
 HELPER FUNCTIONS
 ******************/
// z-axis functions

float printZAccel() {
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            zAccel = BNO055_ReadAccelZ();
            z_arr[i] = zAccel;
            i++;
        }
    }
    for (j = 0; j < 100; j++) {
        sum = sum + z_arr[j];
    }
    z_ave = sum / 100;
    sum = 0;
    i = 0;
    return z_ave;
}

float printZMag() {
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            zAccel = BNO055_ReadMagZ();
            z_arr[i] = zAccel;
            i++;
        }
    }
    for (j = 0; j < 100; j++) {
        sum = sum + z_arr[j];
    }
    z_ave = sum / 100;
    sum = 0;
    i = 0;
    return z_ave;
}

float printZGyro() {
    while (1) {
        sum += BNO055_ReadGyroZ();
        i++;
        if (TIMERS_GetMilliSeconds() % 1200000 < 3) {
            break;
        }
    }
    z_Gave = sum / i;
    sum = 0;
    i = 0;
    return z_Gave;
}

// y-axis functions

float printYAccel() {
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            yAccel = BNO055_ReadAccelY();
            y_arr[i] = yAccel;
            i++;
        }
    }
    for (j = 0; j < 100; j++) {
        sum = sum + y_arr[j];
    }
    y_ave = sum / 100;
    sum = 0;
    i = 0;
    return y_ave;
}

float printYMag() {
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            zAccel = BNO055_ReadMagY();
            z_arr[i] = zAccel;
            i++;
        }
    }
    for (j = 0; j < 100; j++) {
        sum = sum + z_arr[j];
    }
    z_ave = sum / 100;
    sum = 0;
    i = 0;
    return z_ave;
}

float printYGyro() {
while (1) {
        sum += BNO055_ReadGyroY();
        i++;
        if (TIMERS_GetMilliSeconds() % 10000 < 3) {
            break;
        }
    }
    y_Gave = sum / i;
    sum = 0;
    i = 0;
    return y_Gave;
}

// x-axis functions

float printXAccel() {
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            xAccel = BNO055_ReadAccelX();
            x_arr[i] = xAccel;
            i++;
        }
    }
    for (j = 0; j < 100; j++) {
        sum = sum + x_arr[j];
    }
    x_ave = sum / 100;
    sum = 0;
    i = 0;
    return x_ave;
}

float printXMag() {
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            zAccel = BNO055_ReadMagX();
            z_arr[i] = zAccel;
            i++;
        }
    }
    for (j = 0; j < 100; j++) {
        sum = sum + z_arr[j];
    }
    z_ave = sum / 100;
    sum = 0;
    i = 0;
    return z_ave;
}

float printXGyro() {
while (1) {
        sum += BNO055_ReadGyroX();
        i++;
        if (TIMERS_GetMilliSeconds() % 10000 < 3) {
            break;
        }
    }
    x_Gave = sum / i;
    sum = 0;
    i = 0;
    return x_Gave;
}

/******************
 MAIN
 ******************/
int main(void) {
    // initializing libraries
    BOARD_Init();
    BNO055_Init();
    TIMERS_Init();
    /*****
     Part2
     *****/
#ifdef PART2
    // calling functions to calibrate IMU
    //    printf("Printing the accelerations\r\n");
    //    while(1){
    //        printf("x accel: %f | y accel: %f | zaccel: %f\n\r",printXAccel(),printYAccel(),printZAccel() );
    //    }
    printf("Printing B\r\n");
    while (1) {
        printf("x B: %f | y B: %f | z B: %f\n\r", printXMag(), printYMag(), printZMag());
    }

#endif

    /*****
     Part3
     *****/
#ifdef PART3
    // 
    printf("Logging data for an hour");
    while (1) {
        printf("x gyro: %f | y gyro: %f | z gyro: %f\r\n", printXGyro(),printYGyro(),printZGyro());
    }

#endif

    /*****
     Part4
     *****/
#ifdef PART4
    // 

#endif

    while (1);
    BOARD_End();
}



