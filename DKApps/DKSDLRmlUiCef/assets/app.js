
if(CPP_DK_GetBrowser() == "RML"){
	CPP_DK_Create("DKWindow");
	CPP_DK_Create("DKRml");
	//CPP_DK_Create("DKSDLText");
}

location.href = CPP_DKAssets_LocalAssets()+"index.html";

/*
CPP_DK_Create("DKDebug/DKDebug.js", function(){});

//DKWidget_SetProperty("body","background-color","blue");
document.body.style["background-color"] = "rgb(20,20,20)";


var assets = CPP_DKAssets_LocalAssets();
var url = "http://www.google.com";


//var iframe = DKWidget_CreateElement("body", "iframe", "DKCef_frame");
var iframe = document.createElement("iframe");
iframe.id = "DKCef_frame";
document.body.appendChild(iframe);

//DKWidget_SetAttribute(iframe, "src", url);
iframe.setAttribute("src", url);	
	
//DKWidget_SetProperty(iframe, "position", "absolute");
iframe.style["position"] = "absolute";

//DKWidget_SetProperty(iframe, "top", "20rem");
iframe.style["top"] = "20rem";

//DKWidget_SetProperty(iframe, "left", "20rem");
iframe.style["left"] = "20rem";

//DKWidget_SetProperty(iframe, "right", "20rem");
iframe.style["right"] = "20rem";

//DKWidget_SetProperty(iframe, "bottom", "20rem");
iframe.style["bottom"] = "20rem";


//var currentBrowser = CPP_DKCef_GetCurrentBrowser(iframe.id);
//CPP_DKCef_SetUrl(iframe.id, url, currentBrowser);
//CPP_DKCef_SetFocus(iframe.id);
*/