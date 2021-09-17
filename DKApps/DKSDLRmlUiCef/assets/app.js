
//if(CPP_DK_GetBrowser() == "Rml"){
	
	CPP_DK_Create("DKCef");
	CPP_DK_Create("DKWindow");
	CPP_DK_Create("DKRml");
	CPP_DK_Create("DKDom");
	CPP_DK_Create("DKWidget");
//}

//CPP_DK_Create("DKDebug/DKDebug.js", function(){});
//DKWidget_SetProperty("body","background-color","blue");
document.body.style.backgroundColor = "blue";


var assets = DKAssets_LocalAssets();
var url = "http://www.google.com";

/*
var iframe = DKWidget_CreateElement("body", "iframe", "DKCef_frame");
DKWidget_SetAttribute(iframe, "src", url);
DKWidget_SetProperty(iframe, "position", "absolute");
DKWidget_SetProperty(iframe, "top", "20rem");
DKWidget_SetProperty(iframe, "left", "20rem");
DKWidget_SetProperty(iframe, "right", "20rem");
DKWidget_SetProperty(iframe, "bottom", "20rem");
var currentBrowser = CPP_DKCef_GetCurrentBrowser(iframe);
CPP_DKCef_SetUrl(iframe, url, currentBrowser);
CPP_DKCef_SetFocus(iframe);
*/