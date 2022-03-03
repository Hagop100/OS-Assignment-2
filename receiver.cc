#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <sys/wait.h>

using namespace std;

//require structure to store messages and their message types
//this form must be implemented as specified by the manual
//mtype stores the code to that specific message in the message queue
//greeting stores the actual message contents
struct msgbuff {
	long mtype;
	char greeting[50];
};

int main(int argc, char *argv[]) {
	//store message queue ID obtained from master in int variable
	int qid = stoi(argv[1]);
	cout << "Receiver, PID " << getpid() << ", begins execution\n";
	cout << "Receiver received message queue id " << qid << " through commandline paramter\n";
	cout << "Receiver: Retrieved the following message from the message queue: \n";
	//create instance of msgbuff structure
	msgbuff msg;
	//obtain size of message
	int size = sizeof(msg) - sizeof(long);
	//call msgrcv()
	//this system call will go into the message queue and obtain the message from that specific message queue 
	//this message queue will be identified with the message queue ID in the first parameter
	//pointer to the address of the instance of our structure we made above to store message
	//pass in the size of the message to be received
	//the message type will grab the specific message in the message queue
	//this must be the same as the mtype delineated in our sender program otherwise no message will be read
	msgrcv(qid, &msg, size, 113, 0);
	//print the message to console
	cout << msg.greeting << endl;
	cout << "Receiver terminates\n";
	return 0;
}