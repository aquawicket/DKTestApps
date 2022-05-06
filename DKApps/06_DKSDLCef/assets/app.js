var USE_CEF = 1
var url = "chrome://gpu";
var width = 800;//CPP_DKWindow_GetWidth()
var height = 600;//CPP_DKWindow_GetHeight()

CPP_DK_Create("DKDuktapeDom")
CPP_DK_Create("DKSDLWindow")
CPP_DK_Create("DKSDLText")
CPP_DK_Create("DKCef")//,"CefSDL",0,0,width,height,url)
CPP_DKCef_NewBrowser("CefSDL",0,0,width,height,url)

//var currentBrowser = CPP_DKCef_GetCurrentBrowser("CefSDL")
//CPP_DKCef_SetUrl(0, url, currentBrowser)
//CPP_DKCef_SetFocus("CefSDL")

//CPP_DK_Create("DKDebug/DKDebug.js")

//DKAddEvent("window", "resize", User_OnEvent)
//window.addEventListener("resize", User_OnEvent)



function User_OnEvent(event){
	/*
	if(event.type == "resize"){
		console.log("User_OnEvent(): resize\n")
		//CPP_DKCef_SetSize("CefSDL", 100, 100)
		var width = CPP_DKWindow_GetWidth()
		var height = CPP_DKWindow_GetHeight()
		DK_CallFunc("CefSDL::OnResize", "0,0,"+String(width)+","+String(height))
	}
	*/
}