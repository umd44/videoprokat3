#include "Client.hpp"
#include "VideoRentalException.hpp"

// Инициализация статических полей класса
// Статические поля должны быть определены вне класса (в файле реализации)
// Существуют в единственном экземпляре для всего класса, а не для каждого объекта
int Client::s_nextClientId = 1;      // Начинаем с ID = 1
int Client::s_totalClientsCount = 0; // Изначально клиентов нет

Client::Client()
    : m_clientId(0), m_depositBalance(0.0), m_isBlacklisted(false)
{
    // Увеличиваем статический счетчик при создании объекта
    // Это поле общее для всех объектов Client
    s_totalClientsCount++;  // Доступ к статическому полю через имя класса (можно и через this->, но не обязательно)
}

Client::Client(int clientId,
               const std::string& firstName,
               const std::string& lastName,
               const std::string& phoneNumber)
    : m_clientId(clientId),
      m_firstName(firstName),
      m_lastName(lastName),
      m_phoneNumber(phoneNumber),
      m_depositBalance(0.0),
      m_isBlacklisted(false)
{
    // Увеличиваем статический счетчик при создании объекта
    // Если clientId не задан (0), используем статический счетчик для автоматической генерации ID
    s_totalClientsCount++;  // Доступ к статическому полю
    
    // Если clientId = 0, присваиваем следующий доступный ID из статического поля
    if (m_clientId == 0) {
        m_clientId = s_nextClientId++;  // Используем текущий ID и увеличиваем счетчик
    } else {
        // Если ID задан явно, обновляем статический счетчик, чтобы избежать конфликтов
        if (clientId >= s_nextClientId) {
            s_nextClientId = clientId + 1;  // Обновляем, чтобы следующий ID был больше
        }
    }
}

int Client::getClientId() const { return m_clientId; }
const std::string& Client::getFirstName() const { return m_firstName; }
const std::string& Client::getLastName() const { return m_lastName; }
const std::string& Client::getPhoneNumber() const { return m_phoneNumber; }

double Client::getDepositBalance() const { return m_depositBalance; }
bool Client::getIsBlacklisted() const { return m_isBlacklisted; }

void Client::addToDeposit(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
}

bool Client::blockDepositFunds(double amount)
{
    if (amount <= 0.0) return false;
    if (m_depositBalance >= amount) {
        m_depositBalance -= amount;
        return true;
    }
    return false;
}

// Пример 1: Использование throw для выбрасывания исключения
// Демонстрация инструкции throw и обработки исключений
void Client::blockDepositFundsOrThrow(double amount)
{
    // Проверка на некорректные данные
    if (amount <= 0.0) {
        throw InvalidDataException("amount", "сумма должна быть положительной");
    }
    
    // Проверка на недостаток средств и выброс исключения
    if (m_depositBalance < amount) {
        // ИНСТРУКЦИЯ THROW - выбрасываем исключение
        // Создаем объект исключения и выбрасываем его
        throw InsufficientFundsException(amount, m_depositBalance);
    }
    
    // Если все в порядке, выполняем операцию
    m_depositBalance -= amount;
}

void Client::unblockDepositFunds(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
}

void Client::setBlacklisted(bool value)
{
    m_isBlacklisted = value;
}

// Пример 1: Method chaining - возврат ссылки на себя через this
// Позволяет создавать цепочки вызовов: client.addToDepositChain(100).setBlacklistedChain(true)
Client& Client::addToDepositChain(double amount)
{
    if (amount > 0.0) {
        m_depositBalance += amount;
    }
    return *this;  // Возвращаем ссылку на текущий объект через разыменование this
}

// Пример 2: Method chaining - возврат ссылки на себя через this
Client& Client::setBlacklistedChain(bool value)
{
    m_isBlacklisted = value;
    return *this;  // Возвращаем ссылку на текущий объект для цепочки вызовов
}

// Пример 3: Разрешение конфликта имен между параметром и полем класса с помощью this->
// Использование this-> явно указывает на поле класса, а не на параметр
Client& Client::setFirstName(const std::string& firstName)
{
    // Параметр называется firstName, поле класса тоже m_firstName
    // Используем this-> для явного указания на поле класса (хотя в данном случае можно без this)
    // Но это демонстрирует явное использование оператора this
    this->m_firstName = firstName;  // this-> явно указывает на член класса
    return *this;  // Возвращаем ссылку на себя для цепочки вызовов
}

// Пример 4: Разрешение конфликта имен с помощью this->
Client& Client::setLastName(const std::string& lastName)
{
    this->m_lastName = lastName;  // this-> явно указывает на член класса
    return *this;  // Возвращаем ссылку на себя для цепочки вызовов
}

// Пример 5: Использование this для проверки сравнения объекта с самим собой
// Оптимизация: если сравниваем объект с самим собой, сразу возвращаем true
bool Client::operator==(const Client& other) const
{
    // Используем this для проверки: не сравниваем ли объект с самим собой?
    if (this == &other) {  // Сравниваем указатели - если это один и тот же объект
        return true;       // Сразу возвращаем true (оптимизация)
    }
    // Если это разные объекты, сравниваем по логике
    return m_clientId == other.m_clientId;
}

// Пример 6: Статический метод - работает с классом в целом, а не с конкретным объектом
// Не имеет доступа к this, так как не привязан к конкретному объекту
// Может быть вызван без создания объекта: Client::getNextClientId()
int Client::getNextClientId()
{
    // Статический метод имеет доступ к статическим полям класса
    // Доступ к статическому полю через имя класса (не через this)
    return s_nextClientId;  // Возвращаем следующий доступный ID
}

// Пример 7: Статический метод для получения общего количества клиентов
// Использует статическое поле s_totalClientsCount
int Client::getTotalClientsCount()
{
    // Статический метод может быть вызван без объекта:
    // int count = Client::getTotalClientsCount();
    // ИЛИ через объект: client->getTotalClientsCount() (но это не требует объекта)
    return s_totalClientsCount;  // Возвращаем общее количество созданных клиентов
}

// Пример 8: Статический метод для сброса счетчиков (полезно для тестирования)
void Client::resetClientCounter()
{
    // Статический метод может изменять статические поля
    s_nextClientId = 1;       // Сбрасываем счетчик ID
    s_totalClientsCount = 0;  // Сбрасываем счетчик объектов
}
