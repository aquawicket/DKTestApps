#ifdef HAVE_DK
#include "DK/stdafx.h"
#include "assets.h"
#include "App.h"

#if WIN32
	#include "conio.h"
#else
	#include <termios.h>  //for system()
	static struct termios old, current;
#endif
#include <stdio.h>
#include <stdlib.h>



bool App::Init(){
	
	while (1) {
		char c;
		printf("(getche example) please type a letter: ");
		c = getche();
		printf("\nYou typed: %c\n", c);
		printf("(getch example) please type a letter...");
		c = getch();
		printf("\nYou typed: %c\n", c);

	/*
		int a, b; // The getchar function returns an int (important for EOF check)
		if ((a = GetChar()) == 27) { //  Escape read, there's more characters to read
			if ((b = getchar()) == 79) { // It's a function key, there's one more characters to read
				 int c = getchar();
				 printf("->TO USER %d\n", c);
			}
			else {
				 printf("->TO USER %d\n", b);  // Not a function key, perhaps Alt-D? 
			}
		}
		else {
			printf("->TO USER %d\n", a);     // Not escape, a normal key...
		}
	*/
	}
}

#ifndef _WIN32
void initTermios(int echo){
	tcgetattr(0, &old); /* grab old terminal i/o settings */
	current = old; /* make new settings same as old settings */
	current.c_lflag &= ~ICANON; /* disable buffered i/o */
	if (echo) {
		current.c_lflag |= ECHO; /* set echo mode */
	}
	else {
		current.c_lflag &= ~ECHO; /* set no echo mode */
	}
	tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */

	//system("stty raw"); // Set terminal to raw mode, (no wait for enter)
}

void restoreTermios(void){
	tcsetattr(0, TCSANOW, &old);
	//system("stty cooked"); // Reset terminal to normal "cooked" mode
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo){
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

/* Read 1 character without echo */
char getch(void){
	return getch_(0);
}

/* Read 1 character with echo */
char getche(void){
	return getch_(1);
}
#endif //!WIN32



#endif //HAVE_DK
