#include "driver_traffic_light.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 23455
#define BUF_MAX 512

int main()
{
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (sockfd < 0)
    {
        fprintf(stderr, "[DAEMON]: failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        fprintf(stderr, "[DAEMON]: failed to bind sket to port %d\n", PORT);
        shutdown(sockfd, SHUT_RDWR);
        exit(EXIT_FAILURE);
    }


    while (1)
    {
        int client_sockfd; // сокет, через который будем общаться с клиентом
        struct sockaddr_in client_address;
        
        // на listen программа будет висеть до того момента, 
        // пока клиент не совершит попытку подключения к сокету
        if (listen(sockfd, 1) < 0) // слушаем сокет на предмет подключений к нему
        {
            fprintf(stderr, "[DAEMON]: failed to listen socket\n");
            shutdown(sockfd, SHUT_RDWR);
            exit(EXIT_FAILURE);
        }

        // принимаем подключение от клиента
        socklen_t clilen = sizeof(client_address);
        client_sockfd = accept(sockfd, (struct sockaddr*)&client_address, &clilen);
        if (client_sockfd < 0)
        {
            fprintf(stderr, "[DAEMON]: failed to accept client connection\n");
            shutdown(sockfd, SHUT_RDWR);
            exit(EXIT_FAILURE);
        }

        char buf[BUF_MAX]; // сюда будем читать из сокета
        int symb_c; // а сюда писать сколько символов прочитали
        

        
        while (1)
        {
            memset(buf, 0, BUF_MAX);
            symb_c = read(client_sockfd, &buf, BUF_MAX);
            
            if (symb_c < 0)
            {
                fprintf(stderr, "[DAEMON]: error reading from socket\n");
                close(client_sockfd);
                shutdown(sockfd, SHUT_RDWR);
                exit(EXIT_FAILURE);
            }
            
            // функции API
            if (!strcmp(buf, "kill_daemon"))
            {
                strcpy(buf, "Daemon is killed");
                close(client_sockfd);
                shutdown(sockfd, SHUT_RDWR);
                return 0;
            } 
            else 
            if (!strcmp(buf, "poweron"))
            {
                memset(buf, 0, BUF_MAX);
                if (traffic_light_is_powered())
                    strcpy(buf, "Device is already working");
                else
                    strcpy(buf, "device started");
                driver_traffic_light_power();
            } 
            else 
            if (!strcmp(buf, "poweroff"))
            {
                memset(buf, 0, BUF_MAX);
                if (!traffic_light_is_powered())
                    strcpy(buf, "the device is already turned off");
                else
                    strcpy(buf, "device stopped");
                driver_traffic_light_power();
            } 
            else 
            if (!strcmp(buf, "status"))
            {
                memset(buf, 0, BUF_MAX);
                if (traffic_light_is_powered())
                    strcpy(buf, "device is turned on");
                else
                    strcpy(buf, "device is turned off");
            } 
            else
            if (!strcmp(buf, "find_color"))
            {
                memset(buf, 0, BUF_MAX);
                if(traffic_light_is_powered()){
                    FILE* data = fopen("state_light.txt", "r");
                    SignalColor color = getSignalColor(data);
                    printf("%d", color);
                    fclose(data);
                    switch (color) {
                        case RED:
                            sprintf(buf, "Now color is RED");
                            sleep(1);
                            break;
                        case YELLOWTOGREEN:
                            sprintf(buf, "Now color is YELLOWTOGREEN");
                            sleep(1);
                            break;
                        case GREEN:
                            sprintf(buf, "Now color is GREEN");
                            sleep(1);
                            break;
                        case YELLOWTORED:
                            sprintf(buf, "Now color is YELLOWTORED");
                            sleep(1);
                            break;
                        default:
                            sprintf(buf, "Color is invalid");
                            sleep(1);
                            break;
                    }
                }
                else
                    strcpy(buf, "device is turned off");
            } 
            else
            if (!strcmp(buf, "set_color_red"))
            {
                memset(buf, 0, BUF_MAX);
                if(traffic_light_is_powered()){
                    FILE* data = fopen("state_light.txt", "w");
                    setSignalColor(RED, data);
                    fclose(data);
                    sprintf(buf, "RED color is set");
                    }
                else
                    strcpy(buf, "device is turned off");
            } 
            else
            if (!strcmp(buf, "set_color_yellowgreen"))
            {
                memset(buf, 0, BUF_MAX);
                if(traffic_light_is_powered()){
                    FILE* data = fopen("state_light.txt", "w");
                    setSignalColor(YELLOWTOGREEN, data);
                    fclose(data);
                    sprintf(buf, "YELLOWTOGREEN color is set");
                    }
                else
                    strcpy(buf, "device is turned off");
            } 
            else
            if (!strcmp(buf, "set_color_green"))
            {
                memset(buf, 0, BUF_MAX);
                if(traffic_light_is_powered()){
                    FILE* data = fopen("state_light.txt", "w");
                    setSignalColor(GREEN, data);
                    fclose(data);
                    sprintf(buf, "GREEN color is set");
                    }
                else
                    strcpy(buf, "device is turned off");
            } 
            else
            if (!strcmp(buf, "set_color_yellowred"))
            {
                memset(buf, 0, BUF_MAX);
                if(traffic_light_is_powered()){
                    FILE* data = fopen("state_light.txt", "w");
                    setSignalColor(YELLOWTORED, data);
                    fclose(data);
                    sprintf(buf, "YELLOWTORED color is set");
                    }
                else
                    strcpy(buf, "device is turned off");
            } 
            else
            {
                memset(buf, 0, BUF_MAX);
                strcpy(buf, "invalid request");
            }

            symb_c = write(client_sockfd, buf, strlen(buf));
            if (symb_c < 0)
            {
                fprintf(stderr, "[DAEMON]: error writing to socket\n");
                close(client_sockfd);
                shutdown(sockfd, SHUT_RDWR);
                exit(EXIT_FAILURE);
            }
        }
    }
    
    shutdown(sockfd, SHUT_RDWR);
    return 0;
}
