var USE_CEF = 1;
var url = "http://www.google.com/";
//var url = "chrome://gpu";
//var url = "http://127.0.0.1:2393"

var width = 800;
var height = 600;
CPP_DK_Create("DKCef,Cef,0,0,"+width+","+height+","+url);
CPP_DKCef_NewBrowser("Cef",0,0,width,height,url);
