@ECHO OFF
git fetch origin
git branch --set-upstream-to=origin/main main
git pull
@REM git reset --soft origin/main
