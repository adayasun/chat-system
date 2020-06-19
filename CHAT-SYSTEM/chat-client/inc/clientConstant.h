/*
*	FILE		: clientConstant.h
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06
*	DESCRIPTION	: 	
*		This file contains the constants
*					
*/

// global to keep track of the number of connections
static unsigned int 	nClients = 0;
char			name[5];
static int 		socketConnection = 0;
static int 		flag = 0;

#define PORT 		5000
#define RUN 		1
#define BYE		">>bye<<"
#define LINE_MAX	80
#define LINE		40	
#define MAX_CLIENTS	10
#define SERVER_BACKLOG	10
#define SOCKERROR	0
#define NAME_SIZE	5
char    IPbuffer[BUFSIZ];

#define SINGLE		1
#define	PART_ONE	2
#define PART_TWO	3

WINDOW *msgWin; 
WINDOW *inpWin;
WINDOW *msgWinBox;
WINDOW *inpWinBox;
static int cursor = 0;

#define BUFFER_LENGTH	80
#define COMMAND_BUFFER 20
#define MAX_LINE 40
#define MAX_MESSAGE 80
#define WINDOW_WIDTH 90
#define CHAT_HISTORY_HEIGHT 15
#define INPUT_HEIGHT 7
#define MAX_DISPLAY 10

#define FAILURE -1
#define SUCCESS 1
#define NAME_CODE 2
#define IP_CODE 3

#define MAX_USERNAME 5
#define MAX_IP 16
#define MIN_IP 7
#define SWITCH_CHAR "-"
#define TIME_LENGTH 9

#define MESSAGE_HEADER "Messages"
#define INPUT_HEADER "Outgoing Message"