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
	//create msgbuff instance
	msgbuff myMessage;
	//store its size
	int size = sizeof(myMessage) - sizeof(long);
	//identify code
	myMessage.mtype = 113;
	char input[50];
	cout << "Sender, PID " << getpid() << ", begins execution.\n";
	cout << "Sender received message queue id " << argv[1] << " through commandline parameter\n";
	cout << "Sender: Please input your message.\n";
	//acquire user input
	cin.getline(input, 50);
	cout << "Sender sent message to message queue.\n";
	//copy input into string
	strcpy(myMessage.greeting, input);
	//argv[1] is the message queue ID sent from master program
	//store in int
	int qid = stoi(argv[1]);
	//send message to the message queue
	//pass the message queue ID, a pointer to the address, and the size
	msgsnd(qid, &myMessage, size, 0);
	cout << "Sender terminates\n";
	return 0;
}