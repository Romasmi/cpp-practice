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

rem Columns count is not equal to rows count
%PROGRAM%  3x3_matrix.txt 2x3_matrix.txt > %TEMP%\result.txt
if NOT ERRORLEVEL 1 goto error

rem One cell matrix
%PROGRAM% 1x1_matrix.txt 1x1_matrix.txt > %TEMP%\result.txt
fc %TEMP%\result.txt 1x1_matrix_result.txt
if ERRORLEVEL 1 goto error

rem Correct quad matrix by equal matrix
%PROGRAM% 3x3_matrix.txt 3x3_matrix.txt > %TEMP%\result.txt
fc %TEMP%\result.txt 3x3_matrix_result.txt
if ERRORLEVEL 1 goto error

rem Correct 3*2 matrix by 3*3 matrix
%PROGRAM% 2x3_matrix.txt 3x3_matrix.txt > %TEMP%\result.txt
fc %TEMP%\result.txt 2x3-3x3_matrix_result.txt
if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1