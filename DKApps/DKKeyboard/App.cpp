#ifdef HAVE_DK
#include "DK/stdafx.h"
#include "assets.h"
#include "App.h"

#if WIN32
	#include "conio.h"
#else
#endif
#include <stdio.h>
#include <stdlib.h>

// https://stackoverflow.com/a/4028974


bool App::Init() {

	bool loop = true;
	while (loop) {
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
		if (a == 0 || a == 27 || a == 224){ //  Escape read, there's more characters to read
			
		    // TODO - poll for key here with timeout
		    // https://stackoverflow.com/a/57513499
			/*
			#include <time.h>
			#define TIMEOUT 10   // milliseconds
			clock_t tstart = clock();
			int b = -1;                   // default key press
			while ((clock() - tstart) < TIMEOUT) {
				if (kbhit()) {
					b = getch();
					break;
				}
			}
			if (b == -1) {
				printf("ESCAPE KEY");
				loop = false;
				break;
			}
			*/
			if (b == 79) { // It's a function key, there's one more characters to read
				int c = getch();
				printf("FUNCTION_KEY c->%d-%d-%d\n\n", a, b, c);
			}
			else {
				printf("UNKNOWN_KEY b->%d-%d\n\n", a, b);  // Not a function key, perhaps Alt-D?
			}
		}
		else {
			printf("CHAR_KEY a->%d\n\n", a);     // Not escape, a normal key...
		}
	}
	return 0;
}

#endif //HAVE_DK
