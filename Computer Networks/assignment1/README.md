# Client-Server communication and TCP half-close
#### TCP server


1. Creates a TCP (server) socket
2. Binds the server socket to port 1234, and listens to 2 connection requests
3. Accepts both client connection requests by an iterative approach
4. After accepting each client:
    * Loads the content of the ¡®data.txt¡¯ text file into a buffer
    * Server sends a number (a byte) which means the length of the ¡®data.txt¡¯ file (which is equal to 10 bytes)
    * Server then sends the content of the text file (that is loaded in a buffer) to the client
    *  Server terminates its output in the socket (TCP half-close)
    * Receives a number (a byte) from client, and prints it out on the screen
    * Closes the client socket
5. After both clients¡¯ connections are terminated, closes the file and server socket
<br/>

#### TCP client
1. Creates a TCP socket
2. Connects to the TCP local server (by IP address 127.0.0.1, and port 1234)
3. Client receives a number (a byte, which means the length of the further incoming data)
4. Client receives the incoming data (the size of which we already know from the previously
received number)
5. Prints out the received data as a string (which means you should put a terminating
character ¡®\0¡¯ at the end)
6. Sends a number 0 (a byte) to server
7. Closes the socket

<br/>

![ÀÌ¹ÌÁö 10](https://user-images.githubusercontent.com/36736904/82204773-764dfa80-9940-11ea-8c08-df20b5374aab.png)
