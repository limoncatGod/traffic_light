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
    YELLOW,
    GREEN
} SignalColor;


int driver_traffic_light_init();
void getSignalColor(FILE *data);
void setSignalColor(SignalColor color, FILE *data);

#endif
