#pragma once
#include <string>

/**
 * Абстрактный класс для обработки платежей.
 * Демонстрирует использование абстрактных классов и чисто виртуальных функций.
 */
class PaymentProcessor
{
public:
    PaymentProcessor();
    virtual ~PaymentProcessor();
    
    /**
     * Чисто виртуальная функция - должна быть реализована в производных классах.
     */
    virtual bool processPayment(double amount, const std::string& details) = 0;
    
    /**
     * Чисто виртуальная функция для возврата средств.
     */
    virtual bool refund(double amount, const std::string& transactionId) = 0;
    
    /**
     * Не виртуальная функция, которая вызывает чисто виртуальную.
     * Демонстрирует вызов виртуальной функции через не виртуальную.
     */
    void executePayment(double amount, const std::string& details);

protected:
    int m_transactionCount;
};

/**
 * Конкретная реализация - обработчик наличных платежей.
 */
class CashPaymentProcessor : public PaymentProcessor
{
public:
    CashPaymentProcessor();
    virtual ~CashPaymentProcessor();
    
    virtual bool processPayment(double amount, const std::string& details) override;
    virtual bool refund(double amount, const std::string& transactionId) override;
};

/**
 * Конкретная реализация - обработчик карточных платежей.
 */
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
