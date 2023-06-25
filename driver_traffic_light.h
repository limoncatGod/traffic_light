#ifndef DRIVER_TRAFFIC_LIGHT_H
#define DRIVER_TRAFFIC_LIGHT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RED,
    YELLOW,
    GREEN
} SignalColor;


int driver_traffic_light_init();
void getSignalColor(FILE *data);
void setSignalColor(SignalColor color, FILE *data);

#endif
