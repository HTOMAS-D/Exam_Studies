#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Structure to represent a client with an ID and a message buffer
typedef struct client {
    int id;
    char msg[424242]; // Buffer for messages from this client
} t_client;

// Global variables for client information, buffers, and file descriptor sets
t_client clients[1024];         // Array to store client data
char buffRead[424242], buffWrite[424242]; // Buffers for reading and writing data
int max = 0, next_id = 0;       // Maximum file descriptor and next client ID
fd_set active_fds, Read_fds, Write_fds; // Sets for tracking active, readable, and writable sockets

// Function to handle fatal errors by printing an error message and exiting
void errorExit(char *str) {
    write(2, str, strlen(str)); // Write error message to standard error
    exit(1);                    // Exit the program
}

// Function to send a message to all connected clients except the sender
void sendMsg(int send_fd) {
    for (int fd = 0; fd <= max; fd++) {
        // Check if the file descriptor is writable and is not the sender
        if (FD_ISSET(fd, &Write_fds) && fd != send_fd)
            write(fd, buffWrite, strlen(buffWrite)); // Send the message
    }
}

int main(int ac, char **av) {
    // Check if the correct number of arguments are provided
    if (ac != 2)
        errorExit("Wrong number of arguments\n");

    // Create a socket and set it as the maximum file descriptor initially
    int sockfd = max = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        errorExit("Fatal error\n");

    // Initialize the file descriptor set and add the server socket
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);

    // Configure the server address
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(2130706433); // IP address 127.0.0.1
    servaddr.sin_port = htons(atoi(av[1]));      // Port number from argument

    // Bind the socket to the address and port
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
        errorExit("Fatal error\n");

    // Start listening for incoming connections
    if (listen(sockfd, 10) != 0)
        errorExit("Fatal error\n");

    // Main server loop
    while (1) {
        // Copy the active file descriptors to read and write sets
        Read_fds = Write_fds = active_fds;

        // Use select to monitor file descriptors for readability/writability
        if (select(max + 1, &Read_fds, &Write_fds, NULL, NULL) < 0)
            continue; // Continue on error

        // Iterate over file descriptors to handle events
        for (int fd = 0; fd <= max; fd++) {
            // Check if there's a new connection on the server socket
            if (FD_ISSET(fd, &Read_fds) && fd == sockfd) {
                int ClientSocket = accept(sockfd, NULL, NULL); // Accept new client
                max = (ClientSocket > max) ? ClientSocket : max; // Update max
                clients[ClientSocket].id = next_id++;            // Assign client ID
                bzero(clients[ClientSocket].msg, strlen(clients[ClientSocket].msg)); // Clear message buffer
                FD_SET(ClientSocket, &active_fds);               // Add to active set
                sprintf(buffWrite, "server: client %d just arrived\n", clients[ClientSocket].id); // Welcome message
                sendMsg(ClientSocket);                           // Notify other clients
                break;
            }

            // Handle readable data from existing clients
            if (FD_ISSET(fd, &Read_fds) && fd != sockfd) {
                int read = recv(fd, buffRead, sizeof(buffRead), 0); // Read data
                if (read <= 0) { // Client disconnected
                    sprintf(buffWrite, "server: client %d just left\n", clients[fd].id); // Notify others
                    sendMsg(fd);
                    FD_CLR(fd, &active_fds); // Remove from active set
                    close(fd);              // Close socket
                    break;
                } else { // Process client message
                    for (int i = 0, j = strlen(clients[fd].msg); i < read; i++, j++) {
                        clients[fd].msg[j] = buffRead[i]; // Append to message buffer
                        if (clients[fd].msg[j] == '\n') { // Message complete
                            clients[fd].msg[j] = '\0'; // Null-terminate message
                            sprintf(buffWrite, "client %d: %s\n", clients[fd].id, clients[fd].msg); // Format message
                            sendMsg(fd); // Send to other clients
                            bzero(clients[fd].msg, strlen(clients[fd].msg)); // Clear buffer
                            j = -1; // Reset index for next message
                        }
                    }
                    break;
                }
            }
        }
    }
}
