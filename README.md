## A simple ftp application
Using tcp/ip, socket programming.

Theres is two programm: Server and client.
Client can ask server to run the followig commands:  

**ls:**  list all file in the server directorie  
**up <filename>:**  upload a file to server
**dl <filename>:**  download a file from server

(More options should come, like mkdir ...)

## How to Run
```bash
make server && ./server <port_number>
make client && ./client <port_number>
```