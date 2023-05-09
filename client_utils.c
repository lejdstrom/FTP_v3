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
    FTP_COMMANDS choice;

    do
    {
        display_menu();
        char input[BUFF_SIZE];
        memset(input, 0, BUFF_SIZE);
        puts("Enter a command");
        fgets(input, BUFF_SIZE, stdin);

        // dl <filename>
        // up <filename>
        // ls
        // exit
        choice = parse_ftp_cmd(input);

        switch (choice)
        {
        case DOWNLOAD:
            send(server_sck, input, BUFF_SIZE, 0);
            recv_file_from_socket(input, server_sck, SERVER_TO_CLIENT);
            memset(input, 0, BUFF_SIZE);
            break;

        case UPLOAD:
            send(server_sck, input, BUFF_SIZE, 0);
            send_file_to_socket(input, server_sck, CLIENT_TO_SERVER);
            memset(input, 0, BUFF_SIZE);
            break;

        case LIST:
            get_server_listing(server_sck);
            break;

        case EXIT:
            break;

        default:
            puts("unknow command");
            break;
        }

    } while (choice != EXIT);
}

void get_server_listing(int server_sck)
{

}