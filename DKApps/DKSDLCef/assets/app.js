//var USE_CEF = 1;
DKCreate("DKWindow");
//var url = "file:///C:/Users/aquawicket/digitalknob/DKApps/DKIDE/assets/index.html";
var url = "http://google.com";
var width = 800;//DKWindow_GetWidth();
var height = 600;//DKWindow_GetHeight();
DKCreate("DKCef,CefSDL,0,0,"+width+","+height+","+url);
DKCef_NewBrowser("CefSDL",0,0,width,height,url);
var currentBrowser = DKCef_GetCurrentBrowser("CefSDL");
DKCef_SetUrl(0, url, currentBrowser);
//DKCef_SetFocus("CefSDL");

//DKCreate("DKDebug/DKDebug.js");

//DKAddEvent("window", "resize", User_OnEvent);


////////////////////////////
function User_OnEvent(event)
{
	/*
	if(DK_Type(event, "resize")){
		//DKLog("User_OnEvent(): resize\n", DKINFO);
		//DKCef_SetSize("CefSDL", 100, 100);
		var width = DKWindow_GetWidth();
		var height = DKWindow_GetHeight();
		DK_CallFunc("CefSDL::OnResize", "0,0,"+String(width)+","+String(height));
	}
	*/
}