//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess

#include<string.h>

int main(){

    int server_socket=socket(AF_INET,SOCK_STREAM,  0);

    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(2000);
    server_address.sin_addr.s_addr=INADDR_ANY;
 


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

    int client_socket= accept(server_socket, NULL, NULL);

    char client_response[4096],server_message[4096];

    while(1){
        ssize_t  amountReceived=recv(client_socket,client_response, sizeof(client_response),0);
        if(amountReceived>0){
            client_response[amountReceived]='\0';
            printf("Server received %s\n",client_response);
            strcpy(server_message,client_response);
            send(client_socket, server_message, strlen(server_message), 0);
        }
        if(amountReceived==0) break;
    }


    close(server_socket);

    return 0;
}