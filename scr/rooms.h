

struct MeetingRoom {
    char* RoomName;
    char* MeetingSytem;
    char* RoomLink;
    char* DisplayName;        
};


#define     MAX_LINE_LENGTH     500
//#define     ROOM_FILE           "/home/pi/Meet/rooms.txt"
#define     ROOM_FILE           "/var/www/html/rooms.txt"


int CountRooms(void) ;
struct MeetingRoom GetMeetingRoom(int index);
