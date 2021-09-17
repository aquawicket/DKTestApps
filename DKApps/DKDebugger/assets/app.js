var USE_CEF = 1;
var url = "http://127.0.0.1:2393";
var width = 800;
var height = 600;

CPP_DK_Create("DKCef");
CPP_DK_Create("DKCef,Cef,0,0,"+width+","+height+","+url);
//CPP_DK_SetFramerate(5);
CPP_DK_Create("DK/DK.js");
CPP_DK_Create("DKDebug/DKDebug.js");

//DKAddEvent("GLOBAL", "keypress", User_OnEvent);
document.addEventListener("keypress", User_OnEvent);

function User_OnEvent(event) {
	console.log(event);
	if(event.type === "keypress") { //press a key to run this after a DevTools context menu is open, it will find 'Save'
		CPP_DKCef_RunJavascript("CefSDL", "var x = document.getElementsByClassName('soft-context-menu');");
		CPP_DKCef_RunJavascript("CefSDL", "var shadow_root = x[0].shadowRoot;");
		CPP_DKCef_RunJavascript("CefSDL", "var y = shadow_root.childNodes;");
		CPP_DKCef_RunJavascript("CefSDL", "var z = y[3].getElementsByClassName('soft-context-menu-item');");
		CPP_DKCef_RunJavascript("CefSDL", "var save = z[z.length-2];");
		CPP_DKCef_RunJavascript("CefSDL", "console.log(save.innerHTML);");
		
		//FIXME - we can get the element of the save button, but we cannot add an event.
		CPP_DKCef_RunJavascript("CefSDL", "save.onclick = function(){alert('save clicked.')};");  ///grrrrr
		//CPP_DKCef_RunJavascript("CefSDL", "save.addEventListener('focus', function(event){ event.preventDefault(); console.log('click'); });");
	}
}
