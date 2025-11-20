#pragma once
#include <string>

// Представляет клиента видеопроката с депозитом и статусом
class Client
{
public:
    // Проверка на неравенство клиентов
    bool operator!=(const Client& other) const;
    // Пополнение депозита через оператор +=
    Client& operator+=(double amount);
    Client();
    Client(int clientId,
           const std::string& firstName,
           const std::string& lastName,
           const std::string& phoneNumber);
    // Конструктор копирования
    Client(const Client& other);
    ~Client() = default;

    // Геттеры для основных полей
    int getClientId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getPhoneNumber() const;
    double getDepositBalance() const;
    bool getIsBlacklisted() const;

    // Работа с депозитом
    void addToDeposit(double amount);
    Client& addToDepositChain(double amount);
    bool blockDepositFunds(double amount);
    void blockDepositFundsOrThrow(double amount);
    void unblockDepositFunds(double amount);
    
    // Управление статусом
    void setBlacklisted(bool value);
    Client& setBlacklistedChain(bool value);
    Client& setFirstName(const std::string& firstName);
    Client& setLastName(const std::string& lastName);

    static int getNextClientId();
    static int getTotalClientsCount();
    static void resetClientCounter();

private:
    int m_clientId;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phoneNumber;
    double m_depositBalance;
    bool m_isBlacklisted;
    
    static int s_nextClientId;
    static int s_totalClientsCount;
};
