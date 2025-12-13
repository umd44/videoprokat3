#!/bin/bash

clear

echo "╔═══════════════════════════════════════════════════════════════╗"
echo "║                                                               ║"
echo "║       ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА                    ║"
echo "║       Запуск графического интерфейса (GUI)                   ║"
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
echo "[2/2] Запуск GUI приложения..."
echo "ℹ️  Откроется окно с графическим интерфейсом"
echo ""

java videoprokat.VideoprokatGUI &

echo ""
echo "✓ GUI приложение запущено!"
echo ""
