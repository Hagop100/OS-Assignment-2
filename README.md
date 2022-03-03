# OS-Assignment-2

Program Description

The purpose of this programming assignment was to use the msgget(), msgsnd(), and
msgrcv() system calls to communicate between different programs. These different programs
were executed in combination with fork() and exec(). Three programs were created: master.cc,
sender.cc, and receiver.cc. The master program was responsible for forking twice to execute
both sender and receiver. More importantly however, the master program would create our
message queue by calling msgget(). We would then go into the sender program and ask the
user for an input message. This would be accepted in the form of a character array and then
sent to the message queue using msgsnd(). We would then go into the receiver and receive the
message from the message queue using msgrcv(). These are how the three programs will
interact with each other.

In the master program, we begin by creating a message queue with msgget(). This is
possible because the key identified is IPC_PRIVATE and the msgflag is identified as
IPC_CREAT. Our msgget() function will return to us the message queue ID which is of type
integer. We then begin our first fork() and execute the sender program. We will use execlp() and
pass the message queue ID, as this is required to access the specific message queue created
by our master program. We will then fork() a second time and execute the receiver program this
time. Again, we will pass the message queue ID using execlp() to ensure we have access to the
message queue to retrieve the message. It is important to store our child process ID in the
master program as we will need access to it when we print to the console. In the sender
program, we will use msgsnd(). It is important that we begin by creating a struct called msgbuff
(cannot be called msgbuf due to that already existing in <sys/msg.h>). This struct will have
components long int msgtype and char greeting[]. The “greeting” variable will be used to store
the message and send it to the message queue. The “msgtype” variable will store a specific
code for that message that we want to obtain from the queue as there can be multiple
messages in a single queue. We will then ask for the user to input a message which we will
store in a character array. We then convert that into a string using strcpy(). We then access the
message queue ID from the command line parameter and convert that into an integer using
stoi(). We finally call msgsnd() where we will pass in the message queue ID, a pointer to the
instance of the struct we created, and a size of the message in our instance of our struct. Finally
we reach the receiver. The receiver will contain the same struct from the sender program. This
is to store our message obtained from the message queue. We will do the same again to obtain
the message queue ID from the command line parameter and convert it into an integer data
type. Then we will call msgrcv() where we will pass in the message queue ID, a pointer to the
message structure we are trying to store our message in, the size, and most importantly the
message type. This must be the same as identified in our sender program, otherwise it will not
read any message. Lastly, we print our message to show that it was received.
