#include "server_utils.h"

void* client_routine(void *args)
{
    pthread_detach(pthread_self());

    int client_socket = (int)args;
    char buffer[BUFF_SIZE];
    size_t bytes_recv = 0;
    char * filename = NULL;

    do
    {
        bytes_recv = recv(client_socket, buffer, BUFF_SIZE - 1, 0);
        // null terminate receved string
        buffer[bytes_recv] = 0;

        switch (parse_ftp_cmd(buffer))
        {
        case DOWNLOAD:
            filename = strtok(buffer + strlen("dl "), "\n");
                #ifdef DEBUG
                    printf("\tDEBUG: filename: %s\n", filename);
                #endif
            send_file_to_socket(filename, client_socket, SERVER_TO_CLIENT);
            break;
        
        case UPLOAD:
            filename = strtok(buffer + strlen("up "), "\n");
                #ifdef DEBUG
                    printf("\tDEBUG: filename: %s\n", filename);
                #endif

            recv_file_from_socket(filename, client_socket, CLIENT_TO_SERVER);
            break;

        case LIST:
            break;

        case EXIT:
            close(client_socket);
            return NULL;
            break;

        default:
            break;
        }

    } while (bytes_recv > 0);
    

    return NULL;
}