//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess

int main(){
    //create a string to hold data to send to client
    char server_message[256]="You have reached the server";
    //create the server socket
    int server_socket=socket(AF_INET,SOCK_STREAM,  0);

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(2000);
    server_address.sin_addr.s_addr=INADDR_ANY;
    //listen for any incoming address 

    //bind the socket to our specifiwed ip and port
    int result_bind=bind(server_socket, 
        (struct sockaddr *)& server_address,
        sizeof(server_address)
    ); 

     if(result_bind==0){
        printf("socket bound successfully\n");
    }
    else if(result_bind==-1){
        printf("socket bound unsuccessfully\n");        
    }
   
    //the incpming sockets will coonect to the server socket  
    //p1
    //p2 backlog how many connections can be waiting for this socket at one point of time
    //before calling the accept function
    //server can queue upto 5 connections
    //DOUBT
    int listen_result=listen(server_socket, 5);
     if(listen_result==0){
        printf("socket listening successfully\n");
    }
    else if(listen_result==-1){
        printf("socket bound unsuccessfully\n");        
    }    

    //p1
    //p2 address of remote client
    //sizeof adddress
    int client_socket= accept(server_socket, NULL, NULL);
    //accpet is blocking call
    //

    //last parameter is optional
    char response[4096];
    recv(client_socket,&response, sizeof(response),0);
    printf("Server received %s/n",response);

    // send(client_socket, server_message, sizeof(server_message), 0);


    close(server_socket);

    return 0;
}