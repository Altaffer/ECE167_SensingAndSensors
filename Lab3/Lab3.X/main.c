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
#include <xc.h>
#include <I2C.h>
#include <stdio.h>
#include "BNO055.h"
#include "timers.h"

// defines for different parts 
//#define PART2
//#define PART3
//#define PART3_1
//#define PART3_2
#define PART4

/******************
 VARIABLES 
 ******************/
// z-axis variables
int zAccel; // the z axis acceleration value
int zMag; // the z axis magnetic field value
int z_arr[100]; // array to calculate the average of all the z acceleration values
double z_ave; // average of all the z axis acceleration values
double z_Gave; // average for gyro
double sumz; // helper variable for gyro average 
double z_0; // initial position of gyro
double z; // updated position of gyro
double yaw; // roll angle of gyro

// y-axis variables
int yAccel; // the y axis acceleration value
int yMag; // the y axis magnetic field value
int y_arr[100]; // array to calculate the average of all the y acceleration values
double y_ave; // average of all the x axis acceleration values
double y_Gave; // average for gyro
double sumy; // helper variable for gyro average 
double y_0; // initial position of gyro
double y; // updated position of gyro
double roll; // pitch angle of gyro

// x-axis variables
int xAccel; // the x axis acceleration value
int xMag; // the x axis magnetic field value
int x_arr[100]; // array to calculate the average of all the0 x acceleration values
double x_ave; // average of all the x axis acceleration values
double x_Gave; // average for gyro
double sumx; // helper variable for gyro average 
double x_0; // initial position of gyro
double x; // updated position of gyro
double pitch; // pitch angle of gyro

// loop helper variables
int i = 0; // loop to add components to array
int j = 0; // loop to sum for average
int sum; // holder for the sum

/******************
 HELPER FUNCTIONS
 ******************/
// z-axis functions

float printZAccel() { // Getting the Acceleration in the z axis
    while (i < 100) { // taking 100 samples
        if (TIMERS_GetMilliSeconds() % 20 == 0) { // taking samples every 20 ms
            zAccel = BNO055_ReadAccelZ();
            z_arr[i] = zAccel; // adding readings to an array
            i++; // increasing the counter
        }
    }
    for (j = 0; j < 100; j++) { // summing items in the array
        sum = sum + z_arr[j];
    }
    z_ave = sum / 100; // calculating the average 
    sum = 0; // reseting 
    i = 0; // reseting
    return z_ave;
}

float printZMag() { // Getting the Magnetic Field in the z axis
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            zMag = BNO055_ReadMagZ();
            z_arr[i] = zMag;
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

// y-axis functions

float printYAccel() { // Getting the Acceleration in the y axis
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

float printYMag() { // Getting the Magnetic Field in the y axis
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            yMag = BNO055_ReadMagY();
            z_arr[i] = yMag;
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

// x-axis functions

float printXAccel() { // Getting the Acceleration in the x axis
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

float printXMag() { // Getting the Magnetic field in the z axis
    while (i < 100) {
        if (TIMERS_GetMilliSeconds() % 20 == 0) {
            xMag = BNO055_ReadMagX();
            z_arr[i] = xMag;
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

/******************
 MAIN
 ******************/
int main(void) {
    // initializing libraries
    BOARD_Init();
    printf("dick\n\r");
    BNO055_Init();
    TIMERS_Init();
    printf("dick2\n\r");

    /*****
     Part2
     *****/
#ifdef PART2
    printf("Printing B & Acceleration\r\n");
    while (1) { // printing the data loop
        printf("x B: %f | y B: %f | z B: %f\n\r", printXMag(), printYMag(), printZMag());
        printf("x accel: %f | y accel: %f | zaccel: %f\n\r", printXAccel(), printYAccel(), printZAccel());
    }

#endif

    /*****
     Part3
     *****/
#ifdef PART3
    // 
#ifdef PART3_1
    printf("Logging data for an hour\n\r");
    while (1) {
        while (1) { // summing all the axes for each tick  and recoding the count
            sumx += BNO055_ReadGyroX();
            sumy += BNO055_ReadGyroY();
            sumz += BNO055_ReadGyroZ();
            i++;
            if (TIMERS_GetMilliSeconds() % 120000 < 3) { // break every 2 minutes
                break;
            }
        }
        // Averaging the data 
        x_Gave = sumx / i;
        y_Gave = sumy / i;
        z_Gave = sumz / i;
        // resetting the data 
        sumx = 0;
        sumy = 0;
        sumz = 0;
        i = 0;
        printf("x gyro: %f | y gyro: %f | z gyro: %f\r\n", x_Gave, y_Gave, z_Gave);
    }
#endif
#ifdef PART3_2
    printf("part3.2\n\r");
    // Initializing timers
    int currtime = TIMERS_GetMilliSeconds();
    int tentime = TIMERS_GetMilliSeconds();
    int prevtime = TIMERS_GetMilliSeconds();
    while (1) { // loop for calulating the bias
        currtime = TIMERS_GetMilliSeconds(); // setting the current time
        if ((currtime - prevtime) >= 20) { // trigger every 20 ms
            // sum for each tick
            sumx += BNO055_ReadGyroX();
            sumy += BNO055_ReadGyroY();
            sumz += BNO055_ReadGyroZ();
            i++;
            prevtime = currtime; // setting the prevtime for next tick
        }
        if ((currtime - tentime) >= 10000) { // break out after 10 seconds
            tentime = currtime;
            break;
        }
    }
    // after the 10 seconds, take the averages and reset everything
    x_Gave = sumx / i;
    y_Gave = sumy / i;
    z_Gave = sumz / i;
    sumx = 0;
    sumy = 0;
    sumz = 0;
    i = 0;
    tentime = TIMERS_GetMilliSeconds();
    prevtime = TIMERS_GetMilliSeconds();
    while (1) { // loop for calculating the angle after find the bias
        currtime = TIMERS_GetMilliSeconds(); // redefine the current time
        if ((currtime - prevtime) >= 20) { // taking samples every 20 ms
            // setting the initial point for the axes
            x_0 = BNO055_ReadGyroX();
            y_0 = BNO055_ReadGyroY();
            z_0 = BNO055_ReadGyroZ();
            // update the point but subtracting the bias
            x = x_0 - x_Gave;
            y = y_0 - y_Gave;
            z = z_0 - z_Gave;
            // solving for the current angle 
            yaw += ((250 * z * 0.02) / 32767);
            pitch += ((250 * x * 0.02) / 32767);
            roll += ((250 * y * 0.02) / 32767);
            // print and rest
            printf("x gyro: %f | y gyro: %f | z gyro: %f\r\n", pitch, roll, yaw);
            prevtime = currtime;
        }
    }

#endif
#endif

    /*****
     Part4
     *****/
#ifdef PART4
    // Getting tumble data 
    while (1) {
        if (TIMERS_GetMilliSeconds() % 100 >= 3) {
            printf("%d, %d, %d, %d, %d, %d\n\r", BNO055_ReadAccelX(), BNO055_ReadAccelY(), BNO055_ReadAccelZ(), BNO055_ReadMagX(), BNO055_ReadMagY(), BNO055_ReadMagZ());
        }
    }

#endif

    while (1);
    BOARD_End();
}



