#include "commons.h"
#include "server_utils.h"


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == SOCKET_ERROR) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, MAX_CONNECTIONS) == SOCKET_ERROR) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        socklen_t len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, (socklen_t*)&len);

        if(client_sock == SOCKET_ERROR)
        {
            perror("Accept Failed");
            continue;
        }

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, client_routine, (void*)client_sock);
    }
    
    return 0;
}