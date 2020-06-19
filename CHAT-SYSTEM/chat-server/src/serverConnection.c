/*
*	FILE		: serverConnection.c
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-06	
*	DESCRIPTION	: 	
*		This file sets up connections and maintains the connections for the 
*		thread
*					
*/

#include "../inc/serverInclude.h"
#include "../inc/serverConstant.h"
#include "../inc/serverStructs.h"
#include "../inc/serverPrototypes.h"

pthread_mutex_t clientsMutex = PTHREAD_MUTEX_INITIALIZER;

/*
* FUNCTION	: clientConnection
* 
* DESCRIPTION	: Starts a thread for the new client in the server
*
* PARAMETERS	: void *cThread : allocation of the pThread
*
* RETURNS	: Nothing
*/

void *clientConnection(void *cThread)
{
  char buffer[BUFSIZ];
  char name[NAME_SIZE];
  int endChat = 0;

  nClient++;
  clientThread *runThread = (clientThread *)cThread;

  // Name
  if (recv(runThread->socketConnection, name, BUFSIZ, 0) <= 0 || strlen(name) < 2 || strlen(name) >= 32 - 1)
  {
    printf("Didn't enter the name.\n");
    endChat = 1;
  }
  else
  {
    char *position;
    int pos = 0;
    int recvLength = 0;
    char IPAddress[20];

    recvLength = strlen(name); //Total Length
    position = strchr(name, SEP);
    pos = strlen(position); 

    strncpy(IPAddress, name, (recvLength - pos));
    IPAddress[recvLength - pos] = '\0';

    strcpy(name, &name[recvLength - pos + 1]);

    strcpy(runThread->name, name);
    strcpy(runThread->IPAddr, IPAddress);
    sprintf(buffer, "%s has joined [%s]\n", runThread->name, runThread->IPAddr);
    printf("%s", buffer);
  }

  bzero(buffer, BUFSIZ);

  while (RUN)
  {
    if (endChat)
    {
      break;
    }

    int receive = recv(runThread->socketConnection, buffer, BUFSIZ, 0);
    if (receive > 0) //Make sure there is a message received
    {
      if (receive == 0 || strcmp(buffer, BYE) == 0)
      {
        sprintf(buffer, "%s:%s:%s has left\n", runThread->IPAddr, runThread->name, runThread->name); 
        printf("%s\n", buffer);
        sendMsg(buffer, runThread->userID);
        endChat = 1;
      }
      else if (strlen(buffer) > 0)
      {
        strTrim(buffer, strlen(buffer));
        sendMsg(buffer, runThread->userID);

        printf("Message from : %s\n", buffer);
      }
      else
      {
        printf("ERROR: -1\n");
        endChat = 1;
      }
    }

    bzero(buffer, BUFSIZ);
    sleep(1);
  }

  /* Delete client from queue and yield thread */
  close(runThread->socketConnection);
  removeClient(runThread->userID);
  free(runThread);
  nClient--;
  pthread_detach(pthread_self());

  return NULL;
}

/*
* FUNCTION	: printClientAddress
* 
* DESCRIPTION	: Print the value of the IPV4
*
* PARAMETERS	: struct sockaddr_in : To get the IPV4 value
*
* RETURNS	: Nothing
*/

void printClientAddress(struct sockaddr_in addr)
{
  printf("%d.%d.%d.%d",
         addr.sin_addr.s_addr & 0xff,
         (addr.sin_addr.s_addr & 0xff00) >> 8,
         (addr.sin_addr.s_addr & 0xff0000) >> 16,
         (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/*
* FUNCTION	: strTrim
* 
* DESCRIPTION	: Replaces the carriage return with a null
*
* PARAMETERS	: char *message - message to be altered
*		  int length - The string length of the message
*
* RETURNS	: Nothing
*/
void strTrim(char *message, int length)
{
  int counter = 0;
  for (counter = 0; counter < length; counter++)
  { // trim
    if (message[counter] == '\n')
    {
      message[counter] = '\0';
      break;
    }
  }
}

/*
* FUNCTION	: addClientToList
* 
* DESCRIPTION	: Add's client to the array
*
* PARAMETERS	: clientThread *connectClient - the recently connected client
*
* RETURNS	: Nothing
*/
void addClientToList(clientThread *connectClient)
{
  pthread_mutex_lock(&clientsMutex);
  int counter = 0;
  for (counter = 0; counter < MAX_CLIENTS; counter++)
  {
    if (!clients[counter])
    {
      clients[counter] = connectClient;
      break;
    }
  }

  pthread_mutex_unlock(&clientsMutex);
}

/*
* FUNCTION	: removeClient
* 
* DESCRIPTION	: Remove the client from the array that matches the user's ID
*
* PARAMETERS	: int uID - client to be removed
*
* RETURNS	: Nothing
*/
void removeClient(int uID)
{
  pthread_mutex_lock(&clientsMutex);
  int counter = 0;
  for (counter = 0; counter < MAX_CLIENTS; counter++)
  {
    if (clients[counter])
    {
      if (clients[counter]->userID == uID)
      {
        clients[counter] = NULL;
        break;
      }
    }
  }

  pthread_mutex_unlock(&clientsMutex);
}

/*
* FUNCTION	: sendMsg 
* 
* DESCRIPTION	: Send the received message to other clients
*
* PARAMETERS	: char *msg - the message that is to be sent to the user
*		  int uID - the user that sent the message
*
* RETURNS	: Nothing
*/
void sendMsg(char *msg, int uID)
{
  pthread_mutex_lock(&clientsMutex);
  int counter = 0;
  int lastChar = 0;
  char *endVal;
  //Check if message has 2 parts. Known as 2 and 3
  lastChar = strlen(msg) - 1;
  //strcpy(endVal, msg[lastChar]);

  for (counter = 0; counter < MAX_CLIENTS; counter++)
  {
    if (clients[counter])
    {
      if (clients[counter]->userID != uID)
      {
        if (write(clients[counter]->socketConnection, msg, strlen(msg)) < 0)
        {
          perror("ERROR: write to descriptor failed");
          break;
        }
      }
    }
  }

  pthread_mutex_unlock(&clientsMutex);
}
