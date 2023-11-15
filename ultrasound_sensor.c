#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

#define PIN_NUM1	27
#define PIN_NUM2	29

int main(void) {
	unsigned int start_time, end_time;
	float distance;
	if(wiringPiSetup() == -1)
		return -1;
	
	pinMode(PIN_NUM1, OUTPUT);
	pinMode(PIN_NUM2, INPUT);
	
	while(1) {
			//digitalWrite(PIN_NUM1, 0);
			//delay(500);
			digitalWrite(PIN_NUM1, 1);
			delayMicroseconds(10);
			digitalWrite(PIN_NUM1, 0);
			
			while(digitalRead(PIN_NUM2) == 0) // while(digitalRead(PIN_NUM2) == 0)
			start_time = micros();
			//printf("start_time : %d\n", start_time);
			while(digitalRead(PIN_NUM2) == 1)	// while(digitalRead(PIN_NUM2) == 1)
			end_time = micros();
			//printf("end_time : %d\n", end_time);
			
			distance = (float)(end_time - start_time) / 58.0;
			printf("distance: %.2f cm\n", distance);
			sleep(1);
	}
}
