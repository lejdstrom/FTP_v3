#include "commons.h"

FTP_COMMANDS parse_ftp_cmd(const char * client_message)
{
    if (!strncmp(client_message, "ls", 2))
    {
        return LIST;
    }
    else if (!strncmp(client_message, "dl", 2))
    {
        return DOWNLOAD;
    }
    else if (!strncmp(client_message, "up", 2))
    {
        return UPLOAD;
    }
    else if(!strncmp(client_message, "exit", 5))
    {
        return EXIT;
    }
}



int send_file_to_socket(const char * filename, int socket, DIRECTION direction)
{

}
int recv_file_from_socket(const char * filename, int socket, DIRECTION direction)
{

}
int get_file_size(FILE * file)
{

}