#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <wiringPi.h>
#include "Frequency.h"

int convert(float pitch) {
	float  second = (float)(1.0 / pitch);
	float  ms = second * 1000.0;
	float  us = ms * 1000.0;
	
	return us / 2;
}

void sw_udelay(int t) {
	int now = micros();
	int target = now + t;
	int current;
	while((current = micros()) < target);
}


void play(int pin_Buzz, int pitch, int t) {
	int now = millis();
	int target = now + t;
	int current;
	while((current = millis()) < target) {
		digitalWrite(pin_Buzz, 1);
		sw_udelay(pitch);
		digitalWrite(pin_Buzz, 0);
		sw_udelay(pitch);
	}
}

#define PORT	9998
// EchoClient_exer2

int main(void) {
	
	int sock;
	struct sockaddr_in addr;
	char buffer[1024];
	char recv_data[100];
	int recv_len, pin_LEDB, pin_Buzz;
	int highC;
	
	for (int i = 0; i < 2; i++) {

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
	
	printf("input num(1: LED, 2: Buzzer) : ");
	char input_num[10];
	char send_data[100];
	switch(atoi(gets(input_num))) {
		case 1:
			strcpy(send_data, "LED");
			break;
		case 2:
			strcpy(send_data, "Buzzer");
			break;
		default:
			printf("wrong number!");
			break;
	}
	send_data[strlen(send_data)] = '\0';

	if(send(sock, (void*)send_data, sizeof(send_data), 0) < 0) {
		perror("send ");
		return 1;
	}

	if((recv_len = recv(sock, recv_data, sizeof(recv_data), 0)) < 0) {
		perror("recv ");
		return 1;
	}

	recv_data[recv_len] = '\0';

	printf("received data : %s\n", recv_data);

	int recv_data_int = atoi(recv_data);
	switch(recv_data_int) {
			case 4:
				pin_LEDB = recv_data_int;
				break;
			case 27:
				pin_Buzz = recv_data_int;
				break;
	}
	close(sock);
	}
	

	printf("%d, %d, %d, %d", pin_LEDB, pin_Buzz);
	
	
	if(wiringPiSetup() == -1)
		return -1;
		
	pinMode(pin_LEDB, OUTPUT);
	pinMode(pin_Buzz, OUTPUT);
	
	printf("input Number(1: LED On, 2: LED Off, 3: LED blinking, 4: Buzzer) :");
	char tmp[10];
	gets(tmp);
	int inputNum = atoi(tmp);
	switch(inputNum) {
		case 1:
			digitalWrite(pin_LEDB, 1);
			break; 
		case 2:
			digitalWrite(pin_LEDB, 0);
			break;
		case 3:
			digitalWrite(pin_LEDB, 1);
			digitalWrite(pin_LEDB, 0);
			delay(500);
			digitalWrite(pin_LEDB, 0);
			digitalWrite(pin_LEDB, 1);
			delay(500);
			digitalWrite(pin_LEDB, 1);
			digitalWrite(pin_LEDB, 0);
			delay(500);
			digitalWrite(pin_LEDB, 0);
			digitalWrite(pin_LEDB, 1);
			delay(500);
			break;
		case 4:
			play(pin_Buzz, convert(523.25), 1000);
			break;
		default:
			printf("wrong number");
			break;
		
	}
	return 0;
}
