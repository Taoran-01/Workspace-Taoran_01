@ECHO OFF
set /A tim=0
:loop
set /A tim=%tim%+1
echo Test #%tim%
maker && test>test.out && stable>stable.out
fc test.out stable.out >nul
if %ERRORLEVEL%==0 (goto loop)
fc test.out stable.out
pause
