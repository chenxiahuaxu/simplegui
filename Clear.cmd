@echo off
echo *********************************************************** 
echo Marge source code collation
echo ***********************************************************
echo The following information will be cleared.
echo [1]Linux link file. (*.o)
echo [2]Shared object file. (*.so)
echo [3]Makefile dependencies. (*.d)
echo [4]Back up file. (*.bak)"
echo [5]SVN or Git version control information. (.svn/.git)
echo [6]Blank folder.
echo.
echo Press any key to start process...
pause >> NUL
echo.
echo Process 1: Remove all linux link file. (*.o)
@for /f "delims=" %%i in ('dir /b /a-d /s "*.o"') do del %%i
echo Process 2: Remove all shared object file. (*.so)
@for /f "delims=" %%i in ('dir /b /a-d /s "*.so"') do del %%i
echo Process 4: Remove all makefile dependencies. (*.d)
@for /f "delims=" %%i in ('dir /b /a-d /s "*.d"') do del %%i
echo Process 5: Remove all back up file. (*.bak)
@for /f "delims=" %%i in ('dir /b /a-d /s "*.bak"') do del %%i
echo Process 6: Clear SVN or Git version control information. (.svn/.git)
@for /r . %%a in (.) do @if exist "%%a\.svn" rd /s /q "%%a\.svn" 
@for /r . %%a in (.) do @if exist "%%a\.svn" rd /s /q "%%a\.git" 
echo Process 7: Remove all blank folder.
@for /f "tokens=*" %%i in ('dir/s/b/ad^|sort /r') do rd "%%i"
echo.
echo Process done.
echo Press any key to exit...
pause >> NUL