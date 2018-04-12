set PROGRAM="%~1"

rem Empty input
%PROGRAM%
IF NOT ERRORLEVEL 1 goto error

rem Incorrect input
%PROGRAM% a b c
IF NOT ERRORLEVEL 1 goto error

rem Incorrect input
%PROGRAM% 10 11 ""
IF NOT ERRORLEVEL 1 goto error

rem Non conformity of input radix and input number
%PROGRAM% 10 11 FF
IF NOT ERRORLEVEL 1 goto error	

rem Input number overflow
%PROGRAM% 10 16 20000000000
IF NOT ERRORLEVEL 1 goto error	

rem Equal radix
%PROGRAM% 10 10 10 > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 10_10_10.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

rem Correct input
%PROGRAM% 16 2 FF > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 16_2_255.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

rem Correct negaive input number
%PROGRAM% 16 2 -FF > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 16_2_miuns_255.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

echo Program testing succeded
exit 0

:error
echo Program testing failed
exit 1