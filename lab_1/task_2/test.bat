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
%PROGRAM% 10 11 Ff
IF NOT ERRORLEVEL 1 goto error

rem Input number overflow
%PROGRAM% 10 16 1234567891145655645
IF NOT ERRORLEVEL 1 goto error	

rem Equal radix
%PROGRAM% 10 10 10 > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 10_10_10.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

rem Convert zero
%PROGRAM% 10 11 0 > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 10_11_0.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

rem Correct input
%PROGRAM% 16 2 fF > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 16_2_255.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

rem Convert max unsigned int
%PROGRAM% 16 10 FFFFFFFF > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 16_10_FFFFFFFF.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

rem Correct negaive input number
%PROGRAM% 16 2 -Ff > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe 16_2_minus_255.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

:good
echo Program testing succeded
exit 0

:error
echo Program testing failed
exit 1