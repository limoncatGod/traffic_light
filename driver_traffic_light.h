#ifndef DRIVER_TRAFFIC_LIGHT_H
#define DRIVER_TRAFFIC_LIGHT_H

#define LIGHTCONST 10
#define REDTIME 30
#define YELLOWTIME 5
#define GREENTIME 30


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef enum {
    RED,
    YELLOWTOGREEN,
    GREEN,
    YELLOWTORED
} SignalColor;


int driver_traffic_light_power();
int traffic_light_is_powered();
SignalColor getSignalColor(FILE *data);
void setSignalColor(SignalColor color, FILE *data);

#endif
