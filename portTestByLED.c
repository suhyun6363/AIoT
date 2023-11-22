#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
		if (argc != 3) {
				printf("wrong argument!\n");\
				return 0;
		}
		
		if (strcmp(argv[0], "./led") != 0 && (strcmp(argv[2], "on") != 0 || strcmp(argv[2], "off") != 0)) {
				printf("wrong argument!\n");\
				return 0;
		}
		else {
			short port;
			port = atoi(argv[1]);
			
			if(wiringPiSetup() == -1)
				return -1;
			pinMode(port, OUTPUT);
			
			if (strcmp(argv[2], "on") == 0) {
				digitalWrite(port, 1);
			} else if(strcmp(argv[2], "off") == 0) {
				digitalWrite(port, 0);
			}
		}
		return 0;
}
