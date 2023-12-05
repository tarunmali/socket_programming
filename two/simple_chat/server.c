//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess


#include <string.h>

int main(){

    char server_message[256]="You have reached the server";
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
   

    int listen_result=listen(server_socket, 5);
     if(listen_result==0){
        printf("socket listening successfully\n");
    }
    else if(listen_result==-1){
        printf("socket bound unsuccessfully\n");        
    }    


    int client_socket= accept(server_socket, NULL, NULL);
    //accpet is blocking call
    //


    char *line=NULL;
    size_t lineSize=0;
    printf("Type and will send....(type exit)\n");

    while(1){
        ssize_t charCount= getline(&line,&lineSize,stdin);
        if(charCount>0){
            if(strcmp(line,"exit\n")==0) break;
            ssize_t amountWasSent=send(client_socket,line,strlen(line),0);
        }
    }


    char response[1024];

    while(1){
        ssize_t  amountReceived=recv(client_socket,response, sizeof(response),0);
        if(amountReceived>0){
            response[amountReceived]='\0';
            printf("Server received %s\n",response);
        }
        if(amountReceived==0) break;
    }


    close(client_socket);
    shutdown(server_socket,SHUT_RDWR);

    return 0;
}