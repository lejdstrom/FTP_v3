#include "client_utils.h"

void display_menu()
{
    puts("\nWelcome to ftp client\n");
    puts("Call one of the following functions:");

    printf("dl <filename>\t\tDownload file\n");
    printf("up <filename\t\tUpload file\n");
    printf("ls\t\t\tList files in server\n");
    printf("exit\t\t\tClose the client\n");
}

void handle_client_cmd(int server_sck)
{
    char input[BUFF_SIZE];

    puts("Enter a command");
    fgets(input, BUFF_SIZE, stdin);

    // dl <filename>
    // up <filename>
    // ls
    // exit

    switch (parse_ftp_cmd(input))
    {
    case DOWNLOAD:
        break;

    case UPLOAD:
        break;

    case LIST:
        break;

    case EXIT:
        break;
    
    default:
        break;
    }

}