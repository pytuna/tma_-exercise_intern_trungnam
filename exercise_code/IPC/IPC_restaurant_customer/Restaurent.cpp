// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <iostream>
#include <atomic>
#include<vector>
#include<mutex>
#include<string>
#include"Priority_Queue.h"
using namespace std;
#define MAX 100


Priority_Queue pq;

mutex m;
string data_send = "";

template<class T>
vector<T> split_string(string input, char del){
    vector<T> output;
    stringstream ss(input);
    string e;
    while (!ss.eof()) {
        getline(ss, e, del);
        output.push_back(e);
    }
    return output;
}
// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[1000];
   
} message;

void receive(){
    key_t key;
	int msgid;
    while (1)
    {
        // ftok to generate unique key
        key = ftok("tuna", 65);

        // msgget creates a message queue
        // and returns identifier
        msgid = msgget((key_t)123456, 0666 | IPC_CREAT);

        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 0, 0666);

        m.lock();

        // display the message
        printf(">>%s\n",message.mesg_text);
        string input(message.mesg_text);
        input = input.substr(0, input.length()-1);
        vector<string> a = split_string<string>(input, ' ');
        string choice = a[0];
        
        if(choice == "request"){
            a.push_back("");
            a.push_back("");
            int size_a = a.size();
            int id, isVip = 0;
            string name="", food= "";

            char *c_id = new char[a[1].length() + 1];
            strcpy(c_id, a[1].c_str());
            sscanf( c_id, "%d", &id);
            
            food = a[2];
            if (size_a >= 4) name = a[3];

            if(size_a >= 5){
                char *c_vip = new char[a[4].length() + 1];
                strcpy(c_vip, a[4].c_str());
                sscanf( c_vip, "%d", &isVip);
            }
            
            pq.add(id, food, name, isVip);

        
        }else{
            cout<<"Nhập sai!!!\n";
        }
        a.clear();
        m.unlock();
    }
    
	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
}

void send(){
    key_t key;
	int msgid;
    while(1){
        // ftok to generate unique key
        key = ftok("nam", 65);
        // msgget creates a message queue
        // and returns identifier
        msgid = msgget((key_t)12345, 0600 | IPC_CREAT);
        message.mesg_type = 1;

	    // fgets(message.mesg_text,MAX,stdin);
        string input;
        getline(cin, input);

        m.lock();
        vector<string> a = split_string<string>(input, ' ');
        string choice = a[0];

        if(choice == "serve"){
             pq.serve();
             char buffer[MAX];
             snprintf(buffer, MAX, "id: %d name: %s", pq.last_customer_pop->id, pq.last_customer_pop->name.c_str());
             string temp = buffer;
             data_send = "Don mon phuc vu: ";
             data_send.append(temp);

        }else if(choice == "show"){
            pq.show();
            
        }else if(choice == "exit"){
            break;
        }else{
            cout<<"Nhập sai!!!\n";
        }
        a.clear();
        strcpy(message.mesg_text, data_send.c_str());
        data_send = "";
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
        
        m.unlock();
    }
}
int main()
{
	
    thread thread_receive(&receive);
    thread thread_send(&send);

    thread_receive.join();
    thread_send.join();
	return 0;
}




