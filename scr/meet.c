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
#include "rooms.h"


#define		VERSION		"1.01"


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

 

void StartMeeting(struct MeetingRoom room) {

char * buffer;

LED_RED;

pid = fork();		// create seperate process....

if(pid == 0) {
	// build meeting link	
	asprintf(&buffer, "chromium --kiosk --noerrdialogs --disable-session-crashed-bubble --disable-infobars --check-for-update-interval=604800 --disable-pinch '%s%s#userInfo.displayName=\"%s\"&config.prejoinPageEnabled=false&interfaceConfig.TOOLBAR_BUTTONS=[\"microphone\",\"camera\",\"hangup\",\"tileview\"]&interfaceConfig.TOOLBAR_ALWAYS_VISIBLE=true' --use-fake-ui-for-media-stream", room.ServerLink, room.RoomLink, room.DisplayName );
	system(buffer); 
	
	free(buffer);
	exit(EXIT_SUCCESS);
	}
}


void PrepareMeeting(char number) {
	
struct MeetingRoom room;
	
	if(!(status & ACTIVE)) {
		status |= ACTIVE;
		#ifdef DEBUG					
		printf("START Meeting %d\n", number);
		#endif
		// Open MeetingRoom File
		room = GetMeetingRoom(number);
		#ifdef DEBUG
		printf("Meeting Room: %s%s %s \n", room.ServerLink, room.RoomLink, room.DisplayName);
		#endif
		StartMeeting(room);
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


void ShowRoom(int number) {
	struct MeetingRoom room;
	room = GetMeetingRoom(number);
	#ifdef DEBUG
	printf("Meeting Room: %d - %s\n", number, room.RoomName);
	#endif
	}


int main()
{
char devname[] = "/dev/input/by-path/platform-ir-receiver@f-event";
int device = open(devname, O_RDONLY);
struct input_event ev;
char meetingRoom;

meetingRoom = 1;


status = 0;

printf("Version " VERSION "\n");

signal(SIGINT, INThandler);					// Interrupt for CRRL + C to break
signal(SIGALRM, &sigalrm_handler);  		// set a signal handler for mute delay

					
system("sudo ir-keytable -p " INIT_IR_FRAME_FORMAT); 	// define IR frame format


system("v4l2-ctl --set-ctrl rotate=180");	// Rotate picture
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
				if(!(status & ACTIVE) && !(status & MUTEDELAY)) {
					#ifdef DEBUG
					printf("UPDATE\n");
					#endif
					LED_YELLOW;
					system("~/Meet/update.sh");
					status |= MUTEDELAY;
					alarm(1);  		
					}
				break;
								
			case GREEN:						// Start Video Call
					PrepareMeeting(meetingRoom);
				break;

			case FAV_1:						// Start Video Call - FAV 1
					PrepareMeeting(1);
				break;			

			case FAV_2:						// Start Video Call - FAV 2
					PrepareMeeting(2);
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
					if(!(status & ACTIVE) && !(status & MUTEDELAY)) {
						if(meetingRoom > 1) meetingRoom--;
						#ifdef DEBUG
							printf(">>> %d\n", meetingRoom);
						#endif
						status |= MUTEDELAY;
						alarm(1);  				// Just one event per second
						ShowRoom(meetingRoom);		
						}		

				break;	
				
			case PLUS:
					if(!(status & ACTIVE) && !(status & MUTEDELAY)) {
						if(meetingRoom < CountRooms() ) meetingRoom++;
						#ifdef DEBUG
							printf(">>> %d\n", meetingRoom);
						#endif
						status |= MUTEDELAY;
						alarm(1);  				// Just one event per second
						ShowRoom(meetingRoom);								
						}

				break;		
								
			default:
					#ifdef DEBUG
					printf("NOP\n");
					#endif
			}						
						
		}
	}
}
