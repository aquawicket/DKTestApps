DKCreate("DKWindow");
//DKCreate("DKRocket");
//DKCreate("DKWidget");
//DKCreate("test.html");
//DKCreate("DKGui/DKFrame.js");
//DKCreate("DKDebug/DKDebug.js");
//DKCreate("scale.js");
//DKCreate("DKDom");
//DKCreate("DKNotepad/DKNotepad.js", function(){
//	DKWidget_SetProperty("DKNotepad.html", "width", "100%");
//	DKWidget_SetProperty("DKNotepad.html", "height", "100%");
//});
//DKCreate("square.html");


/////////////////////////
//ANDROID back key = exit
//DKAddEvent("GLOBAL", "keydown", User_OnEvent);
//function User_OnEvent(event)  //Duktape
//{
//	if(DK_Type(event, "keydown")){
//		if(DK_GetValue(event) == "4"){ //Exit for ANDROID
//		    DK_Exit();
//		}
//		EatMemory();
//	}
//}
//////////////////////////


//function EatMemory()
//{
//	for(var i=0; i<10000; i++){
//		DKLog("DKWindow_TestString() = "+DKWindow_TestString("this is a test string")+"\n", DKINFO);
//	}
//}
