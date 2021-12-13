#ifdef HAVE_DK
#include "DK/stdafx.h"
#include "assets.h"
#include "App.h"

#if WIN32
	#include "conio.h"
#else
	#include <termios.h>  //for system()
	static struct termios current, saved;
#endif
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
void initTermios(int echo)
{
	tcgetattr(0, &old);              // save current terminal settings 
	current = old;                   // store them
	current.c_lflag &= ~ICANON;      // disable buffered i/o
	if (echo) {
		current.c_lflag |= ECHO;     // set echo mode on
	}
	else {
		current.c_lflag &= ~ECHO;    // set echo mode off
	}
	tcsetattr(0, TCSANOW, &current);  // use created terminal settings

	/*
	// Fallback shell command method
	if (echo) {
		system("stty raw echo"); // Set terminal to raw mode with echo, (no wait for enter)
	}
	else {
		system("stty raw -echo"); // Set terminal to raw mode without echo, (no wait for enter)
	}
	*/
}

void restoreTermios(void)
{
	tcsetattr(0, TCSANOW, &old);
	// Fallback shell command method
	// system("stty cooked"); // Reset terminal to normal "cooked" mode
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
	char ch;
	initTermios(echo);
	ch = getchar();
	restoreTermios();
	return ch;
}

/* Read 1 character without echo */
char getch(void)
{
	return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
	return getch_(1);
}
#endif //!WIN32




bool App::Init() {

	while (1) {
		/*
		char c;
		printf("(getche example) please type a letter: ");
		c = getche();
		printf("\nYou typed: %c\n", c);
		printf("(getch example) please type a letter...");
		c = getch();
		printf("\nYou typed: %c\n", c);
		*/

		int b; // The getchar function returns an int (important for EOF check)
		int a = getch();
		if (a == 0 || a == 224){ //  Escape read, there's more characters to read
			int b =  getch();
			if (b == 79) { // It's a function key, there's one more characters to read
				 int c = getch();
				 printf("   c->%d-%d-%d\n", a, b, c);
			}
			else {
				 printf("   b->%d-%d\n", a, b);  // Not a function key, perhaps Alt-D?
			}
		}
		else {
			printf("   a->%d\n", a);     // Not escape, a normal key...
		}		
	}
}

#endif //HAVE_DK
