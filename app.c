#include "driver_traffic_light.h"

int main() {
    driver_traffic_light_init();
    while (1) {
        printf("Traffic light is on\n");
        printf("1. Find out the current state of the traffic light\n");
        printf("2. Set signal of the traffic light\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sleep(1);
                printf("Current state is %s\n");
                //print current state
                break;
            case 2:
                sleep(1);
                printf("Choose signal RED YELLOW GREEN:");
                char signal[LIGHTCONST];
                scanf("%s", signal);
                //set signal color
                break;
            case 3:
                printf("exiting...\n");
                system("killall -9 file1");
                return 0;
            default:
                printf("invalid choice\n");
        }
    }
    return 0;
}
