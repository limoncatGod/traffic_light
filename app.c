#include "driver_traffic_light.h"

int main() {
    driver_traffic_light_init();
    while (1) {
        printf("Traffic light\n");
        printf("1. Turn on traffic light\n");
        printf("2. Find out the current state of the traffic light\n");
        printf("3. Set signal of the traffic light\n");
        printf("4. Turn off traffic light\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sleep(1);
                printf("Turn on traffic light\n");
                driver_traffic_light_init();
                break;
            case 2:
                sleep(1);
                printf("Finding out...:");
                FILE *data = fopen("state_light.txt", "r");
                getSignalColor(data);
                fclose(data);
                break;
            case 3:
                sleep(1);
                printf("Choose signal RED YELLOWTOGREEN GREEN YELLOWTORED:");
                char signal[LIGHTCONST];
                scanf("%s", signal);
                SignalColor LightColor = 3;
                if(strcmp(signal, "RED") == 0){
                    LightColor = RED;
                } else if(strcmp(signal, "YELLOWTOGREEN") == 0){
                    LightColor = YELLOWTOGREEN;
                } else if(strcmp(signal, "GREEN") == 0){
                    LightColor = GREEN;
                } else if(strcmp(signal, "YELLOWTORED") == 0){
                    LightColor = YELLOWTORED;
                }
                FILE *data2 = fopen("state_light.txt", "w");
                setSignalColor(LightColor, data2);
                fclose(data2);
                FILE *file = fopen("time.txt", "w");
                fprintf(file, "%lld\n", time(NULL));
                fclose(file);
                break;
            case 4:
                printf("Stopping traffic light...\n");
                system("killall -9 file1");//???
                break;
            case 5:
                printf("exiting...\n");
                return 0;
            default:
                printf("invalid choice\n");
        }
    }
    return 0;
}
