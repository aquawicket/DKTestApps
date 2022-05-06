var USE_CEF = 1

var url = "chrome://gpu";
//const url = "http://duckduckgo.com"
//const url = "http://www.google.com/"
//const url = "http://127.0.0.1:2393"
//const url = CPP_DKAssets_LocalAssets()+"index.html"
//const url = CPP_DKAssets_LocalAssets()+"DKWebTest/index.html"


////// RmlUi
if(CPP_DK_GetBrowser() === "RML"){
	CPP_DK_Create("DKDuktapeDom")
	CPP_DK_Create("DKSDLWindow")    //DO NOT Create DKSDLWindow directly
	CPP_DK_Create("DKSDLText")
	CPP_DK_Create("DKRml")
}

var width = CPP_DKWindow_GetWidth()
var height = CPP_DKWindow_GetHeight()

location.href = CPP_DKAssets_LocalAssets()+"index.html"



///// CEF 
CPP_DK_Create("DKCef") //,Cef,0,0,"+width+","+height+","+url)
CPP_DKCef_NewBrowser("Cef",0,0,width,height,url)
//CPP_DKCef_ShowDevTools(0)

window.addEventListener("keydown", function mykeydown(event){
	if(event.key === "F12")
		CPP_DKCef_ShowDevTools(0)	
})

window.addEventListener("resize", function onresize(event){
	//console.log("User_OnEvent(): resize\n")
	//CPP_DKCef_SetSize("CefSDL", 100, 100)
	var width = CPP_DKWindow_GetWidth()
	var height = CPP_DKWindow_GetHeight()
	DK_CallFunc("CefSDL::OnResize", "0,0,"+String(width)+","+String(height))
})
