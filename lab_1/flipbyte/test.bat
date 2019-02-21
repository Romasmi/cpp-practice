set PROGRAM="%~1"

rem Empty args
%PROGRAM%
if NOT ERRORLEVEL 1 goto error

rem Number out of range
%PROGRAM% 99999999999999
if NOT ERRORLEVEL 1 goto error
%PROGRAM% -10
if NOT ERRORLEVEL 1 goto error

rem Correct number
rem min number
%PROGRAM% 0 > %TEMP%\flipped_0.txt
fc %TEMP%\flipped_0.txt flipped_0.txt
if ERRORLEVEL 1 goto error
rem max number
%PROGRAM% 255 > %TEMP%\flipped_255.txt
fc %TEMP%\flipped_255.txt flipped_255.txt
if ERRORLEVEL 1 goto error
rem some number
%PROGRAM% 8 > %TEMP%\flipped_8.txt
fc %TEMP%\flipped_8.txt flipped_8.txt
if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1