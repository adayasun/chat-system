/*
*	FILE		: serverConnection.c
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file sets up connections for the clients
*					
*/

#include "../inc/clientInclude.h"
#include "../inc/clientConstant.h"
#include "../inc/clientStructs.h"
#include "../inc/clientPrototypes.h" 


pthread_mutex_t clientMutex = PTHREAD_MUTEX_INITIALIZER;

/*
* FUNCTION	: strWrite
* 
* DESCRIPTION	: Don't really need it now since the client uses ncurses
*
* PARAMETERS	: Nothing
*
* RETURNS	: Nothing
*/

void strWrite() 
{
	printf("%s", "> ");
	fflush(stdout);
}
/*
* FUNCTION	: strTrim
* 
* DESCRIPTION	: Used to replace carriage return with null
*
* PARAMETERS	: char* msg	: message
*		  int length	: length of the message 
*
* RETURNS	: Nothing
*/
void strTrim(char* msg, int length) 
{
	int counter;
	for (counter = 0; counter < length; counter++) 
	{ 
		if (msg[counter] == '\n') 
		{
			msg[counter] = '\0';
			break;
		}
	}
}


