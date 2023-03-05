//The client program first creates a socket and sets the IP address and port number of the server it wants to connect to. 
//It then connects to the server using the connect() function. 
//Once the connection is established, the client enters a loop where it repeatedly prompts the user to enter a message, 
//sends the message to the server using the send() function, receives a reply from the server using the recv() function, 
//and prints the reply to the console. 
//The loop continues until the user types "exit", at which point the program closes the socket and terminates.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int socket_desc;
    struct sockaddr_in server;
    char message[2000], server_reply[2000];
    
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket Created");
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    server.sin_family = AF_INET;
    server.sin_port = htons(8888); // Server port
    
    // Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connect failed. Error");
        return 1;
    }
    
    puts("Connected to the server\n");
    
    // Communicate with server
    while (1) {
        printf("Enter message: ");
        scanf("%s", message);
        
        // Send data to server
        if (send(socket_desc, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }
        
        // Receive data from server
        if (recv(socket_desc, server_reply, 2000, 0) < 0) {
            puts("Receive failed");
            break;
        }
        
        //puts("Server reply: ");
        //puts(server_reply);
        printf("Server reply: %s\n",server_reply);
    }
    
    close(socket_desc);
    return 0;
}
