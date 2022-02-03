#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "irController.h"
#include "led.h"
#include "fan.h"





void INThandler(){
	FanStop() ;
	LED_OFF;
	
	exit(0);
}



int main()
{
char input;
	
printf("Hardware Test\n");

signal(SIGINT, INThandler);					// Interrupt for CRRL + C to break


wiringPiSetup();
pinMode(PIN_LED_RED, OUTPUT); 
pinMode(PIN_LED_GREEN, OUTPUT); 	

FanInit();


LED_GREEN;
printf("1. LED Green?\n");
scanf("%s", &input);

LED_RED;
printf("2. LED red?\n");
scanf("%s", &input);
LED_OFF;

FanTest();
printf("3. Fan on?\n");
scanf("%s", &input);
FanStop();


printf("4. Audio Test - PLease make noise!\n\n");
system("arecord -D dmic_sv -c2 -r 44100 -f S32_LE -t wav -V mono  HardwareTestAudio.wav --duration=5"); 

system("aplay -D hw:b1 HardwareTestAudio.wav"); 

printf("\n\nDid Sound Worked?\n");
scanf("%s", &input);


}
