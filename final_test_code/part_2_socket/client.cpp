// C program for the Client Side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
 
// inet_addr
#include <arpa/inet.h>
#include <unistd.h>
 
// For threading, link with lpthread
#include <pthread.h>
#include <semaphore.h>
 
#include<iostream>
#include<thread>
#define MAX 999
using namespace std;

 void thread_send(int socket){
    while(1){
        char hello[MAX];
        fgets(hello,MAX,stdin);
        send(socket, hello, strlen(hello), 0);
    }
 }
 void thread_rcv(int socket){
    while(1){
        
        char buffer[999] {};
        int on = recv(socket, buffer, 999, 0);
        if(!on){
            exit(EXIT_FAILURE);
        }
        printf("server>>");
	    printf("%s", buffer);
    }
 }

// Driver Code
int main()
{
    int network_socket;
 
    // Create a stream socket
    network_socket = socket(AF_INET,
                            SOCK_STREAM, 0);
 
    // Initialise port number and address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8989);
 
    // Initiate a socket connection
    int connection_status = connect(network_socket,
                                    (struct sockaddr*)&server_address,
                                    sizeof(server_address));
 
    // Check for connection error
    if (connection_status < 0) {
        puts("Error\n");
        return 0;
    }
 
    printf("Nhập username: ");
    char username[32];
    fgets(username, 32, stdin);
    username[strlen(username)-1] = '\0';
    send(network_socket, &username,
        sizeof(username), 0);
    printf("Kết nối thành công\n");
    std::thread w_thread(&thread_send, network_socket);
    std::thread r_thread(&thread_rcv, network_socket);

     // Send data to the socket
    w_thread.join();
    r_thread.join();


    // Close the connection
    close(network_socket);
}