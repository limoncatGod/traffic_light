#include "driver_traffic_light.h"


// Включение светофора
int driver_traffic_light_init() {
    sleep(1);
    return 0;
}


// Функция для определения текущего цвета сигнала светофора
void getSignalColor(FILE *data) {
    char color[LIGHTCONST];
    fscanf(data, "%s\n", color);
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
    switch (LightColor) {
        case RED:
            printf("Now the traffic light is red.\n");
            sleep(1);
            break;
        case YELLOWTOGREEN:
            printf("Now the traffic light is yellow (next green).\n");
            sleep(1);
            break;
        case GREEN:
            printf("Now the traffic light is green.\n");
            sleep(1);
            break;
        case YELLOWTORED:
            printf("Now the traffic light is yellow (next red).\n");
            sleep(1);
            break;
        default:
            printf("Тow the traffic light is invalid.\n");
            sleep(1);
            break;
    }
}

// Функция для установки цвета сигнала светофора
void setSignalColor(SignalColor color, FILE *data) {

    switch (color) {
        case RED:
            printf("Red traffic light set.\n");
            fprintf(data, "RED\n");
            sleep(1);
            break;
        case YELLOWTOGREEN:
            printf("Yellow (next Green) traffic light set.\n");
            fprintf(data, "YELLOWTOGREEN\n");
            sleep(1);
            break;
        case GREEN:
            printf("Green traffic light set.\n");
            fprintf(data, "GREEN\n");
            sleep(1);
            break;
        case YELLOWTORED:
            printf("Yellow (next Red) traffic light set.\n");
            fprintf(data, "YELLOWTORED\n");
            sleep(1);
            break;
        default:
            printf("Invalid traffic light color.\n");
            sleep(1);
            break;
    }
}