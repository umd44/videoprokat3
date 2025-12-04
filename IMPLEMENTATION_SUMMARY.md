# Отчет о Реализации Задания L5

## Выполненные Задачи

### Общие для C++ и Java:

#### ✅ 1. Производные классы
Созданы следующие производные классы:

**Java:**
- `PremiumClient` (extends Client, implements Discountable, Notifiable) - премиальный клиент с системой лояльности
- `CorporateClient` (extends Client, implements Discountable) - корпоративный клиент
- `DVDCarrier` (extends VideoCarrier, implements Cloneable) - DVD носитель
- `BluRayCarrier` (extends VideoCarrier) - BluRay носитель

**C++:**
- `PremiumClient` : public Client - премиальный клиент
- `DVDCarrier` : public VideoCarrier - DVD носитель
- `BluRayCarrier` : public VideoCarrier - BluRay носитель
- `CashPaymentProcessor` : public PaymentProcessor - обработчик наличных
- `CardPaymentProcessor` : public PaymentProcessor - обработчик карт

#### ✅ 2. Модификатор protected

**Базовые классы с protected полями:**

```cpp
// Client.hpp
protected:
    int m_clientId;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phoneNumber;
    double m_depositBalance;
    bool m_isBlacklisted;
```

```cpp
// VideoCarrier.hpp
protected:
    int m_inventoryNumber;
    std::string m_title;
    std::string m_carrierType;
    std::string m_genre;
    double m_rentalPricePerDay;
    double m_fullPrice;
    std::string m_status;
```

**Protected методы в производных классах:**
- `PremiumClient::updateLoyalty()` - обновление бонусов лояльности
- `CorporateClient::calculateCorporateDiscount()` - расчет корпоративной скидки
- `DVDCarrier::applyDVDDiscount()` - применение скидки на DVD
- `BluRayCarrier::calculatePremiumPrice()` - расчет премиальной цены

#### ✅ 3. Перегрузка методов базового класса

**С вызовом метода базового класса:**

```java
// PremiumClient.java
@Override
public void addToDeposit(double amount) {
    super.addToDeposit(amount);  // ВЫЗОВ базового метода
    loyaltyPoints += (int)(amount / 20.0);
    System.out.println("Начислено бонусных баллов");
}
```

```cpp
// PremiumClient.cpp
void PremiumClient::addToDeposit(double amount)
{
    Client::addToDeposit(amount);  // ВЫЗОВ базового метода
    m_loyaltyPoints += static_cast<int>(amount / 20.0);
    std::cout << "Начислено бонусных баллов\n";
}
```

**Без вызова метода базового класса:**

```java
// PremiumClient.java
@Override
public boolean blockDepositFunds(double amount) {
    // БЕЗ ВЫЗОВА super.blockDepositFunds()
    // Полностью новая реализация с применением скидки
    double discountedAmount = applyDiscount(amount);
    if (depositBalance >= discountedAmount) {
        depositBalance -= discountedAmount;
        return true;
    }
    return false;
}
```

#### ✅ 4. Виртуальные функции

**Объявление виртуальных функций:**

```cpp
// Client.hpp
virtual void addToDeposit(double amount);
virtual bool blockDepositFunds(double amount);
virtual ~Client();
```

```cpp
// VideoCarrier.hpp
virtual void markAsRented();
virtual void markAsAvailable();
virtual ~VideoCarrier();
```

**Вызов виртуальной функции через не виртуальную функцию базового класса:**

```cpp
// Client.cpp
void Client::processTransaction(double amount)
{
    std::cout << "Client::processTransaction вызывает виртуальную addToDeposit()\n";
    addToDeposit(amount);  // Вызов виртуального метода
}
```

```cpp
// PaymentProcessor.cpp
void PaymentProcessor::executePayment(double amount, const std::string& details)
{
    std::cout << "PaymentProcessor::executePayment вызывает виртуальную processPayment()\n";
    if (processPayment(amount, details)) {  // Вызов виртуального метода
        m_transactionCount++;
    }
}
```

**Демонстрация полиморфизма:**

```cpp
// InheritanceDemo.cpp - работа через указатель базового класса
Client* basePtr = new PremiumClient(...);
basePtr->addToDeposit(1000.0);  // Вызывается метод PremiumClient
basePtr->processTransaction(500.0);  // Вызывает виртуальный addToDeposit
delete basePtr;
```

**Демонстрация изменения поведения без virtual:**
В коде есть комментарии, объясняющие, что если бы методы не были виртуальными, вызывались бы методы базового класса, и не было бы специфичного поведения производных классов.

#### ✅ 5. Клонирование объектов

**Поверхностное клонирование:**

```cpp
// DVDCarrier.cpp
DVDCarrier* DVDCarrier::shallowClone() const
{
    DVDCarrier* clone = new DVDCarrier();
    // Копирование всех полей
    clone->m_subtitles = this->m_subtitles;  // ПОВЕРХНОСТНОЕ - указатели совпадают
    return clone;
}
```

**Глубокое клонирование:**

```cpp
// DVDCarrier.cpp
DVDCarrier::DVDCarrier(const DVDCarrier& other)
    : VideoCarrier(other),
      m_diskNumber(other.m_diskNumber),
      m_region(other.m_region),
      m_subtitles(new std::vector<std::string>(*other.m_subtitles))  // ГЛУБОКОЕ
{
}

DVDCarrier* DVDCarrier::deepClone() const
{
    return new DVDCarrier(*this);  // Использует конструктор копирования
}
```

**Демонстрация различий:**
- При поверхностном клонировании изменения в списке субтитров клона влияют на оригинал
- При глубоком клонировании списки полностью независимы

#### ✅ 6. Вызов конструктора базового класса с параметрами

```cpp
// PremiumClient.cpp
PremiumClient::PremiumClient(int clientId,
                             const std::string& firstName,
                             const std::string& lastName,
                             const std::string& phoneNumber,
                             const std::string& email,
                             double discountPercentage)
    : Client(clientId, firstName, lastName, phoneNumber),  // Вызов конструктора базового
      m_discountPercentage(discountPercentage),
      m_loyaltyPoints(0),
      m_email(email)
{
    std::cout << "Создан премиум-клиент\n";
}
```

```java
// PremiumClient.java
public PremiumClient(int clientId, String firstName, String lastName, 
                    String phoneNumber, String email, double discountPercentage) {
    super(clientId, firstName, lastName, phoneNumber);  // Вызов конструктора базового
    this.discountPercentage = discountPercentage;
    this.loyaltyPoints = 0;
    this.email = email;
}
```

#### ✅ 7. Абстрактные классы

**Java - абстрактные классы с абстрактными методами:**

```java
public abstract class Client {
    public abstract int getClientId();
    public abstract String getFirstName();
    // ... другие абстрактные методы
}
```

**C++ - абстрактный класс с чисто виртуальными функциями:**

```cpp
class PaymentProcessor
{
public:
    virtual bool processPayment(double amount, const std::string& details) = 0;
    virtual bool refund(double amount, const std::string& transactionId) = 0;
    
    void executePayment(double amount, const std::string& details);
};
```

**Демонстрация использования:**

```cpp
// Нельзя создать: PaymentProcessor* p = new PaymentProcessor(); // ОШИБКА!
// Можно использовать через производные классы:
PaymentProcessor* processor = new CashPaymentProcessor();
processor->executePayment(1500.0, "Оплата");
delete processor;
```

### Специфично для C++:

#### ✅ 8. Перегрузка оператора присваивания

```cpp
// PremiumClient.hpp
PremiumClient& operator=(const Client& base);

// PremiumClient.cpp
PremiumClient& PremiumClient::operator=(const Client& base)
{
    if (this != &base) {
        // Копирование полей базового класса
        m_clientId = base.getClientId();
        m_firstName = base.getFirstName();
        m_lastName = base.getLastName();
        // ... и т.д.
        
        // Инициализация специфичных полей производного класса
        m_discountPercentage = 5.0;
        m_loyaltyPoints = 0;
        m_email = "";
    }
    return *this;
}
```

**Демонстрация:**

```cpp
Client baseClient(10, "John", "Doe", "+7-100");
PremiumClient premiumClient(20, "Jane", "Smith", "+7-200", "jane@example.com", 20.0);
premiumClient = baseClient;  // Присваивание базового производному
```

#### ✅ 9. Запрет конструктора копирования

```cpp
// PremiumClient.hpp
PremiumClient(const PremiumClient&) = delete;

// BluRayCarrier.hpp
BluRayCarrier(const BluRayCarrier&) = delete;
```

**Эффект:**
Попытка копирования приведет к ошибке компиляции:
```cpp
// PremiumClient client2 = client1; // ОШИБКА КОМПИЛЯЦИИ!
```

#### ✅ 10. Виртуальный деструктор

```cpp
// Client.hpp
virtual ~Client();

// VideoCarrier.hpp
virtual ~VideoCarrier();

// PaymentProcessor.hpp
virtual ~PaymentProcessor();
```

**Реализация:**

```cpp
// Client.cpp
Client::~Client()
{
    std::cout << "Деструктор Client для " << m_firstName << "\n";
}

// PremiumClient.cpp
PremiumClient::~PremiumClient()
{
    std::cout << "Деструктор PremiumClient для " << m_firstName << "\n";
}
```

**Демонстрация:**

```cpp
Client* client = new PremiumClient(30, "Bob", "Brown", ...);
delete client;
// Вывод:
// Деструктор PremiumClient для Bob
// Деструктор Client для Bob
```

**Что изменилось:**
Без виртуального деструктора вызывался бы только `~Client()`, что могло привести к утечке памяти, если у `PremiumClient` есть динамически выделенные ресурсы.

### Специфично для Java:

#### ✅ 11. Интерфейсы

**Определение интерфейсов:**

```java
// Discountable.java
public interface Discountable {
    double getDiscountPercentage();
    double applyDiscount(double amount);
    boolean isDiscountAvailable();
}

// Notifiable.java
public interface Notifiable {
    void sendNotification(String message);
    String getPreferredNotificationMethod();
}
```

**Реализация:**

```java
// PremiumClient.java
public class PremiumClient extends Client implements Discountable, Notifiable {
    @Override
    public double getDiscountPercentage() {
        return discountPercentage;
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - discountPercentage / 100.0);
    }
    
    @Override
    public void sendNotification(String message) {
        System.out.println("[EMAIL to " + email + "] " + message);
    }
    // ... другие методы
}
```

#### ✅ 12. Множественное наследование

```java
// PremiumClient.java - наследует от абстрактного класса и реализует интерфейсы
public class PremiumClient extends Client implements Discountable, Notifiable {
    // Методы от Client
    @Override
    public int getClientId() { ... }
    
    // Методы от Discountable
    @Override
    public double applyDiscount(double amount) { ... }
    
    // Методы от Notifiable
    @Override
    public void sendNotification(String message) { ... }
}
```

```java
// CorporateClient.java - множественное наследование с одним интерфейсом
public class CorporateClient extends Client implements Discountable {
    // Реализация методов от Client и Discountable
}
```

## Структура Демонстрационных Программ

### Java: InheritanceDemo.java
Демонстрирует:
1. Множественное наследование
2. Полиморфизм через базовые ссылки
3. Работу с массивами через полиморфизм
4. Клонирование (поверхностное и глубокое)
5. Виртуальные методы через указатели
6. Перегрузку методов

### C++: InheritanceDemo.cpp
Демонстрирует:
1. Виртуальные функции
2. Полиморфизм с массивами
3. Клонирование
4. Оператор присваивания
5. Абстрактные классы
6. Виртуальные деструкторы
7. Protected члены
8. Удаленные конструкторы копирования

## Запуск Демонстраций

### Java:
```bash
cd /home/engine/project
javac -d . *.java
java videoprokat.InheritanceDemo
```

### C++:
```bash
cd /home/engine/project/videoprokat
make InheritanceDemo
./InheritanceDemo
```

## Результаты

Все требуемые концепции успешно реализованы и продемонстрированы:
- ✅ Производные классы (несколько)
- ✅ Модификатор protected
- ✅ Перегрузка методов (с вызовом и без вызова базового)
- ✅ Виртуальные функции
- ✅ Клонирование (поверхностное и глубокое)
- ✅ Вызов конструктора базового класса с параметрами
- ✅ Абстрактные классы
- ✅ Перегрузка оператора присваивания (C++)
- ✅ Запрет конструктора копирования (C++)
- ✅ Виртуальный деструктор (C++)
- ✅ Интерфейсы (Java)
- ✅ Множественное наследование (Java)

Все программы компилируются и работают корректно, демонстрируя правильную реализацию всех концепций ООП.
