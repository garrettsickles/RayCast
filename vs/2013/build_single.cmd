"C:\Program Files (x86)\MSBuild\12.0\Bin\amd64\msbuild.exe" "%~dp0raycast.sln" /target:Clean;Build /property:Configuration=%1;Platform="x64"
"%~dp0bin\x64\"%1"\raycast_test\raycast_test.exe"
if %errorlevel% NEQ 0 exit /b 1