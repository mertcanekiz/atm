@echo off
if not exist ".\bin\atm.exe" (
    echo "Compiling"
    cd src
    gcc application.c md5.c user.c screens.c -L../lib -lncursesw -o ../bin/atm.exe -I../include -v
    cd ..
)

cd bin
type nul >> "users.csv"
atm.exe