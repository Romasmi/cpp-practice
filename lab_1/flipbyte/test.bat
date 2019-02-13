set PROGRAM="%~1"

rem Empty args
%PROGRAM%
if NOT ERRORLEVEL 1 goto error

rem Number out of range
%PROGRAM% 99999999999999
if NOT ERRORLEVEL 1 goto error

%PROGRAM% 8 > %TEMP%\flipped_8.txt
fc %TEMP%\flipped_8.txt flipped_8.txt
if ERRORLEVEL 1 goto error

rem Merge one empty file
rem %PROGRAM% empty.txt %TEMP%\out.txt
rem if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1