#ifndef COMMONS_H
#define COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <dirent.h>


#define BUFF_SIZE (1024)
#define LOCAL_HOST "127.0.0.1"

typedef enum{
    LIST, UPLOAD, DOWNLOAD, EXIT /*MKDIR, CD*/
}FTP_COMMANDS;

typedef enum{
    SERVER_TO_CLIENT, CLIENT_TO_SERVER
}DIRECTION;

FTP_COMMANDS parse_ftp_cmd(const char * client_message);

int send_file_to_socket(const char * filename, int socket, DIRECTION direction);
int recv_file_from_socket(const char * filename, int socket, DIRECTION direction);
int get_file_size(FILE * file);


#endif