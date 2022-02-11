#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rooms.h"


int CountRooms(void) {
    
    int linecounter = 0;
    FILE *file;
    char line[MAX_LINE_LENGTH] = {};

    // Open the file in the path.
    if((file = fopen(ROOM_FILE, "r")) < 0) {
        printf("cost file open error\n");
        }


   // Get each line until there are none left
    while (fgets(line, MAX_LINE_LENGTH, file))
        linecounter++;


    // Close the file in the path.
    if(fclose(file) < 0) {
        printf("cost file close error\n");
        }

    
    return  --linecounter;
    }


struct MeetingRoom GetMeetingRoom (int index) {
	
FILE *file;
char line[MAX_LINE_LENGTH] = {};
struct MeetingRoom mem;
int  linecounter = 0;
char * token;


    // Open the file in the path.
    if((file = fopen(ROOM_FILE, "r")) < 0) {
        printf("cost file open error\n");
        }


   // Get each line until there are none left
    while (fgets(line, MAX_LINE_LENGTH, file) && (linecounter++ < index));

    token = strtok( line, ";");
    mem.RoomName = token;
    token = strtok( NULL, ";");    
    mem.MeetingSytem = token;
    token = strtok( NULL, ";");    
    mem.RoomLink = token;
    token = strtok( NULL, ";");   
    mem.DisplayName = token;      


    // Close the file in the path.
    if(fclose(file) < 0) {
        printf("cost file close error\n");
        }

return mem;
} 

	
