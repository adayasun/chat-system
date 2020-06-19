/*
*	FILE		: clientPrototypes.h
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file contains the prototypes.
*					
*/

/* serverSocket.c */
int checkConnection(int connection, const char* errorMsg);

/* serverSignal.c */
void clientsLeaving (int countClients);
void watchDogTimer(int sigNumb);
int initializeServer();
void catchExit(int signal);

/* serverConnection.c */
void recvMsg();
void sendMsg();
void strTrim(char* arr, int length);
void strWrite(); 

void checkHostName(int hostname);
void checkHostEntry(struct hostent * hostentry);
void checkIPbuffer(char *IPbuffer);


/* clientUI.c */
WINDOW *outputWinMaker(WINDOW *sub);
WINDOW *createNewWin(int height, int width, int starty, int startx, const char* headerTitle);
void displayMsgWin(WINDOW *win, char *word);
void createDerwin(WINDOW *dom, const char* headerTitle);
WINDOW *createMessageWin(WINDOW *dom);
void input_win(WINDOW *win, char *word);
void blankWin(WINDOW *win);
void inputWin(WINDOW *win, char *word);

/* clientInput.c */
int processCommand(char *command);
void parseCommand(char *command, char *buffer);
int validateIP(char *ip);
void constructDispMsg(char *output, char *ip, char *username, char *content);
void timeMaker(char *output);
