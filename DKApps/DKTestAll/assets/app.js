var url = DKAssets_LocalAssets()+"DKWebTest/index.html";

//// Create SDL Rocket window
DKCreate("DKWindow");
DKCreate("DKRocket");
location.href = url;
window.moveTo(screen.width/2, 36);
window.resizeTo(screen.width / 2 - 10, screen.height-84);
//DKRocket_ToggleDebugger();



////////////////// OLD CODE ///////////////////
/*
var USE_CEF = 0;

DKCreate("DKDebug/DKDebug.js");

var welcome = "\n";
welcome = "######################### \n";
welcome += "####### DKTestAll ####### \n";
welcome += "######################### \n";
console.log(welcome);


//TestJavascript
DKCreate("TestJavascript.js");
DKClose("TestJavascript.js");

//TestWindow
DKCreate("TestWindow.js");

//TestRocket
DKCreate("TestRocket.js");
*/
//////////////////////////////////////////////