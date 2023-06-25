#include "driver_traffic_light.h"

long long int time_prev;


int main() {
    if (driver_traffic_light_init() != 0) {
        printf("Traffic light is not initialized\n");
        return 1;
    }
    printf("Daemon is running...\n");

    time_prev = time(NULL);
    FILE *file = fopen("time.txt", "w");
    fprintf(file, "%lld\n", time_prev);
    fclose(file);
    while (1) {
        char light_state[LIGHTCONST];
        file = fopen("time.txt", "r");
        fscanf(file, "%lld", &time_prev);
        fclose(file);
        FILE *data = fopen("state_light.txt", "r");
        if (data == NULL) {
            printf("Problem with file.\n");
            return 1;
        }

        fscanf(data, "%s", light_state);
        fclose(data);
        if(strcmp(light_state, "RED") == 0){
            if((time(NULL)-time_prev) >= REDTIME){
                file = fopen("time.txt", "w");
                fprintf(file, "%lld\n", time(NULL));
                fclose(file);
                data = fopen("state_light.txt", "w");
                setSignalColor(YELLOWTOGREEN,data);
            }
        } else if(strcmp(light_state, "YELLOWTOGREEN") == 0){
            if((time(NULL)-time_prev) >= YELLOWTIME){
                file = fopen("time.txt", "w");
                fprintf(file, "%lld\n", time(NULL));
                fclose(file);
                data = fopen("state_light.txt", "w");
                setSignalColor(GREEN,data);
            }
        } else if(strcmp(light_state, "GREEN") == 0){
            if((time(NULL)-time_prev) >= GREENTIME){
                file = fopen("time.txt", "w");
                fprintf(file, "%lld\n", time(NULL));
                fclose(file);
                data = fopen("state_light.txt", "w");
                setSignalColor(YELLOWTORED,data);
            }
        } else if(strcmp(light_state, "YELLOWTORED") == 0){
            if((time(NULL)-time_prev) >= GREENTIME){
                file = fopen("time.txt", "w");
                fprintf(file, "%lld\n", time(NULL));
                fclose(file);
                data = fopen("state_light.txt", "w");
                setSignalColor(RED,data);
            }
        }

        fclose(data);
        sleep(1);
    }
}
