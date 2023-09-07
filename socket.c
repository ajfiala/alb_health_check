#include "socket.h"
#define BUFFER_SIZE (516)

/* Initialize the socket and bind it to a port */
int initialize_socket(int port)
{
	if (port < 0 || port > 65535) {
		perror("Invalid port number");
		exit(EXIT_FAILURE);
	}
	int server_fd;
	struct sockaddr_in address;

	int opt = 1;  // for setsockopt() SO_REUSEADDR

	/* Create a socket */
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == 0) {
		perror("Failed to create socket");
		exit(EXIT_FAILURE);
	}

	// Set SO_REUSEADDR so the port can be reused immediately after the server exits.
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("Failed to set SO_REUSEADDR");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	/* Bind the socket to the port */
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Failed to bind socket to port");
		exit(EXIT_FAILURE);
	}
	
	return server_fd;
}

/* Listen for incoming connections */
int start_listening(int server_fd)
{
	if (listen(server_fd, 10) < 0) {
		perror("Failed to listen");
		exit(EXIT_FAILURE);
	}

	printf("Listening on port 8080...\n");
	return 0;
}

/* Handle incoming requests */
void handle_client(int client_fd)
{
	if (client_fd < 0) {
		perror("Invalid client file descriptor");
		exit(EXIT_FAILURE);
	}

	char buffer[BUFFER_SIZE] = {0};
	char *http_response = "HTTP/1.1 200 OK\nContent-Type: application/json\nContent-Length: 29\n\n{\"message\": \"Hello, World!\"}\n";
	char *bad_response = "HTTP/1.1 405 Method Not Allowed\nContent-Type: application/json\nContent-Length: 23\n\n{\"message\": \"Invalid\"}\n";

	/* Read client request */
	if (recv(client_fd, buffer, BUFFER_SIZE, 0) < 0) {
		perror("Failed to read from client");
		exit(EXIT_FAILURE);
	}
	bool valid_input = false;
	valid_input = parse_request(buffer);

	/* Send HTTP response */
	if (valid_input){
		if (send(client_fd, http_response, strlen(http_response), 0) < 0) {
		perror("Failed to send response");
		exit(EXIT_FAILURE);
		}
	}
	else{
		if (send(client_fd, bad_response, strlen(bad_response), 0) < 0) {
		perror("Failed to send response");
		exit(EXIT_FAILURE);
		}
	}

	close(client_fd);
}

/*
   Parses buffer to check if the request is valid. only GET is supported. If request is invalid,
   function flushed the buffer.
*/
bool parse_request(char *buffer) {
	if (strncmp(buffer, "GET ", 4) != 0) {
		perror("Invalid request: Only GET is supported");
		printf("%s\n", buffer);
		memset(buffer, 0, BUFFER_SIZE);
		return false;
	}
	return true;
}