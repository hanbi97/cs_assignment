# IPC (Pipe) + Multi-processing TCP server

#### Multi-processing TCP server 
1. Create a Pipe (for communication of tcp server’s parent and child processes, explained on part 4, and 3.1)
2. Listens and accepts only two connection requests (creates 2 client sockets)
3. Creates two child processes (and assign for each client socket)
    * The child processes will be reading data from Pipe (IPC)
    * After reading, each child process sends the data to their respective client socket
    * Whenever you get a termination string from pipe (“q”, “Q”), close the client socket and stop the child process (don’t forget to clean if there are any zombie processes from the parent process)
4. After accepting two client connection requests, the parent process:
    * Getting user input (a string) that will be later sent to the two child processes using a Pipe (IPC)
    * Whenever the user input is a termination string (“q”, “Q”), send the termination string to the two child processes and finish the program.


#### Basic TCP client 
1. Creates a TCP socket and connects to server
2. Keeps receiving data from server and prints out the received data
3. Closes the socket when no data is to be received (as in usual data transfers)
<br/>

![弊覆1](https://user-images.githubusercontent.com/36736904/82205046-e2306300-9940-11ea-8e9a-22eca633215d.jpg)
![弊覆2](https://user-images.githubusercontent.com/36736904/82205048-e3fa2680-9940-11ea-8dba-4850c9fdfd6f.jpg)
