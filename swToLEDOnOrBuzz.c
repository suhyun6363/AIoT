#include <wiringPi.h>
#include <stdio.h>
#include "Frequency.h"

#define SW 1
#define LEDR 4
#define LEDB 5
#define BUZZER 27
#define FINISH 0
#define STOP 1

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


void play(int pitch, int t) {
	int now = millis();
	int target = now + t;
	int current;
	while((current = millis()) < target) {
		digitalWrite(BUZZER, 1);
		sw_udelay(pitch);
		digitalWrite(BUZZER, 0);
		sw_udelay(pitch);
	}
}
 
int main(void) {
	if(wiringPiSetup() == -1)
		return -1;
		
	pinMode(SW, INPUT);
	pinMode(LEDR, OUTPUT);
	pinMode(LEDB, OUTPUT);
	pinMode(BUZZER, OUTPUT);
	
	printf("input Number(1: LED Binking, 2: Buzzer) :");
	char tmp[10];
	gets(tmp);
	int inputNum = atoi(tmp);
	if(inputNum == 1) {
		while(1) {
			if(digitalRead(SW) == 0) {
				digitalWrite(LEDR, 0);
				digitalWrite(LEDB, 1);
			} else {
				digitalWrite(LEDR, 1);
				digitalWrite(LEDB, 0);
			}
			delay(10);
		}
	} else {
		float Fq[8] = {C, D, E, F, G, A, B, HIGHC};
		int index = 0;
		int flag = FINISH;
		
		while(1) {
				if(digitalRead(SW) == 1) {
					if(FINISH) {
						for(int i = 0; i < 8; i++) {
							if(digitalRead(SW) == 0) {
								index = i;
								flag = STOP;
								break;
							}
							int convert_time= convert(Fq[i]);
							play(convert_time, 500);
						}
					}
					if(STOP) {
						if(digitalRead(SW) == 1) {
						for(int i = index; i < 8; i++) {
							if(digitalRead(SW) == 0) {
								index = i;
								flag = STOP;
								break;
							}
							int convert_time= convert(Fq[i]);
							play(convert_time, 500);
							if(i = 7) {
									index = 0;
									flag = FINISH;
							}
						}
					}
					}
				}
			
			delay(10);
		}	
	}
	
	return 0;
}
