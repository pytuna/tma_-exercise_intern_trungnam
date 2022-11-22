// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[1000];
   
} message;

int main()
{
	key_t key;
	int msgid;
    while (1)
    {
        // ftok to generate unique key
	key = ftok("tuna", 65);

	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);

	// msgrcv to receive message
	msgrcv(msgid, &message, sizeof(message), 0, 0666);

	// display the message
	printf("Data Received is : %s",
					message.mesg_text);
    }
    
	

	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}

// #include <stdio.h>
// #include <sys/ipc.h>
// #include <sys/msg.h>
// #define MAX 1000


// struct msg_buffer
// {
//     long msg_type;
//     char mesg[1000];
   
// }msg1, msg2;

// int main(){
//     key_t key;
//     int msg_id;

//     while(1){
//         key = ftok("progfile", 65);

//         msg_id = msgget(key, 0662|IPC_CREAT);

//         msgrcv(msg_id, &msg1, sizeof(msg1), 1, 0);

//         printf("\nData received text: %s", msg1.mesg);
//     }
//     msgctl(msg_id, IPC_RMID, NULL);
//     return 0;
// }