function MyApp(){}
const myapp = DKPlugin(MyApp);

myapp.loadFiles = function myapp_loadFiles() {
	console.log("myapp.loadFiles()")
	dk.create("myapp.css")
}

myapp.loadApp = function myapp_loadApp() {
	console.log("myapp.loadApp()")
	let ele = document.createElement("div")
	ele.id = "idvalue"
	ele.setAttribute("class", "classvalue")
	ele.setAttribute("test", "testvalue")
	ele.style.display = "block"
	ele.style.width = "100px"
	ele.style.height = "100px"
	//ele.style.backgroundColor = "black"
	document.body.appendChild(ele)

	let ele2 = document.createElement("div")
	ele2.id = "idvalue2"
	//ele2.setAttribute("class", "classvalue2")
	ele2.setAttribute("Test", "TestValue")
	ele2.style.position = "absolute"
	ele2.style.display = "block"
	ele2.style.width = "66px"
	ele2.style.height = "66px"
	//ele.ele2.style.backgroundColor = "white";
	ele.appendChild(ele2)
}

DUKTAPE && myapp.loadFiles();
DUKTAPE && myapp.loadApp();