#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess
#include <pthread.h>

#include <string.h>




void *handleIndividualPrinting(void *arg){
    int client_socket = *((int *)arg);
    char response[4096];
    recv(client_socket,&response, sizeof(response),0);
    printf("Client also received %s",response);

}


//for strcmp
#include <string.h>


    int connection_status=connect(client_socket, yyyy
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
    //pointer to the line
    size_t lineSize=0;
    printf("Type and will send....(type exit)\n");   

    // while(1){
        while(1){
            //blocking
            ssize_t charCount= getline(&line,&lineSize,stdin);
            if(charCount>0){
                if(strcmp(line,"exit\n")==0) break;
                ssize_t amountWasSent=send(client_socket,line,sizeof(line),0);
            }

        }
        pthread_t id;
        pthread_create(&id, NULL, handleIndividualPrinting, &client_socket);
        pthread_detach(id);

    // }



    return 0;
}
