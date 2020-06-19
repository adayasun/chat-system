/*
*	FILE		: windowFunctions.c
*	PROJECT		: SENG*2030 - System Programming
*	PROGRAMMER	: Amy Dayasundara, Paul Smith
*	FIRST VERSION	: 2020-04-11	
*	DESCRIPTION	: 
*			Contains functions for the creation and management of 
*                	ncurse library windows.					
*/

#include "../inc/clientInclude.h"
#include "../inc/clientConstant.h"
#include "../inc/clientStructs.h"
#include "../inc/clientPrototypes.h" 

/*
Function	:	createNewWin
Description	:	Creates a new window to be displayed for UI purposes 
Paramters	:	int height :	desired height of the window
              		int width  :	desired width of the window
              		int starty :	starting y position of window
              		int startx :	starting x position of window
              const char* headerTitle :	string for window header
Returns		:	WINDOW *local_win :	pointer to constructed window
*/
WINDOW *createNewWin(int height, int width, int starty, int startx, const char* headerTitle)
{
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);  // new window instantiated
  
  box(local_win, 0, 0);   // draws box around window
  wmove(local_win, 1, 1); // positions cursor at top  
  
  wrefresh(local_win);    // refreshes window to display
  createDerwin(local_win, headerTitle); //calls function to create subwindow
  return local_win;
}

/*
Function		:	displayMsgWin
Description	:	Refreshes window containing chat messages for each new message
              received
Paramters	  :	WINDOW *win		     : window to display messages into
              char *word		     : string containing message to print to window          
Returns		  :	NONE
*/
void displayMsgWin(WINDOW *win, char *word)
{
  if (cursor < MAX_DISPLAY)
  {
    wmove(win, cursor, 0); // cursor moved to correct position    
  }
  else if (cursor >= MAX_DISPLAY)
  {
    wmove(win, (MAX_DISPLAY-1), 0);     // cursor now stays at bottom of window
    scroll(win);          // window scrolls to allow for continuous reading
  }
  cursor++;             //increments cursor value
  waddstr(win, word);   // string displayed in window
  curs_set(0);          // cursor reset
  wrefresh(win);  
} 

/*
Function		:	createDerwin
Description	:	Creates window containing coloured box and header for chat window
Paramters	  :	WINDOW *dom		            : window to display header
              const char* headerTitle	  : string containing message to print to header          
Returns		  :	NONE
*/
void createDerwin(WINDOW *dom, const char* headerTitle)
{
  start_color();        // enables use of colour effect
  WINDOW *local_win;
  int maxHeight =0;
  int maxWidth = 0;
  int minus = 0;
  init_pair(1,COLOR_WHITE,COLOR_BLUE);    // applies colours to header

  getmaxyx(dom, maxHeight, maxWidth); // max values of window determined
  local_win = derwin(dom, 3, maxWidth , 0, 0);  // subwindow constructed
 
  box(local_win, 0, 0);             // border created
  wbkgd(local_win,COLOR_PAIR(1));   
  minus= strlen(headerTitle)/2;     // string is centered on screen
  wmove(local_win, 1, (maxWidth/2-minus));
  waddstr(local_win, headerTitle);
  wrefresh(local_win);
}

/*
Function		:	createMessageWin
Description	:	Creates window for the taking of user input 
Paramters	  :	WINDOW *dom		     :	parent window in which message window is housed
Returns		  :	WINDOW *local_win	 :	pointer to constructed window
*/
WINDOW *createMessageWin(WINDOW *dom)
{
  WINDOW *local_win;
  int maxHeight = 0;
  int maxWidth = 0;

  getmaxyx(dom, maxHeight, maxWidth); // finds max values of passed window

  local_win = derwin(dom, maxHeight-5, maxWidth-4 , 3, 2);  // constructs derwin with appropriate height
  wrefresh(local_win);
  return local_win;
}

/*
Function	:	inputWin
Description	:	Manages input reception from user and refreshes window when finished
Paramters	:	WINDOW *win   	: window to manage/receive input from
              		char *word	: buffer to hold input from user
Returns		  :	NONE
*/
void inputWin(WINDOW *win, char *word)
{
  curs_set(1);
  int i, ch;
  int maxrow, maxcol, row = 1, col = 0;
  blankWin(win);                          // window cleared of old input 
  getmaxyx(win, maxrow, maxcol);          // get window size
  bzero(word, MAX_MESSAGE);                  // empties buffer for new insertion
  wgetnstr(win, word, MAX_MESSAGE);                       /* position cusor at top */
  
} 

/*
Function	:	blankWin
Description	:	Clears window of previous input
              		*function from example on e-conestoga: ncurses-01*
Paramters	:	WINDOW *win   : window to clear input from              
Returns		:	NONE
*/
void blankWin(WINDOW *win)
{
  int i;
  int maxrow, maxcol;
     
  getmaxyx(win, maxrow, maxcol);  //max valuefound
  for (i = 1; i < maxcol-2; i++)  // runs through loop clearing all characters from window
  {
    wmove(win, i, 1);
    refresh();
    wclrtoeol(win);
    wrefresh(win);
  }
  wrefresh(win);
}
