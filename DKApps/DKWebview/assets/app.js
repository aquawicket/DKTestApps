CPP_DK_Create("DKDuktapeDom")
if(CPP_DK_GetOS() == "Win32" || CPP_DK_GetOS() == "Win64"  || CPP_DK_GetOS() == "Mac" || CPP_DK_GetOS() == "Linux"){
	var USE_CEF = 1
}
if(CPP_DK_GetOS() == "Android"){
	var USE_Webview = 1
}

/*
if(CPP_DK_GetBrowser() == "RML"){
	CPP_DK_Create("DKWindow")
	CPP_DK_Create("DKRml")
}
*/
CPP_DK_Create("DKWebview")
CPP_DK_Create("DKDebug/DKDebug.js", function(){})


//DKAddEvent("GLOBAL", "keydown", User_OnEvent)
window.addEventListener("keydown", User_OnEvent)

function User_OnEvent(event) {  //Duktape
	console.log("event")
	
	if(event.type == "DKCef_OnQueueNewBrowser"){
		var currentBrowser = CPP_DKCef_GetCurrentBrowser("DKCef_frame");
		CPP_DKCef_SetUrl("DKCef_frame", DK_GetValue(event), currentBrowser);
	}
	if(event.type == "keydown"){
		if(event.value == "4") //Exit for ANDROID
		    CPP_DK_Exit();
	}
}


if(CPP_DK_GetBrowser() == "RML" && USE_CEF){
	var assets = CPP_DKAssets_LocalAssets()
	var url = "file:///"+assets+"/index.html"
	
	//var iframe = DKWidget_CreateElement("body", "iframe", "DKCef_frame")
	let iframe = document.createElement("iframe")
	iframe.id = "DKCef_frame";
	
	//DKWidget_SetAttribute(iframe, "src", url)
	iframe.setAttribute("src", url)
	
	DKWidget_SetProperty(iframe, "position", "absolute")
	iframe.style["position"] = "absolute";
	
	DKWidget_SetProperty(iframe, "top", "0rem")
	iframe.style["top"] = "0rem";
	
	DKWidget_SetProperty(iframe, "left", "0rem")
	iframe.style["left"] = "0rem";
	
	DKWidget_SetProperty(iframe, "width", "100%")
	iframe.style["width"] = "0rem";
	
	DKWidget_SetProperty(iframe, "bottom", "0rem")
	iframe.style["bottom"] = "0rem";
	
	var currentBrowser = CPP_DKCef_GetCurrentBrowser(iframe)
	CPP_DKCef_SetUrl(iframe, url, currentBrowser)
	CPP_DKCef_SetFocus(iframe)
	
	//DKAddEvent("GLOBAL", "DKCef_OnQueueNewBrowser", User_OnEvent)
	window.addEventListener("DKCef_OnQueueNewBrowser", User_OnEvent)
}
else if(CPP_DK_GetBrowser() == "RML" && USE_Webview){ //Duktape
	var assets = CPP_DKAssets_LocalAssets()
	var url = "file:///"+assets+"/index.html"
	DKAddEvent("GLOBAL", "keydown", User_OnEvent)
}
else{  //Duktape or V8 or Webview
	//DKWidget_SetProperty("body","background-color","grey")
	document.body.style["background-color"] = "grey"
	CPP_DK_Create("DKScale/DKScale.js", function(){})
	CPP_DK_Create("DKWebview/DKWebviewTest.js", function(){})
}
