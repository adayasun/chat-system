/*
*	FILE		: serverStructs.h
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file contains the structs.
*					
*/

typedef struct{
	struct sockaddr_in address;
	int socketConnection;
	int userID;
	char name[NAME_SIZE];
  char IPAddr[IP_SIZE];
} clientThread;

clientThread* clients[MAX_CLIENTS];


