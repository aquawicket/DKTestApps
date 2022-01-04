@echo off
if not defined in_subprocess (cmd /k set in_subprocess=y ^& %0 %*) & exit )

set "DIGITALKNOB=C:\Users\%USERNAME%\digitalknob"
set "SDKMANAGER=%DIGITALKNOB%\DK\3rdParty\android-sdk\tools\bin\sdkmanager.bat"
set "JDK=%DIGITALKNOB%\DK\3rdParty\openjdk-9.0.4_windows-x64_bin"
set "GOOGLE_CERT=%JDK%\google.cer"
set "MAVEN_CERT=%JDK%\maven.cer"

//kill java.exe if it's running
taskkill /IM "java.exe" /F

:: sign the licenses
"%SDKMANAGER%" --licenses

:: create and import the google.cer key
echo -n | "%OPENSSL_EXE%" s_client -connect google.com:443 | "%OPENSSL_EXE%" x509 > "%GOOGLE_CERT%"
"%KEYTOOL_EXE%" -import -noprompt -alias google -cacerts -file "%GOOGLE_CERT%" -storepass changeit

:: create and import the maven.cer key
echo -n | "%OPENSSL_EXE%" s_client -connect repo.maven.apache.org:443 | "%OPENSSL_EXE%" x509 > "%MAVEN_CERT%"
"%KEYTOOL_EXE%" -import -noprompt -alias maven -cacerts -file "%MAVEN_CERT%" -storepass changeit

gradlew build --info

echo press and key to continue or wait 5 seconds... && timeout /t 5 > nul