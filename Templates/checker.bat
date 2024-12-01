@ECHO off

IF [%1]==[] (
	echo Problematic Code Required.
	exit
)
IF [%2]==[] (
	echo Answer Code Required.
	exit
)
IF [%3]==[] (
	echo Maker Code Required.
	exit
)

SET p1cpp=%1
SET p1=%p1cpp:.cpp=%.exe
SET f1=%p1cpp:.cpp=%.in
SET f2=%p1cpp:.cpp=%.out
SET f3=%p1cpp:.cpp=%.ans
SET p2cpp=%2
SET p2=%p2cpp:.cpp=%.exe
SET p3cpp=%3
SET p3=%p3cpp:.cpp=%.exe

@REM p1 code.exe  p2 answer.exe   p3 maker.exe
@REM f1 test.in  f2 test.out  f3 test.ans

g++ %p1cpp% -std=c++14 -o %p1%
g++ %p2cpp% -std=c++14 -o %p2%
g++ %p3cpp% -std=c++14 -o %p3%

SET /A tim=0

:loop
SET /A tim=%tim%+1 && echo Test #%tim%
%p3% >%f1% && %p1% <%f1% >%f2% && %p2% <%f1% >%f3%
fc %f2% %f3% >nul
if %ERRORLEVEL%==0 (
	goto loop
)

del %p1% && del %p2% && del %p3%
fc %f2% %f3%

pause
