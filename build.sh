x86_64-w64-mingw32-g++ main.cpp -o COM Surrogate.exe -static -mwindows -luser32

git add *
git commit -m "Add Windows clipboard application"
# git tag -a v1.0-windows -m "Windows clipboard application version 1

git push 
