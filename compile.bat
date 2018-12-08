@echo off
cd src
gcc application.c md5.c user.c screens.c -L../lib -lncursesw -o ../bin/atm.exe -I../include
cd ..