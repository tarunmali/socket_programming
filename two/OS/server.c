//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess
#include <pthread.h>


int acceptedClients[10];
int cntAcceptedClients=0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void sendToAllClients(const char *message, int sender_socket) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < cntAcceptedClients; i++) {
        if (acceptedClients[i] != sender_socket) {
            send(acceptedClients[i], message, sizeof(message), 0);
        }
    }
    pthread_mutex_unlock(&mutex);
}


void *handleIndividualConnections(void *arg){

    int client_socket = *((int *)arg);
    pthread_mutex_lock(&mutex);
    acceptedClients[cntAcceptedClients++] = client_socket;
    pthread_mutex_unlock(&mutex);
    char response[256];

    while (1) {
        ssize_t  amountReceived=recv(client_socket,response, sizeof(response),0);
        if(amountReceived>0){
            response[amountReceived]='\0';
            printf("Server received %s\n",response);
            sendToAllClients(response, client_socket);
        }
        if(amountReceived<=0){
            printf("Client disconnected\n");
            close(client_socket);  


            pthread_mutex_lock(&mutex);
            for (int i = 0; i < cntAcceptedClients; i++) {
                if (acceptedClients[i] == client_socket) {
                    // Remove the client socket from the list
                    for (int j = i; j < cntAcceptedClients - 1; j++) {
                        acceptedClients[j] = acceptedClients[j + 1];
                    }
                    cntAcceptedClients--;
                    break;
                }
            }
            pthread_mutex_unlock(&mutex);

            break;
        } 
    }
    return NULL;
}


int main(){

    int server_socket=socket(AF_INET,SOCK_STREAM,  0);


    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(2000);
    server_address.sin_addr.s_addr=INADDR_ANY;


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
    

    return 0;
}