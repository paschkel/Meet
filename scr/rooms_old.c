#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rooms.h"


struct MeetingRoom GetMeetingRoom (int index) {
	
struct MeetingRoom mem;
FILE *infile;
int  linecounter = 0;

// Open person.dat for reading
infile = fopen ("rooms.txt", "r");
if (infile == NULL) {
    fprintf(stderr, "\nError opening file\n");
    exit (1);
    }

index--;

// read file contents till end of file
while(fread(&mem, sizeof(struct MeetingRoom), 1, infile) && (linecounter++ < index)) {
 printf("file line: %d - %s\n", linecounter, mem.RoomName);
 }


// close file
fclose (infile);

return mem;
} 

	
	
void PresetRooms(void)	{
	
	FILE *outfile;
     
    // open file for writing
    outfile = fopen ("rooms.txt", "w");
    if (outfile == NULL){
        fprintf(stderr, "\nError opened file\n");
        exit (1);
		}
 
    struct MeetingRoom input1 = {"paschkel","jitsi","https://meet.jit.si/","paschkel.de","Pascal"};
    struct MeetingRoom input2 = {"Yvonne","jitsi","https://meet.jit.si/","YvonneAusHamburg","Yvonne"};
    struct MeetingRoom input3 = {"ratamatata","jitsi","https://meet.jit.si/","ratamatata","ICH"};
    struct MeetingRoom input4 = {"TEST4","jitsi","https://meet.jit.si/","test4","Testname4"};
    struct MeetingRoom input5 = {"TEST5","jitsi","https://meet.jit.si/","test5","Testname5"};
    	     
    // write struct to file
    fwrite (&input1, sizeof(struct MeetingRoom), 1, outfile);
    fwrite (&input2, sizeof(struct MeetingRoom), 1, outfile);
    fwrite (&input3, sizeof(struct MeetingRoom), 1, outfile);
    fwrite (&input4, sizeof(struct MeetingRoom), 1, outfile);
    fwrite (&input5, sizeof(struct MeetingRoom), 1, outfile);
         

 
    // close file
    fclose (outfile);
}
