#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 

#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons()

#include <string.h>

int main(){


    //one liner html file
    // FILE* html_data=fopen("oneLine.html","r");
    // char response_data[1024]={'\0'};
    // fgets(response_data,1024,html_data);

    // multiline html file
    FILE* html_data=fopen("index.html","r");
    char buffer[128];
    char response_data[2048]={'\0'};
    while(fgets(buffer, sizeof(buffer), html_data)){
            strcat(response_data, buffer);
        }

    char http_header[2048]="HTTP/1.1 200 OK\r\n\n";
    strcat(http_header,response_data);

    //create the server socket
    int server_socket=socket(AF_INET,SOCK_STREAM,  0);

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(8001);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //bind
    bind(server_socket, 
        (struct sockaddr *)& server_address,
        sizeof(server_address)
    ); 

    //listen
     listen(server_socket, 5);

    int client_socket;
    while(1){
        client_socket= accept(server_socket, NULL, NULL);        
        send(client_socket,http_header, sizeof(http_header),0);
        // close(client_socket);
    }


    //accept



}