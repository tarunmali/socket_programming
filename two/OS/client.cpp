#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess

//for strcmp
#include <string.h>
#include <pthread.h>


void *receiveMessages(void *arg) {
     int client_socket = *((int *)arg);
    char response[256];
    ssize_t bytesRead;

    while ((bytesRead = recv(client_socket, response, sizeof(response) - 1, 0)) > 0) {
        response[bytesRead] = '\0';
        printf("Server: %s", response);
    }

    // Handle disconnection or error here
    printf("Disconnected from the server\n");

    // Exit the client application when the server disconnects
    exit(1);

    return NULL;
}

int main(){
    int client_socket=socket(AF_INET,SOCK_STREAM,  0);
    //@todo
    //socket file descriptor is returned
    //socket is implemented like a file in you sysytem
    //?

    //we can use this socket to connect to some remote socket
    

    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(2000);
    // server_address.sin_addr.s_addr=INADDR_ANY;
    // char *ip="172.253.115.100";
    char *ip="127.0.0.1";
    inet_pton(AF_INET,ip,  &server_address.sin_addr.s_addr);

    int connection_status=connect(client_socket, 
        (struct sockaddr *)& server_address,
            sizeof(server_address)
        );

    if(connection_status==0){
        printf("Successfull connection of socket to server\n");
    }
    else if(connection_status==-1){
        printf("Unsuccessfull connection of socket to server\n");        
    }

    char *line = NULL;
    size_t lineSize = 0;
    printf("Type and will send.... (type exit to quit)\n");

    // Create a thread to handle server responses
    pthread_t id;
    pthread_create(&id, NULL, receiveMessages, &client_socket);

    while (1) {
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if (charCount > 0) {
            if (strcmp(line, "exit\n") == 0) break;
            ssize_t amountWasSent = send(client_socket, line, charCount, 0);
            if (amountWasSent == -1) {
                perror("send");
                break;
            }
        }
    }

    // Close the client socket and join the receive thread
    close(client_socket);
    pthread_detach(id);
    free(line);

    return 0;

}