#include <stdio.h>
#include <stdlib.h>
//why?


#include <sys/types.h>
#include <sys/socket.h>  

//to store address  information
#include <netinet/in.h>

int main(){
    //domain of socket, => since it is internet socket , AF_INET
    //defined in header file


    //@todo see datagram 
    //SOCK_STREAM tupe of the socket, tcp socket (connection socket)
    //vs the data gram socket which is UDP


    //protocol we are using 0, as we are already using tcp
    //

    int network_socket=socket(AF_INET,SOCK_STREAM,  );
    return 0;
}
