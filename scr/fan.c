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


#include "fan.h"

int readCPU_Temp(void){
 char buffer[10];
 FILE * temp;
 
 temp = fopen("/sys/class/thermal/thermal_zone0/temp","rt");
 fread(buffer,10,1,temp);
 fclose(temp);
  
 return strtol(buffer, NULL, 10)/1000; 	
 }
 
 
 
void FanControl(char active) {
	
	if(70 < readCPU_Temp()) {
		if(active)
			softPwmWrite (PIN_FAN, 30);		
		else
			softPwmWrite (PIN_FAN, 80);
		}
	else
		softPwmWrite (PIN_FAN, 0);	
		
	} 

void FanTest(void) {
	
	softPwmWrite (PIN_FAN, 70);
	} 
 
 
void FanStop(void) {
	softPwmWrite (PIN_FAN, 0);
	
	}
	
	
		
void FanInit(void) {
	wiringPiSetup();
	
	pinMode(PIN_FAN, OUTPUT); 	
	softPwmCreate (PIN_FAN, 0, 100) ;
	}
