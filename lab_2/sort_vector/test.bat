set PROGRAM="%~1"

rem Empty input
%PROGRAM% < empty.txt
if NOT ERRORLEVEL 1 goto error

rem One cell matrix
rem %PROGRAM% 1x1_matrix.txt 1x1_matrix.txt > %TEMP%\result.txt
rem fc %TEMP%\result.txt 1x1_matrix_result.txt
rem if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1