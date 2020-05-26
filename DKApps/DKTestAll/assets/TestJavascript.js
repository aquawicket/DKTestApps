console.log("Opening TestJavascript.js...");

//////////////////////////////
function TestJavascript_Init()
{
	console.log("Running TestJavascript_Init()");
	var a = 123;
	var b = 456;
	var c = a + b;
	console.log(a+" + "+b+" = "+c);
	
	//console.log("Press any key to test keyboard");
	//var key = DK_GetKey();
	//console.log("Key pressed = "+key);
}

/////////////////////////////
function TestJavascript_End()
{
	console.log("Running TestJavascript_End()");
	console.log("closing TestJavascript.js...");
}