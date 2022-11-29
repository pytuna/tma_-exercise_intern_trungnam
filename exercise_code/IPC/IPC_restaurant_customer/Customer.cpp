#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <thread>
#include <iostream>
using namespace std;
#define MAX 100

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[1000];
    
} message, m2;

void receive(){
    key_t key;
	int msgid;
    while (1)
    {
        // ftok to generate unique key
        key = ftok("nam", 65);

        // msgget creates a message queue
        // and returns identifier
        msgid = msgget((key_t)12345, 0600 | IPC_CREAT);

        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 0, 0600);

        // display the message
        printf(">>%s\n",message.mesg_text);
    }
    
	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
}

void send(){
    key_t key;
	int msgid;
    while(1){
        // ftok to generate unique key
        key = ftok("tuna", 65);
        // msgget creates a message queue
        // and returns identifier
        msgid = msgget((key_t)123456, 0666 | IPC_CREAT);
        message.mesg_type = 1;
        
	    fgets(message.mesg_text,MAX,stdin);

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

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
