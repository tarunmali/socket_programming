//we wont connect to a server this time
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <unistd.h>     // Add this for close()
#include <arpa/inet.h>  // Add this for htons() and converting network addressess
#include <pthread.h>

#include <bits/stdc++.h>


std::map<std::string, std::string> m;
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
            std::string str(response);

            std::stringstream ss(str);
            std::string tok;
            std::vector<std::string> vos;
            while(getline(ss,tok,' ')) vos.push_back(tok);
            std::string cmd=vos[0],key=vos[1],value=vos[2];

//   int space1 = str.find(" ");

//   // Extract the first string.
//   std::string cmd = str.substr(0, space1);

//   // Find the position of the second space.
//   int space2 = str.find(" ", space1 + 1);

//   // Extract the second string.
//   std::string key = str.substr(space1 + 1, space2 - space1 - 1);

//   // Extract the third string.
//   std::string value = str.substr(space2 + 1);


            char* cmd_c = strdup(cmd.c_str());
            printf("CMD %s\n",cmd_c);
            char* key_c = strdup(key.c_str());
            printf("Key %s\n",key_c);
            char* value_c = strdup(value.c_str());
            printf("Value %s\n",value_c);  
            char* value_d = strdup(value.c_str());



        pthread_mutex_lock(&mutex);
            if(m.find(key)==m.end()){
                // printf("key does not exist adding %s\n",value_d); 
                printf("mess\n");
                m[key]=value;
            }
            else{
                printf("jen\n");
                // printf("key  exist adding %s\n",value_d);
                // printf("%s","Dev");
            }
        pthread_mutex_unlock(&mutex);
            // sendToAllClients(response, client_socket);
        }
        if(amountReceived<=0){
            printf("Client disconnected: Total clients=>%d\n",cntAcceptedClients);
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



    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        printf("Client connected: Total clients=>%d\n",cntAcceptedClients+1);

        // Create a new thread to handle this client
        pthread_t id;
        pthread_create(&id, NULL, handleIndividualConnections, &client_socket);

        // Detach the thread so its resources are automatically cleaned up when it exits
        pthread_detach(id);
    }
    

    return 0;
}