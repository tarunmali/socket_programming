

    // // struct sockaddr is another data structure used for socket addresses, but it's more general and can be used for various types of socket addresses, including both IPv4 and IPv6. It's often used for compatibility and to pass socket addresses to functions that expect a struct sockaddr pointer.

    // // to receieve the data we need a string
    // //size
    // //optional flag make it zero

    // char server_response[256];
    // recv(client_socket, &server_response, sizeof(server_response),0);


    // printf("The server sent data is%s\n", server_response);