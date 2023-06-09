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
    char * new_file_name = filename + 3;
    long int file_size;
    size_t bytes_read, byte_sent;

    #ifdef DEBUG
        printf("\tDEBUG: in send_file\n");
    #endif

    // from where we read ?
    // download
    if(direction == SERVER_TO_CLIENT)
    {
        snprintf(file_path, sizeof(file_path), "server_files/%s", filename);

    }       // upload
    else if (direction == CLIENT_TO_SERVER)
    {
        snprintf(file_path, sizeof(file_path), "client_files/%s", new_file_name);
    }

    #ifdef DEBUG
        printf("\tDEBUG: filepath: %s\n", file_path);
    #endif

    // remove new line
    file_path[strcspn(file_path, "\n")] = 0;
    file_ptr = fopen(file_path, "rb");

    if(file_ptr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    file_size = get_file_size(file_ptr);

    // send file size
    send(socket, &file_size, sizeof(long int), 0);
    #ifdef DEBUG
        printf("\tfile size sent: %ld\n", file_size);
    #endif

    while (file_size > 0)
    {
        bytes_read = fread(buffer, sizeof(char), BUFF_SIZE, file_ptr);

        if(bytes_read < 0)
        {
            perror("Error reading file");
            return -1;
        }

        byte_sent = send(socket, buffer, bytes_read, 0); //write(socket, buffer, bytes_read)

        if(byte_sent < 0)
        {
            perror("Error sending files");
            return -1;
        }

        #ifdef DEBUG
        printf("\tsent: %ld\nread: %ld\n", byte_sent, bytes_read);
        #endif

        file_size -= bytes_read;
    }

    
    fclose(file_ptr);

    /*
    if(direction == CLIENT_TO_SERVER)
    {
        char ack[BUFF_SIZE];
        recv(socket, ack, BUFF_SIZE, 0);
    }
    */

    //log message
    return 0;
}

int recv_file_from_socket(const char * filename, int socket, DIRECTION direction)
{
    FILE * file_ptr = NULL;
    char * new_file_name = filename + 3;
    char file_path[BUFF_SIZE];
    char buffer[BUFF_SIZE];
    long int file_size;
    long int copy_file_size, recv_acc = 0;
    size_t bytes_receved, byte_write;

    #ifdef DEBUG
        printf("\tin recv_file\n\t: new file name: %s\n", new_file_name);
    #endif

    // where we create the file ?
    if(direction == SERVER_TO_CLIENT)
    {
        snprintf(file_path, sizeof(file_path), "client_files/%s", new_file_name);

    }
    else if (direction == CLIENT_TO_SERVER)
    {
        snprintf(file_path, sizeof(file_path), "server_files/%s", filename);
    }

    #ifdef DEBUG
        printf("\tfile_path: %s\n", file_path);
    #endif

    file_ptr = fopen(file_path, "wb");

    if(file_ptr == NULL)
    {
        perror("Error creating file");
        return -1;
    }

    // recv size of file
    //recv(socket, &file_size, sizeof(long int), 0);
    recv(socket, &file_size, sizeof(long int), 0);

    #ifdef DEBUG
        printf("\tfile size recv: %ld\n", file_size);
    #endif

    if(file_size <= 0)
    {
        perror("Empty file");
        return -1;
    }

    copy_file_size = file_size;

    while (file_size > 0)
    {
        bytes_receved = recv(socket, buffer, BUFF_SIZE, 0);
        byte_write = fwrite(buffer, sizeof(char), bytes_receved, file_ptr);

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
        printf("%ld\/%ld\n", recv_acc, copy_file_size);
        
        file_size -= bytes_receved;
        
    }

    /*
    if(direction == SERVER_TO_CLIENT)
    {
        char ack[BUFF_SIZE];
        recv(socket, ack, BUFF_SIZE, 0);
    }
    */

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