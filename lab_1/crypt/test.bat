set PROGRAM="%~1"

rem Empty args
%PROGRAM%
if NOT ERRORLEVEL 1 goto erro

rem Invalid crypt command
%PROGRAM% magic one_line.txt out.txt 10
if NOT ERRORLEVEL 1 goto erro

rem Not existing input file
%PROGRAM% crypt one_mile.txt out.txt 10
if NOT ERRORLEVEL 1 goto erro

rem Invalid output file
%PROGRAM% crypt one_mile.txt %TEMP%\454564\out.txt 10
if NOT ERRORLEVEL 1 goto erro

rem Key is out of range
%PROGRAM% crypt one_mile.txt %TEMP%\454564\out.txt -1
if NOT ERRORLEVEL 1 goto erro
%PROGRAM% crypt one_mile.txt %TEMP%\454564\out.txt 256
if NOT ERRORLEVEL 1 goto erro
%PROGRAM% crypt one_mile.txt %TEMP%\454564\out.txt 99999999999999
if NOT ERRORLEVEL 1 goto erro

rem Crypt One line file
%PROGRAM% crypt one_line.txt %TEMP%\out.txt 10
if ERRORLEVEL 1 goto error
%PROGRAM% decrypt %TEMP%\out.txt %TEMP%\one_line.txt  10
if ERRORLEVEL 1 goto error
fc /b one_line.txt %TEMP%\one_line.txt
if ERRORLEVEL 1 goto error

rem Crypt Multiline file
%PROGRAM% crypt multiline.txt %TEMP%\out.txt 10
if ERRORLEVEL 1 goto error
%PROGRAM% decrypt %TEMP%\out.txt %TEMP%\multiline.txt  10
if ERRORLEVEL 1 goto error
fc /b multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1