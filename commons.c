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
    else
    {
        return EXIT;
    }
}

// return 0 if succes
// return -1 if fail
int send_file_to_socket(const char * filename, int socket, DIRECTION direction)
{
    FILE * file_ptr = NULL;
    char file_path[BUFF_SIZE];
    char buffer[BUFF_SIZE];
    long int file_size;
    size_t bytes_read, byte_sent;

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

    #ifdef DEBUG
        printf("\tDEBUG: filename: %s\n", filename);
    #endif

    file_ptr = fopen(filename, "rb");

    if(file_ptr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    file_size = get_file_size(file_ptr);

    // send file size
    send(socket, &file_size, sizeof(long int), 0);

    while (file_size > 0)
    {
        bytes_read = fread(buffer, sizeof(char), BUFF_SIZE, file_ptr);

        if(bytes_read < 0)
        {
            perror("Error reading file");
            return -1;
        }

        byte_sent = send(socket, buffer, BUFF_SIZE, 0);

        if(byte_sent < 0)
        {
            perror("Error sending files");
            return -1;
        }

        #ifdef DEBUG
        printf("\tDEBUG: sent: %ld\nread: %ld\n", byte_sent, bytes_read);
        #endif

        file_size -= bytes_read;
    }
    
    fclose(file_ptr);

    //log message
    return 0;
}

int recv_file_from_socket(const char * filename, int socket, DIRECTION direction)
{
    FILE * file_ptr = NULL;
    char file_path[BUFF_SIZE];
    char buffer[BUFF_SIZE];
    long int file_size;
    long int copy_file_size, recv_acc = 0;
    size_t bytes_receved, byte_write;

    // where we create the file ?
    if(direction == SERVER_TO_CLIENT)
    {
        snprintf(file_path, sizeof(file_path), "client_files/%s", filename);

    }
    else if (direction == CLIENT_TO_SERVER)
    {
        snprintf(file_path, sizeof(file_path), "server_files/%s", filename);
    }


    #ifdef DEBUG
        printf("\tDEBUG: filename: %s\n", filename);
    #endif

    file_ptr = fopen(filename, "wb");

    if(file_ptr == NULL)
    {
        perror("Error creating file");
        return -1;
    }

    // recv size of file
    recv(socket, &file_size, sizeof(long int), 0);
    copy_file_size = file_size;

    do
    {
        bytes_receved = recv(socket, buffer, BUFF_SIZE, 0);
        byte_write = fwrite(buffer, sizeof(char), BUFF_SIZE, file_ptr);

        if(byte_write < 0)
        {
            perror("Error writing file");
            return -1;
        }

        if(bytes_receved < 0)
        {
            perror("Error receving file");
            return -1;
        }

        // progress bar
        recv_acc += bytes_receved;
        printf("%ld/%ld\n", recv_acc, copy_file_size);
        
        file_size -= bytes_receved;
        
    } while (file_size > 0 && bytes_receved > 0);

    fclose(file_ptr);
    return 0;

}
long int get_file_size(FILE * file)
{
    long int file_size = 0;
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    return file_size;
}