@ECHO off
:loop
maker.exe>data.in && chengxu.exe<data.in>data.out && baoli.exe<data.in>data.ans
fc data.out data.ans
if %ERRORLEVEL%==0 (
	goto loop
)
pause
