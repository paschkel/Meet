

struct MeetingRoom {
    char* RoomName;
    char* MeetingSytem;
    char* ServerLink;
    char* RoomLink;
    char* DisplayName;        
};


#define     MAX_LINE_LENGTH     500
#define     ROOM_FILE           "/home/pi/Meet/rooms.txt"

int CountRooms(void) ;
struct MeetingRoom GetMeetingRoom(int index);
void PresetRooms(void);
