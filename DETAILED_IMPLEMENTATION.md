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

## Дополнительные Требования: STL и Collections Framework

### 15. Контейнеры с объектами базового и производного классов

#### ✅ Требование: Придумать разумное использование контейнеров, алгоритма сортировки и алгоритма поиска. В контейнере должны храниться объекты как базового, так и производного классов

#### Шаблонный класс Repository<T>

**C++:**
```cpp
// Repository.hpp
template<typename T>
class Repository
{
public:
    // Не шаблонные методы
    void add(T* item);
    size_t size() const;
    const std::vector<T*>& getAll() const;
    
    // Шаблонные методы
    template<typename Predicate>
    T* findIf(Predicate pred) const;
    
    template<typename Comparator>
    void sort(Comparator comp);
    
    template<typename Predicate>
    size_t removeIf(Predicate pred);

private:
    std::vector<T*> m_items;
};
```

**Java:**
```java
// Repository.java
public class Repository<T> {
    private List<T> items;
    
    // Не generic методы
    public void add(T item) { ... }
    public int size() { ... }
    public List<T> getAll() { ... }
    
    // Generic методы
    public <R extends T> R findIf(Predicate<T> predicate) { ... }
    public <R extends T> void sort(Comparator<T> comparator) { ... }
    public <R extends T> int removeIf(Predicate<T> predicate) { ... }
}
```

#### Демонстрация с полиморфными объектами

**C++:**
```cpp
void demonstrateRepositoryWithPolymorphism()
{
    // Создание репозитория для базового класса VideoCarrier
    Repository<VideoCarrier> repo;
    
    // Добавление объектов РАЗНЫХ ТИПОВ (базовый и производные)
    repo.add(new VideoCarrier(100, "Classic", "VHS", "Drama", 30.0, 300.0));     // Базовый
    repo.add(new DVDCarrier(101, "Modern", "Action", 45.0, 450.0, 1, "2"));       // Производный
    repo.add(new BluRayCarrier(102, "New", "Sci-Fi", 60.0, 600.0, true, true));   // Производный
    repo.add(new DVDCarrier(103, "Oldies", "Comedy", 40.0, 400.0, 2, "1"));       // Производный
    
    std::cout << "Добавлено носителей: " << repo.size() << "\n";
    
    // ПОИСК элемента (std::find_if)
    auto found = repo.findIf([](VideoCarrier* vc) { 
        return vc->getInventoryNumber() == 102; 
    });
    if (found) {
        std::cout << "Найден: " << found->getTitle() << "\n";
    }
    
    // ПОИСК всех дорогих носителей (std::copy_if)
    auto expensive = repo.findAll([](VideoCarrier* vc) {
        return vc->getRentalPricePerDay() >= 50.0;
    });
    std::cout << "Найдено дорогих: " << expensive.size() << "\n";
    
    // СОРТИРОВКА по цене (std::sort)
    repo.sort([](VideoCarrier* a, VideoCarrier* b) {
        return a->getRentalPricePerDay() < b->getRentalPricePerDay();
    });
    
    std::cout << "После сортировки по цене:\n";
    repo.forEach([](VideoCarrier* vc) {
        std::cout << "- " << vc->getTitle() << ": " 
                  << vc->getRentalPricePerDay() << " руб/день\n";
    });
    
    // УДАЛЕНИЕ дешевых (std::remove_if)
    size_t removed = repo.removeIf([](VideoCarrier* vc) {
        return vc->getRentalPricePerDay() < 40.0;
    });
    std::cout << "Удалено: " << removed << ", Осталось: " << repo.size() << "\n";
}
```

**Java:**
```java
public static void demonstrateRepositoryWithPolymorphism() {
    // Создание репозитория для базового класса VideoCarrier
    Repository<VideoCarrier> repo = new Repository<>();
    
    // Добавление объектов РАЗНЫХ ТИПОВ (базовый и производные)
    repo.add(new VideoCarrierReal(100, "Classic", "VHS", "Drama", 30.0, 300.0));  // Базовый
    repo.add(new DVDCarrier(101, "Modern", "Action", 45.0, 450.0, 1, "2"));        // Производный
    repo.add(new BluRayCarrier(102, "New", "Sci-Fi", 60.0, 600.0, true, true));    // Производный
    repo.add(new DVDCarrier(103, "Oldies", "Comedy", 40.0, 400.0, 2, "1"));        // Производный
    
    System.out.println("Добавлено носителей: " + repo.size());
    
    // ПОИСК элемента (Stream.filter().findFirst())
    VideoCarrier found = repo.findIf(vc -> vc.getInventoryNumber() == 102);
    if (found != null) {
        System.out.println("Найден: " + found.getTitle());
    }
    
    // ПОИСК всех дорогих носителей (Stream.filter().collect())
    List<VideoCarrier> expensive = repo.findAll(vc -> vc.getRentalPricePerDay() >= 50.0);
    System.out.println("Найдено дорогих: " + expensive.size());
    
    // СОРТИРОВКА по цене (Collections.sort())
    repo.sort((a, b) -> Double.compare(a.getRentalPricePerDay(), 
                                      b.getRentalPricePerDay()));
    
    System.out.println("После сортировки по цене:");
    repo.forEach(vc -> 
        System.out.println("- " + vc.getTitle() + ": " + 
                         vc.getRentalPricePerDay() + " руб/день"));
    
    // УДАЛЕНИЕ дешевых (List.removeIf())
    int removed = repo.removeIf(vc -> vc.getRentalPricePerDay() < 40.0);
    System.out.println("Удалено: " + removed + ", Осталось: " + repo.size());
}
```

**Вывод:**
```
Добавлено носителей: 4

Найден: New (BluRay)

Найдено дорогих: 1

После сортировки по цене:
- Classic: 30.0 руб/день
- Oldies: 40.0 руб/день
- Modern: 45.0 руб/день
- New: 60.0 руб/день

Удалено: 1, Осталось: 3
```

---

### 16. Шаблонные функции с ограничениями

#### ✅ Требование: Реализовать шаблонную функцию. Функция не должна быть в классе, она должна что-то вычислять. Предусмотреть ограничение на допустимые типы на уровне компиляции

#### Функция вычисления среднего значения

**C++:**
```cpp
// TemplateUtils.hpp

/**
 * Шаблонная функция для вычисления среднего значения.
 * Ограничение: работает только с арифметическими типами.
 */
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, double>::type
calculateAverage(const std::vector<T>& values)
{
    if (values.empty()) return 0.0;
    
    T sum = std::accumulate(values.begin(), values.end(), T(0));
    return static_cast<double>(sum) / values.size();
}
```

**Использование:**
```cpp
// ✅ РАБОТАЕТ - double является арифметическим типом
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
double avg = calculateAverage(prices);  // ✅ Компилируется
std::cout << "Средняя цена: " << avg << "\n";

// ✅ РАБОТАЕТ - int является арифметическим типом
std::vector<int> ratings = {5, 4, 5, 3, 4, 5};
double avgRating = calculateAverage(ratings);  // ✅ Компилируется
std::cout << "Средний рейтинг: " << avgRating << "\n";

// ❌ НЕ РАБОТАЕТ - string не является арифметическим типом
std::vector<std::string> names = {"A", "B", "C"};
// double avgName = calculateAverage(names);  // ❌ ОШИБКА КОМПИЛЯЦИИ!
```

**Java:**
```java
// GenericUtils.java

/**
 * Generic функция для вычисления среднего значения.
 * Ограничение: работает только с числовыми типами (extends Number).
 */
public static <T extends Number> double calculateAverage(List<T> values) {
    if (values == null || values.isEmpty()) {
        return 0.0;
    }
    
    double sum = values.stream()
                      .mapToDouble(Number::doubleValue)
                      .sum();
    return sum / values.size();
}
```

**Использование:**
```java
// ✅ РАБОТАЕТ - Double extends Number
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
double avg = GenericUtils.calculateAverage(prices);  // ✅ Компилируется
System.out.println("Средняя цена: " + avg);

// ✅ РАБОТАЕТ - Integer extends Number
List<Integer> ratings = Arrays.asList(5, 4, 5, 3, 4, 5);
double avgRating = GenericUtils.calculateAverage(ratings);  // ✅ Компилируется
System.out.println("Средний рейтинг: " + avgRating);

// ❌ НЕ РАБОТАЕТ - String не extends Number
List<String> names = Arrays.asList("A", "B", "C");
// double avgName = GenericUtils.calculateAverage(names);  // ❌ ОШИБКА КОМПИЛЯЦИИ!
```

**Вывод:**
```
Средняя цена аренды: 56.0
Средний рейтинг: 4.333333
```

#### Функция поиска минимума и максимума

**C++:**
```cpp
/**
 * Шаблонная функция для поиска минимума и максимума.
 * Ограничение: тип должен поддерживать копирование.
 */
template<typename T>
std::pair<T, T> findMinMax(const std::vector<T>& values)
{
    static_assert(std::is_copy_constructible<T>::value, 
                  "Type must be copy constructible");
    
    if (values.empty()) {
        throw std::runtime_error("Empty container");
    }
    
    auto minIt = std::min_element(values.begin(), values.end());
    auto maxIt = std::max_element(values.begin(), values.end());
    
    return std::make_pair(*minIt, *maxIt);
}
```

**Java:**
```java
/**
 * Generic функция для поиска минимума и максимума.
 * Ограничение: тип должен реализовывать Comparable.
 */
public static <T extends Comparable<T>> Pair<T, T> findMinMax(List<T> values) {
    if (values == null || values.isEmpty()) {
        throw new IllegalArgumentException("Empty list");
    }
    
    T min = Collections.min(values);
    T max = Collections.max(values);
    
    return new Pair<>(min, max);
}
```

**Вывод:**
```
Мин. цена: 45.0, Макс. цена: 70.0
```

#### Другие шаблонные функции

**C++:**
```cpp
/**
 * Фильтрация элементов.
 */
template<typename T, typename Predicate>
std::vector<T> filterElements(const std::vector<T>& source, Predicate pred)
{
    std::vector<T> result;
    std::copy_if(source.begin(), source.end(), 
                 std::back_inserter(result), pred);
    return result;
}

/**
 * Преобразование элементов.
 */
template<typename TIn, typename TOut, typename Transform>
std::vector<TOut> transformElements(const std::vector<TIn>& source, Transform func)
{
    std::vector<TOut> result;
    result.reserve(source.size());
    std::transform(source.begin(), source.end(), 
                   std::back_inserter(result), func);
    return result;
}

/**
 * Проверка наличия элементов, удовлетворяющих условию.
 */
template<typename T, typename Predicate>
bool anyOf(const std::vector<T>& source, Predicate pred)
{
    return std::any_of(source.begin(), source.end(), pred);
}
```

**Java:**
```java
public static <T> List<T> filterElements(List<T> source, Predicate<T> predicate) {
    return source.stream().filter(predicate).collect(Collectors.toList());
}

public static <T, R> List<R> transformElements(List<T> source, Function<T, R> mapper) {
    return source.stream().map(mapper).collect(Collectors.toList());
}

public static <T> boolean anyOf(List<T> source, Predicate<T> predicate) {
    return source.stream().anyMatch(predicate);
}
```

---

### 17. Демонстрация всех контейнеров и алгоритмов

#### Контейнеры

**C++ (STL):**
```cpp
// 1. std::array - фиксированный массив
std::array<double, 5> prices = {50.0, 60.0, 45.0, 70.0, 55.0};

// 2. std::vector - динамический массив
std::vector<int> inventoryNumbers = {100, 101, 102, 103, 104};
inventoryNumbers.push_back(105);

// 3. std::list - двусвязный список
std::list<std::string> genres = {"Sci-Fi", "Action", "Drama", "Comedy"};
genres.push_front("Horror");

// 4. std::map - ассоциативный контейнер
std::map<int, std::string> clientNames;
clientNames[1] = "Иван Иванов";

// 5. std::span (C++20) - представление
std::span<int> view(inventoryNumbers);
```

**Java (Collections Framework):**
```java
// 1. Массив - фиксированный
Double[] prices = {50.0, 60.0, 45.0, 70.0, 55.0};

// 2. ArrayList - динамический список
ArrayList<Integer> inventoryNumbers = new ArrayList<>(Arrays.asList(100, 101, 102));
inventoryNumbers.add(103);

// 3. LinkedList - двусвязный список
LinkedList<String> genres = new LinkedList<>(Arrays.asList("Sci-Fi", "Action"));
genres.addFirst("Horror");

// 4. HashMap - хеш-таблица
HashMap<Integer, String> clientNames = new HashMap<>();
clientNames.put(1, "Иван Иванов");

// 5. List.subList() - представление (аналог span)
List<Integer> view = inventoryNumbers.subList(0, 3);
```

#### Алгоритмы

| Операция | C++ | Java |
|----------|-----|------|
| **std::min_element, std::max_element** | `std::min_element(v.begin(), v.end())` | `Collections.min(list)` |
| **std::find, std::find_if** | `std::find_if(v.begin(), v.end(), pred)` | `stream().filter(pred).findFirst()` |
| **std::copy(), std::copy_if()** | `std::copy_if(src.begin(), src.end(), dst, pred)` | `stream().filter(pred).collect()` |
| **std::remove(), std::remove_if()** | `std::remove_if + erase` | `list.removeIf(pred)` |
| **std::sort()** | `std::sort(v.begin(), v.end())` | `Collections.sort(list)` |
| **std::filter_view()** | `v | std::views::filter(pred)` | `stream().filter(pred)` |
| **std::transform, std::transform_view()** | `std::transform(src, dst, func)` | `stream().map(func)` |
| **std::any_of** | `std::any_of(v.begin(), v.end(), pred)` | `stream().anyMatch(pred)` |
| **std::variant** | `std::variant<int, double, string>` | `Object` или sealed classes |

---

### 18. Дополнительные алгоритмы и операции

#### C++ Ranges (C++20)

```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Фильтрация (ленивое вычисление)
auto evenNumbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });

// Преобразование
auto doubled = numbers | std::views::transform([](int n) { return n * 2; });

// Комбинирование
auto result = numbers 
            | std::views::filter([](int n) { return n > 5; })
            | std::views::transform([](int n) { return n * n; });
```

#### Java Streams

```java
List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

// Фильтрация (ленивое вычисление)
Stream<Integer> evenNumbers = numbers.stream().filter(n -> n % 2 == 0);

// Преобразование
Stream<Integer> doubled = numbers.stream().map(n -> n * 2);

// Комбинирование
List<Integer> result = numbers.stream()
                             .filter(n -> n > 5)
                             .map(n -> n * n)
                             .collect(Collectors.toList());

// Reduce (свертка)
int sum = numbers.stream().reduce(0, Integer::sum);

// FlatMap (разворачивание)
List<List<Integer>> nested = Arrays.asList(
    Arrays.asList(1, 2, 3),
    Arrays.asList(4, 5, 6)
);
List<Integer> flattened = nested.stream()
                                .flatMap(List::stream)
                                .collect(Collectors.toList());
```

---

### 19. std::variant - Вариантный тип

**C++:**
```cpp
// std::variant может хранить один из нескольких типов
using ClientData = std::variant<int, double, std::string>;

ClientData data;

data = 123;  // Хранит int
std::cout << "ID: " << std::get<int>(data) << "\n";

data = 99.99;  // Хранит double
std::cout << "Баланс: " << std::get<double>(data) << "\n";

data = std::string("Иван Иванов");  // Хранит string
std::cout << "Имя: " << std::get<std::string>(data) << "\n";

// Проверка текущего типа
if (std::holds_alternative<std::string>(data)) {
    std::cout << "Текущий тип: string\n";
}

// Visitor pattern
std::visit([](auto&& value) {
    std::cout << "Значение: " << value << "\n";
}, data);
```

**Вывод:**
```
ID клиента (int): 123
Баланс (double): 99.99
Имя (string): Иван Иванов
Текущий тип: string
Значение: Иван Иванов
```

---

### 20. Файлы реализации

#### C++

- **Repository.hpp** - Шаблонный класс репозитория
- **TemplateUtils.hpp** - Шаблонные функции
- **STLDemo.cpp** - Демонстрационная программа (380+ строк)

#### Java

- **Repository.java** - Generic класс репозитория
- **GenericUtils.java** - Generic функции
- **CollectionsDemo.java** - Демонстрационная программа (350+ строк)

---

### 21. Запуск демонстрации

#### C++
```bash
cd /home/engine/project/videoprokat
make STLDemo
./STLDemo
```

#### Java
```bash
cd /home/engine/project
javac -d . *.java
java videoprokat.CollectionsDemo
```

---

## Сводная Таблица Реализации (Обновленная)

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
| **15** | **Контейнеры с полиморфизмом** | **Repository<VideoCarrier>** | **Repository<VideoCarrier>** | **✅** |
| **16** | **Шаблонные функции** | **GenericUtils** | **TemplateUtils.hpp** | **✅** |
| **17** | **Шаблонный класс** | **Repository<T>** | **Repository<T>** | **✅** |
| **18** | **Контейнеры (array, vector, list, map, span)** | **✅** | **✅** | **✅** |
| **19** | **Алгоритмы (sort, find, copy_if, etc.)** | **✅** | **✅** | **✅** |
| **20** | **Ограничения на типы** | **<T extends Number>** | **enable_if, static_assert** | **✅** |

---

## Детальная Реализация STL Контейнеров и Методов

### Контейнеры STL (C++) и их аналоги в Java

#### 1. std::array ↔ Массив (Java)

**Описание:** Фиксированный массив с размером, определенным на этапе компиляции.

**C++ (std::array):**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <array>

void demonstrateSTLContainers()
{
    // std::array - массив фиксированного размера
    std::array<double, 5> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
    
    std::cout << "std::array - фиксированный массив:\n";
    std::cout << "   Цены аренды: ";
    for (const auto& price : prices) {
        std::cout << price << " ";
    }
    std::cout << "\n";
    std::cout << "   Размер: " << prices.size() << "\n";
    std::cout << "   Элемент [0]: " << prices[0] << "\n";
    std::cout << "   Элемент at(2): " << prices.at(2) << "\n";
}
```

**Java (Array):**
```java
// Файл: CollectionsDemo.java
public static void demonstrateCollections() {
    // Фиксированный массив
    Double[] prices = {50.0, 60.0, 45.0, 70.0, 55.0};
    
    System.out.println("Фиксированный массив:");
    System.out.println("   Цены: " + Arrays.toString(prices));
    System.out.println("   Размер: " + prices.length);
    System.out.println("   Элемент [0]: " + prices[0]);
    System.out.println("   Элемент [2]: " + prices[2]);
}
```

**Вывод:**
```
std::array - фиксированный массив:
   Цены аренды: 50 60 45 70 55
   Размер: 5
   Элемент [0]: 50
   Элемент at(2): 45
```

**Особенности:**
- **C++:** `std::array` знает свой размер, безопасный доступ через `.at()`, итераторы
- **Java:** Обычный массив, доступ через `[]`, размер через `.length`

---

#### 2. std::vector ↔ ArrayList (Java)

**Описание:** Динамический массив с автоматическим изменением размера.

**C++ (std::vector):**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <vector>

void demonstrateSTLContainers()
{
    // std::vector - динамический массив
    std::vector<int> inventoryNumbers = {100, 101, 102, 103, 104};
    
    // Добавление элементов
    inventoryNumbers.push_back(105);
    inventoryNumbers.push_back(106);
    
    std::cout << "std::vector - динамический массив:\n";
    std::cout << "   Инвентарные номера: ";
    for (const auto& num : inventoryNumbers) {
        std::cout << num << " ";
    }
    std::cout << "\n";
    std::cout << "   Размер: " << inventoryNumbers.size() << "\n";
    std::cout << "   Вместимость: " << inventoryNumbers.capacity() << "\n";
    
    // Удаление последнего элемента
    inventoryNumbers.pop_back();
    
    // Доступ к элементам
    std::cout << "   Первый элемент: " << inventoryNumbers.front() << "\n";
    std::cout << "   Последний элемент: " << inventoryNumbers.back() << "\n";
}
```

**Java (ArrayList):**
```java
// Файл: CollectionsDemo.java
import java.util.ArrayList;

public static void demonstrateCollections() {
    // ArrayList - динамический список
    ArrayList<Integer> inventoryNumbers = new ArrayList<>(
        Arrays.asList(100, 101, 102, 103, 104)
    );
    
    // Добавление элементов
    inventoryNumbers.add(105);
    inventoryNumbers.add(106);
    
    System.out.println("ArrayList - динамический список:");
    System.out.println("   Инвентарные номера: " + inventoryNumbers);
    System.out.println("   Размер: " + inventoryNumbers.size());
    
    // Удаление последнего элемента
    inventoryNumbers.remove(inventoryNumbers.size() - 1);
    
    // Доступ к элементам
    System.out.println("   Первый элемент: " + inventoryNumbers.get(0));
    System.out.println("   Последний элемент: " + inventoryNumbers.get(inventoryNumbers.size() - 1));
}
```

**Вывод:**
```
std::vector - динамический массив:
   Инвентарные номера: 100 101 102 103 104 105 106
   Размер: 7
   Вместимость: 10
   Первый элемент: 100
   Последний элемент: 105
```

**Использование в Repository:**
```cpp
// Файл: videoprokat/Repository.hpp
template<typename T>
class Repository
{
private:
    std::vector<T*> m_items;  // ← Используем std::vector
};
```

---

#### 3. std::list ↔ LinkedList (Java)

**Описание:** Двусвязный список с эффективной вставкой/удалением в любом месте.

**C++ (std::list):**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <list>

void demonstrateSTLContainers()
{
    // std::list - двусвязный список
    std::list<std::string> genres = {"Sci-Fi", "Action", "Drama", "Comedy"};
    
    // Добавление в начало и конец
    genres.push_front("Horror");
    genres.push_back("Fantasy");
    
    std::cout << "std::list - двусвязный список:\n";
    std::cout << "   Жанры: ";
    for (const auto& genre : genres) {
        std::cout << genre << " ";
    }
    std::cout << "\n";
    std::cout << "   Размер: " << genres.size() << "\n";
    
    // Вставка в середину
    auto it = genres.begin();
    std::advance(it, 2);  // Переходим к 3-му элементу
    genres.insert(it, "Thriller");
    
    std::cout << "   После вставки 'Thriller': ";
    for (const auto& genre : genres) {
        std::cout << genre << " ";
    }
    std::cout << "\n";
}
```

**Java (LinkedList):**
```java
// Файл: CollectionsDemo.java
import java.util.LinkedList;

public static void demonstrateCollections() {
    // LinkedList - двусвязный список
    LinkedList<String> genres = new LinkedList<>(
        Arrays.asList("Sci-Fi", "Action", "Drama", "Comedy")
    );
    
    // Добавление в начало и конец
    genres.addFirst("Horror");
    genres.addLast("Fantasy");
    
    System.out.println("LinkedList - двусвязный список:");
    System.out.println("   Жанры: " + genres);
    System.out.println("   Размер: " + genres.size());
    
    // Вставка в середину
    genres.add(2, "Thriller");
    
    System.out.println("   После вставки 'Thriller': " + genres);
}
```

**Вывод:**
```
std::list - двусвязный список:
   Жанры: Horror Sci-Fi Action Drama Comedy Fantasy
   Размер: 6
   После вставки 'Thriller': Horror Sci-Fi Thriller Action Drama Comedy Fantasy
```

---

#### 4. std::map ↔ HashMap (Java)

**Описание:** Ассоциативный контейнер (словарь) для хранения пар ключ-значение.

**C++ (std::map):**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <map>

void demonstrateSTLContainers()
{
    // std::map - упорядоченный ассоциативный контейнер
    std::map<int, std::string> clientNames;
    
    // Добавление элементов
    clientNames[1] = "Иван Иванов";
    clientNames[2] = "Петр Петров";
    clientNames[3] = "Сидор Сидоров";
    clientNames.insert({4, "Василий Васильев"});
    
    std::cout << "std::map - словарь:\n";
    std::cout << "   Клиенты:\n";
    for (const auto& [id, name] : clientNames) {
        std::cout << "   ID " << id << ": " << name << "\n";
    }
    
    // Поиск элемента
    if (clientNames.find(2) != clientNames.end()) {
        std::cout << "   Найден клиент ID 2: " << clientNames[2] << "\n";
    }
    
    // Размер
    std::cout << "   Количество клиентов: " << clientNames.size() << "\n";
    
    // Удаление элемента
    clientNames.erase(3);
    std::cout << "   После удаления ID 3: " << clientNames.size() << " клиентов\n";
}
```

**Java (HashMap):**
```java
// Файл: CollectionsDemo.java
import java.util.HashMap;

public static void demonstrateCollections() {
    // HashMap - хеш-таблица (неупорядоченная)
    HashMap<Integer, String> clientNames = new HashMap<>();
    
    // Добавление элементов
    clientNames.put(1, "Иван Иванов");
    clientNames.put(2, "Петр Петров");
    clientNames.put(3, "Сидор Сидоров");
    clientNames.put(4, "Василий Васильев");
    
    System.out.println("HashMap - словарь:");
    System.out.println("   Клиенты:");
    clientNames.forEach((id, name) -> 
        System.out.println("   ID " + id + ": " + name)
    );
    
    // Поиск элемента
    if (clientNames.containsKey(2)) {
        System.out.println("   Найден клиент ID 2: " + clientNames.get(2));
    }
    
    // Размер
    System.out.println("   Количество клиентов: " + clientNames.size());
    
    // Удаление элемента
    clientNames.remove(3);
    System.out.println("   После удаления ID 3: " + clientNames.size() + " клиентов");
}
```

**Вывод:**
```
std::map - словарь:
   Клиенты:
   ID 1: Иван Иванов
   ID 2: Петр Петров
   ID 3: Сидор Сидоров
   ID 4: Василий Васильев
   Найден клиент ID 2: Петр Петров
   Количество клиентов: 4
   После удаления ID 3: 3 клиентов
```

---

#### 5. std::span (C++20) ↔ List.subList() (Java)

**Описание:** Легковесное представление непрерывной последовательности элементов.

**C++ (std::span):**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <span>  // C++20

void demonstrateSTLContainers()
{
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // std::span - легковесное представление (не копирует данные)
    std::span<int> view(data);
    std::span<int> first5(data.data(), 5);  // Первые 5 элементов
    
    std::cout << "std::span - представление:\n";
    std::cout << "   Полное представление: ";
    for (int n : view) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    std::cout << "   Первые 5 элементов: ";
    for (int n : first5) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // Изменение через span меняет оригинальные данные
    first5[0] = 100;
    std::cout << "   После изменения первого элемента через span: ";
    std::cout << data[0] << "\n";  // Выведет 100
}
```

**Java (List.subList()):**
```java
// Файл: CollectionsDemo.java
public static void demonstrateCollections() {
    List<Integer> data = new ArrayList<>(
        Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
    );
    
    // subList - представление части списка (не копирует данные)
    List<Integer> view = data.subList(0, data.size());
    List<Integer> first5 = data.subList(0, 5);  // Первые 5 элементов
    
    System.out.println("List.subList() - представление:");
    System.out.println("   Полное представление: " + view);
    System.out.println("   Первые 5 элементов: " + first5);
    
    // Изменение через subList меняет оригинальные данные
    first5.set(0, 100);
    System.out.println("   После изменения первого элемента: " + data.get(0));  // Выведет 100
}
```

**Вывод:**
```
std::span - представление:
   Полное представление: 1 2 3 4 5 6 7 8 9 10
   Первые 5 элементов: 1 2 3 4 5
   После изменения первого элемента через span: 100
```

---

### Методы STL (C++) и их аналоги в Java

#### 1. std::min_element, std::max_element ↔ Collections.min, Collections.max

**Описание:** Поиск минимального и максимального элемента в контейнере.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <algorithm>

void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0, 40.0};
    
    // std::min_element - возвращает итератор на минимальный элемент
    auto minIt = std::min_element(prices.begin(), prices.end());
    
    // std::max_element - возвращает итератор на максимальный элемент
    auto maxIt = std::max_element(prices.begin(), prices.end());
    
    std::cout << "Поиск минимума и максимума:\n";
    std::cout << "   Минимальная цена: " << *minIt << "\n";
    std::cout << "   Максимальная цена: " << *maxIt << "\n";
    std::cout << "   Индекс минимума: " << std::distance(prices.begin(), minIt) << "\n";
    std::cout << "   Индекс максимума: " << std::distance(prices.begin(), maxIt) << "\n";
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
import java.util.Collections;

public static void demonstrateStreamOperations() {
    List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0, 40.0);
    
    // Collections.min - возвращает минимальный элемент
    Double minPrice = Collections.min(prices);
    
    // Collections.max - возвращает максимальный элемент
    Double maxPrice = Collections.max(prices);
    
    System.out.println("Поиск минимума и максимума:");
    System.out.println("   Минимальная цена: " + minPrice);
    System.out.println("   Максимальная цена: " + maxPrice);
    System.out.println("   Индекс минимума: " + prices.indexOf(minPrice));
    System.out.println("   Индекс максимума: " + prices.indexOf(maxPrice));
}
```

**Использование в шаблонной функции:**
```cpp
// Файл: videoprokat/TemplateUtils.hpp
template<typename T>
std::pair<T, T> findMinMax(const std::vector<T>& values)
{
    auto minIt = std::min_element(values.begin(), values.end());
    auto maxIt = std::max_element(values.begin(), values.end());
    
    return std::make_pair(*minIt, *maxIt);
}
```

**Вывод:**
```
Поиск минимума и максимума:
   Минимальная цена: 40
   Максимальная цена: 70
   Индекс минимума: 5
   Индекс максимума: 3
```

---

#### 2. std::find, std::find_if ↔ Stream.filter().findFirst()

**Описание:** Поиск элемента в контейнере по значению или условию.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
    
    // std::find - поиск конкретного значения
    auto findIt = std::find(prices.begin(), prices.end(), 60.0);
    if (findIt != prices.end()) {
        std::cout << "std::find - Найдена цена 60.0 на позиции " 
                  << std::distance(prices.begin(), findIt) << "\n";
    }
    
    // std::find_if - поиск по условию (предикату)
    auto findIfIt = std::find_if(prices.begin(), prices.end(), 
                                  [](double p) { return p > 65.0; });
    if (findIfIt != prices.end()) {
        std::cout << "std::find_if - Первая цена > 65.0: " << *findIfIt << "\n";
    }
    
    // Поиск с пользовательским компаратором
    auto findCustom = std::find_if(prices.begin(), prices.end(),
                                    [](double p) { return p >= 50.0 && p <= 55.0; });
    if (findCustom != prices.end()) {
        std::cout << "std::find_if - Цена в диапазоне [50, 55]: " << *findCustom << "\n";
    }
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateStreamOperations() {
    List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
    
    // Stream.filter().findFirst() - поиск конкретного значения
    Optional<Double> found = prices.stream()
                                   .filter(p -> p == 60.0)
                                   .findFirst();
    found.ifPresent(p -> 
        System.out.println("filter().findFirst() - Найдена цена: " + p));
    
    // Stream.filter().findFirst() - поиск по условию
    Optional<Double> foundIf = prices.stream()
                                     .filter(p -> p > 65.0)
                                     .findFirst();
    foundIf.ifPresent(p -> 
        System.out.println("filter().findFirst() - Первая цена > 65.0: " + p));
    
    // Поиск с пользовательским условием
    Optional<Double> foundCustom = prices.stream()
                                         .filter(p -> p >= 50.0 && p <= 55.0)
                                         .findFirst();
    foundCustom.ifPresent(p -> 
        System.out.println("filter().findFirst() - Цена в диапазоне [50, 55]: " + p));
}
```

**Использование в Repository:**
```cpp
// Файл: videoprokat/Repository.hpp
template<typename T>
template<typename Predicate>
T* Repository<T>::findIf(Predicate pred) const
{
    auto it = std::find_if(m_items.begin(), m_items.end(), pred);
    return (it != m_items.end()) ? *it : nullptr;
}
```

**Вывод:**
```
std::find - Найдена цена 60.0 на позиции 1
std::find_if - Первая цена > 65.0: 70
std::find_if - Цена в диапазоне [50, 55]: 50
```

---

#### 3. std::copy(), std::copy_if() ↔ Stream.filter().collect()

**Описание:** Копирование элементов из одного контейнера в другой с возможностью фильтрации.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0, 40.0};
    
    // std::copy - копирование всех элементов
    std::vector<double> allPrices;
    std::copy(prices.begin(), prices.end(), std::back_inserter(allPrices));
    
    std::cout << "std::copy - все элементы: ";
    for (const auto& p : allPrices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    
    // std::copy_if - копирование с условием
    std::vector<double> expensivePrices;
    std::copy_if(prices.begin(), prices.end(), 
                 std::back_inserter(expensivePrices),
                 [](double p) { return p >= 55.0; });
    
    std::cout << "std::copy_if - дорогие цены (>= 55): ";
    for (const auto& price : expensivePrices) {
        std::cout << price << " ";
    }
    std::cout << "\n";
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateStreamOperations() {
    List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0, 40.0);
    
    // Stream.collect() - копирование всех элементов
    List<Double> allPrices = prices.stream()
                                   .collect(Collectors.toList());
    
    System.out.println("stream().collect() - все элементы: " + allPrices);
    
    // Stream.filter().collect() - копирование с условием
    List<Double> expensivePrices = prices.stream()
                                        .filter(p -> p >= 55.0)
                                        .collect(Collectors.toList());
    
    System.out.println("filter().collect() - дорогие цены (>= 55): " + expensivePrices);
}
```

**Использование в шаблонной функции:**
```cpp
// Файл: videoprokat/TemplateUtils.hpp
template<typename T, typename Predicate>
std::vector<T> filterElements(const std::vector<T>& source, Predicate pred)
{
    std::vector<T> result;
    std::copy_if(source.begin(), source.end(), 
                 std::back_inserter(result), pred);
    return result;
}
```

**Вывод:**
```
std::copy - все элементы: 50 60 45 70 55 40
std::copy_if - дорогие цены (>= 55): 60 70 55
```

---

#### 4. std::remove(), std::remove_if() ↔ List.removeIf()

**Описание:** Удаление элементов из контейнера по значению или условию.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0, 40.0};
    
    std::cout << "До удаления: ";
    for (const auto& p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    
    // std::remove_if - перемещает элементы, удовлетворяющие условию, в конец
    // Возвращает итератор на начало "удаленных" элементов
    auto newEnd = std::remove_if(prices.begin(), prices.end(),
                                  [](double p) { return p < 50.0; });
    
    // erase - физически удаляет элементы с конца
    prices.erase(newEnd, prices.end());
    
    std::cout << "std::remove_if + erase - После удаления цен < 50: ";
    for (const auto& price : prices) {
        std::cout << price << " ";
    }
    std::cout << "\n";
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateStreamOperations() {
    List<Double> prices = new ArrayList<>(
        Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0, 40.0)
    );
    
    System.out.println("До удаления: " + prices);
    
    // List.removeIf() - удаляет элементы, удовлетворяющие условию
    prices.removeIf(p -> p < 50.0);
    
    System.out.println("removeIf() - После удаления цен < 50: " + prices);
}
```

**Использование в Repository:**
```cpp
// Файл: videoprokat/Repository.hpp
template<typename T>
template<typename Predicate>
size_t Repository<T>::removeIf(Predicate pred)
{
    auto oldSize = m_items.size();
    auto newEnd = std::remove_if(m_items.begin(), m_items.end(), pred);
    m_items.erase(newEnd, m_items.end());
    return oldSize - m_items.size();
}
```

**Вывод:**
```
До удаления: 50 60 45 70 55 40
std::remove_if + erase - После удаления цен < 50: 50 60 70 55
```

---

#### 5. std::sort() ↔ Collections.sort()

**Описание:** Сортировка элементов контейнера.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {60.0, 40.0, 70.0, 45.0, 55.0};
    
    std::cout << "До сортировки: ";
    for (const auto& p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    
    // std::sort - сортировка по возрастанию (по умолчанию)
    std::sort(prices.begin(), prices.end());
    
    std::cout << "std::sort - После сортировки по возрастанию: ";
    for (const auto& p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    
    // Сортировка по убыванию с пользовательским компаратором
    std::sort(prices.begin(), prices.end(), 
              [](double a, double b) { return a > b; });
    
    std::cout << "std::sort - После сортировки по убыванию: ";
    for (const auto& p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateStreamOperations() {
    List<Double> prices = new ArrayList<>(
        Arrays.asList(60.0, 40.0, 70.0, 45.0, 55.0)
    );
    
    System.out.println("До сортировки: " + prices);
    
    // Collections.sort() - сортировка по возрастанию (по умолчанию)
    Collections.sort(prices);
    
    System.out.println("Collections.sort() - После сортировки по возрастанию: " + prices);
    
    // Сортировка по убыванию с компаратором
    Collections.sort(prices, (a, b) -> Double.compare(b, a));
    
    System.out.println("Collections.sort() - После сортировки по убыванию: " + prices);
}
```

**Использование в Repository:**
```cpp
// Файл: videoprokat/Repository.hpp
template<typename T>
template<typename Comparator>
void Repository<T>::sort(Comparator comp)
{
    std::sort(m_items.begin(), m_items.end(), comp);
}

// Использование:
repo.sort([](VideoCarrier* a, VideoCarrier* b) {
    return a->getRentalPricePerDay() < b->getRentalPricePerDay();
});
```

**Вывод:**
```
До сортировки: 60 40 70 45 55
std::sort - После сортировки по возрастанию: 40 45 55 60 70
std::sort - После сортировки по убыванию: 70 60 55 45 40
```

---

#### 6. std::filter_view() (C++20 Ranges) ↔ Stream.filter()

**Описание:** Ленивая фильтрация элементов без создания промежуточных копий.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <ranges>  // C++20

void demonstrateRanges()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // std::views::filter - ленивая фильтрация (не создает копию)
    auto evenNumbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });
    
    std::cout << "std::views::filter - Четные числа: ";
    for (int n : evenNumbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // Можно комбинировать несколько фильтров
    auto filtered = numbers 
                  | std::views::filter([](int n) { return n > 3; })
                  | std::views::filter([](int n) { return n < 8; });
    
    std::cout << "Комбинированные фильтры (> 3 и < 8): ";
    for (int n : filtered) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}
```

**Альтернатива для C++17 (без ranges):**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateRanges()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Альтернатива без ranges - создается копия
    std::vector<int> evenNumbers;
    std::copy_if(numbers.begin(), numbers.end(), 
                 std::back_inserter(evenNumbers),
                 [](int n) { return n % 2 == 0; });
    
    std::cout << "std::copy_if - Четные числа: ";
    for (int n : evenNumbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateAdvancedStreams() {
    List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    
    // Stream.filter() - ленивая фильтрация (не создает копию до вызова collect)
    List<Integer> evenNumbers = numbers.stream()
                                      .filter(n -> n % 2 == 0)
                                      .collect(Collectors.toList());
    
    System.out.println("Stream.filter() - Четные числа: " + evenNumbers);
    
    // Можно комбинировать несколько фильтров
    List<Integer> filtered = numbers.stream()
                                   .filter(n -> n > 3)
                                   .filter(n -> n < 8)
                                   .collect(Collectors.toList());
    
    System.out.println("Комбинированные фильтры (> 3 и < 8): " + filtered);
}
```

**Вывод:**
```
std::views::filter - Четные числа: 2 4 6 8 10
Комбинированные фильтры (> 3 и < 8): 4 5 6 7
```

---

#### 7. std::transform, std::transform_view() ↔ Stream.map()

**Описание:** Преобразование каждого элемента контейнера с помощью функции.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
    
    // std::transform - преобразование элементов
    std::vector<double> discounted;
    std::transform(prices.begin(), prices.end(), 
                   std::back_inserter(discounted),
                   [](double p) { return p * 0.9; });  // Скидка 10%
    
    std::cout << "std::transform - Цены со скидкой 10%: ";
    for (const auto& price : discounted) {
        std::cout << price << " ";
    }
    std::cout << "\n";
    
    // Преобразование in-place
    std::transform(prices.begin(), prices.end(), prices.begin(),
                   [](double p) { return p * 1.1; });  // Увеличение на 10%
    
    std::cout << "std::transform in-place - Цены после увеличения: ";
    for (const auto& p : prices) {
        std::cout << p << " ";
    }
    std::cout << "\n";
}
```

**C++ Ranges:**
```cpp
// std::views::transform - ленивое преобразование
auto doubled = numbers | std::views::transform([](int n) { return n * 2; });
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateStreamOperations() {
    List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
    
    // Stream.map() - преобразование элементов
    List<Double> discounted = prices.stream()
                                   .map(p -> p * 0.9)  // Скидка 10%
                                   .collect(Collectors.toList());
    
    System.out.println("Stream.map() - Цены со скидкой 10%: " + discounted);
    
    // Преобразование типов
    List<String> priceStrings = prices.stream()
                                     .map(p -> String.format("%.2f руб", p))
                                     .collect(Collectors.toList());
    
    System.out.println("Stream.map() - Цены как строки: " + priceStrings);
}
```

**Использование в шаблонной функции:**
```cpp
// Файл: videoprokat/TemplateUtils.hpp
template<typename TIn, typename TOut, typename Transform>
std::vector<TOut> transformElements(const std::vector<TIn>& source, Transform func)
{
    std::vector<TOut> result;
    result.reserve(source.size());
    std::transform(source.begin(), source.end(), 
                   std::back_inserter(result), func);
    return result;
}
```

**Вывод:**
```
std::transform - Цены со скидкой 10%: 45 54 40.5 63 49.5
std::transform in-place - Цены после увеличения: 55 66 49.5 77 60.5
```

---

#### 8. std::any_of ↔ Stream.anyMatch()

**Описание:** Проверка, что хотя бы один элемент удовлетворяет условию.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
void demonstrateSTLAlgorithms()
{
    std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
    
    // std::any_of - проверка наличия хотя бы одного элемента
    bool hasExpensive = std::any_of(prices.begin(), prices.end(),
                                    [](double p) { return p > 65.0; });
    
    std::cout << "std::any_of - Есть цены > 65: " 
              << (hasExpensive ? "Да" : "Нет") << "\n";
    
    // std::all_of - проверка, что все элементы удовлетворяют условию
    bool allPositive = std::all_of(prices.begin(), prices.end(),
                                   [](double p) { return p > 0; });
    
    std::cout << "std::all_of - Все цены положительные: " 
              << (allPositive ? "Да" : "Нет") << "\n";
    
    // std::none_of - проверка, что ни один элемент не удовлетворяет условию
    bool noneNegative = std::none_of(prices.begin(), prices.end(),
                                     [](double p) { return p < 0; });
    
    std::cout << "std::none_of - Нет отрицательных цен: " 
              << (noneNegative ? "Да" : "Нет") << "\n";
}
```

**Java:**
```java
// Файл: CollectionsDemo.java
public static void demonstrateStreamOperations() {
    List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
    
    // Stream.anyMatch() - проверка наличия хотя бы одного элемента
    boolean hasExpensive = prices.stream()
                                .anyMatch(p -> p > 65.0);
    
    System.out.println("Stream.anyMatch() - Есть цены > 65: " + 
                      (hasExpensive ? "Да" : "Нет"));
    
    // Stream.allMatch() - проверка, что все элементы удовлетворяют условию
    boolean allPositive = prices.stream()
                               .allMatch(p -> p > 0);
    
    System.out.println("Stream.allMatch() - Все цены положительные: " + 
                      (allPositive ? "Да" : "Нет"));
    
    // Stream.noneMatch() - проверка, что ни один элемент не удовлетворяет условию
    boolean noneNegative = prices.stream()
                                .noneMatch(p -> p < 0);
    
    System.out.println("Stream.noneMatch() - Нет отрицательных цен: " + 
                      (noneNegative ? "Да" : "Нет"));
}
```

**Использование в шаблонной функции:**
```cpp
// Файл: videoprokat/TemplateUtils.hpp
template<typename T, typename Predicate>
bool anyOf(const std::vector<T>& source, Predicate pred)
{
    return std::any_of(source.begin(), source.end(), pred);
}
```

**Вывод:**
```
std::any_of - Есть цены > 65: Да
std::all_of - Все цены положительные: Да
std::none_of - Нет отрицательных цен: Да
```

---

#### 9. std::variant ↔ Object / sealed classes

**Описание:** Тип-объединение, который может хранить значение одного из нескольких типов.

**C++:**
```cpp
// Файл: videoprokat/STLDemo.cpp.example
#include <variant>

void demonstrateVariant()
{
    // std::variant может хранить один из нескольких типов
    using ClientData = std::variant<int, double, std::string>;
    
    ClientData data;
    
    // Хранит int
    data = 123;
    std::cout << "std::variant:\n";
    std::cout << "   ID клиента (int): " << std::get<int>(data) << "\n";
    
    // Хранит double
    data = 99.99;
    std::cout << "   Баланс (double): " << std::get<double>(data) << "\n";
    
    // Хранит string
    data = std::string("Иван Иванов");
    std::cout << "   Имя (string): " << std::get<std::string>(data) << "\n";
    
    // Проверка текущего типа
    if (std::holds_alternative<std::string>(data)) {
        std::cout << "   Текущий тип: string\n";
    }
    
    // Visitor pattern - обработка любого типа
    std::visit([](auto&& value) {
        std::cout << "   Значение через visitor: " << value << "\n";
    }, data);
    
    // Получение индекса типа
    std::cout << "   Индекс типа: " << data.index() << "\n";
}
```

**Java (Object):**
```java
// Файл: CollectionsDemo.java
public static void demonstrateVariant() {
    // В Java нет прямого аналога, используется Object
    Object data;
    
    // Хранит Integer
    data = 123;
    System.out.println("Object:");
    System.out.println("   ID клиента (Integer): " + data);
    
    // Хранит Double
    data = 99.99;
    System.out.println("   Баланс (Double): " + data);
    
    // Хранит String
    data = "Иван Иванов";
    System.out.println("   Имя (String): " + data);
    
    // Проверка текущего типа
    if (data instanceof String) {
        System.out.println("   Текущий тип: String");
        String name = (String) data;  // Требуется приведение типа
    }
}
```

**Java (Sealed Classes - Java 17+):**
```java
// Более типобезопасная альтернатива с sealed классами
sealed interface ClientData permits IntData, DoubleData, StringData {
    Object getValue();
}

record IntData(int value) implements ClientData {
    public Object getValue() { return value; }
}

record DoubleData(double value) implements ClientData {
    public Object getValue() { return value; }
}

record StringData(String value) implements ClientData {
    public Object getValue() { return value; }
}

// Использование с pattern matching
String process(ClientData data) {
    return switch(data) {
        case IntData(int val) -> "ID: " + val;
        case DoubleData(double val) -> "Balance: " + val;
        case StringData(String val) -> "Name: " + val;
    };
}
```

**Вывод:**
```
std::variant:
   ID клиента (int): 123
   Баланс (double): 99.99
   Имя (string): Иван Иванов
   Текущий тип: string
   Значение через visitor: Иван Иванов
   Индекс типа: 2
```

**Использование в реальном коде:**
```cpp
// Вариант для хранения результата операции
using OperationResult = std::variant<
    std::string,           // Успешное сообщение
    std::exception_ptr,    // Ошибка
    int                    // Код результата
>;

OperationResult performOperation() {
    try {
        // ... операция ...
        return std::string("Успешно");
    } catch (...) {
        return std::current_exception();
    }
}
```

---

## Сравнительная Таблица Контейнеров и Методов

| Концепция | C++ STL | Java Collections | Примечания |
|-----------|---------|------------------|------------|
| **Фиксированный массив** | `std::array<T, N>` | `T[]` | C++ знает размер, Java - нет |
| **Динамический массив** | `std::vector<T>` | `ArrayList<T>` | Оба с автоувеличением |
| **Связный список** | `std::list<T>` | `LinkedList<T>` | Двусвязный список в обоих |
| **Словарь** | `std::map<K,V>` (упорядоченный) | `HashMap<K,V>` (неупорядоченный) | C++ - дерево, Java - хеш-таблица |
| **Представление** | `std::span<T>` (C++20) | `List.subList()` | Легковесное, не копирует |
| **Мин/Макс** | `std::min_element` | `Collections.min` | Возвращает итератор vs значение |
| **Поиск** | `std::find_if` | `stream().filter().findFirst()` | C++ - итератор, Java - Optional |
| **Копирование с фильтром** | `std::copy_if` | `stream().filter().collect()` | Оба создают новый контейнер |
| **Удаление** | `std::remove_if + erase` | `removeIf()` | C++ - два шага, Java - один |
| **Сортировка** | `std::sort` | `Collections.sort` | In-place в обоих |
| **Ленивая фильтрация** | `std::views::filter` (C++20) | `stream().filter()` | Не создает копию до терминальной операции |
| **Преобразование** | `std::transform` | `stream().map()` | Применяет функцию к каждому элементу |
| **Проверка условия** | `std::any_of` | `stream().anyMatch()` | True если хотя бы один элемент |
| **Вариантный тип** | `std::variant<...>` | `Object` или sealed classes | C++ - типобезопасно, Java - требует приведения |

---

## Заключение

Все требования задания L5, включая работу с STL и Collections Framework, успешно реализованы и задокументированы. Проект демонстрирует глубокое понимание:
- Концепций ООП в обоих языках программирования
- Работы с контейнерами и алгоритмами
- Шаблонного/generic программирования
- Ограничений на типы на уровне компиляции
- Полиморфизма в контейнерах

Полная документация доступна в файле **STL_COLLECTIONS_GUIDE.md** (1500+ строк).
