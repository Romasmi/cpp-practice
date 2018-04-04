set PROGRAM="%~1"

rem Empty input
%PROGRAM%
if NOT ERRORLEVEL 1 goto error

rem Devision by zero
%PROGRAM% 1 * 100 / 0
if NOT ERRORLEVEL 1 goto error

rem Last Parameter is any operation
%PROGRAM% 1 * 100 / 0 + 
if NOT ERRORLEVEL 1 goto error

rem Incorrect input
%PROGRAM% 1 1 1 1
if NOT ERRORLEVEL 1 goto error

rem Just one parameter - number
%PROGRAM% 200 > %TEMP%\result.txt
if ERRORLEVEL 1 goto error
fc.exe %TEMP%\result.txt result_200.txt
if ERRORLEVEL 1 goto error

rem Correct expression
%PROGRAM% 1 * 100 / 2 + 160 - 10 > %TEMP%\result.txt
if ERRORLEVEL 1 goto error
fc.exe %TEMP%\result.txt result_200.txt
if ERRORLEVEL 1 goto error

echo Program testing succeeded
exit 0

:error
echo Program testing failed
exit 1 