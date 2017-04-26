//var url = "http://google.com";
var url = "chrome://gpu";
var width = 800;
var height = 600;
DKCreate("DKCef,Cef,0,0,"+width+","+height+","+url);
//var currentBrowser = DKCef_GetCurrentBrowser("Cef");
//DKCef_SetUrl("Cef", url, currentBrowser);
//DKCef_SetFocus("Cef");

DKCreate("DKDebug/DKDebug.js");
//DKAddEvent("GLOBAL", "resize", User_OnEvent);


////////////////////////////
function User_OnEvent(event)
{	
	//TODO
	/*
	if(DK_Type(event, "resize")){
		//DKLog("User_OnEvent(): resize\n", DKINFO);
		var width = DKWindow_GetWidth();
		var height = DKWindow_GetHeight();
		DK_CallFunc("Cef::OnResize", "0,0,"+String(width)+","+String(height));
	}
	*/
}