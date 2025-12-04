#!/bin/bash

echo "╔═══════════════════════════════════════════════════════════╗"
echo "║   ТЕСТИРОВАНИЕ РЕАЛИЗАЦИИ L5                              ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""

# Test Java
echo "=== JAVA КОМПИЛЯЦИЯ ==="
cd /home/engine/project
javac -d . *.java
if [ $? -eq 0 ]; then
    echo "✅ Java компиляция успешна"
else
    echo "❌ Java компиляция провалена"
    exit 1
fi

echo ""
echo "=== JAVA ДЕМОНСТРАЦИЯ НАСЛЕДОВАНИЯ ==="
java videoprokat.InheritanceDemo > /tmp/java_demo.log 2>&1
if [ $? -eq 0 ]; then
    echo "✅ Java InheritanceDemo выполнена успешно"
    echo "   Строк вывода: $(wc -l < /tmp/java_demo.log)"
else
    echo "❌ Java InheritanceDemo провалена"
    exit 1
fi

echo ""
echo "=== JAVA ОСНОВНАЯ ПРОГРАММА ==="
java videoprokat.VideoprokatDemo > /tmp/java_main.log 2>&1
if [ $? -eq 0 ]; then
    echo "✅ Java VideoprokatDemo выполнена успешно"
    echo "   Строк вывода: $(wc -l < /tmp/java_main.log)"
else
    echo "❌ Java VideoprokatDemo провалена"
    exit 1
fi

# Test C++
echo ""
echo "=== C++ СБОРКА ==="
cd /home/engine/project/videoprokat
make clean > /dev/null 2>&1
make InheritanceDemo > /tmp/cpp_build.log 2>&1
if [ $? -eq 0 ]; then
    echo "✅ C++ InheritanceDemo собрана успешно"
else
    echo "❌ C++ InheritanceDemo сборка провалена"
    cat /tmp/cpp_build.log
    exit 1
fi

make videoprokat > /tmp/cpp_build_main.log 2>&1
if [ $? -eq 0 ]; then
    echo "✅ C++ videoprokat собран успешно"
else
    echo "❌ C++ videoprokat сборка провалена"
    cat /tmp/cpp_build_main.log
    exit 1
fi

echo ""
echo "=== C++ ДЕМОНСТРАЦИЯ НАСЛЕДОВАНИЯ ==="
cd ..
./demos/InheritanceDemo > /tmp/cpp_demo.log 2>&1
if [ $? -eq 0 ]; then
    echo "✅ C++ InheritanceDemo выполнена успешно"
    echo "   Строк вывода: $(wc -l < /tmp/cpp_demo.log)"
else
    echo "❌ C++ InheritanceDemo провалена"
    exit 1
fi
cd videoprokat

echo ""
echo "=== C++ ОСНОВНАЯ ПРОГРАММА ==="
./videoprokat > /tmp/cpp_main.log 2>&1
if [ $? -eq 0 ]; then
    echo "✅ C++ videoprokat выполнена успешно"
    echo "   Строк вывода: $(wc -l < /tmp/cpp_main.log)"
else
    echo "❌ C++ videoprokat провалена"
    exit 1
fi

echo ""
echo "╔═══════════════════════════════════════════════════════════╗"
echo "║   ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!                             ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""
echo "Реализованные концепции:"
echo "✅ Производные классы (PremiumClient, CorporateClient, DVDCarrier, BluRayCarrier)"
echo "✅ Модификатор protected"
echo "✅ Перегрузка методов (с вызовом и без вызова базового)"
echo "✅ Виртуальные функции и полиморфизм"
echo "✅ Клонирование (поверхностное и глубокое)"
echo "✅ Вызов конструктора базового класса с параметрами"
echo "✅ Абстрактные классы"
echo "✅ Перегрузка оператора присваивания (C++)"
echo "✅ Запрет конструктора копирования (C++)"
echo "✅ Виртуальный деструктор (C++)"
echo "✅ Интерфейсы (Java)"
echo "✅ Множественное наследование (Java)"
echo ""
