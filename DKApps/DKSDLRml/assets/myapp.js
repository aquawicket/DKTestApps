function MyApp(){}
const myapp = DKPlugin(MyApp);

myapp.loadFiles = function myapp_loadFiles() {
	console.log("myapp.loadFiles()")
}

myapp.loadApp = function myapp_loadApp() {
	console.log("myapp.loadApp()")
}

DUKTAPE && myapp.loadFiles();
DUKTAPE && myapp.loadApp();