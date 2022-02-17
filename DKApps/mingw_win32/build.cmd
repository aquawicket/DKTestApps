%dkbatch%

set PATH=%PATH%;C:\Users\Administrator\digitalknob\DK\3rdParty\mingw64-8.1.0\bin

cmake -G "MinGW Makefiles"

cmake --build .
%DKEND% 
