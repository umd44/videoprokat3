# Видеопрокат - Система управления кинопрокатом

Кроссязыковой проект (Java и C++) для демонстрации OOP концепций, STL/Collections Framework, шаблонов и производных классов.

## Содержание проекта

### 📋 Основные классы

#### Абстрактные классы (базовые типы)
- **Client** - Абстрактный базовый класс для клиентов
- **VideoCarrier** - Абстрактный базовый класс для видеоносителей
- **Rental** - Абстрактный базовый класс для аренды
- **Catalog** - Абстрактный базовый класс для каталога
- **RentalManager** - Абстрактный базовый класс для управления арендами
- **FinancialCalculator** - Абстрактный базовый класс для финансовых расчётов
- **ReportGenerator** - Абстрактный базовый класс для генерации отчётов

#### Конкретные реализации
- **ClientReal** - Стандартный клиент
- **VideoCarrierReal** - Стандартный видеоноситель
- **RentalReal** - Конкретная реализация аренды
- **CatalogReal** - Конкретная реализация каталога
- **RentalManagerReal** - Конкретная реализация менеджера аренды
- **FinancialCalculatorReal** - Конкретная реализация финансовых расчётов
- **ReportGeneratorReal** - Конкретная реализация генератора отчётов

### 🎯 Производные классы

#### Производные классы Client
1. **PremiumClient** - Премиальный клиент с системой лояльности и уведомлениями
   - Реализует: `Discountable`, `Notifiable`
   - Функции: скидки, баллы лояльности, email/SMS уведомления

2. **CorporateClient** - Корпоративный клиент
   - Реализует: `Discountable`
   - Функции: корпоративные скидки на основе размера компании

3. **StudentClient** - Студентский клиент
   - Реализует: `Discountable`, `Notifiable`
   - Функции: студенческие скидки с валидацией статуса

4. **VIPClient** - ВИП клиент с максимальными привилегиями
   - Реализует: `Discountable`, `Notifiable`
   - Функции: уровни ВИП (platinum, gold, silver), накопление кэшбека

#### Производные классы VideoCarrier
1. **PremiumVideoCarrier** - Премиальный видеоноситель (4K/Ultra HD)
   - Функции: форматы, специальные функции, добавки к цене

### 🔌 Интерфейсы

- **Discountable** - Интерфейс для применения скидок
- **Notifiable** - Интерфейс для отправки уведомлений

## 📚 Документация

### STL_JCF_Examples.md
Подробная документация с примерами для:

#### C++ STL
- Контейнеры: `std::array`, `std::vector`, `std::list`, `std::map`, `std::span`
- Алгоритмы: `std::sort`, `std::find_if`, `std::copy_if`, `std::remove_if`, `std::min_element`, `std::max_element`, `std::any_of`
- Шаблонные функции с ограничениями типов (concepts C++20)
- Шаблонные классы с шаблонными и нешаблонными методами
- Использование производных классов с полиморфизмом

#### Java Collections Framework
- Контейнеры: `ArrayList`, `LinkedList`, `HashMap`, `TreeMap`, `HashSet`, `TreeSet`
- Stream API: фильтрация, преобразование, сортировка
- Шаблонные методы (generics) с ограничениями
- Производные классы и интерфейсы
- Примеры с реальными производными классами проекта

#### C# Collections
- Контейнеры: `List<T>`, `LinkedList<T>`, `Dictionary<K,V>`, `SortedDictionary`, `HashSet<T>`, `SortedSet<T>`
- LINQ: Where, Select, OrderBy, Min, Max, Any
- Обобщенные методы (Generics)
- Полиморфизм и наследование

## 🎮 Примеры использования

### Запуск демонстрации производных классов (Java)
```bash
javac -d . *.java
java -cp . videoprokat.DerivedClassesDemo
```

### Запуск главной демонстрации (Java)
```bash
java -cp . videoprokat.VideoprokatDemo
```

### C++ (Visual Studio)
Проект находится в папке `videoprokat/` и может быть открыт в Visual Studio.

## 📖 Ключевые концепции

### 1. Полиморфизм
- Производные классы хранятся в контейнерах базовых типов
- Динамическое связывание методов через виртуальные функции/интерфейсы
- Применение различных операций к объектам разных типов

### 2. Использование контейнеров и алгоритмов
- **Сортировка**: `std::sort()` / `Collections.sort()` / LINQ `OrderBy`
- **Поиск**: `std::find_if()` / Stream API `filter()` / LINQ `Where`
- **Копирование**: `std::copy_if()` / Stream API `collect()` / LINQ `Select`
- **Удаление**: `std::remove_if()` / `removeIf()` / `RemoveAll()`
- **Min/Max**: `std::min_element()`, `std::max_element()` / `Collections.min/max` / LINQ Min/Max
- **Проверка**: `std::any_of()` / Stream API `anyMatch()` / LINQ `Any()`

### 3. Шаблоны (Generics/Templates)
- **Шаблонные функции**: вычисления, преобразования, фильтрация
- **Шаблонные классы**: коллекции с типобезопасностью
- **Ограничения типов**: ограничение на компиляции (concepts, extends, where)

### 4. Интерфейсы и абстрактные классы
- Определение контрактов для производных классов
- Множественная реализация интерфейсов
- Полиморфное поведение

## 📊 Структура файлов

```
project/
├── README.md                      # Этот файл
├── STL_JCF_Examples.md           # Подробная документация с примерами
├── .gitignore                     # Git конфигурация
│
├── Java классы (видеопрокат):
├── Client.java                    # Абстрактный класс клиента
├── ClientReal.java               # Реализация клиента
├── VideoCarrier.java             # Абстрактный класс видеоносителя
├── VideoCarrierReal.java         # Реализация видеоносителя
├── Rental.java, RentalReal.java
├── Catalog.java, CatalogReal.java
├── RentalManager.java, RentalManagerReal.java
├── FinancialCalculator.java, FinancialCalculatorReal.java
├── ReportGenerator.java, ReportGeneratorReal.java
├── VideoprokatDemo.java           # Главная демонстрация
│
├── Интерфейсы:
├── Discountable.java             # Интерфейс для скидок
├── Notifiable.java               # Интерфейс для уведомлений
│
├── Производные классы:
├── PremiumClient.java            # Премиальный клиент
├── CorporateClient.java          # Корпоративный клиент
├── StudentClient.java            # Студентский клиент
├── VIPClient.java                # ВИП клиент
├── PremiumVideoCarrier.java      # Премиальный видеоноситель
│
├── Демонстрация:
├── DerivedClassesDemo.java       # Демонстрация производных классов
│
└── videoprokat/ (C++ Visual Studio проект)
    ├── videoprokat.cpp
    ├── videoprokat.hpp
    ├── Client.hpp/.cpp
    ├── VideoCarrier.hpp/.cpp
    └── ... (другие файлы)
```

## 🔧 Технические требования

- **Java**: JDK 8+
- **C++**: Visual Studio 2019+ с C++17 (для std::span) или C++20 (для concepts)
- **C#**: .NET Framework 4.7+

## 📝 Примеры кода

### Использование производных классов в контейнере (Java)
```java
List<Client> clients = new ArrayList<>();
clients.add(new ClientReal(1, "John", "Doe", "+1-111"));
clients.add(new PremiumClient(2, "Jane", "Smith", "+1-222", "jane@email.com", 15.0));
clients.add(new VIPClient(3, "David", "Wilson", "+1-333", "platinum", "david@email.com", "Manager"));

// Применение скидок полиморфно
for (Client client : clients) {
    if (client instanceof Discountable) {
        double price = ((Discountable) client).applyDiscount(100.0);
        System.out.println(client.getFirstName() + ": $" + price);
    }
}

// Поиск с Stream API
List<Client> vips = clients.stream()
    .filter(c -> c instanceof VIPClient)
    .collect(Collectors.toList());
```

### Использование STL контейнеров с производными классами (C++)
```cpp
std::vector<std::unique_ptr<Client>> clients;
clients.push_back(std::make_unique<RegularClient>("John"));
clients.push_back(std::make_unique<PremiumClientCpp>("Jane", 15.0));

// Сортировка по скидке
std::sort(clients.begin(), clients.end(),
    [](const auto& a, const auto& b) {
        return a->getDiscount() < b->getDiscount();
    }
);

// Поиск
auto premium = std::find_if(clients.begin(), clients.end(),
    [](const auto& c) { return c->getDiscount() > 0.0; }
);
```

## 🎓 Образовательная ценность

Этот проект демонстрирует:

1. **Object-Oriented Programming**
   - Наследование
   - Полиморфизм
   - Инкапсуляция
   - Абстракция

2. **Data Structures & Algorithms**
   - Контейнеры (массивы, списки, деревья)
   - Алгоритмы сортировки и поиска
   - Эффективное использование памяти

3. **Generic Programming**
   - Шаблоны функций
   - Шаблоны классов
   - Ограничения типов

4. **Best Practices**
   - SOLID принципы
   - Design Patterns
   - Code reusability

## 📄 Лицензия

Образовательный проект

## 👥 Автор

Проект разработан как демонстрация современных подходов к программированию на Java и C++.
