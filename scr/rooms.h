

//struct MeetingRoom {
    //char RoomName[20];
    //char MeetingSytem[10];
    //char ServerLink[50];
    //char RoomLink[50];
    //char DisplayName[20];        
//};

struct MeetingRoom {
    char* RoomName;
    char* MeetingSytem;
    char* ServerLink;
    char* RoomLink;
    char* DisplayName;        
};


#define MAX_LINE_LENGTH 500

struct MeetingRoom GetMeetingRoom(int index);
void PresetRooms(void);
