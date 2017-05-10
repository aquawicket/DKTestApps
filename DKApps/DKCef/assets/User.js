var USE_CEF = 1;
var url = "http://www.google.com/";
//var url = "http://digitalknob.com";
//var url = "chrome://gpu";
var width = 800;
var height = 600;
DKCreate("DKCef,Cef,0,0,"+width+","+height+","+url);
DK_SetFramerate(5);
DKCreate("DKDebug/DKDebug.js");


DKAddEvent("GLOBAL", "DKCef_OnLoadingStateChange", User_OnEvent);
////////////////////////////
function User_OnEvent(event)  //Duktape
{
	DKLog("User_OnEvent("+DK_GetId(event)+","+DK_GetType(event)+","+DK_GetValue(event)+")\n", DKINFO);

	//Alter the google page logo
	if(DK_Type(event, "DKCef_OnLoadingStateChange")){
		if(DKCef_GetUrl("Cef", 0) == "http://www.google.com/"){
			UpdateGoogle();
		}
	}
}

///////////////////////
function UpdateGoogle()
{
	DKCef_RunJavascript("Cef", "document.getElementById('hplogo').setAttribute('src','http://digitalknob.com/DKSearch/DKSearch/logo.png');");
	DKCef_RunJavascript("Cef", "var myButton = document.createElement('button');");
	DKCef_RunJavascript("Cef", "myButton.id = 'myButton';");
	DKCef_RunJavascript("Cef", "myButton.style.position = 'absolute';");
	DKCef_RunJavascript("Cef", "myButton.style.top = '313px';");
	DKCef_RunJavascript("Cef", "myButton.style.left = '489px';");
	DKCef_RunJavascript("Cef", "myButton.style.width = '90px';");
	DKCef_RunJavascript("Cef", "myButton.style.height = '32px';");
	DKCef_RunJavascript("Cef", "myButton.innerHTML = 'MyButton';");
	DKCef_RunJavascript("Cef", "myButton.onclick = function(){alert('myButton clicked.')};");
	DKCef_RunJavascript("Cef", "document.body.appendChild(myButton);");
	
}
