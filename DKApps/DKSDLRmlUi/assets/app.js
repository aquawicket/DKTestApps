DKCreate("DKWindow");
DKCreate("DKRml");
//DKRml_ToggleDebugger();

location.href = "C:/digitalknob/DKTestApps/DKApps/DKSDLRmlUi/assets/test.html";

console.log("window = "+window);
console.log("location = "+location);
console.log("document = "+document);

console.log(document.getElementById("test.html").innerHTML);
document.getElementById("test.html").innerHTML = "<img id=\"gif_image\" src=\"test.gif\" style=\"position:absolute;left:10%;top:35%;width:40%;\"></img>"
console.log(document.getElementById("test.html").innerHTML);