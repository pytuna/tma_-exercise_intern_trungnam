// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[1000];
    
} message, m2;

int main()
{
	key_t key;
	int msgid;

	
    while(1){
        // ftok to generate unique key
        key = ftok("tuna", 65);
        // msgget creates a message queue
        // and returns identifier
        msgid = msgget(key, 0666 | IPC_CREAT);
        message.mesg_type = 1;
        
        printf("Write Data : ");
	    fgets(message.mesg_text,MAX,stdin);

        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

        // display the message
        printf("Data send is : %s \n", message.mesg_text);
    }
	

	return 0;
}

// // C Program for Message Queue (Writer Process)
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
//         msg1.msg_type = 1;

//         printf("\nInput text: ");
//         fgets(msg1.mesg,MAX,stdin);

//         int check = msgsnd(msg_id, &msg1, sizeof(msg1), 0);
        
//         printf("Data send status %d", check);
//     }
//     return 0;
// }