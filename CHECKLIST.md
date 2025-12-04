# Чек-лист Реализации Задания L5

## Модифицировать проект на С++, Java:

### ✅ Производные классы (несколько)
- **Java:**
  - [x] `PremiumClient extends Client implements Discountable, Notifiable`
  - [x] `CorporateClient extends Client implements Discountable`
  - [x] `DVDCarrier extends VideoCarrier implements Cloneable`
  - [x] `BluRayCarrier extends VideoCarrier`

- **C++:**
  - [x] `class PremiumClient : public Client`
  - [x] `class DVDCarrier : public VideoCarrier`
  - [x] `class BluRayCarrier : public VideoCarrier`
  - [x] `class CashPaymentProcessor : public PaymentProcessor`
  - [x] `class CardPaymentProcessor : public PaymentProcessor`

### ✅ Модификатор protected
- **Java:**
  - [x] `Client`: protected fields (clientId, firstName, depositBalance, blacklisted)
  - [x] `VideoCarrier`: protected fields (inventoryNumber, title, rentalPricePerDay, status)
  - [x] Protected методы: `updateLoyalty()`, `calculateCorporateDiscount()`

- **C++:**
  - [x] `Client.hpp`: protected members (m_clientId, m_firstName, m_depositBalance, m_isBlacklisted)
  - [x] `VideoCarrier.hpp`: protected members (m_inventoryNumber, m_title, m_rentalPricePerDay, m_status)
  - [x] Protected методы: `updateLoyalty()`, `applyDVDDiscount()`, `calculatePremiumPrice()`

### ✅ Перегрузка методов с вызовом базового класса
- **Java:**
  - [x] `PremiumClient.addToDeposit()` - вызывает `super.addToDeposit()`
  - [x] `BluRayCarrier.markAsAvailable()` - вызывает базовый метод

- **C++:**
  - [x] `PremiumClient::addToDeposit()` - вызывает `Client::addToDeposit()`
  - [x] `BluRayCarrier::markAsAvailable()` - вызывает `VideoCarrier::markAsAvailable()`

### ✅ Перегрузка методов без вызова базового класса
- **Java:**
  - [x] `PremiumClient.blockDepositFunds()` - не вызывает super
  - [x] `BluRayCarrier.markAsRented()` - полностью новая реализация

- **C++:**
  - [x] `PremiumClient::blockDepositFunds()` - не вызывает базовый метод
  - [x] `BluRayCarrier::markAsRented()` - полностью новая реализация

### ✅ Виртуальные функции
- **Java:** (все методы виртуальные по умолчанию)
  - [x] Полиморфизм через Client reference
  - [x] Полиморфизм через VideoCarrier reference

- **C++:**
  - [x] `virtual void addToDeposit(double amount)` в Client
  - [x] `virtual bool blockDepositFunds(double amount)` в Client
  - [x] `virtual void markAsRented()` в VideoCarrier
  - [x] `virtual void markAsAvailable()` в VideoCarrier

### ✅ Вызов виртуальной функции НЕ виртуальной функцией базового класса
- **Java:**
  - [x] (В Java все методы виртуальные, демонстрация через обычные вызовы)

- **C++:**
  - [x] `Client::processTransaction()` вызывает виртуальную `addToDeposit()`
  - [x] `PaymentProcessor::executePayment()` вызывает виртуальную `processPayment()`

### ✅ Вызов виртуальной функции через динамические объекты
- **Java:**
  - [x] `Client baseRef = new PremiumClient(...)` в InheritanceDemo
  - [x] `List<VideoCarrier> carriers` с разными типами

- **C++:**
  - [x] `Client* basePtr = new PremiumClient(...)` в InheritanceDemo
  - [x] `std::vector<VideoCarrier*> carriers` с разными типами

### ✅ Демонстрация изменения работы, если функция не виртуальная
- [x] Описано в комментариях и выводе InheritanceDemo
- [x] Объяснено, что без virtual вызывались бы методы базового класса

### ✅ Клонирование (поверхностное и глубокое)
- **Java:**
  - [x] `DVDCarrier.shallowClone()` - поверхностное клонирование
  - [x] `DVDCarrier.deepClone()` - глубокое клонирование
  - [x] Демонстрация разницы в InheritanceDemo

- **C++:**
  - [x] `DVDCarrier::shallowClone()` - поверхностное клонирование
  - [x] `DVDCarrier::deepClone()` - глубокое клонирование через конструктор копирования
  - [x] Демонстрация разницы в InheritanceDemo

### ✅ Вызов конструктора базового класса с параметрами
- **Java:**
  - [x] Все производные классы вызывают `super(clientId, firstName, ...)`

- **C++:**
  - [x] Все производные классы используют список инициализации: `: Client(clientId, ...)`

### ✅ Абстрактные классы
- **Java:**
  - [x] `Client` - абстрактный класс с абстрактными методами
  - [x] `VideoCarrier` - абстрактный класс с абстрактными методами
  - [x] `Rental` - абстрактный класс

- **C++:**
  - [x] `PaymentProcessor` - абстрактный класс с чисто виртуальными функциями
  - [x] `processPayment() = 0` и `refund() = 0`
  - [x] Демонстрация использования через производные классы

## Модифицировать проект на С++:

### ✅ Перегрузка оператора присваивания для присваивания объекту производного класса объектов базового класса
- [x] `PremiumClient& operator=(const Client& base)` в PremiumClient
- [x] Демонстрация в InheritanceDemo: `premiumClient = baseClient`

### ✅ Запрет конструктора копирования
- [x] `PremiumClient(const PremiumClient&) = delete`
- [x] `BluRayCarrier(const BluRayCarrier&) = delete`
- [x] Описание в демонстрации

### ✅ Виртуальный деструктор
- [x] `virtual ~Client()` в Client.hpp
- [x] `virtual ~VideoCarrier()` в VideoCarrier.hpp
- [x] `virtual ~PaymentProcessor()` в PaymentProcessor.hpp
- [x] Реализация в .cpp файлах
- [x] Демонстрация корректного вызова деструкторов производных классов
- [x] Объяснение изменений в InheritanceDemo

## Модифицировать проект на Java:

### ✅ Интерфейсы
- [x] `Discountable` - интерфейс для объектов со скидками
  - [x] `getDiscountPercentage()`
  - [x] `applyDiscount(double amount)`
  - [x] `isDiscountAvailable()`

- [x] `Notifiable` - интерфейс для отправки уведомлений
  - [x] `sendNotification(String message)`
  - [x] `getPreferredNotificationMethod()`

### ✅ Множественное наследование (от абстрактного класса и интерфейсов)
- [x] `PremiumClient extends Client implements Discountable, Notifiable`
  - Наследует от абстрактного класса Client
  - Реализует интерфейс Discountable
  - Реализует интерфейс Notifiable

- [x] `CorporateClient extends Client implements Discountable`
  - Наследует от абстрактного класса Client
  - Реализует интерфейс Discountable

## Демонстрационные программы:

### ✅ Java: InheritanceDemo.java
- [x] Демонстрация полиморфизма
- [x] Демонстрация работы с массивами
- [x] Демонстрация клонирования
- [x] Демонстрация виртуальных методов через ссылки
- [x] Демонстрация перегрузки методов
- [x] Демонстрация множественного наследования
- [x] Демонстрация интерфейсов

### ✅ C++: InheritanceDemo.cpp
- [x] Демонстрация виртуальных функций
- [x] Демонстрация полиморфизма с массивами
- [x] Демонстрация клонирования
- [x] Демонстрация оператора присваивания
- [x] Демонстрация абстрактных классов
- [x] Демонстрация виртуальных деструкторов
- [x] Демонстрация protected членов
- [x] Демонстрация удаленных конструкторов копирования

## Дополнительные файлы:

### ✅ Документация
- [x] README.md - подробная документация проекта
- [x] IMPLEMENTATION_SUMMARY.md - отчет о реализации
- [x] CHECKLIST.md - данный чек-лист

### ✅ Сборка и тестирование
- [x] Makefile для C++
- [x] test_all.sh - скрипт для тестирования всех компонентов
- [x] .gitignore - игнорирование временных файлов

## Статус выполнения: ✅ ВЫПОЛНЕНО 100%

Все требования задания успешно реализованы и протестированы.
