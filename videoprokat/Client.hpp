#pragma once
#include <string>

// Клиент видеопроката
class Client
{
public:
    // Пустой клиент по умолчанию
    Client();
    // Клиент с основными данными
    Client(int clientId,
           const std::string& firstName,
           const std::string& lastName,
           const std::string& phoneNumber);
    
    /**
     * Виртуальный деструктор для корректного удаления производных классов.
     */
    virtual ~Client();

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

    /**
     * Виртуальные методы для демонстрации полиморфизма.
     */
    // Пополнение залога
    virtual void addToDeposit(double amount);
    // Блокировка части залога (возврат false, если не хватает средств)
    virtual bool blockDepositFunds(double amount);
    // Разблокировка средств залога
    void unblockDepositFunds(double amount);
    // Установка флага «в черном списке»
    void setBlacklisted(bool value);
    
    /**
     * Не виртуальная функция, которая вызывает виртуальную.
     * Демонстрирует вызов виртуальной функции через не виртуальную.
     */
    void processTransaction(double amount);

protected:
    int m_clientId;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_phoneNumber;
    double m_depositBalance;
    bool m_isBlacklisted;
};
