@echo off
echo ====================================================
echo      QUAN LY CHI TIEU CA NHAN - BUILD SCRIPT
echo ====================================================
echo Bien dich voi g++...

if not exist build mkdir build

g++ -Wall -Wextra -I include/ -o build\quanlychitieu ^
    src\main.cpp src\tienich.cpp src\giaodich.cpp ^
    src\ngansach.cpp src\baocao.cpp src\taodata.cpp

if %errorlevel% neq 0 (
    echo.
    echo [THAT BAI] Bien dich loi. Kiem tra lai code.
    pause
    exit /b 1
)

echo [OK] Bien dich thanh cong! -> build\quanlychitieu.exe
echo.
echo Dang chay chuong trinh...
echo ====================================================
.\build\quanlychitieu
