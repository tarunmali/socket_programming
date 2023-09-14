//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess
#include <pthread.h>


int acceptedSockets[10];
int cntAcceptedSockets=0; 

void sendReceivedMessagesToOtherClients(char * response, int itself){\
    for(int i=0;i<cntAcceptedSockets;i++)
        if(acceptedSockets[i]!=itself)
            send(acceptedSockets[i], response, sizeof(response), 0);   
}

void *handleIndividualConnections(void *arg){
    int client_socket = *((int *)arg);
    char response[256];

    while (1) {
        ssize_t  amountReceived=recv(client_socket,response, sizeof(response),0);
        if(amountReceived>0){
            response[amountReceived]='\0';
            printf("Server received %s\n",response);
            sendReceivedMessagesToOtherClients(response, client_socket);
        }
        if(amountReceived<=0){
            printf("Client disconnected\n");
            close(client_socket);            
            break;
        } 
    }

    return NULL;

}

void startAccepetingIncomingConnections(int server_socket){


    // pthread_t id;
    // pthread_create(&id,NULL,handleIndividualConnections,&server_socket);
}

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
    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        acceptedSockets[cntAcceptedSockets++]=client_socket;
        printf("Client %d connected\n",cntAcceptedSockets);

        // Create a new thread to handle this client
        pthread_t id;
        pthread_create(&id, NULL, handleIndividualConnections, &client_socket);

        // Detach the thread so its resources are automatically cleaned up when it exits
        pthread_detach(id);
    }

    return 0;
}