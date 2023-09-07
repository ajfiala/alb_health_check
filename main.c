/*
    This is a simple HTTP health-check app that responds with a JSON message to a GET request.
    It is intented to be used with the AWS EKS Load Balancer Controller to keep a load balancer running
    at all times in a Kubernetes cluster even when the applications that use it are down. This avoids the 
    need to change DNS records to reflect new ALB addresses when the applications are restarted.
    Created by: Andrew Fiala
    Date: 7/9/2023
*/
#include "socket.h"

int main(void)
{
	int server_fd;
	int client_fd;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	/* Initialize socket and bind it to port 8080 */
	server_fd = initialize_socket(8080);

	/* Start listening for incoming connections */
	start_listening(server_fd);

	while (1) {
		/* Accept incoming connection */
		client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
		if (client_fd < 0) {
			perror("Failed to accept connection");
			exit(EXIT_FAILURE);
		}

		/* Handle client request */
		handle_client(client_fd);
	}

	return 0;
}