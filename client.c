#include "commons.h"
#include "client_utils.h"


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int sockfd;
    struct sockaddr_in servaddr = {};

    /* Connect to the server */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(LOCAL_HOST);
    servaddr.sin_port = htons(atoi(argv[1]));

    



    return 0;
}

