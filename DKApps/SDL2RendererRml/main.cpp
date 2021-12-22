#include <App.h>

int main(int argc, char** argv)
{
//#ifdef IOS
//	@autoreleasepool{
//		return UIApplicationMain(argc, argv, nil, @"iphoneViewerAppDelegate");
//	}
//#else
	App app;
	if (argc > 1)
	{
		App::mFile = argv[1];
	}
	App::init();
//#endif
	return 0;
}