#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess

//for strcmp
#include <string.h>

int main(){
    int client_socket=socket(AF_INET,SOCK_STREAM,  0);

    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(2000);
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
    close(client_socket);

    return 0;
}