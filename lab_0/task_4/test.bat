set PROGRAM="%~1"

%PROGRAM%
if NOT ERRORLEVEL 1 goto error

%PROGRAM% 1 * 100 / 0
if NOT ERRORLEVEL 1 goto error

%PROGRAM% 1 * 100 / 2 + 150 > %TEMP%\result.txt
if ERRORLEVEL 1 goto error
fc.exe %TEMP%\result.txt result_200.txt
if ERRORLEVEL 1 goto error

echo Program testing succeeded
exit 0

:error
echo Program testing failed
exit 1 