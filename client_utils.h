#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include "commons.h"

void display_menu();

void handle_client_cmd(int server_sck);
void get_server_listing(int server_sck);





#endif