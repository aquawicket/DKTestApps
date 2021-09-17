CPP_DK_Create("DKSFMLWindow");
CPP_DK_Create("DKWindow");

console.log("CPP_DKWindow_TestInt(1234) = "+CPP_DKWindow_TestInt(1234)+"\n");
console.log("CPP_DKWindow_TestString(\"test string\") = "+CPP_DKWindow_TestString("test string")+"\n");
console.log("CPP_DKWindow_TestReturnInt() = "+CPP_DKWindow_TestReturnInt()+"\n");
console.log("CPP_DKWindow_TestReturnString() = "+CPP_DKWindow_TestReturnString()+"\n");


window.addEventListener("keydown", User_OnEvent); //ANDROID back key = exit

function User_OnEvent(event){
	if(event.type === "keydown"){
		console.log("KEYDOWN: "+event.value);
		if(event.value == "4") //FIXME: Exit for ANDROID button
		    CPP_DK_Exit();
	}
}