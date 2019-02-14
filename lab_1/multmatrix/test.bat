set PROGRAM="%~1"

rem Invalid arguments count
%PROGRAM%
if NOT ERRORLEVEL 1 goto error
%PROGRAM% matrix.txt
if NOT ERRORLEVEL 1 goto error

rem Empty files
%PROGRAM% empty.txt empty.txt
if NOT ERRORLEVEL 1 goto error

rem IncorrectMatrix
%PROGRAM% incorrect_matrix.txt matrix.txt
if NOT ERRORLEVEL 1 goto error

rem Correct quad matrix by equal matrix
%PROGRAM% 4x4_matrix.txt 4x4_matrix.txt > %TEMP%\result.txt
fc %TEMP%\result.txt 4x4_matrix_result.txt
if ERRORLEVEL 1 goto error

rem Correct 4*2 matrix by 4*4 matrix

echo OK
exit 0

:error
echo Program Testing failed
exit 1