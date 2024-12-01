@ECHO OFF
cd ../..
dir
git clone . ../Workspace-Taoran_01-1
git rm -r --cached .
git checkout --orphan temp
git add .
git commit -m "Initial commit with cleaned history"
git branch -D main
git branch -m main
git push -f origin main
