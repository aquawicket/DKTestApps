/*
#ifdef IOS
#import "App.h"

@implementation iphoneViewerAppDelegate

- (void)applicationDidFinishLaunching:(UIApplication *)application {

    NSBundle *bundle = [NSBundle mainBundle];
    NSDictionary *info = [bundle infoDictionary];
    NSString *prodName = [info objectForKey:@"CFBundleExecutable"];
    std::string appname = std::string([prodName UTF8String]);
    //printf("appname = %s\n", appname.c_str());
    NSString *epath = [[NSBundle mainBundle] executablePath];
    std::string exePath = std::string([epath UTF8String]); //NSString to std::string
    exePath = exePath.substr(0, exePath.find_last_of("/\\"));
    //printf("exe_path = %s\n", exe+path.c_str());
    
    
    //NSString *documentsDirectory = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	//NSString *sourcePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Populator"];
	//NSString *folderPath = [documentsDirectory stringByAppendingPathComponent:@"Files"];
	//NSLog(@"Source Path: %@\n Documents Path: %@ \n Folder Path: %@", sourcePath, documentsDirectory, folderPath);

    App app;
    App::mFile = exePath+"/assets/demo.rml";
    App::init();

    [NSTimer scheduledTimerWithTimeInterval:1.0/30.0 target:self selector:@selector(updateScene) userInfo:nil repeats:YES];
}

- (void)updateScene
{
    if(App::mActive){
        App::do_frame();
	}
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    
}

-(void)applicationWillTerminate:(UIApplication *)application
{
    App::exit();
} 

- (void)accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration
{
    //Use a basic low-pass filter to only keep the gravity in the accelerometer values
    accel[0] = acceleration.x * 30.0 + accel[0] * (1.0 - 0.1);
    accel[1] = acceleration.y * 30.0 + accel[1] * (1.0 - 0.1);
    accel[2] = acceleration.z * 30.0 + accel[2] * (1.0 - 0.1);
}

- (void)dealloc
{
    //[super dealloc];
}

@end
#endif //IOS
*/
