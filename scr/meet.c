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



// status
#define		DEBUG

#define 	ACTIVE		0x01
#define		MUTEDELAY	0x02



// Global Variable
char status;
pid_t pid;




void INThandler(){
	FanStop() ;
	LED_OFF;
	
	exit(0);
}



void sigalrm_handler(int sig) {
status &= ~MUTEDELAY;
}

 

void StartMeeting(char *server, char *meeting, char *name) {
char buffer[450];
//"chromium --kiosk --noerrdialogs --disable-session-crashed-bubble --disable-infobars -- check-for-update-interval=604800 --disable-pinch  'https://meet.jit.si/paschkel.de#userInfo.displayName=\"Pascal\"&config.prejoinPageEnabled=false&interfaceConfig.TOOLBAR_BUTTONS=[\"microphone\",\"camera\",\"hangup\"]&interfaceConfig.TOOLBAR_ALWAYS_VISIBLE=false'"

LED_RED;

pid = fork();		// create seperate process....

if(pid == 0) {
	// build meeting link
	
	strcpy(buffer, "chromium --kiosk --noerrdialogs --disable-session-crashed-bubble --disable-infobars --check-for-update-interval=604800 --disable-pinch '");
	strcat(buffer, server);
	strcat(buffer, meeting);
	strcat(buffer, "#userInfo.displayName=\"");
	strcat(buffer, name);
	strcat(buffer, "\"&config.prejoinPageEnabled=false&interfaceConfig.TOOLBAR_BUTTONS=[\"microphone\",\"camera\",\"hangup\",\"tileview\"]&interfaceConfig.TOOLBAR_ALWAYS_VISIBLE=true' --use-fake-ui-for-media-stream");

	system(buffer); 

	exit(EXIT_SUCCESS);
	}
}

void PrepareMeeting(char number) {
	
	if(!(status & ACTIVE)) {
		status |= ACTIVE;
		#ifdef DEBUG					
		printf("START Meeting %d\n", number);
		#endif
		// Open MeetingRoom File
		//StartMeeting("https://meet.jit.si/", "maximewird5", "Maxime");
		}
	}


void TerminateMeeting(void) {
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
	}




int main()
{
char devname[] = "/dev/input/by-path/platform-ir-receiver@f-event";
int device = open(devname, O_RDONLY);
struct input_event ev;
char meetingRoom;

meetingRoom = 1;


status = 0;

signal(SIGINT, INThandler);					// Interrupt for CRRL + C to break
signal(SIGALRM, &sigalrm_handler);  		// set a signal handler for mute delay

					
system("sudo ir-keytable -p " INIT_IR_FRAME_FORMAT); 	// define IR frame format


//system("v4l2-ctl --set-ctrl rotate=180");	// Rotate picture
system("v4l2-ctl -p 10");					// 15 fps


wiringPiSetup();
pinMode(PIN_LED_RED, OUTPUT); 
pinMode(PIN_LED_GREEN, OUTPUT); 	
LED_GREEN;

FanInit();






while(1)
	{
	FanControl(status & ACTIVE);
		
	read(device,&ev, sizeof(ev));
	//if(1) {
	if(ev.type == INIT_IR_EVENT_TYPE && ev.code == INIT_IR_EVENT_CODE){
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

			case FAV_2:						// Start Video Call - FAV 2
				if(!(status & ACTIVE)) {
					status |= ACTIVE;
					#ifdef DEBUG					
					printf("START\n");
					#endif
					StartMeeting("https://meet.jit.si/", "maximewird5", "Maxime");
					}
				break;			

			case FAV_3:						// Start Video Call - FAV 3
					PrepareMeeting(3);
				break;	

			case FAV_4:						// Start Video Call - FAV 4
					PrepareMeeting(4);
				break;	
				
			case FAV_5:						// Start Video Call - FAV 5
					PrepareMeeting(5);
				break;					
								
			case RED:						// End Video Call
					TerminateMeeting();
				break;

			case ON_OFF:					// Shut down
					LED_OFF;					
					system("sudo halt");
				break;				

			case MINUS:
					if(meetingRoom > 0) meetingRoom--;
					#ifdef DEBUG
						printf(">>> %d\n", meetingRoom);
					#endif
				break;	
				
			case PLUS:
					if(meetingRoom < 5) meetingRoom++;
					#ifdef DEBUG
						printf(">>> %d\n", meetingRoom);
					#endif
				break;		
								
			default:
					#ifdef DEBUG
					printf("NOP\n");
					#endif
			}						
						
		}
	}
}
