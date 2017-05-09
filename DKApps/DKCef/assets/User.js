var url = "google.com";
//var url = "http://digitalknob.com";
//var url = "chrome://gpu";
var width = 800;
var height = 600;
DKCreate("DKCef,Cef,0,0,"+width+","+height+","+url);
DK_SetFramerate(5);

DKCreate("DKDebug/DKDebug.js");