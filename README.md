## A simple ftp application
Using TCP/IP and socket programming.

Theres are two programs: the server and the client.  
Client can ask the server to execute the following commands:  

- **ls:**  list all files in the server directory  
- **up filename:**   upload a file to the server  
- **dl filename:**   download a file from the server

(More options should be added, such as mkdir ...)

## How to Run
```bash
make server && ./server <port_number>
make client && ./client <port_number>
```