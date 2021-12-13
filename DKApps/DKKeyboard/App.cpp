#ifdef HAVE_DK
#include "DK/stdafx.h"
#include "assets.h"
#include "App.h"

#include <stdio.h>
#include <stdlib.h>

bool App::Init(){
	
	int i=0;
	while(i<6){
	printf("> \n");
	int ch;
    while ((ch=getchar()) != EOF)   /* read/print "abcde" from stdin */
        printf("%d", ch);
	
	
		i++;
	}
	return true;
}

#endif //HAVE_DK