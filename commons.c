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
    FILE * file_ptr = NULL;
    char file_path[BUFF_SIZE];
    char buffer[BUFF_SIZE];
    long int file_size;

    // from where we read ?
    // download
    if(direction == SERVER_TO_CLIENT)
    {
        snprintf(file_path, sizeof(file_path), "server_files/%s", filename);

    }       // upload
    else if (direction == CLIENT_TO_SERVER)
    {
        snprintf(file_path, sizeof(file_path), "client_files/%s", filename);
    }


    file_ptr = fopen(filename, "rb");

    if(file_ptr == NULL)
    {
        perror("Error opening file");
        return;
    }

    file_size = get_file_size(file_ptr);

    // send file size
    send(socket, &file_size, sizeof(long int), 0);

    




    

}
int recv_file_from_socket(const char * filename, int socket, DIRECTION direction)
{

}
long int get_file_size(FILE * file)
{
    long int file_size = 0;
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    return file_size;
}