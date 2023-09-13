//client socket creation
//connected to a remote address with connect
//? we can retrieve data with receve

#include <stdio.h>
#include <stdlib.h>
//why?


#include <sys/types.h>
#include <sys/socket.h>  

//to store address  information
//ip address port of the remote socket we want to connect to
#include <netinet/in.h>

#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons()

int main(){
    //domain of socket, => since it is internet socket , AF_INET
    //defined in header file


    //@todo see datagram 
    //SOCK_STREAM tupe of the socket, tcp socket (connection socket)
    //vs the data gram socket which is UDP


    //protoco: we are using 0, as we are already using tcp
    //which is the default protocol
    //we might want to describe it explicitly ,
    // for ex  raw sockets
    //independent of an actual protocol




    //one side
    int client_socket=socket(AF_INET,SOCK_STREAM,  0);

    //ADDRESS we want to connect to 
    //address family
    //same as socket family
    //same as AF_INET
    struct sockaddr_in server_address;

    server_address.sin_family=AF_INET;
    //or 9002
    server_address.sin_port=htons(9002);
    //address 
    //in our case it is the ip address
    // if you want to bind to any address on your locol 
    //computer use 0.0.0.0
    //but there is a shortcyut
    server_address.sin_addr.s_addr=INADDR_ANY;

    //p1 p2 p3==> size of addreess
    //cast our server address structure to soem  
    int connection_status=connect(client_socket, 
    (struct sockaddr *)& server_address,
        sizeof(server_address)
    );
    if(connection_status==0){
        printf("Successfull\n");
    }


    // struct sockaddr is another data structure used for socket addresses, but it's more general and can be used for various types of socket addresses, including both IPv4 and IPv6. It's often used for compatibility and to pass socket addresses to functions that expect a struct sockaddr pointer.

    // to receieve the data we need a string
    //size
    //optional flag make it zero

    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response),0);


    printf("The server sent data is %s\n", server_response);


    // doubt
    // ?
    close(client_socket);


    return 0;
}
