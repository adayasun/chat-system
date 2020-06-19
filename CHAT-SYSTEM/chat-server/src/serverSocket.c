/*
*	FILE		: serverSocket.c
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file is initializes and maintains server sockets. There is a 
*		function to cut down on the lines of code for the if statement on errors
*					
*/

#include "../inc/serverInclude.h"
#include "../inc/serverConstant.h"
#include "../inc/serverStructs.h"
#include "../inc/serverPrototypes.h"

/*
* FUNCTION	: initializeServer
* 
* DESCRIPTION	: Setting up the server connection
*
* PARAMETERS	: Nothing
*
* RETURNS	: int : return the server socket value
*/
int initializeServer()
{
	int option = 1;
	int serverListen = 0;
	struct sockaddr_in servAddr;

	printf("Let's serve server sockets looks\n");
	fflush(stdout);

	/* SOCKET SETTING */
	serverListen = socket(AF_INET, SOCK_STREAM, 0);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	/* Ignore pipe signals */ //See if this is good to prevent the user from using CTRL^C
	//signal(SIGPIPE, SIG_IGN);
	checkConnection((setsockopt(serverListen, SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),(char*)&option,sizeof(option))), "ERROR: setsockopt failed");

	
	/* Bind */
	checkConnection((bind(serverListen, (struct sockaddr*)&servAddr, sizeof(servAddr))), "ERROR: Socket binding failed");
	

	/* Listen */
	checkConnection((listen(serverListen, 10)), "ERROR: Socket listening failed");
	
	return serverListen;
}


/*
* FUNCTION	: checkConnection
* 
* DESCRIPTION	: Type of error handle
*
* PARAMETERS	: int connection - connection number
*		  const char* errorMsg - If connection failed
*
* RETURNS	: int : Value of connection
*/
int checkConnection(int connection, const char* errorMsg)
{
	if(connection < SOCKERROR)
	{
		perror(errorMsg);
		exit(1);
	}
	return connection;
}
