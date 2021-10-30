#!/bin/bash
APP="DKCore"
OS="linux32"
TYPE="Release"

cd /home/"$USER"/digitalknob
echo Deleteing all CMake Cache files . . .
find . -name "CMakeCache.*" -delete
#find . -type d -name "CMakeFiles" -delete
#find . -type d -name "CMakeFiles" -exec rm -rf {} \;
rm -rf `find . -type d -name CMakeFiles`
		
mkdir /home/"$USER"/digitalknob/DKTestApps/DKApps/$APP/$OS
mkdir /home/"$USER"/digitalknob/DKTestApps/DKApps/$APP/$OS/$TYPE
cd /home/"$USER"/digitalknob/DKTestApps/DKApps/$APP/$OS/$TYPE
if [[ $TYPE -eq "Debug" ]]
then
	echo cmake -G "Unix Makefiles" -DDEBUG=ON -DREBUILDALL=ON -DSTATIC=ON /home/"$USER"/digitalknob/DK
	cmake -G "Unix Makefiles" -DDEBUG=ON -DREBUILDALL=ON -DSTATIC=ON /home/"$USER"/digitalknob/DK
fi
if [[ $TYPE -eq "Release" ]]
then
	echo cmake -G "Unix Makefiles" -DRELEASE=ON -DREBUILDALL=ON -DSTATIC=ON /home/"$USER"/digitalknob/DK
	cmake -G "Unix Makefiles" -DRELEASE=ON -DREBUILDALL=ON -DSTATIC=ON /home/"$USER"/digitalknob/DK
fi
#chmod +x /home/"$USER"/digitalknob/DKTestApps/DKBuilder.sh

#cd /home/"$USER"/digitalknob/DKTestApps/DKApps/$APP/$OS/$TYPE
make $APP
#chmod +x /home/"$USER"/digitalknob/DKTestApps/DKApps/$APP/$OS/$TYPE/$APP