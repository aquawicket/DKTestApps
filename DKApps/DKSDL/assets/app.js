CPP_DKDuktape_Create("DKSDLWindow");
CPP_DKDuktape_Create("DKWindow");

console.log("DKWindow_TestInt(1234) = "+DKWindow_TestInt(1234)+"\n");
console.log("DKWindow_TestString(\"test string\") = "+DKWindow_TestString("test string")+"\n");
console.log("DKWindow_TestReturnInt() = "+DKWindow_TestReturnInt()+"\n");
console.log("DKWindow_TestReturnString() = "+DKWindow_TestReturnString()+"\n");

/////////////////////////
//ANDROID back key = exit
document.addEventListener("keydown", User_OnEvent);

function User_OnEvent(event){
	if(event.type === "keydown"){
		console.log("KEYDOWN: "+DK_GetValue(event));
		if(event.value == "4"){ //FIXME: Exit for ANDROID
		    CPP_DKDuktape_Exit();
		}
	}
}
//////////////////////////
