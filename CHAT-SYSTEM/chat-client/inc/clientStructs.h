/*
*	FILE		: clientStructs.h
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file contains the structs.
*					
*/

typedef struct
{
	struct sockaddr_in address;
	char name[NAME_SIZE];
	int userID;
	char msg[LINE_MAX];
	int msgType;
} clientThread;



