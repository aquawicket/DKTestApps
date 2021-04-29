var USE_CEF = 1;
var url = "file:///C:/Users/aquawicket/digitalknob/DKTasmota/DKApps/DKTasmota/assets/index.html";
//var url = "http://www.google.com/";
//var url = "http://digitalknob.com";
//var url = "chrome://gpu";
var width = 800;
var height = 600;
CPP_DK_Create("DKCef,Cef,0,0,"+width+","+height+","+url);
CPP_DKCef_NewBrowser("Cef",0,0,width,height,url);

//DKCreate("DKDebug/DKDebug.js");
//DKCreate("DKCef/DKDevTools.js");

CPP_DK_AddEvent("window", "DKCef_OnLoadingStateChange", User_OnEvent);
////////////////////////////
function User_OnEvent(event)  //Duktape
{
	console.log("User_OnEvent("+CPP_DK_GetId(event)+","+CPP_DK_GetType(event)+","+CPP_DK_GetValue(event)+")\n");

	//Alter the google page logo and add button
	//if(DK_Type(event, "DKCef_OnLoadingStateChange")){
	//	if(DKCef_GetUrl("Cef", 0) == "http://www.google.com/"){
			//UpdateGoogle();
	//	}
	//}
}

///////////////////////
function UpdateGoogle()
{
	CPP_DKCef_RunJavascript("document.getElementById('hplogo').setAttribute('src','http://digitalknob.com/DKSearch/DKSearch/logo.png');", 0);
	CPP_DKCef_RunJavascript("var myButton = document.createElement('button');", 0);
	CPP_DKCef_RunJavascript("myButton.id = 'myButton';", 0);
	CPP_DKCef_RunJavascript("myButton.style.position = 'absolute';", 0);
	CPP_DKCef_RunJavascript("myButton.style.top = '313px';", 0);
	CPP_DKCef_RunJavascript("myButton.style.left = '489px';", 0);
	CPP_DKCef_RunJavascript("myButton.style.width = '90px';", 0);
	CPP_DKCef_RunJavascript("myButton.style.height = '32px';", 0);
	CPP_DKCef_RunJavascript("myButton.innerHTML = 'MyButton';", 0);
	CPP_DKCef_RunJavascript("myButton.onclick = function(){alert('myButton clicked.')};", 0);
	CPP_DKCef_RunJavascript("document.body.appendChild(myButton);", 0);
}