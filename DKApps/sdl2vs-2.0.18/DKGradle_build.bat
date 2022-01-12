@echo off
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit )

::kill java.exe if it's runningC:\Users\Administrator\digitalknob\DKTestApps\DKApps\sdl2vs-2.0.18\app\.cxx\cmake\arm7Debug\armeabi-v7a
taskkill /IM "java.exe" /F

set "DIGITALKNOB=C:\Users\%USERNAME%\digitalknob"
set "SDKMANAGER=%DIGITALKNOB%\DK\3rdParty\android-sdk\tools\bin\sdkmanager.bat"
set "GOOGLE_CERT=%JAVA_HOME%\google.cer"
set "MAVEN_CERT=%JAVA_HOME%\maven.cer"
set "KEYTOOL_EXE=%JAVA_HOME%\bin\keytool.exe"
set "CACERTS=%JAVA_HOME%\lib\security\cacerts"
if exist "C:\Program Files (x86)\OpenSSL-win32\bin\openssl.exe" set "OPENSSL_EXE=C:\Program Files (x86)\OpenSSL-win32\bin\openssl.exe"
if exist "C:\Program Files\OpenSSL-Win64\bin\openssl.exe" set "OPENSSL_EXE=C:\Program Files\OpenSSL-Win64\bin\openssl.exe"

if not exist "%DIGITALKNOB%/DK/3rdParty/android-sdk/licenses" (
	"%SDKMANAGER%" --licenses
)

if not exist "%DIGITALKNOB%/DKTestApps/DKApps/sdl2vs-2.0.18/app/.cxx/cmake" (
	:: create and import the google.cer key
	echo -n | "%OPENSSL_EXE%" s_client -connect google.com:443 | "%OPENSSL_EXE%" x509 > "%GOOGLE_CERT%"
	"%KEYTOOL_EXE%" -import -noprompt -alias google -cacerts -file "%GOOGLE_CERT%" -storepass changeit

	:: create and import the maven.cer key
	echo -n | "%OPENSSL_EXE%" s_client -connect repo.maven.apache.org:443 | "%OPENSSL_EXE%" x509 > "%MAVEN_CERT%"
	"%KEYTOOL_EXE%" -import -noprompt -alias maven -cacerts -file "%MAVEN_CERT%" -storepass changeit
)

gradlew build --info
