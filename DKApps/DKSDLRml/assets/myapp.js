function MyApp(){}
const myapp = DKPlugin(MyApp);

myapp.loadFiles = function myapp_loadFiles() {
	console.log("myapp.loadFiles()")
	dk.create("myapp.css")
}

myapp.loadApp = function myapp_loadApp() {
	console.log("myapp.loadApp()")
	let ele1 = document.createElement("div")
	ele1.id = "idvalue1"
	ele1.setAttribute("class", "classvalue1")
	ele1.setAttribute("test", "testvalue1")
	//ele1.style.display = "block"
	ele1.style.width = "100px"
	ele1.style.height = "100px"
	document.body.appendChild(ele1)

	let ele2 = document.createElement("div")
	ele2.id = "idvalue2"
	ele2.setAttribute("class", "classvalue2")
	ele2.setAttribute("test", "testvalue2")
	//ele2.style.display = "block"
	ele2.style.width = "75px"
	ele2.style.height = "75px"
	document.body.appendChild(ele2)
	
	let ele3 = document.createElement("div")
	ele3.id = "idvalue3"
	ele3.setAttribute("class", "classvalue3")
	ele3.setAttribute("test", "testvalue3")
	//ele3.style.display = "block"
	ele3.style.width = "50px"
	ele3.style.height = "50px"
	document.body.appendChild(ele3)
	
	let ele4 = document.createElement("div")
	ele4.id = "idvalue4"
	ele4.setAttribute("class", "classvalue4")
	ele4.setAttribute("test", "testvalue4")
	//ele4.style.display = "block"
	ele4.style.width = "25px"
	ele4.style.height = "25px"
	document.body.appendChild(ele4)
}

DUKTAPE && myapp.loadFiles();
DUKTAPE && myapp.loadApp();