#include "driver_traffic_light.h"

int is_init = 0;


// Включение светофора
int driver_traffic_light_power() {
    is_init = (is_init == 1) ? 0 : 1;
    sleep(1);
    return 0;
}


int traffic_light_is_powered(){
    return is_init;
}


// Функция для определения текущего цвета сигнала светофора
SignalColor getSignalColor(FILE *data) {
    char color[LIGHTCONST];
    fscanf(data, "%s", color);
    SignalColor LightColor = 4;//неопределлёный цвет

    if(strcmp(color, "RED") == 0){
        LightColor = RED;
    } else if(strcmp(color, "YELLOWTOGREEN") == 0){
        LightColor = YELLOWTOGREEN;
    } else if(strcmp(color, "GREEN") == 0){
        LightColor = GREEN;
    } else if(strcmp(color, "YELLOWTORED") == 0){
        LightColor = YELLOWTORED;
    }
    return LightColor;
}

// Функция для установки цвета сигнала светофора
void setSignalColor(SignalColor color, FILE *data) {

    switch (color) {
        case RED:
            fprintf(data, "RED\n");
            sleep(1);
            break;
        case YELLOWTOGREEN:
            fprintf(data, "YELLOWTOGREEN\n");
            sleep(1);
            break;
        case GREEN:
            fprintf(data, "GREEN\n");
            sleep(1);
            break;
        case YELLOWTORED:
            fprintf(data, "YELLOWTORED\n");
            sleep(1);
            break;
        default:
            sleep(1);
            break;
    }
}
