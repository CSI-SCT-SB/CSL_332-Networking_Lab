// This code creates a socket, binds it to a local address, listens for incoming connections, accepts incoming connections. // And communicates with the client by echoing messages back to it. 
// When the client disconnects, the server closes the connection and terminates.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[2000];
    
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888); // Server port
    
    // Bind socket to local address
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed. Error");
        return 1;
    }
    
    puts("Bind done");
    
    // Listen for incoming connections
    listen(socket_desc, 3);
    
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    
    // Accept incoming connection
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0) {
        perror("Accept failed");
        return 1;
    }
    
    puts("Connection accepted");
    
    // Communicate with client
    while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        // Send data to client
        write(client_sock, client_message, strlen(client_message));
    }
    
    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("Receive failed");
        return 1;
    }
    
    close(client_sock);
    return 0;
}