# Детальная Реализация Задания L5

## Содержание
1. [Общие требования (C++ и Java)](#общие-требования)
2. [Специфичные требования для C++](#специфичные-требования-для-c)
3. [Специфичные требования для Java](#специфичные-требования-для-java)
4. [Как запустить демонстрацию](#как-запустить-демонстрацию)

---

## Общие требования

### 1. Производные классы

#### ✅ Требование: Придумать для чего в вашем проекте нужен производный класс (желательно не один) и создать его (их)

**Реализовано 4+ производных класса:**

#### Java: PremiumClient (премиальный клиент)

**Назначение:** Клиент с системой лояльности, скидками и уведомлениями

```java
// PremiumClient.java
public class PremiumClient extends Client implements Discountable, Notifiable {
    
    private double discountPercentage;
    private int loyaltyPoints;
    private String email;
    private String preferredNotificationMethod;
    
    public PremiumClient(int clientId, String firstName, String lastName, 
                        String phoneNumber, String email, double discountPercentage) {
        super(clientId, firstName, lastName, phoneNumber);
        this.discountPercentage = discountPercentage;
        this.loyaltyPoints = 0;
        this.email = email;
        this.preferredNotificationMethod = "email";
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - discountPercentage / 100.0);
    }
    
    @Override
    public void sendNotification(String message) {
        System.out.println("[EMAIL to " + email + "] " + message);
    }
}
```

#### Java: CorporateClient (корпоративный клиент)

**Назначение:** Клиент от компании с корпоративными скидками

```java
// CorporateClient.java
public class CorporateClient extends Client implements Discountable {
    
    private String companyName;
    private double corporateDiscount;
    private int employeeCount;
    
    public CorporateClient(int clientId, String firstName, String lastName,
                          String phoneNumber, String companyName, int employeeCount) {
        super(clientId, firstName, lastName, phoneNumber);
        this.companyName = companyName;
        this.employeeCount = employeeCount;
        this.corporateDiscount = calculateCorporateDiscount();
    }
    
    protected double calculateCorporateDiscount() {
        if (employeeCount > 100) return 25.0;
        if (employeeCount > 50) return 20.0;
        if (employeeCount > 10) return 15.0;
        return 10.0;
    }
}
```

#### Java: DVDCarrier (DVD носитель)

**Назначение:** DVD диск с поддержкой субтитров и клонирования

```java
// DVDCarrier.java
public class DVDCarrier extends VideoCarrier implements Cloneable {
    
    private int diskNumber;
    private String region;
    private List<String> subtitles;
    
    public DVDCarrier(int inventoryNumber, String title, String genre,
                     double rentalPricePerDay, double fullPrice, 
                     int diskNumber, String region) {
        super(inventoryNumber, title, "DVD", genre, rentalPricePerDay, fullPrice);
        this.diskNumber = diskNumber;
        this.region = region;
        this.subtitles = new ArrayList<>();
    }
}
```

#### Java: BluRayCarrier (BluRay носитель)

**Назначение:** BluRay диск с поддержкой 4K и HDR

```java
// BluRayCarrier.java
public class BluRayCarrier extends VideoCarrier {
    
    private boolean is4K;
    private boolean hasHDR;
    private int storageGB;
    
    public BluRayCarrier(int inventoryNumber, String title, String genre,
                        double rentalPricePerDay, double fullPrice, 
                        boolean is4K, boolean hasHDR) {
        super(inventoryNumber, title, "BluRay", genre, rentalPricePerDay, fullPrice);
        this.is4K = is4K;
        this.hasHDR = hasHDR;
        this.storageGB = is4K ? 50 : 25;
    }
    
    protected double calculatePremiumPrice() {
        double basePrice = rentalPricePerDay;
        if (is4K) basePrice *= 1.5;
        if (hasHDR) basePrice *= 1.2;
        return basePrice;
    }
}
```

#### C++: PremiumClient

```cpp
// PremiumClient.hpp
class PremiumClient : public Client
{
public:
    PremiumClient(int clientId,
                  const std::string& firstName,
                  const std::string& lastName,
                  const std::string& phoneNumber,
                  const std::string& email,
                  double discountPercentage);
    
    virtual ~PremiumClient();
    
    double applyDiscount(double amount) const;
    void sendNotification(const std::string& message) const;

protected:
    double m_discountPercentage;
    int m_loyaltyPoints;
    std::string m_email;
};
```

---

### 2. Модификатор protected

#### ✅ Требование: Продемонстрировать разумное применение модификатора protected

**Реализовано:** Protected поля в базовых классах доступны производным классам

#### Базовый класс Client с protected полями

**Java:**
```java
// Client.java
public abstract class Client {
    protected int clientId;
    protected String firstName;
    protected String lastName;
    protected String phoneNumber;
    protected double depositBalance;
    protected boolean blacklisted;
}
```

**C++:**
```cpp
// Client.hpp
class Client
{
protected:
    int m_clientId;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phoneNumber;
    double m_depositBalance;
    bool m_isBlacklisted;
};
```

#### Использование protected полей в производном классе

**Java:**
```java
// CorporateClient.java
public class CorporateClient extends Client implements Discountable {
    
    // Метод использует protected поля базового класса
    protected double calculateCorporateDiscount() {
        // Прямой доступ к protected полю employeeCount
        if (employeeCount > 100) return 25.0;
        if (employeeCount > 50) return 20.0;
        return 10.0;
    }
}
```

**C++:**
```cpp
// PremiumClient.cpp
PremiumClient& PremiumClient::operator=(const Client& base)
{
    if (this != &base) {
        // Прямой доступ к protected полям базового класса
        m_clientId = base.getClientId();
        m_firstName = base.getFirstName();
        m_depositBalance = base.getDepositBalance();
        // ...
    }
    return *this;
}
```

#### Базовый класс VideoCarrier с protected полями

**Java:**
```java
// VideoCarrier.java
public abstract class VideoCarrier {
    protected int inventoryNumber;
    protected String title;
    protected String carrierType;
    protected String genre;
    protected double rentalPricePerDay;
    protected double fullPrice;
    protected String status;
}
```

**C++:**
```cpp
// VideoCarrier.hpp
class VideoCarrier
{
protected:
    int m_inventoryNumber;
    std::string m_title;
    std::string m_carrierType;
    std::string m_genre;
    double m_rentalPricePerDay;
    double m_fullPrice;
    std::string m_status;
};
```

#### Protected методы в производных классах

**Java:**
```java
// BluRayCarrier.java
protected double calculatePremiumPrice() {
    double basePrice = rentalPricePerDay;  // Доступ к protected полю
    if (is4K) basePrice *= 1.5;
    if (hasHDR) basePrice *= 1.2;
    return basePrice;
}
```

**C++:**
```cpp
// DVDCarrier.cpp
void DVDCarrier::applyDVDDiscount()
{
    m_rentalPricePerDay *= 0.9;  // Доступ к protected полю
}
```

---

### 3. Перегрузка методов

#### ✅ Требование: Продемонстрировать перегрузку метода базового класса в производном классе (с вызовом метода базового класса и без такого вызова)

#### 3.1. Перегрузка С ВЫЗОВОМ базового метода

**Java:**
```java
// PremiumClient.java
/**
 * Перегрузка С ВЫЗОВОМ базового метода.
 */
@Override
public void addToDeposit(double amount) {
    super.addToDeposit(amount);  // ← ВЫЗОВ базового метода
    
    // Дополнительная логика производного класса
    loyaltyPoints += (int)(amount / 20.0);
    System.out.println("Начислено " + (int)(amount / 20.0) + " бонусных баллов");
}
```

**C++:**
```cpp
// PremiumClient.cpp
void PremiumClient::addToDeposit(double amount)
{
    Client::addToDeposit(amount);  // ← ВЫЗОВ базового метода
    
    // Дополнительная логика производного класса
    m_loyaltyPoints += static_cast<int>(amount / 20.0);
    std::cout << "Начислено " << static_cast<int>(amount / 20.0) 
              << " бонусных баллов\n";
}
```

**Результат:** Выполняется логика базового класса (пополнение депозита) + логика производного класса (начисление бонусов)

#### 3.2. Перегрузка БЕЗ ВЫЗОВА базового метода

**Java:**
```java
// PremiumClient.java
/**
 * Перегрузка БЕЗ ВЫЗОВА базового метода.
 * Полностью переопределяет логику блокировки для премиум-клиентов.
 */
@Override
public boolean blockDepositFunds(double amount) {
    // НЕТ вызова super.blockDepositFunds()
    
    // Полностью новая реализация с применением скидки
    if (amount <= 0.0) return false;
    double discountedAmount = applyDiscount(amount);
    
    if (depositBalance >= discountedAmount) {
        depositBalance -= discountedAmount;
        System.out.println("Применена скидка " + discountPercentage 
                         + "%. Заблокировано: " + discountedAmount);
        return true;
    }
    return false;
}
```

**C++:**
```cpp
// PremiumClient.cpp
bool PremiumClient::blockDepositFunds(double amount)
{
    // НЕТ вызова Client::blockDepositFunds()
    
    // Полностью новая реализация
    if (amount <= 0.0) return false;
    double discountedAmount = applyDiscount(amount);
    
    if (m_depositBalance >= discountedAmount) {
        m_depositBalance -= discountedAmount;
        std::cout << "Применена скидка " << m_discountPercentage 
                  << "%. Заблокировано: " << discountedAmount << "\n";
        return true;
    }
    return false;
}
```

**Результат:** Базовая логика игнорируется, выполняется только логика производного класса с применением скидки

#### 3.3. Еще пример перегрузки

**Java:**
```java
// BluRayCarrier.java
@Override
public void markAsRented() {
    // БЕЗ вызова super
    status = "rented";
    System.out.println("BluRay диск " + (is4K ? "4K " : "") 
                     + "арендован: " + title);
}

@Override
public void markAsAvailable() {
    // С вызовом super
    System.out.println("BluRay возвращен: " + title);
    super.markAsAvailable();  // ← Вызов базового метода
}
```

---

### 4. Виртуальные функции

#### ✅ Требование: Придумать разумное использование виртуальных функций и создать их в вашем проекте

#### 4.1. Объявление виртуальных функций

**C++:**
```cpp
// Client.hpp
class Client
{
public:
    /**
     * Виртуальные методы для демонстрации полиморфизма.
     */
    virtual void addToDeposit(double amount);
    virtual bool blockDepositFunds(double amount);
    
    /**
     * Виртуальный деструктор.
     */
    virtual ~Client();
    
    /**
     * Не виртуальная функция, которая вызывает виртуальную.
     */
    void processTransaction(double amount);
};
```

```cpp
// VideoCarrier.hpp
class VideoCarrier
{
public:
    virtual void markAsRented();
    virtual void markAsAvailable();
    virtual ~VideoCarrier();
};
```

**Java:** В Java все методы виртуальные по умолчанию
```java
// Client.java
public abstract class Client {
    // Все методы виртуальные по умолчанию
    public void addToDeposit(double amount) { ... }
    public boolean blockDepositFunds(double amount) { ... }
}
```

#### 4.2. Вызов виртуальной функции через не виртуальную функцию базового класса

**C++:**
```cpp
// Client.cpp
void Client::processTransaction(double amount)
{
    std::cout << "Client::processTransaction вызывает виртуальную addToDeposit()\n";
    addToDeposit(amount);  // ← Вызов виртуальной функции
}
```

**Демонстрация:**
```cpp
// InheritanceDemo.cpp
Client* basePtr = new PremiumClient(...);
basePtr->processTransaction(500.0);
// Вызывается PremiumClient::addToDeposit(), а не Client::addToDeposit()
```

**Вывод:**
```
Client::processTransaction вызывает виртуальную addToDeposit()
Начислено 25 бонусных баллов
```

#### 4.3. Вызов через динамические объекты базового класса

**C++:**
```cpp
// Указатель базового класса на объект производного
Client* basePtr = new PremiumClient(1, "Alice", "Johnson", 
                                    "+7-222", "alice@example.com", 15.0);

// Вызывается метод производного класса (PremiumClient::addToDeposit)
basePtr->addToDeposit(1000.0);

delete basePtr;
```

**Java:**
```java
// Ссылка базового класса на объект производного
Client baseRef = new PremiumClient(1, "Alice", "Johnson", 
                                   "+7-222", "alice@example.com", 15.0);

// Вызывается метод производного класса
baseRef.addToDeposit(1000.0);
```

#### 4.4. Вызов через динамические объекты производного класса

**C++:**
```cpp
PremiumClient* derivedPtr = new PremiumClient(...);
derivedPtr->addToDeposit(1000.0);
delete derivedPtr;
```

#### 4.5. Демонстрация изменения работы, если функция не виртуальная

**Описание в InheritanceDemo:**

```cpp
std::cout << "--- 3. Демонстрация изменения поведения БЕЗ virtual ---\n";
std::cout << "Если бы методы не были виртуальными, вызывались бы методы базового класса\n";
std::cout << "и не было бы сообщений о начислении бонусных баллов.\n";
```

**Что происходит:**
- **С virtual:** `basePtr->addToDeposit()` вызывает `PremiumClient::addToDeposit()`
- **Без virtual:** `basePtr->addToDeposit()` вызывал бы `Client::addToDeposit()`

#### 4.6. Абстрактный класс с чисто виртуальными функциями

**C++:**
```cpp
// PaymentProcessor.hpp
class PaymentProcessor
{
public:
    /**
     * Чисто виртуальные функции.
     */
    virtual bool processPayment(double amount, const std::string& details) = 0;
    virtual bool refund(double amount, const std::string& transactionId) = 0;
    
    virtual ~PaymentProcessor();
    
    /**
     * Не виртуальная функция, вызывающая виртуальную.
     */
    void executePayment(double amount, const std::string& details);
};
```

```cpp
// PaymentProcessor.cpp
void PaymentProcessor::executePayment(double amount, const std::string& details)
{
    std::cout << "PaymentProcessor::executePayment вызывает виртуальную processPayment()\n";
    if (processPayment(amount, details)) {  // ← Вызов чисто виртуальной
        m_transactionCount++;
    }
}
```

**Использование:**
```cpp
PaymentProcessor* processor = new CashPaymentProcessor();
processor->executePayment(1500.0, "Оплата аренды");
// Вызывается CashPaymentProcessor::processPayment()
delete processor;
```

---

### 5. Клонирование

#### ✅ Требование: Любой из классов сделать допускающий клонирование. Продемонстрировать варианты с поверхностным и глубоким клонированием

#### 5.1. Поверхностное клонирование

**Java:**
```java
// DVDCarrier.java
public class DVDCarrier extends VideoCarrier implements Cloneable {
    
    private List<String> subtitles;
    
    /**
     * Поверхностное клонирование.
     * Список subtitles будет РАЗДЕЛЯТЬСЯ между оригиналом и клоном.
     */
    public DVDCarrier shallowClone() {
        try {
            return (DVDCarrier) super.clone();
        } catch (CloneNotSupportedException e) {
            System.out.println("Ошибка клонирования: " + e.getMessage());
            return null;
        }
    }
}
```

**C++:**
```cpp
// DVDCarrier.cpp
DVDCarrier* DVDCarrier::shallowClone() const
{
    DVDCarrier* clone = new DVDCarrier();
    
    // Копирование примитивных полей
    clone->m_inventoryNumber = this->m_inventoryNumber;
    clone->m_title = this->m_title;
    
    // Поверхностное копирование - копируется УКАЗАТЕЛЬ
    delete clone->m_subtitles;
    clone->m_subtitles = this->m_subtitles;  // ← Тот же указатель!
    
    std::cout << "Поверхностное клонирование DVDCarrier\n";
    return clone;
}
```

**Демонстрация поверхностного клонирования:**
```java
DVDCarrier original = new DVDCarrier(500, "Inception", "Sci-Fi", 45.0, 450.0, 1, "2");
original.addSubtitle("English");
original.addSubtitle("Russian");

DVDCarrier shallowClone = original.shallowClone();
shallowClone.addSubtitle("Spanish");

// ПРОБЛЕМА: изменения в клоне влияют на оригинал!
System.out.println("Субтитры оригинала: " + original.getSubtitles());
// Вывод: [English, Russian, Spanish] ← Spanish добавлен!
```

#### 5.2. Глубокое клонирование

**Java:**
```java
// DVDCarrier.java
/**
 * Глубокое клонирование.
 * Создает НОВЫЙ список subtitles для клона.
 */
public DVDCarrier deepClone() {
    try {
        DVDCarrier cloned = (DVDCarrier) super.clone();
        cloned.subtitles = new ArrayList<>(this.subtitles);  // ← Новый список!
        return cloned;
    } catch (CloneNotSupportedException e) {
        System.out.println("Ошибка клонирования: " + e.getMessage());
        return null;
    }
}
```

**C++:**
```cpp
// DVDCarrier.hpp
/**
 * Конструктор копирования для глубокого клонирования.
 */
DVDCarrier(const DVDCarrier& other);

/**
 * Глубокое клонирование.
 */
DVDCarrier* deepClone() const;
```

```cpp
// DVDCarrier.cpp
DVDCarrier::DVDCarrier(const DVDCarrier& other)
    : VideoCarrier(other),
      m_diskNumber(other.m_diskNumber),
      m_region(other.m_region),
      m_subtitles(new std::vector<std::string>(*other.m_subtitles))  // ← Новый вектор!
{
    std::cout << "Конструктор копирования DVDCarrier (глубокое копирование)\n";
}

DVDCarrier* DVDCarrier::deepClone() const
{
    return new DVDCarrier(*this);  // Использует конструктор копирования
}
```

**Демонстрация глубокого клонирования:**
```java
DVDCarrier original2 = new DVDCarrier(501, "Matrix", "Sci-Fi", 50.0, 500.0, 1, "1");
original2.addSubtitle("English");
original2.addSubtitle("Russian");

DVDCarrier deepClone = original2.deepClone();
deepClone.addSubtitle("French");

// Оригинал НЕ изменен!
System.out.println("Субтитры оригинала: " + original2.getSubtitles());
// Вывод: [English, Russian] ← French НЕ добавлен!

System.out.println("Субтитры клона: " + deepClone.getSubtitles());
// Вывод: [English, Russian, French]
```

#### 5.3. Сравнение поверхностного и глубокого клонирования

| Характеристика | Поверхностное | Глубокое |
|---------------|---------------|----------|
| Копирование примитивов | ✅ Да | ✅ Да |
| Копирование указателей/ссылок | Копируется указатель | Создается новый объект |
| Изменения в клоне влияют на оригинал | ✅ Да | ❌ Нет |
| Безопасность | ⚠️ Опасно | ✅ Безопасно |

---

### 6. Вызов конструктора базового класса

#### ✅ Требование: Продемонстрировать в конструкторе производного класса с параметрами вызов конструктора базового класса

#### 6.1. Java - использование super()

```java
// PremiumClient.java
public class PremiumClient extends Client implements Discountable, Notifiable {
    
    /**
     * Конструктор с параметрами.
     * Демонстрирует вызов конструктора базового класса с параметрами.
     */
    public PremiumClient(int clientId, String firstName, String lastName, 
                        String phoneNumber, String email, double discountPercentage) {
        // ← Вызов конструктора базового класса
        super(clientId, firstName, lastName, phoneNumber);
        
        // Инициализация полей производного класса
        this.discountPercentage = discountPercentage;
        this.loyaltyPoints = 0;
        this.email = email;
        this.preferredNotificationMethod = "email";
    }
}
```

```java
// DVDCarrier.java
public DVDCarrier(int inventoryNumber, String title, String genre,
                 double rentalPricePerDay, double fullPrice, 
                 int diskNumber, String region) {
    // ← Вызов конструктора базового класса
    super(inventoryNumber, title, "DVD", genre, rentalPricePerDay, fullPrice);
    
    // Инициализация полей производного класса
    this.diskNumber = diskNumber;
    this.region = region;
    this.subtitles = new ArrayList<>();
}
```

#### 6.2. C++ - использование списка инициализации

```cpp
// PremiumClient.cpp
PremiumClient::PremiumClient(int clientId,
                             const std::string& firstName,
                             const std::string& lastName,
                             const std::string& phoneNumber,
                             const std::string& email,
                             double discountPercentage)
    // ← Вызов конструктора базового класса через список инициализации
    : Client(clientId, firstName, lastName, phoneNumber),
      m_discountPercentage(discountPercentage),
      m_loyaltyPoints(0),
      m_email(email)
{
    std::cout << "Создан премиум-клиент: " << firstName << " " << lastName 
              << " со скидкой " << discountPercentage << "%\n";
}
```

```cpp
// DVDCarrier.cpp
DVDCarrier::DVDCarrier(int inventoryNumber,
                       const std::string& title,
                       const std::string& genre,
                       double rentalPricePerDay,
                       double fullPrice,
                       int diskNumber,
                       const std::string& region)
    // ← Вызов конструктора базового класса
    : VideoCarrier(inventoryNumber, title, "DVD", genre, rentalPricePerDay, fullPrice),
      m_diskNumber(diskNumber),
      m_region(region),
      m_subtitles(new std::vector<std::string>())
{
    std::cout << "Создан DVD носитель: " << title << " (диск #" << diskNumber << ")\n";
}
```

**Важно:** 
- В Java вызов `super()` должен быть первой строкой в конструкторе
- В C++ инициализация базового класса происходит в списке инициализации

---

### 7. Абстрактные классы

#### ✅ Требование: Придумать разумное использование абстрактного класса и создать его. Продемонстрировать его использование

#### 7.1. Абстрактные классы Java

**Client - абстрактный класс клиента:**
```java
// Client.java
public abstract class Client {
    
    protected int clientId;
    protected String firstName;
    // ...
    
    /**
     * Абстрактные методы - должны быть реализованы в производных классах.
     */
    public abstract int getClientId();
    public abstract String getFirstName();
    public abstract String getLastName();
    public abstract boolean isBlacklisted();
    
    /**
     * Методы с реализацией по умолчанию.
     */
    public void addToDeposit(double amount) {
        if (amount > 0.0) {
            depositBalance += amount;
        }
    }
}
```

**VideoCarrier - абстрактный класс видеоносителя:**
```java
// VideoCarrier.java
public abstract class VideoCarrier {
    
    protected int inventoryNumber;
    protected String title;
    // ...
    
    /**
     * Абстрактные методы.
     */
    public abstract int getInventoryNumber();
    public abstract String getTitle();
    public abstract boolean isAvailable();
    
    /**
     * Методы с реализацией.
     */
    public void markAsRented() {
        status = "rented";
    }
}
```

#### 7.2. Абстрактный класс C++ с чисто виртуальными функциями

**PaymentProcessor - обработчик платежей:**
```cpp
// PaymentProcessor.hpp
/**
 * Абстрактный класс для обработки платежей.
 */
class PaymentProcessor
{
public:
    PaymentProcessor();
    virtual ~PaymentProcessor();
    
    /**
     * Чисто виртуальные функции = 0.
     * Класс становится абстрактным, нельзя создать объект напрямую.
     */
    virtual bool processPayment(double amount, const std::string& details) = 0;
    virtual bool refund(double amount, const std::string& transactionId) = 0;
    
    /**
     * Не виртуальная функция, которая вызывает чисто виртуальную.
     */
    void executePayment(double amount, const std::string& details);

protected:
    int m_transactionCount;
};
```

#### 7.3. Конкретные реализации абстрактного класса

**CashPaymentProcessor - обработчик наличных:**
```cpp
// PaymentProcessor.hpp
class CashPaymentProcessor : public PaymentProcessor
{
public:
    CashPaymentProcessor();
    virtual ~CashPaymentProcessor();
    
    // Реализация чисто виртуальных функций
    virtual bool processPayment(double amount, const std::string& details) override;
    virtual bool refund(double amount, const std::string& transactionId) override;
};
```

```cpp
// PaymentProcessor.cpp
bool CashPaymentProcessor::processPayment(double amount, const std::string& details)
{
    std::cout << "Обработка наличного платежа: " << amount 
              << " руб. (" << details << ")\n";
    return true;
}
```

**CardPaymentProcessor - обработчик карточных платежей:**
```cpp
class CardPaymentProcessor : public PaymentProcessor
{
public:
    CardPaymentProcessor();
    virtual ~CardPaymentProcessor();
    
    virtual bool processPayment(double amount, const std::string& details) override;
    virtual bool refund(double amount, const std::string& transactionId) override;

protected:
    double m_processingFee;
};
```

```cpp
bool CardPaymentProcessor::processPayment(double amount, const std::string& details)
{
    double fee = amount * m_processingFee;
    double total = amount + fee;
    std::cout << "Обработка платежа по карте: " << amount << " + " << fee 
              << " (комиссия) = " << total << " руб. (" << details << ")\n";
    return true;
}
```

#### 7.4. Демонстрация использования абстрактного класса

```cpp
// InheritanceDemo.cpp
void demonstrateAbstractClass()
{
    std::cout << "PaymentProcessor - абстрактный класс\n";
    std::cout << "Нельзя создать: PaymentProcessor* p = new PaymentProcessor(); // ОШИБКА!\n\n";
    
    // Работа через указатель базового класса
    PaymentProcessor* processor1 = new CashPaymentProcessor();
    processor1->executePayment(1500.0, "Оплата аренды");
    delete processor1;
    
    PaymentProcessor* processor2 = new CardPaymentProcessor();
    processor2->executePayment(2000.0, "Оплата депозита");
    delete processor2;
}
```

**Вывод:**
```
Создан обработчик наличных платежей
PaymentProcessor::executePayment вызывает виртуальную processPayment()
Обработка наличного платежа: 1500 руб. (Оплата аренды)
Деструктор CashPaymentProcessor
Деструктор PaymentProcessor. Обработано транзакций: 1
```

---

## Специфичные требования для C++

### 8. Перегрузка оператора присваивания

#### ✅ Требование: Выполнить перегрузку оператора присваивания объекту производного класса объектов базового класса

```cpp
// PremiumClient.hpp
class PremiumClient : public Client
{
public:
    /**
     * Перегрузка оператора присваивания.
     * Позволяет присваивать объект базового класса производному.
     */
    PremiumClient& operator=(const Client& base);
};
```

```cpp
// PremiumClient.cpp
PremiumClient& PremiumClient::operator=(const Client& base)
{
    if (this != &base) {
        // Копирование полей базового класса
        m_clientId = base.getClientId();
        m_firstName = base.getFirstName();
        m_lastName = base.getLastName();
        m_phoneNumber = base.getPhoneNumber();
        m_depositBalance = base.getDepositBalance();
        m_isBlacklisted = base.getIsBlacklisted();
        
        // Инициализация полей производного класса значениями по умолчанию
        m_discountPercentage = 5.0;
        m_loyaltyPoints = 0;
        m_email = "";
        
        std::cout << "Присвоение базового Client производному PremiumClient\n";
    }
    return *this;
}
```

**Демонстрация:**
```cpp
// InheritanceDemo.cpp
void demonstrateAssignmentOperator()
{
    std::cout << "Создаем обычного клиента:\n";
    Client baseClient(10, "John", "Doe", "+7-100");
    baseClient.addToDeposit(2000.0);
    
    std::cout << "\nСоздаем премиум-клиента:\n";
    PremiumClient premiumClient(20, "Jane", "Smith", "+7-200", 
                                "jane@example.com", 20.0);
    
    std::cout << "\nПрисваиваем базовый класс производному:\n";
    premiumClient = baseClient;  // ← Вызывается operator=
    
    std::cout << "Имя премиум-клиента после присваивания: " 
              << premiumClient.getFirstName() << " " 
              << premiumClient.getLastName() << "\n";
    std::cout << "Баланс: " << premiumClient.getDepositBalance() << "\n";
    std::cout << "Скидка (сброшена на дефолт): " 
              << premiumClient.getDiscountPercentage() << "%\n";
}
```

**Вывод:**
```
Присваиваем базовый класс производному:
Присвоение базового Client производному PremiumClient
Имя премиум-клиента после присваивания: John Doe
Баланс: 2000
Скидка (сброшена на дефолт): 5%
```

---

### 9. Запрет конструктора копирования

#### ✅ Требование: Для классов, у которых реализован конструктор копирования по умолчанию, запретить его использование

```cpp
// PremiumClient.hpp
class PremiumClient : public Client
{
public:
    PremiumClient();
    PremiumClient(int clientId, ...);
    
    /**
     * Конструктор копирования УДАЛЕН для демонстрации.
     * Попытка копирования приведет к ошибке компиляции.
     */
    PremiumClient(const PremiumClient&) = delete;
    
    virtual ~PremiumClient();
};
```

```cpp
// BluRayCarrier.hpp
class BluRayCarrier : public VideoCarrier
{
public:
    BluRayCarrier();
    BluRayCarrier(int inventoryNumber, ...);
    
    /**
     * Конструктор копирования УДАЛЕН.
     */
    BluRayCarrier(const BluRayCarrier&) = delete;
    
    virtual ~BluRayCarrier();
};
```

**Демонстрация:**
```cpp
void demonstrateDeletedCopyConstructor()
{
    std::cout << "PremiumClient и BluRayCarrier имеют удаленный конструктор копирования:\n";
    std::cout << "PremiumClient(const PremiumClient&) = delete;\n";
    std::cout << "BluRayCarrier(const BluRayCarrier&) = delete;\n\n";
    
    std::cout << "Попытка копирования приведет к ошибке компиляции:\n";
    std::cout << "// PremiumClient client2 = client1; // ОШИБКА КОМПИЛЯЦИИ!\n";
    std::cout << "// BluRayCarrier bluray2 = bluray1; // ОШИБКА КОМПИЛЯЦИИ!\n";
}
```

**Что происходит при попытке копирования:**
```cpp
PremiumClient client1(1, "Alice", "Johnson", "+7-222", "alice@example.com", 15.0);

// ОШИБКА КОМПИЛЯЦИИ:
// error: use of deleted function 'PremiumClient::PremiumClient(const PremiumClient&)'
PremiumClient client2 = client1;
```

---

### 10. Виртуальный деструктор

#### ✅ Требование: У созданного базового класса сделать деструктор виртуальным, разобраться, что изменилось

#### 10.1. Объявление виртуальных деструкторов

**Client.hpp:**
```cpp
class Client
{
public:
    Client();
    Client(int clientId, ...);
    
    /**
     * Виртуальный деструктор для корректного удаления производных классов.
     */
    virtual ~Client();
    
    // ...
};
```

**VideoCarrier.hpp:**
```cpp
class VideoCarrier
{
public:
    VideoCarrier();
    VideoCarrier(int inventoryNumber, ...);
    
    /**
     * Виртуальный деструктор.
     */
    virtual ~VideoCarrier();
    
    // ...
};
```

**PaymentProcessor.hpp:**
```cpp
class PaymentProcessor
{
public:
    PaymentProcessor();
    
    /**
     * Виртуальный деструктор.
     */
    virtual ~PaymentProcessor();
    
    // ...
};
```

#### 10.2. Реализация деструкторов

**Client.cpp:**
```cpp
Client::~Client()
{
    std::cout << "Деструктор Client для " << m_firstName << "\n";
}
```

**PremiumClient.cpp:**
```cpp
PremiumClient::~PremiumClient()
{
    std::cout << "Деструктор PremiumClient для " << m_firstName << "\n";
}
```

#### 10.3. Что изменилось - демонстрация

**С виртуальным деструктором:**
```cpp
void demonstrateVirtualDestructor()
{
    std::cout << "--- С виртуальным деструктором ---\n";
    std::cout << "При удалении через указатель базового класса\n";
    std::cout << "вызываются деструкторы и производного, и базового класса:\n\n";
    
    Client* client = new PremiumClient(30, "Bob", "Brown", "+7-300", 
                                       "bob@example.com", 10.0);
    delete client;  // ← Удаление через указатель базового класса
    
    std::cout << "\nЕсли бы деструктор не был виртуальным,\n";
    std::cout << "вызывался бы только деструктор базового класса,\n";
    std::cout << "что могло бы привести к утечке памяти в производном классе.\n";
}
```

**Вывод:**
```
--- С виртуальным деструктором ---
При удалении через указатель базового класса
вызываются деструкторы и производного, и базового класса:

Создан премиум-клиент: Bob Brown со скидкой 10%
Деструктор PremiumClient для Bob    ← Вызван деструктор производного класса
Деструктор Client для Bob            ← Вызван деструктор базового класса
```

**БЕЗ виртуального деструктора (если бы `~Client()` не был virtual):**
```
Деструктор Client для Bob            ← Вызван ТОЛЬКО деструктор базового класса
                                       Деструктор PremiumClient НЕ вызван!
                                       УТЕЧКА ПАМЯТИ!
```

#### 10.4. Почему это важно

**Пример с утечкой памяти:**
```cpp
class DVDCarrier : public VideoCarrier
{
    std::vector<std::string>* m_subtitles;  // Динамическая память
    
public:
    DVDCarrier() {
        m_subtitles = new std::vector<std::string>();
    }
    
    ~DVDCarrier() {
        delete m_subtitles;  // Освобождение памяти
    }
};

// Без virtual в ~VideoCarrier():
VideoCarrier* carrier = new DVDCarrier(...);
delete carrier;
// ~DVDCarrier() НЕ вызывается!
// m_subtitles НЕ удаляется!
// УТЕЧКА ПАМЯТИ!

// С virtual в ~VideoCarrier():
VideoCarrier* carrier = new DVDCarrier(...);
delete carrier;
// ~DVDCarrier() вызывается!
// m_subtitles удаляется!
// Утечки нет!
```

---

## Специфичные требования для Java

### 11. Интерфейсы

#### ✅ Требование: Придумать разумное использование интерфейсов и продемонстрировать их использование

#### 11.1. Интерфейс Discountable

**Назначение:** Для объектов, которые поддерживают скидки

```java
// Discountable.java
package videoprokat;

/**
 * Интерфейс для объектов, которые поддерживают скидки.
 */
public interface Discountable {
    
    /**
     * Получить размер скидки в процентах.
     */
    double getDiscountPercentage();
    
    /**
     * Применить скидку к сумме.
     */
    double applyDiscount(double amount);
    
    /**
     * Проверить, доступна ли скидка.
     */
    boolean isDiscountAvailable();
}
```

#### 11.2. Интерфейс Notifiable

**Назначение:** Для объектов, которым можно отправлять уведомления

```java
// Notifiable.java
package videoprokat;

/**
 * Интерфейс для объектов, которым можно отправлять уведомления.
 */
public interface Notifiable {
    
    /**
     * Отправить уведомление.
     */
    void sendNotification(String message);
    
    /**
     * Получить предпочитаемый метод уведомления.
     */
    String getPreferredNotificationMethod();
}
```

#### 11.3. Реализация интерфейсов

**PremiumClient реализует оба интерфейса:**
```java
// PremiumClient.java
public class PremiumClient extends Client implements Discountable, Notifiable {
    
    private double discountPercentage;
    private String email;
    private String preferredNotificationMethod;
    
    // Методы от Discountable
    @Override
    public double getDiscountPercentage() {
        return discountPercentage;
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - discountPercentage / 100.0);
    }
    
    @Override
    public boolean isDiscountAvailable() {
        return !blacklisted && discountPercentage > 0;
    }
    
    // Методы от Notifiable
    @Override
    public void sendNotification(String message) {
        System.out.println("[EMAIL to " + email + "] " + message);
    }
    
    @Override
    public String getPreferredNotificationMethod() {
        return preferredNotificationMethod;
    }
}
```

**CorporateClient реализует один интерфейс:**
```java
// CorporateClient.java
public class CorporateClient extends Client implements Discountable {
    
    private double corporateDiscount;
    
    @Override
    public double getDiscountPercentage() {
        return corporateDiscount;
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - corporateDiscount / 100.0);
    }
    
    @Override
    public boolean isDiscountAvailable() {
        return !blacklisted && corporateDiscount > 0;
    }
}
```

#### 11.4. Демонстрация использования интерфейсов

```java
// InheritanceDemo.java
public static void demonstratePolymorphism(Client client, double amount) {
    System.out.println("Клиент: " + client.getFirstName() + " " + client.getLastName());
    
    client.addToDeposit(amount);
    
    // Проверка и использование интерфейса Discountable
    if (client instanceof Discountable) {
        Discountable discountableClient = (Discountable) client;
        System.out.println("Скидка доступна: " 
                         + discountableClient.getDiscountPercentage() + "%");
        System.out.println("Сумма со скидкой: " 
                         + discountableClient.applyDiscount(100.0));
    }
    
    // Проверка и использование интерфейса Notifiable
    if (client instanceof Notifiable) {
        Notifiable notifiableClient = (Notifiable) client;
        notifiableClient.sendNotification("Ваш депозит пополнен на " + amount);
    }
}

// Использование:
Client premiumClient = new PremiumClient(2, "Jane", "Smith", "+7-200",
                                        "jane@example.com", 15.0);
demonstratePolymorphism(premiumClient, 1000.0);
```

**Вывод:**
```
Клиент: Jane Smith
Начислено 50 бонусных баллов
Баланс депозита: 1000.0
Скидка доступна: 15.0%
Сумма со скидкой: 85.0
[EMAIL to jane@example.com] Ваш депозит пополнен на 1000.0
```

---

### 12. Множественное наследование

#### ✅ Требование: Для производного класса реализовать множественное наследование (от абстрактного класса и интерфейса(-ов))

#### 12.1. PremiumClient - множественное наследование

**Схема наследования:**
```
        Client (абстрактный класс)
           ↑
           |
    PremiumClient
           ↑
           |
    ┌──────┴──────┐
    |             |
Discountable  Notifiable
(интерфейс)   (интерфейс)
```

**Код:**
```java
// PremiumClient.java
/**
 * Множественное наследование:
 * - От абстрактного класса Client
 * - От интерфейса Discountable
 * - От интерфейса Notifiable
 */
public class PremiumClient extends Client implements Discountable, Notifiable {
    
    // Поля производного класса
    private double discountPercentage;
    private int loyaltyPoints;
    private String email;
    private String preferredNotificationMethod;
    
    // Конструктор
    public PremiumClient(int clientId, String firstName, String lastName, 
                        String phoneNumber, String email, double discountPercentage) {
        super(clientId, firstName, lastName, phoneNumber);  // От Client
        this.discountPercentage = discountPercentage;
        this.loyaltyPoints = 0;
        this.email = email;
        this.preferredNotificationMethod = "email";
    }
    
    // ===== Методы от Client (абстрактный класс) =====
    @Override
    public int getClientId() {
        return clientId;
    }
    
    @Override
    public String getFirstName() {
        return firstName;
    }
    
    // ... другие методы от Client
    
    // ===== Методы от Discountable (интерфейс) =====
    @Override
    public double getDiscountPercentage() {
        return discountPercentage;
    }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - discountPercentage / 100.0);
    }
    
    @Override
    public boolean isDiscountAvailable() {
        return !blacklisted && discountPercentage > 0;
    }
    
    // ===== Методы от Notifiable (интерфейс) =====
    @Override
    public void sendNotification(String message) {
        System.out.println("[" + preferredNotificationMethod.toUpperCase() 
                         + " to " + email + "] " + message);
    }
    
    @Override
    public String getPreferredNotificationMethod() {
        return preferredNotificationMethod;
    }
}
```

#### 12.2. CorporateClient - множественное наследование

**Схема наследования:**
```
        Client (абстрактный класс)
           ↑
           |
    CorporateClient
           ↑
           |
      Discountable
      (интерфейс)
```

**Код:**
```java
// CorporateClient.java
/**
 * Множественное наследование:
 * - От абстрактного класса Client
 * - От интерфейса Discountable
 */
public class CorporateClient extends Client implements Discountable {
    
    private String companyName;
    private double corporateDiscount;
    private int employeeCount;
    
    public CorporateClient(int clientId, String firstName, String lastName,
                          String phoneNumber, String companyName, int employeeCount) {
        super(clientId, firstName, lastName, phoneNumber);  // От Client
        this.companyName = companyName;
        this.employeeCount = employeeCount;
        this.corporateDiscount = calculateCorporateDiscount();
    }
    
    // ===== Методы от Client =====
    @Override
    public int getClientId() { return clientId; }
    // ... другие методы
    
    // ===== Методы от Discountable =====
    @Override
    public double getDiscountPercentage() { return corporateDiscount; }
    
    @Override
    public double applyDiscount(double amount) {
        return amount * (1.0 - corporateDiscount / 100.0);
    }
    
    @Override
    public boolean isDiscountAvailable() {
        return !blacklisted && corporateDiscount > 0;
    }
}
```

#### 12.3. Демонстрация множественного наследования

```java
// InheritanceDemo.java
public static void demonstrateMultipleInheritance() {
    System.out.println("=== МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===");
    System.out.println("PremiumClient extends Client implements Discountable, Notifiable");
    
    PremiumClient client = new PremiumClient(300, "Diana", "Prince", "+7-555",
                                            "diana@example.com", 25.0);
    
    System.out.println("\nОт абстрактного класса Client:");
    System.out.println("- getFirstName(): " + client.getFirstName());
    System.out.println("- getDepositBalance(): " + client.getDepositBalance());
    
    System.out.println("\nОт интерфейса Discountable:");
    System.out.println("- getDiscountPercentage(): " + client.getDiscountPercentage() + "%");
    System.out.println("- applyDiscount(1000): " + client.applyDiscount(1000.0));
    
    System.out.println("\nОт интерфейса Notifiable:");
    System.out.println("- getPreferredNotificationMethod(): " 
                     + client.getPreferredNotificationMethod());
    client.sendNotification("Добро пожаловать в премиум-клуб!");
}
```

**Вывод:**
```
=== МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===
PremiumClient extends Client implements Discountable, Notifiable

От абстрактного класса Client:
- getFirstName(): Diana
- getDepositBalance(): 0.0

От интерфейса Discountable:
- getDiscountPercentage(): 25.0%
- applyDiscount(1000): 750.0

От интерфейса Notifiable:
- getPreferredNotificationMethod(): email
[EMAIL to diana@example.com] Добро пожаловать в премиум-клуб!
```

---

## Как запустить демонстрацию

### Java

```bash
# Компиляция
cd /home/engine/project
javac -d . *.java

# Запуск демонстрации наследования
java videoprokat.InheritanceDemo

# Запуск основной программы
java videoprokat.VideoprokatDemo
```

### C++

```bash
# Компиляция
cd /home/engine/project/videoprokat
make clean
make

# Запуск демонстрации наследования
cd /home/engine/project
./demos/InheritanceDemo

# Запуск основной программы
cd /home/engine/project/videoprokat
./videoprokat
```

### Автоматическое тестирование

```bash
cd /home/engine/project
./test_all.sh
```

---

## Сводная таблица реализации

| № | Требование | Java | C++ | Статус |
|---|-----------|------|-----|--------|
| 1 | Производные классы | PremiumClient, CorporateClient, DVDCarrier, BluRayCarrier | PremiumClient, DVDCarrier, BluRayCarrier, CashPaymentProcessor, CardPaymentProcessor | ✅ |
| 2 | Модификатор protected | Client, VideoCarrier | Client, VideoCarrier | ✅ |
| 3 | Перегрузка с вызовом super | addToDeposit() | addToDeposit() | ✅ |
| 4 | Перегрузка без вызова super | blockDepositFunds() | blockDepositFunds() | ✅ |
| 5 | Виртуальные функции | Все методы виртуальные | virtual addToDeposit(), blockDepositFunds(), markAsRented() | ✅ |
| 6 | Вызов виртуальной через не виртуальную | - | processTransaction(), executePayment() | ✅ |
| 7 | Клонирование | DVDCarrier | DVDCarrier | ✅ |
| 8 | Вызов конструктора базового | super() | Список инициализации | ✅ |
| 9 | Абстрактные классы | Client, VideoCarrier | PaymentProcessor | ✅ |
| 10 | Оператор присваивания | - | operator=(const Client&) | ✅ |
| 11 | Запрет копирования | - | = delete | ✅ |
| 12 | Виртуальный деструктор | - | virtual ~Client(), ~VideoCarrier() | ✅ |
| 13 | Интерфейсы | Discountable, Notifiable | - | ✅ |
| 14 | Множественное наследование | PremiumClient, CorporateClient | - | ✅ |

---

## Заключение

Все требования задания L5 успешно реализованы и задокументированы. Проект демонстрирует глубокое понимание концепций ООП в обоих языках программирования.
