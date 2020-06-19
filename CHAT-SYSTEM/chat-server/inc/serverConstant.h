/*
*	FILE		: serverConstant.h
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06
*	DESCRIPTION	: 	
*		This file contains the constants and global variables
*					
*/

// global to keep track of the number of connections

static unsigned int nNoConnections = 0;
static _Atomic unsigned int nClient = 0;
static int uID = 10;

#define PORT 		5000
#define RUN 		1
#define BYE		">>bye<<"
#define LINE_MAX	80
#define MAX_CLIENTS	10
#define SERVER_BACKLOG	10
#define SOCKERROR	0
#define NAME_SIZE	8

#define SEP 		':'
#define IP_SIZE 	20
