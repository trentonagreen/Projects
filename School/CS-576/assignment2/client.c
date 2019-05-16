// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n; 
	unsigned int len;
	
	n = sendto(sockfd, hello, strlen(hello), 
		0, (const struct sockaddr *) &servaddr, 
			sizeof(servaddr)); 
	//printf("Hello message sent.\n"); 
	printf("Your client program sends %s\n", hello);
		
	n = recvfrom(sockfd, buffer, MAXLINE, 
				0, (struct sockaddr *) &servaddr, 
				&len); 
	buffer[n] = '\0'; 
	printf("Your client program would recieve the string ");
	printf("\"%s\" ", buffer);
	printf("from the server.\n");

	close(sockfd); 
	return 0; 
} 
