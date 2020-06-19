/*
*	FILE		: serverPrototypes.h
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

/* serverConnection.c */
void *clientConnection(void *cThread);
void printClientAddress(struct sockaddr_in addr);
void strTrim (char* message, int length);
void addClientToList(clientThread *connectClient);
void removeClient(int uID);
void sendMsg(char *msg, int uID);

/* serverMain.c */

