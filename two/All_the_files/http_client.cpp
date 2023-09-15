#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() anf //converting network addressess

int main(int argc, char *argv[]){
    char *ip=argv[1]; 

    int client_socket=socket(AF_INET,SOCK_STREAM,  0);

    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(80);
    // server_address.sin_addr.s_addr=INADDR_ANY;
    inet_pton(AF_INET,ip, &server_address.sin_addr);

    int connection_status=connect(client_socket, 
    (struct sockaddr *)& server_address,
        sizeof(server_address)
    );
    if(connection_status==0){
        printf("Successfull\n");
    }
    else if(connection_status==-1){
        printf("Unsuccessfull\n");        
    }

    char request[]="GET / HTTP/1.1\r\n\r\n ";
    char response[4096];

    send(client_socket,request,sizeof(request),0);
    recv(client_socket,&response, sizeof(response),0);
    printf("response from the http server %s\n", response);
    close(client_socket);



    return 0;
}
