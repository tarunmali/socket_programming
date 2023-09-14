//we need to bind the socket to an ip and port where it can listen
//for connections


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 

#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons()

int main(){
    //create a string to hold data to send to client
    char server_message[256]="You have reached the server";
    //create the server socket
    int server_socket=socket(AF_INET,SOCK_STREAM,  0);

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //bind the socket to our specifiwed ip and port
    bind(server_socket, 
        (struct sockaddr *)& server_address,
        sizeof(server_address)
    ); 

    //p1
    //p2 backlog how many connections can be waiting for this socket at one point of time
    listen(server_socket, 5);

    //p1
    //p2,  structures that would contain the address of the client connection
    //sizeof adddress
    int client_socket= accept(server_socket, NULL, NULL);
    

    //last parameter is optional
    send(client_socket, server_message, sizeof(server_message), 0);

    close(server_socket);


    return 0;

}
