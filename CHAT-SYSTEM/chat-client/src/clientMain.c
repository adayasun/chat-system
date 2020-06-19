/*
*	FILE		: clientMain.c
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file is the main client file that creates the threads for receiving
*		and sending a message to the server.
*					
*/

#include "../inc/clientInclude.h"
#include "../inc/clientConstant.h"
#include "../inc/clientStructs.h"
#include "../inc/clientPrototypes.h" 

// used for accepting incoming command and also holding the command's response
char buffer[BUFSIZ];


int main(int argc, char **argv)
{
	pthread_t sendThread;
	pthread_t recvThread;
	struct sockaddr_in serverAddr;

  int counter = 0;
  char ip[MAX_IP] = "";
  char buffer [MAX_LINE] = "";
	

	int retCode = 0;
	int messagesHeight, messagesWidth, messagesStartX = 0 , messagesStartY = 0;
  int inputHeight, inputWidth, inputStartX, inputStartY;
	char text[80];
  cursor = 0;
	
	if(argc != 3)
	{ // prints usage statement of proper switch format
		printf("Usage: %s -user<name> -server<xxx.xxx.xxx.xxx>\n", argv[0]);
		return EXIT_FAILURE;
	}
  else
  {   
    for(counter=1;counter<3;counter++)  // checks args for validity
    {
      retCode = processCommand(argv[counter]);  // processes ret code of command check
      if(retCode==NAME_CODE)
      {
        parseCommand(argv[counter], name);    // user entered name
      }
      else if(retCode==IP_CODE)
      {     
        parseCommand(argv[counter], ip);    // user entered IP
      }
      else
      { // user entered invalid name or IP
        printf("Usage: %s -user<name> -server<xxx.xxx.xxx.xxx>\n", argv[0]);
		    return EXIT_FAILURE;
      }     
    }
  } 	

	signal(SIGINT, catchExit);

  // Initialize window settings for ncurse library
  initscr();
	cbreak();
  refresh();

  // Window dimensions are applied
  messagesHeight = CHAT_HISTORY_HEIGHT;
  messagesWidth  = WINDOW_WIDTH;
  inputHeight = INPUT_HEIGHT;
  inputWidth = messagesWidth;
  inputStartY = messagesHeight;

	if (strlen(name) > MAX_USERNAME || strlen(name) < 1)
	{
		printf("Name must equal to or more than 1 character and equal to or less than 5 characters.\n");
		return EXIT_FAILURE;
	}		

  // NEW //
  //IP Address//
  char hostbuffer[BUFSIZ];
  

	/* Socket settings */
	socketConnection = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(PORT);

  sprintf(IPbuffer, "%d.%d.%d.%d",
          ((int)serverAddr.sin_addr.s_addr&0xFF),
          ((int)serverAddr.sin_addr.s_addr&0xFF00)>>8,
          ((int)serverAddr.sin_addr.s_addr&0xFF0000)>>16,
          ((int)serverAddr.sin_addr.s_addr&0xFF000000)>>24);

  // Connect to Server
  	int err = connect(socketConnection, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (err == -1) 
	{
		printf("ERROR: connect\n");
		return EXIT_FAILURE;
	}

	// Send name
	sprintf(hostbuffer, "%s:%s", IPbuffer, name);
  send(socketConnection, hostbuffer, BUFSIZ, 0);

// THREAD FOR SENDING MESSAGES -  FUNCTION CALL IN THIRD PARAM//	
	if(pthread_create(&sendThread, NULL, (void *) sendMsg, NULL) != 0)
	{
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}
// THREAD FOR RECEIVING MESSAGES - FUNCTION CALL IN THIRD PARAM //
	if(pthread_create(&recvThread, NULL, (void *) recvMsg, NULL) != 0)
	{
		printf("ERROR: pthread\n");
		return EXIT_FAILURE;
	}


// Initialize UI via ncurse library functions
  msgWinBox = createNewWin(messagesHeight, messagesWidth, messagesStartY, messagesStartX, MESSAGE_HEADER);
  inpWinBox = createNewWin(inputHeight, inputWidth, inputStartY, inputStartX, INPUT_HEADER);  
  msgWin = createMessageWin(msgWinBox);
  scrollok(msgWin, TRUE);
  inpWin = createMessageWin(inpWinBox); 

	while (RUN)
	{
		if(flag)
		{
			printf("\nBye\n");
			break;
		}
	}

  // socket is closed
	close(socketConnection);

  // windows are deleated
  delwin(msgWin);
  delwin(inpWin);
  delwin(msgWinBox);
  delwin(inpWinBox);  
	endwin();

	return EXIT_SUCCESS;
}

/*
* FUNCTION	: sendMsg
* 
* DESCRIPTION	: When the thread for sending messages is created this assist the thread 
*		  for sending the message to the server to manage
*
* PARAMETERS	: Nothing
*
* RETURNS	: Nothing
*/
void sendMsg() 
{
	char message[BUFSIZ] = {0};
	char goodbye[BUFSIZ] = {0};
	char buffer[BUFSIZ + 32] = {0};
	char messageFirst[40] = {0};
	char messageSecond[40] = {0};

	while(RUN) 
	{
		//strWrite();
		//fgets(message, BUFSIZ, stdin);
    inputWin(inpWin, message);        // takes input from user via input window
		strTrim(message, BUFSIZ);

		if (strcmp(message, BYE) == 0) 
		{
			for(int i = 0; i < strlen(message); i++)
			{
				if(message[i] == '\n')
				{
					message[i] = '\0';
					break;
				}	
			}
			sprintf(goodbye, "BYEBYE: %s", message); // goodbye message created to display in proper window
      displayMsgWin(msgWin, goodbye);
			sprintf(buffer, "%s: %s", name, message);
			//Send the message to the server
			sleep(3);
			send(socketConnection, buffer, strlen(buffer), 0);
			break;
		} 
	  else if(strlen(message) <= 0)
		{
		//	displayMsgWin(msgWin, "Please enter something\n");
		}
		else if (strlen(message) > MAX_LINE)
		{
			//displayMsgWin(msgWin, "long ass string\n");
			strncpy(messageFirst, message, sizeof(messageFirst));
			for(int counter = MAX_LINE; counter >= 0; counter--)
			{
				if(messageFirst[counter] == ' ')  // checks for blank spaces
				{
					//First Message
					int remainingLetters = 0;
					messageFirst[counter] = '\0';

          constructDispMsg(buffer, IPbuffer, name, messageFirst); // message constructed
					send(socketConnection, buffer, strlen(buffer), 0);      // sent to server
          sprintf(buffer, buffer, ">>");       // arrows indicating output inserted
          timeMaker(buffer);                  // time appended to string

          strcat(buffer, "\n");               
          displayMsgWin(msgWin, buffer);			// completed message displayed on client 
					bzero(buffer, BUFSIZ);              // buffer reset to zero

					//Second Part
					remainingLetters = strlen(message) - counter;   // second message is constructed to send out
					strcpy(messageSecond,  &message[counter + 1]);
					strTrim(messageSecond, BUFSIZ);

          constructDispMsg(buffer, IPbuffer, name, messageSecond);
          send(socketConnection, buffer, strlen(buffer), 0);
          sprintf(buffer, buffer, ">>");  
          timeMaker(buffer);
          displayMsgWin(msgWin, buffer);	

          break;									// after second message displayed block is exited
				}	        
			}
		}
		else 
		{
      constructDispMsg(buffer, IPbuffer, name, message);  // message less than 40 chars constructed
      sleep(2);                                           // sleep for 2 seconds to ensure ,essages don't overlap
			send(socketConnection, buffer, strlen(buffer), 0);  // message sent to server

      sprintf(buffer, buffer, ">>");  // message constructed for display in local client
      timeMaker(buffer);
      displayMsgWin(msgWin, buffer);  // message displayed						
		}

    // buffers reset to 0
		bzero(message, BUFSIZ);
		bzero(buffer, BUFSIZ+ 32);
		
	}
	catchExit(2);
}

/*
* FUNCTION	: recvMsg
* 
* DESCRIPTION	: When the receive thread is created, this maintain the thread for 
*		  receiving messages from the other clients
*
* PARAMETERS	: Nothing
*
* RETURNS	: Nothing
*/
void recvMsg() 
{
	char message[BUFSIZ] = {};
	while (RUN) 
	{
		int receive = recv(socketConnection, message, BUFSIZ, 0); // connection amde to receive message
		if (receive > 0) 
		{
    sprintf(message, message, "<<");  // cosntructs incomming message for display
    timeMaker(message);               // appends time to message
    displayMsgWin(msgWin, message);   // message displayed
		} 
		else if (receive == 0)            // breaks if no message received
		{
			break;
		}
		memset(message, 0, sizeof(message)); //buffer reset to 0
	}
}

/*
* FUNCTION	: catchExit
* 
* DESCRIPTION	: Changes the flag in the running loop for sending and receiving messages
*		  to notify the end of usage
*
* PARAMETERS	: int sig - doesn't do anything
*
* RETURNS	: Nothing
*/
void catchExit(int sig) 
{
    flag = 1;
}


