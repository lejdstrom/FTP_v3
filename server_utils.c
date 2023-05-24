#include "server_utils.h"

void* client_routine(void *args)
{
    //pthread_detach(pthread_self());

    #ifdef DEBUG
        printf("\tDEBUG: In client_routine func\n");
    #endif

    int client_socket = (int)args;
    char buffer[BUFF_SIZE];
    size_t bytes_recv = 0;
    char * filename = NULL;

    do
    {
        memset(buffer, 0, BUFF_SIZE);
        bytes_recv = recv(client_socket, buffer, BUFF_SIZE - 1, 0);
        // null terminate receved string
        buffer[bytes_recv] = 0;

        #ifdef DEBUG
            printf("\tDEBUG: buffer: %s\n", buffer);
        #endif

        switch (parse_ftp_cmd(buffer))
        {
        case DOWNLOAD:
            filename = strtok(buffer + strlen("dl "), "\n");
                #ifdef DEBUG
                    printf("\tDEBUG: filename: %s\n", filename);
                #endif
            send_file_to_socket(filename, client_socket, SERVER_TO_CLIENT);
            //send_file_to_client(filename, client_socket);
            memset(buffer, 0, BUFF_SIZE);
            break;
        
        case UPLOAD:
            filename = strtok(buffer + strlen("up "), "\n");
                #ifdef DEBUG
                    printf("\tDEBUG: filename: %s\n", filename);
                #endif

            recv_file_from_socket(filename, client_socket, CLIENT_TO_SERVER);
            //recv_file_from_client(filename, client_socket);
            memset(buffer, 0, BUFF_SIZE);
            break;

        case LIST:
            break;

        case EXIT:
            goto exit;
            break;

        default:
            break;
        }

    } while (bytes_recv > 0);
    
exit:
    close(client_socket);
    return NULL;
}