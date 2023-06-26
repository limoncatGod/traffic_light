#include "driver_traffic_light.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 23455
#define BUF_MAX 256

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "ERROR: failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    // подключение к демону
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("ERROR: failed to connect to the daemon\n");
        exit(EXIT_FAILURE);
    } else
    {
        printf("Succesfully connected to daemon!\n");
    }

    printf("Commands: \n\tstatus\n\tpoweron\n\tpoweroff\n\tkill_daemon\n\tfind_color\n\tset_color_red\n\tset_color_yellowgreen\n\tset_color_green\n\tset_color_yellowred\n\n");

    char buf[BUF_MAX];
    int symb_c;
    while (1) {
        memset(buf, 0, BUF_MAX);
        printf("Enter command: ");
        scanf("%s", buf);
        symb_c = write(sockfd, buf, strlen(buf));
        if (symb_c < 0)
        {
            printf("ERROR: failed to write to the daemon\n");
            exit(EXIT_FAILURE);
        }

        memset(buf, 0, BUF_MAX);
        symb_c = read(sockfd, buf, BUF_MAX);
        if (symb_c < 0)
        {
            printf("ERROR: failed to read the response from daemon\n");
            exit(EXIT_FAILURE);
        }
        printf("Response from daemon: %s\n", buf);
    }
}
