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