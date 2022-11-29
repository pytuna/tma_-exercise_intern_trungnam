// inet_addr
#include <arpa/inet.h> 
// For threading, link with lpthread
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<iostream>
#include<thread>
#include<atomic>
#include<map>

using namespace std;

#define MAX 999
int sockets[9];
int j = 0;
std::atomic<int> I{0};
std::array<std::atomic<int>, 9> std_array = {};
std::map<int, string> m;
std::thread rcv_thread[9];
// Nhận tin từ client theo tên client
void receive_client(int serverSocket){
    string username = m[serverSocket];
    while(1){
        
        char buffer[999] {};
        int on_connected = recv(serverSocket, buffer, 999, 0); 
        if(!on_connected){
            cout<<username<<" disconnected\n";
            m.erase (serverSocket);
            break;
        }
        cout<<username<<">>";
	    printf("%s", buffer);
    }
}
// Lắng nghe sự kiện client join vào socket
void accept_client_join(int serverSocket, struct sockaddr_storage serverStorage){
    
    while(1){
        
        int newSocket;
        socklen_t addr_size = sizeof(serverStorage);
        newSocket = accept(serverSocket,(struct sockaddr*)&serverStorage, &addr_size);
        usleep(100);
        char buffer[999];
        recv(newSocket, buffer, 999, 0);
	    string username(buffer);
        std_array[I++] = newSocket;
        m[std_array[I-1]] = username;
        cout<<"\nUser id: "<<std_array[I-1]<<" - "<<username<<" joined"<<endl;

        rcv_thread[I-1] = std::thread(&receive_client, newSocket);
    }
    
}
// hàm gửi tin cho tất cả client
void send_all(){
    
    fflush(stdin);
    char hello[MAX]{};
    printf("Write Data : ");
    fgets(hello,MAX,stdin);
    for(int k = 0;k<I;k++){
        send(std_array[k], hello, strlen(hello), 0);
    }   
    
}
bool check_key(map<int, string> m, int key)
{
    // Key is not present
    if (m.find(key) == m.end())
        return false;
 
    return true;
}

// Hàm gửi cho client tùy chọn
void send_any(){
    fflush(stdin);
    string id;
    char hello[MAX]{};
    cout<<"\n\tDanh sach client\n";
    for(auto it = m.cbegin(); it != m.cend(); ++it)
    {
        cout << it->first << " - " << it->second <<"\n";
    }

    printf("Nhập id: ");
    getline(cin, id);
    int id_int = stoi(id);
    
    if(check_key(m, id_int)){
        printf("Write Data : ");
        fgets(hello,MAX,stdin);
        send(id_int, hello, strlen(hello), 0);
    }else{
        cout<<"\nKhông tồn tại user";
    }
}

// Hàm xử lí server gửi tin
void server_handle(){
    string choice;
    printf("all. Gửi toàn bộ client\n");
    printf("any. Send client tùy chọn\n");
    while(1){
        printf("\nNhập lựa chọn: ");
        getline(cin, choice);
        if(choice == "all"){
            send_all();
        }else if(choice == "any"){
            send_any();
        }
        
    }
    
}


int main()
{
    
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    int opt = 1;
    socklen_t addr_size;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // AF_INET: IPv4, SOCK_STREAM: TCP/IP
    
    if (setsockopt(serverSocket, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_addr.s_addr = INADDR_ANY;  // localhost
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8989);
 

    bind(serverSocket,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));
 
  
    if (listen(serverSocket, 10) == 0)
        printf("Listening\n");
    else
        printf("Error\n");
    
    std::thread send_all_client(&server_handle);
    std:: thread accept_client(&accept_client_join, serverSocket, serverStorage);
    send_all_client.join();
    accept_client.join();
    
    return 0;
}
