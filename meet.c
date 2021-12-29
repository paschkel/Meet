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

// Hardware
#define 	PIN_FAN			11
#define 	PIN_LED_RED		22
#define 	PIN_LED_GREEN	21

#define     LED_OFF   	digitalWrite(PIN_LED_RED, LOW); digitalWrite(PIN_LED_GREEN, LOW)
#define     LED_RED   	digitalWrite(PIN_LED_RED, HIGH); digitalWrite(PIN_LED_GREEN, LOW)
#define     LED_GREEN  	digitalWrite(PIN_LED_RED, LOW); digitalWrite(PIN_LED_GREEN, HIGH)
#define     LED_YELLOW 	digitalWrite(PIN_LED_RED, HIGH); digitalWrite(PIN_LED_GREEN, HIGH)


// status
#define		DEBUG

#define 	ACTIVE		0x01
#define		MUTEDELAY	0x02






char status;
pid_t pid;




void INThandler(){
	softPwmWrite (PIN_FAN, 0) ;
	LED_OFF;
	
	exit(0);
}



void sigalrm_handler(int sig) {
status &= ~MUTEDELAY;
}


int readCPU_Temp(void){
 char buffer[10];
 FILE * temp;
 
 temp = fopen("/sys/class/thermal/thermal_zone0/temp","rt");
 fread(buffer,10,1,temp);
 fclose(temp);
  
 return strtol(buffer, NULL, 10)/1000; 	
 }
 
 
 
void FanControl(void) {
	
	if(70 < readCPU_Temp()) {
		if((status & ACTIVE))
			softPwmWrite (PIN_FAN, 30);		
		else
			softPwmWrite (PIN_FAN, 80);
		}
	else
		softPwmWrite (PIN_FAN, 0);	
		
	} 
 
 

void StartMeeting(char *server, char *meeting, char *name) {
char buffer[450];
//"chromium-browser --kiosk --noerrdialogs --disable-session-crashed-bubble --disable-infobars -- check-for-update-interval=604800 --disable-pinch --kiosk 'https://meet.jit.si/paschkel.de#userInfo.displayName=\"Pascal\"&config.prejoinPageEnabled=false&interfaceConfig.TOOLBAR_BUTTONS=[\"microphone\",\"camera\",\"hangup\"]&interfaceConfig.TOOLBAR_ALWAYS_VISIBLE=false'"


LED_RED;

pid = fork();		// create seperate process....

if(pid == 0) {
	// build meeting link
	
	strcpy(buffer, "chromium-browser --kiosk --noerrdialogs --disable-session-crashed-bubble --disable-infobars --check-for-update-interval=604800 --disable-pinch '");
	strcat(buffer, server);
	strcat(buffer, meeting);
	strcat(buffer, "#userInfo.displayName=\"");
	strcat(buffer, name);
	strcat(buffer, "\"&config.prejoinPageEnabled=false&interfaceConfig.TOOLBAR_BUTTONS=[\"microphone\",\"camera\",\"hangup\",\"tileview\"]&interfaceConfig.TOOLBAR_ALWAYS_VISIBLE=true' --use-fake-ui-for-media-stream");

	system(buffer); 

//	system("chromium-browser --kiosk --noerrdialogs --disable-session-crashed-bubble --disable-infobars --check-for-update-interval=604800 --disable-pinch --kiosk 'https://meet.jit.si/paschkel#userInfo.displayName=\"pascal\"&config.prejoinPageEnabled=false&interfaceConfig.TOOLBAR_BUTTONS=[\"microphone\",\"camera\",\"hangup\",\"tileview\"]&interfaceConfig.TOOLBAR_ALWAYS_VISIBLE=true' --use-fake-ui-for-media-stream"); 
//	system("chromium-browser  'https://meet.jit.si/paschkel' "); 

	exit(EXIT_SUCCESS);
	}
}




int main()
{
char devname[] = "/dev/input/by-path/platform-ir-receiver@f-event";
int device = open(devname, O_RDONLY);
struct input_event ev;


status = 0;

signal(SIGINT, INThandler);					// Interrupt for CRRL + C to break
signal(SIGALRM, &sigalrm_handler);  		// set a signal handler for mute delay

					
INIT_IR_FRAME_FORMAT;


//system("v4l2-ctl --set-ctrl rotate=180");	// Rotate picture
//system("v4l2-ctl -p 15");					// 15 fps


wiringPiSetup();

pinMode(PIN_LED_RED, OUTPUT); 
pinMode(PIN_LED_GREEN, OUTPUT); 	
LED_GREEN;

pinMode(PIN_FAN, OUTPUT); 	
softPwmCreate (PIN_FAN, 0, 100) ;
	




while(1)
	{
	FanControl();
		
	read(device,&ev, sizeof(ev));
	//if(1) {
	if(ev.type == 4 && ev.code == 4){
		#ifdef DEBUG
		printf("Type: %i Code: %i Value: %i\n",ev.type, ev.code, ev.value);
		#endif
					
		switch (ev.value) {
			case MUTE:						// MUTE MIC
				if((status & ACTIVE) && !(status & MUTEDELAY)) {
					#ifdef DEBUG
					printf("MUTE\n");
					#endif
					system("xdotool key \"m\"");
					status |= MUTEDELAY;
					alarm(1);  				// Just one mute event per second
					}
				break;
				
			case VIDEO:						// VIDEO OFF
				if((status & ACTIVE) && !(status & MUTEDELAY)) {
					#ifdef DEBUG
					printf("VIDEO\n");
					#endif
					system("xdotool key \"v\"");
					status |= MUTEDELAY;
					alarm(1);  				// Just one mute event per second
					}
				break;

			case VIEW:						// Change view
				if((status & ACTIVE) && !(status & MUTEDELAY)) {
					#ifdef DEBUG
					printf("VIEW\n");
					#endif
					system("xdotool key \"w\"");
					status |= MUTEDELAY;
					alarm(1);  				// Just one event per second
					}
				break;
								
			case GREEN:						// Start Video Call
				if(!(status & ACTIVE)) {
					status |= ACTIVE;
					#ifdef DEBUG					
					printf("START\n");
					#endif
					StartMeeting("https://meet.jit.si/", "paschkel.de", "Pascal");
					}
				break;

			case FAV_1:						// Start Video Call - FAV 1
				if(!(status & ACTIVE)) {
					status |= ACTIVE;
					#ifdef DEBUG					
					printf("START\n");
					#endif
					StartMeeting("https://meet.studiumdigitale.uni-frankfurt.de/", "smhTtjkFWI", "PI");
					}
				break;			

			case FAV_2:						// Start Video Call - FAV 1
				if(!(status & ACTIVE)) {
					status |= ACTIVE;
					#ifdef DEBUG					
					printf("START\n");
					#endif
					StartMeeting("https://meet.jit.si/", "maximewird5", "Maxime");
					}
				break;			

				
			case RED:						// End Video Call
				if(status & ACTIVE) {
					status &= ~ACTIVE;
					#ifdef DEBUG
					printf("END\n");
					#endif
					
					LED_GREEN;
					
					if(pid > 0) {
						system("xdotool key alt+F4");
						wait(NULL);				// kill also second process...
						}
					}
				break;

			case ON_OFF:						// Shut down
					system("sudo halt");
					LED_OFF;
				break;				

			case MINUS:

				break;	
				
			case PLUS:

				break;		
								
			default:
					#ifdef DEBUG
					printf("NOP\n");
					#endif
			}						
						
		}
	}
}
