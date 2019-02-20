set PROGRAM="%~1"

rem Too few arguments
%PROGRAM%
if NOT ERRORLEVEL 1 goto error

rem Not existing input files
%PROGRAM% not_exist.txt out.bin
if NOT ERRORLEVEL 1 goto error

rem Not correct output file
%PROGRAM% life.txt %TEMP%\4564564\out.bin
if NOT ERRORLEVEL 1 goto error

rem Empty input
%PROGRAM% empty.txt
if NOT ERRORLEVEL 1 goto error

rem Incorrect chars
%PROGRAM% incorrect_chars.txt
if NOT ERRORLEVEL 1 goto error

rem Invalid border
rem top
%PROGRAM% invalid_top_border.txt
if NOT ERRORLEVEL 1 goto error
rem bottom
%PROGRAM% invalid_bottom_border.txt
if NOT ERRORLEVEL 1 goto error
rem left
%PROGRAM% invalid_left_border.txt
if NOT ERRORLEVEL 1 goto error
rem right
%PROGRAM% invalid_right_border.txt
if NOT ERRORLEVEL 1 goto error

rem Incorrects size
rem Too small life
%PROGRAM% too_small_life.txt
if NOT ERRORLEVEL 1 goto error
rem Too big life
%PROGRAM% too_big_life.txt 
if NOT ERRORLEVEL 1 goto error

rem Border size
rem min size life
%PROGRAM% min_size_life.txt %TEMP%\out.txt
fc %TEMP%\out.txt min_size_life_out.txt
if ERRORLEVEL 1 goto error
rem max size life
%PROGRAM% max_size_life.txt %TEMP%\out.txt
fc %TEMP%\out.txt max_size_life_out.txt
if ERRORLEVEL 1 goto error

echo OK
exit 0

:error
echo Program Testing failed
exit 1