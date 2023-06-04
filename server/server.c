#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "data.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void start_server()
 { int server_fd, new_socket; struct sockaddr_in address; int addrlen = sizeof(address); char buffer[BUFFER_SIZE] = {0};

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { perror("socket failed"); exit(EXIT_FAILURE); }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    { perror("setsockopt"); exit(EXIT_FAILURE); }
   address.sin_family = AF_INET; address.sin_addr.s_addr = INADDR_ANY; address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    { perror("bind failed"); exit(EXIT_FAILURE); }

  if (listen(server_fd, 3) < 0) { perror("listen"); exit(EXIT_FAILURE); }

  if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    { perror("accept"); exit(EXIT_FAILURE); }

    int valread = read(new_socket , buffer, BUFFER_SIZE);
    char *url = strtok(buffer, ",");
    char *name = strtok(NULL, ",");
    char *password = strtok(NULL, ",");

    set_data(url, name, password);

}

int main() { init_data(); start_server();  free_data();  return 0; }
