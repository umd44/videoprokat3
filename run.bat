@echo off
chcp 65001 > nul
cls

echo ╔═══════════════════════════════════════════════════════════════╗
echo ║                                                               ║
echo ║       ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА                    ║
echo ║       Компиляция и запуск программы                          ║
echo ║                                                               ║
echo ╚═══════════════════════════════════════════════════════════════╝
echo.

echo [1/2] Компиляция проекта...
javac -encoding UTF-8 -d . *.java

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ✗ Ошибка компиляции!
    echo Убедитесь, что Java Development Kit (JDK) установлен.
    echo.
    pause
    exit /b 1
)

echo ✓ Компиляция успешна!
echo.
echo [2/2] Запуск интерактивного приложения...
echo.
timeout /t 2 /nobreak > nul

java videoprokat.VideoprokatInteractiveApp

echo.
echo Программа завершена.
pause
