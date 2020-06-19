/*
*	FILE		: serverMain.c
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		Discussion of messaging scheme and data structure. The server will
*		gain the knowledge of the user when the client connects to the server. 
*		The client will be able to send their IP and username upon
*		initialization. When the server receives a >>bye<< it will exit the loop
*		for the user that the thread it's being run on and delete the user from
*		the array that it is stored in. The list of clients are managed in an
*		array and the information of each client is store in a struct format.
*		
*					
*/

#include "../inc/serverInclude.h"
#include "../inc/serverConstant.h"
#include "../inc/serverStructs.h"
#include "../inc/serverPrototypes.h" 

// used for accepting incoming command and also holding the command's response
char buffer[BUFSIZ];

int main(int argc, char* argv[])
{
	int 			serverSocket = 0;
	int 			clientSocket = 0;
	unsigned int		cliLength = 0;
	int 			connection = 0;
	struct sockaddr_in 	cliAddr;

	pthread_t		pThreadClient;
	
	int 			length = 0;
	int 			counter = 0;
	int			uID = 0; 


	//Set up socket for the server
	//Initialize the server info for binding
	serverSocket = initializeServer();
	
	while(RUN)
	{	
		int clientLength = 0;
		//Single connection
		clientLength = sizeof(cliAddr);

		/* ACCEPT CONNECTION */
		connection = accept(serverSocket, (struct sockaddr*)&cliAddr, &cliLength);
	
		printf("Connected\n");

		// Chech Maximum
		if((nClient + 1)== MAX_CLIENTS)
		{
			printf("Max connections met. Connection DENIED, betch: \n");
			printClientAddress(cliAddr);			
			close(connection);
			continue;				
		}

		/* Client settings */
		clientThread *assignCli = (clientThread *)malloc(sizeof(clientThread));
		assignCli->address = cliAddr;
		assignCli->socketConnection = connection;
		assignCli->userID = uID++;

		//Add client to array
		addClientToList(assignCli);
		pthread_create(&pThreadClient, NULL, &clientConnection, (void*)assignCli);

		sleep(1);
		
	}

	return 0;
	
}

