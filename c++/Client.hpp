#pragma once
#include <string>

// Клиент видеопроката
class Client
{
public:
    // Перегрузка оператора равенства
    // Сравнивает клиентов по идентификатору
    bool operator==(const Client& other) const;
    // Пустой клиент по умолчанию
    Client();
    // Клиент с основными данными
    Client(int clientId,
           const std::string& firstName,
           const std::string& lastName,
           const std::string& phoneNumber);
    ~Client() = default;

    // Идентификатор клиента
    int getClientId() const;
    // Имя
    const std::string& getFirstName() const;
    // Фамилия
    const std::string& getLastName() const;
    // Телефон
    const std::string& getPhoneNumber() const;
    // Текущий баланс залога
    double getDepositBalance() const;
    // Флаг «в черном списке»
    bool getIsBlacklisted() const;

    // Пополнение залога
    void addToDeposit(double amount);
    // Пополнение залога с возвратом ссылки на себя (для цепочки вызовов)
    Client& addToDepositChain(double amount);
    // Блокировка части залога (возврат false, если не хватает средств)
    bool blockDepositFunds(double amount);
    // Блокировка части залога с выбрасыванием исключения (для демонстрации throw)
    void blockDepositFundsOrThrow(double amount);
    // Разблокировка средств залога
    void unblockDepositFunds(double amount);
    // Установка флага «в черном списке»
    void setBlacklisted(bool value);
    // Установка флага «в черном списке» с возвратом ссылки на себя (для цепочки вызовов)
    Client& setBlacklistedChain(bool value);
    // Обновление имени клиента (демонстрация разрешения конфликта имен с this)
    Client& setFirstName(const std::string& firstName);
    // Обновление фамилии клиента (демонстрация разрешения конфликта имен с this)
    Client& setLastName(const std::string& lastName);

    // Статические методы - работают с классом в целом, а не с конкретным объектом
    // Получить следующий доступный ID клиента (использует статическое поле)
    static int getNextClientId();
    // Получить общее количество созданных клиентов (использует статическое поле)
    static int getTotalClientsCount();
    // Сброс счетчика клиентов (для тестирования)
    static void resetClientCounter();

private:
    // Обычные (нестатические) поля - уникальны для каждого объекта
    int m_clientId;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phoneNumber;
    double m_depositBalance;
    bool m_isBlacklisted;
    
    // Статическое поле - общее для всех объектов класса
    // Существует в единственном экземпляре независимо от количества объектов
    static int s_nextClientId;      // Следующий доступный ID клиента
    static int s_totalClientsCount; // Общее количество созданных клиентов
};
