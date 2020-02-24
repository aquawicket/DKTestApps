DKCreate("DKSDLWindow");
DKCreate("DKWindow");

console.log("DKWindow_TestInt(1234) = "+DKWindow_TestInt(1234)+"\n");
console.log("DKWindow_TestString(\"test string\") = "+DKWindow_TestString("test string")+"\n");
console.log("DKWindow_TestReturnInt() = "+DKWindow_TestReturnInt()+"\n");
console.log("DKWindow_TestReturnString() = "+DKWindow_TestReturnString()+"\n");

/////////////////////////
//ANDROID back key = exit
DKDuktape_AddEvent("GLOBAL", "keydown", User_OnEvent);
function User_OnEvent(event)  //Duktape
{
	if(DK_Type(event, "keydown")){
		console.log(DK_GetValue(event));
		if(DK_GetValue(event) == "4"){ //Exit for ANDROID
		    DK_Exit();
		}
	}
}
//////////////////////////
