#include "driver_traffic_light.h"


// Включение светофора
int driver_traffic_light_init() {
    printf("Turn on traffic light...\n");
    sleep(1);
    return 0;
}


// Функция для определения текущего цвета сигнала светофора
void getSignalColor(FILE *data) {
    char color[10];
    fscanf(data, "%s\n", color);
    SignalColor LightColor = 3;

    if(strcmp(color, "RED") == 0){
        LightColor = RED;
    } else if(strcmp(color, "YELLOW") == 0){
        LightColor = YELLOW;
    } else if(strcmp(color, "GREEN") == 0){
        LightColor = GREEN;
    }
    switch (LightColor) {
        case RED:
            printf("Установлен красный сигнал светофора.\n");
            sleep(100);
            break;
        case YELLOW:
            printf("Установлен желтый сигнал светофора.\n");
            sleep(100);
            break;
        case GREEN:
            printf("Установлен зеленый сигнал светофора.\n");
            sleep(100);
            break;
        default:
            printf("Недопустимый цвет сигнала светофора.\n");
            sleep(100);
            break;
    }
}

// Функция для установки цвета сигнала светофора
void setSignalColor(SignalColor color, FILE *data) {

    switch (color) {
        case RED:
            printf("Установлен красный сигнал светофора.\n");
            fprintf(data, "RED\n");
            sleep(1000);
            break;
        case YELLOW:
            printf("Установлен желтый сигнал светофора.\n");
            fprintf(data, "YELLOW\n");
            sleep(1000);
            break;
        case GREEN:
            printf("Установлен зеленый сигнал светофора.\n");
            fprintf(data, "GREEN\n");
            sleep(1000);
            break;
        default:
            printf("Недопустимый цвет сигнала светофора.\n");
            sleep(1000);
            break;
    }
}