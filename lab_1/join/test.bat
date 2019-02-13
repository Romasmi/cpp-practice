set PROGRAM="%~1"

rem Too few arguments
%PROGRAM%
%PROGRAM% test.bin
if NOT ERRORLEVEL 1 goto error

rem Not existing input files
%PROGRAM% test1.bin test2.bin out.bin
if NOT ERRORLEVEL 1 goto error

rem Merge one empty file
%PROGRAM% empty.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto error
fc %TEMP%\out.txt empty.txt
if ERRORLEVEL 1 goto error

rem Merge two empty files
%PROGRAM% empty.txt empty.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto error
copy /b empty.txt + empty.txt %TEMP%\out_to_compare.txt
fc %TEMP%\out_to_compare.txt %TEMP%\out.txt 
if ERRORLEVEL 1 goto error

rem Merge one file
%PROGRAM% lorem.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto error
fc %TEMP%\out.txt lorem.txt
if ERRORLEVEL 1 goto error

rem Merge two files
%PROGRAM% lorem.txt dolor.txt %TEMP%\out.txt
if ERRORLEVEL 1 goto error
copy /b lorem.txt + dolor.txt %TEMP%\out_to_compare.txt
fc %TEMP%\out.txt %TEMP%\out_to_compare.txt
if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1