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


    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Warning creating socket");
        return 1;
    }

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr) < 0))
    {
        perror("Warning connecting");
        return 1;
    }

    handle_client_cmd(sockfd);

    return 0;
}