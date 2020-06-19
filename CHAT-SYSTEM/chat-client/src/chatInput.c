/*
*	FILE		  : chatInput.c
*	PROJECT		  : SENG*2030 - System Programming
*	PROGRAMMER	  : Amy Dayasundara, Paul Smith
*	FIRST VERSION	  : 2020-04-11	
*	DESCRIPTION	  : Contains functions for the taking and formatting
*                 		of user input.					
*/

#include "../inc/clientInclude.h"
#include "../inc/clientConstant.h"
#include "../inc/clientStructs.h"
#include "../inc/clientPrototypes.h" 

/*
Function	:	processCommand
Description	:	This function determines what commands the user may have entered 
Paramters	:	char *command	:	the command to be checked
Returns		:	FAILURE		:	command was invalid
			NAME_CODE	:	command was username
              		IP_CODE         : 	command was address
*/
int processCommand(char *command) 
{
  int counter = 0;
	char testC[COMMAND_BUFFER] = "";				//	buffer for holding command
	memset(testC, 0, sizeof(testC));			// cleared to ensure future compares succeed
	
	if(strlen(command) <= (MAX_IP + 1))	// checks if string is correct # of characters for name
	{
		strncpy(testC, command, 1);	// copies command into variable for further checks
	}

	if(strcmp(testC, SWITCH_CHAR) != 0 && strlen(command) == 1) 	// ensures length is greater than switch alone			
	{    
		return FAILURE;
	}
  strcpy(testC, command);
  if(strlen(command)<=(MAX_USERNAME+1))   // checks against potential user name
  {
    for(counter = 1; counter<strlen(command);counter++) 
    {
      if(isdigit(command[counter])!=0)          // ensures there are no weird names by checking for numbers
      {
        return FAILURE;
      }
    }
    return NAME_CODE;                           // if name is relatively normal successfuly name code is returned
  }
  else if(strlen(command)>=6 && strlen(command)<=(MAX_IP+1))  //checks against potential IP address
  {    
    if(validateIP(command)==SUCCESS) //command called for the validation of IPs
    {      
      return IP_CODE;
    }
    else
    {      
      return FAILURE;
    }    
  }
  return FAILURE;
}

/*
Function	:	validateIP
Description	:	Ensures the IP entered is valid 
Paramters	:	char *ip	:	string containing potential IP address
Returns		:	FAILURE		:	string was invalid
			SUCCESS		:	string was valid
*/
int validateIP(char *ip)
{
  int counter = 0;
  char buffer[BUFFER_LENGTH] = "";
  char *token = "";
  const char period[2] = ".";

  strcpy(buffer, ip+1);  
  token = strtok(buffer, period); //string is tokenized to check between '.'
           
  while(token != NULL) // runs through entire string
  {
    for(counter=0;counter<strlen(token);counter++)
    {
      if(isdigit(token[counter])==0)  // checks to ensure each character is digit
      {
        return FAILURE;
      }        
    }    
    token = strtok(NULL, period); // string token moved forward
  }  
  return SUCCESS;
}

/*
Function	:	parseCommand
Description	:	copies command to string, minus the hyphen 
Paramters	:	char *command	:	string containing command to be copied
Returns		:	char* buffer	:	buffer to hold new command
Returns		:	NONE
*/
void parseCommand(char *command, char *buffer) 
{
  strcpy(buffer, command+1); //correctly copies command without switch
}



/*
Function	:	constructDispMsg
Description	:	builds message to be sent to server/displayed in chat
Paramters	:	char *output	:	string to copy completed message into
              		char *ip	:	string containing IP address
              		char *username	:	string containing user name
              		char *content	:	string containing message content
Returns		:	NONE
*/
void constructDispMsg(char *output, char *ip, char *username, char *content)
{
  int counter = 0;
  char buffer[BUFFER_LENGTH] = "";

  // if statement for correctly adding IP address to message
  if(strlen(ip)<MAX_IP)
  {
    for(counter = MAX_IP; counter >= 0;counter--)
    {
      if(content[counter] == '\0')  // appends 0 spaces to string
      {
        content[counter] = ' ';
      }
      else
      {
        break;
      }        
    }
  }
  strcpy(buffer, ip);
  strcat(buffer, " ["); // appends beginning of next section

  // if statement for correctly adding name to message
  if(strlen(username)<MAX_USERNAME)
  {
    for(counter = (MAX_USERNAME-1); counter >= 0;counter--)
    {
      if(username[counter] == '\0')
      {
        username[counter] = ' ';
      }
      else
      {
        break;
      }       
    }
  }
  strcat(buffer, username); // result appended to end of string
  strcat(buffer, "] %s "); // append left open to format for input or output
  
  // if statement for correctly adding content to message
  if(strlen(content)<MAX_LINE)
  {
    for(counter = MAX_LINE; counter >= 0;counter--)
    {
      if(content[counter] == '\0')
      {
        content[counter] = ' ';
      }
      else
      {
        break;
      }        
    }
  }
  strcat(buffer, content);  // message appended to buffer
  strcat(buffer, " (");     // prepares for appending time
  strcpy(output, buffer);   // output string receies constructed string
}

/*
Function		:	timeMaker
Description	:	builds message to be sent to server/displayed in chat
              time-string construction: https://stackoverflow.com/questions/1531055/time-into-string-with-hhmmss-format-c-programming
Paramters	  :	char *output		:	string on which time is appended
Returns		  :	NONE
*/
void timeMaker(char *output)
{
  time_t current_time;
  struct tm * time_info;
  char tString[12];

  time(&current_time);  
  time_info = localtime(&current_time); // client local time applied to variable
  strftime(tString, sizeof(tString), "%H:%M:%S)", time_info); // time values applied to string
  strcat(output, tString);
}
