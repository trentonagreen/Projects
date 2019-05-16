// Server side implementation of UDP client-server model 
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


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	//char *hello = "Hello"; 
	char *snow = " Don't eat the yellow snow";
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int n; 
	unsigned int len = sizeof(servaddr);

	n = recvfrom(sockfd, buffer, MAXLINE, 
				0, ( struct sockaddr *) &cliaddr, 
				&len); 
	buffer[n] = '\0'; 
	//printf("Client : %s\n", buffer); 
	printf("Your server program would recieve the string %s ", buffer);
	printf("from the client.\n");

	char *hello = concat(buffer, snow);

	n = sendto(sockfd, hello, strlen(hello), 
		0, (struct sockaddr *) &cliaddr, 
			len); 
	printf("Your server program sends %s\n", hello);
	
	return 0; 
} 
