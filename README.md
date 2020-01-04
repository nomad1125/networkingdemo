# networkingdemo
Program designed to demonstrate and understand socket programming

all files compiled using gcc
gcc version: 4.2.1
device version: Apple LLVM version 6.1.0

gcc server11.c -o server11
gcc client11b.c -o client11b
gcc client11c.c -o client11c

all prompts are asked for when the code is running.

Always start server first:
./server11


Then you can start either 11b or 11c with:
./client11b
or
./client11c

11b prompts for target server and then prompts for message to send.
11c only prompts for target server and then begins sending messages.

Some of the server responses are sometimes not accurate, but I think it is due to how quickly the program and the messages are running. During testing the messages would come back correctly. Did not get to deeply test how well the programs would work over the network, but I am pretty confident it will work. It worked perfectly over loopback and I got to test between a local vm and a laptop and it seemed to work over local area network.

Lab 1.2
All files compiled with gcc during testing.
Compiler lines:
gcc server12.c -o server12
gcc client12.c -o client12

Similar to before make sure server is running first.
./server12

Then start client program with specific command line arguments.
./client12 (target address) (Operation Code) (Operand A) (Operand B)

Ex:
./client12 127.0.0.1 + 2 3

During testing I found that Operand A and B can only max out at 999. I did not have enough time to write in safety catches so incorrect inputs might work, but will not fully function. Correct inputs seem to work properly. I only tested using whole numbers so fractional number like 2.3 may not work.
