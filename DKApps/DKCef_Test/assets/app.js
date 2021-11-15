var USE_CEF = 1;
var url = "http://www.duckduckgo.com/";
//var url = "chrome://gpu";

var width = 1240;
var height = 900;
CPP_DK_Create("DKCef");
CPP_DKCef_NewBrowser("Cef",0,0,width,height,url);
