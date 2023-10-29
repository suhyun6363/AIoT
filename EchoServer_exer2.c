#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT	9997
//EchoServer_exer2
int main(void) {
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	char recv_data[100];
	char send_data[100];
	int len, addr_len, recv_len, send_data_int;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket ");
		return 1;
	}

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		perror("bind ");
		return 1;
	}

	if(listen(sock, 5) < 0) {
		perror("listen ");
		return 1;
	}

	addr_len = sizeof(client_addr);

	printf("waiting for client..\n");

	while((client_sock = accept(sock, (struct sockaddr*) &client_addr, &addr_len)) > 0) {
		printf("clinet ip : %s\n", inet_ntoa(client_addr.sin_addr));

		if((recv_len = recv(client_sock, (void*)recv_data, sizeof(recv_data), 0)) < 0) {
			perror("recv");
			return 1;
			break;
		}

		char option[3] = {'LED Red', 'LED Blue', 'Buzzer'};
		int pinNum[3] = {4, 5, 27};
		
		for (int i = 0; i < 3; i++) {
			if (strcmp(recv_data, option+i) == 0) {
					send_data_int = *(option+i);
					printf("%d", send_data_int);
			}
		}

		sprintf(send_data, "%d", send_data_int);
		send_data[strlen(send_data)] = '\0';
		
		printf("received data: %s\n", recv_data);

		send(client_sock, send_data, strlen(send_data), 0);

		close(client_sock);
	}
	close(sock);
	return 0;
}
