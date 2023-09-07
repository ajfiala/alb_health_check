#ifndef SOCKET_H
#define SOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* Function to initialize the socket and bind it to a port */
int initialize_socket(int port);

/* Function to listen for incoming connections */
int start_listening(int server_fd);

/* Function to handle incoming requests */
void handle_client(int client_fd);

/* Function to parse incoming HTTP requests */
bool parse_request(char *buffer);

#endif // SOCKET_H