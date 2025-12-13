@echo off
chcp 65001 > nul
cls

echo ╔═══════════════════════════════════════════════════════════════╗
echo ║                                                               ║
echo ║       ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА                    ║
echo ║       Запуск графического интерфейса (GUI)                   ║
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
echo [2/2] Запуск GUI приложения...
echo ℹ️  Откроется окно с графическим интерфейсом
echo.

start javaw videoprokat.VideoprokatGUI

echo.
echo ✓ GUI приложение запущено!
echo   Если окно не появилось, проверьте панель задач.
echo.
pause
