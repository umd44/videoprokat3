#!/bin/bash

clear

echo "╔═══════════════════════════════════════════════════════════════╗"
echo "║                                                               ║"
echo "║       ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА                    ║"
echo "║       Компиляция и запуск программы                          ║"
echo "║                                                               ║"
echo "╚═══════════════════════════════════════════════════════════════╝"
echo ""

echo "[1/2] Компиляция проекта..."
javac -encoding UTF-8 -d . *.java

if [ $? -ne 0 ]; then
    echo ""
    echo "✗ Ошибка компиляции!"
    echo "Убедитесь, что Java Development Kit (JDK) установлен."
    echo ""
    read -p "Нажмите Enter для выхода..."
    exit 1
fi

echo "✓ Компиляция успешна!"
echo ""
echo "[2/2] Запуск интерактивного приложения..."
echo ""
sleep 2

java videoprokat.VideoprokatInteractiveApp

echo ""
echo "Программа завершена."
read -p "Нажмите Enter для выхода..."
