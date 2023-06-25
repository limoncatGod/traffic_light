#include "driver_traffic_light.h"


int main() {
    if (driver_traffic_light_init() != 0) {
        printf("Traffic light is not initialized\n");
        return 1;
    }

    while (1) {
        char light_state[LIGHTCONST];
        FILE *data = fopen("state_light.txt", "r");
        if (data == NULL) {
            printf("Problem with file.\n");
            return 1;
        }

        fscanf(data, "%s", light_state);
        printf("Traffic light state at the moment: %s", light_state);
        fclose(data);

        sleep(10);
    }
}
