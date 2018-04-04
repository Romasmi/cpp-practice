set PROGRAM="%~1"

rem Empty input
%PROGRAM%
IF NOT ERRORLEVEL 1 goto error

rem Non existing input file
%PROGRAM% non_existing_file.txt %TEMP%\updated_file_copy.txt "and" "enjunction"
IF NOT ERRORLEVEL 1 goto error

rem Empty search string
%PROGRAM% sonnete_17_by_shakespeare.txt %TEMP%\updated_file_copy.txt "123"
IF NOT ERRORLEVEL 1 goto error

rem Incorrect output file - current program
%PROGRAM% sonnete_17_by_shakespeare.txt %PROGRAM% "and" "enjunction"
IF NOT ERRORLEVEL 1 goto error

rem Correct input with one line
%PROGRAM% sonnete_17_by_shakespeare_one_line.txt %TEMP%\updated_file_copy.txt "and" "enjunction"
IF ERRORLEVEL 1 goto error
fc.exe sonnete_17_by_shakespeare_one_line_updated.txt %TEMP%\updated_file_copy.txt
IF ERRORLEVEL 1 goto error

rem Correct input with multiline input
%PROGRAM% sonnete_17_by_shakespeare.txt %TEMP%\updated_file_copy.txt "and" "enjunction"
IF ERRORLEVEL 1 goto error
fc.exe sonnete_17_by_shakespeare_updated.txt %TEMP%\updated_file_copy.txt
IF ERRORLEVEL 1 goto error

echo Program testing succeded
exit 0

:error
echo Program testing failed
exit 1