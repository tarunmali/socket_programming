//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess
#include <pthread.h>

// struct AcceptedSockey{
//     int acceptedSocket;
//     int error;
//     bool accpetedSuccessfully;
// }

void *handleIndividualConnections(void *arg){
    int client_socket = *((int *)arg);
    char response[256];

    while (1) {
        ssize_t  amountReceived=recv(client_socket,response, sizeof(response),0);
        if(amountReceived>0){
            response[amountReceived]='\0';
            printf("Server received %s\n",response);
        }
        if(amountReceived<=0){
            printf("Client disconnected\n");
            close(client_socket);            
            break;
        } 
    }

    return NULL;

}
// void startAccepetingIncomingConnections(int server_socket){

//     // pthread_t id;
//     // pthread_create(&id,NULL,handleIndividualConnections,&server_socket);
// }

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
        printf("Client connected\n");

        // Create a new thread to handle this client
        pthread_t id;
        pthread_create(&id, NULL, handleIndividualConnections, &client_socket);

        // Detach the thread so its resources are automatically cleaned up when it exits
        pthread_detach(id);
    }


    //p1
    //p2 address of remote client
    //sizeof adddress
    // startAccepetingIncomingConnections(server_socket);
    // int client_socket= accept(server_socket, NULL, NULL);
    // //accpet is blocking call
    // //
    // //will block the main thread


    // //last parameter is optional
    // char response[1024];

    // while(1){
    //     ssize_t  amountReceived=recv(client_socket,response, sizeof(response),0);
    //     if(amountReceived>0){
    //         response[amountReceived]='\0';
    //         printf("Server received %s\n",response);
    //     }
    //     if(amountReceived==0) break;
    // }


    // // send(client_socket, server_message, sizeof(server_message), 0);

    // close(client_socket);
    // shutdown(server_socket,SHUT_RDWR);

    return 0;
}