#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess

int main(){
    int client_socket=socket(AF_INET,SOCK_STREAM,  0);
    //@todo
    //socket file descriptor is returned
    //socket is implemented like a file in you sysytem
    //?

    //we can use this socket to connect to some remote socket

    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(80);
    // server_address.sin_addr.s_addr=INADDR_ANY;
    char *ip="172.253.115.100";
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


    // char request[]="GET / HTTP/1.1\r\n\r\n ";
    char request[]="GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    //there is no payload in our request

    char response[4096];

    //send a request to the server from the same client_socket
    send(client_socket,request,sizeof(request),0);

    //receve a response to the client_socket from server
    recv(client_socket,&response, sizeof(response),0);


    printf("Response from the server: %s\n", response);

    close(client_socket);




    return 0;
}