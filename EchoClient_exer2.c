#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT	9997
// EchoClient_exer2

int main(void) {
	int sock;
	struct sockaddr_in addr;
	char buffer[1024];
	char recv_data[100];
	int recv_len;

	printf("input numA(1: LED Red, 2:LED Blue, 3: Buzzer) : ");
	char send_data[100];
	gets(send_data);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);

	if(connect(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		perror("connect ");
		return 1;
	}

	if(send(sock, (void*)send_data, sizeof(send_data), 0) < 0) {
		perror("send ");
		return 1;
	}

	if((recv_len = recv(sock, recv_data, sizeof(recv_data), 0)) < 0) {
		perror("recv ");
		return 1;
	}

	buffer[recv_len] = '\0';

	printf("received data : %s\n", recv_data);

	close(sock);

	return 0;
}
