set PROGRAM="%~1"

rem Empty input
%PROGRAM%
IF NOT ERRORLEVEL 1 goto error

rem Empty file
%PROGRAM% empty.txt
IF NOT ERRORLEVEL 1 goto error

rem Incorrect matrix
%PROGRAM% incorrect_matrix.txt
IF NOT ERRORLEVEL 1 goto error

rem Irregular matrix
%PROGRAM% irregular_matrix.txt
IF NOT ERRORLEVEL 1 goto error

rem Correct matrix 3*3
%PROGRAM% matrix_3_3.txt > %TEMP%\output.txt
IF ERRORLEVEL 1 goto error
fc.exe matrix_3_3_inverted.txt %TEMP%\output.txt
IF ERRORLEVEL 1 goto error

echo Program testing succeded
exit 0

:error
echo Program testing failed
exit 1