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

int main(int argc, char *argv[]) {

	//msgget system call is responsible for creation of our message queue
	//We pass in IPC_PRIVATE and IPC_EXCEL to create a new message queue
	//it will return the message queue identifier which is key to accessing messages
	//from the specific message queue created
	int msgid = msgget(IPC_PRIVATE, IPC_EXCL|IPC_CREAT|0600);

	//create variables to store sender and receiver child process identifiers
	pid_t senderPid, receiverPid;

	//begin first fork to execute sender program
	pid_t pid = fork();
	//store sender child process identifier
	senderPid = pid;
	if(pid == 0) {
		//previously was using execvp but was failing because execvp requires commandline arguments to run properly
		//execlp requires the file name, then the executable name, along with the message queue ID and must be NULL terminated
		execlp("./sender", "sender", const_cast<char*>(std::to_string(msgid).c_str()), (char*)NULL);
		exit(0);
	}
	pid_t pid2 = fork();
	receiverPid = pid2;
	if(pid2 == 0) {
		//previously was using execvp but was failing because execvp requires commandline arguments to run properly
		//execlp requires the file name, then the executable name, along with the message queue ID and must be NULL terminated
		execlp("./receiver", "receiver", const_cast<char*>(std::to_string(msgid).c_str()), (char*)NULL);
		exit(0);
	}
	else if(pid2 < 0) {
		perror("Fork failed"); //display error message that fork failed
		exit(1); //exit the program with a return value of 1
	}
	else if(pid2 > 0) {
		//master program
		cout << "Master, PID " << getpid() << ", begins execution." << endl;
		cout << "Master acquired a message queue, id " << msgid << endl;
		cout << "Master created a child process with PID " << senderPid << " to execute sender\n";
		cout << "Master created a child process with PID " << receiverPid << " to execute receiver\n";
		cout << "Master waits for both child processes to terminate\n";
		cout << "Master received termination signals for both child processes, removed message queue, and terminates\n";
		//while loop ensures all child process finish before parent else it becomes left without a parent
		//wait system call returns the exit status of the children and when it returns 0 then it will end
		while(wait(NULL) != -1);
		//msgctl is responsible for removing the message queue as determined by the second parameter IPC_RMID
		msgctl(msgid, IPC_RMID, NULL);
	}
	

	return 0;
}

