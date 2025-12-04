#include "PaymentProcessor.hpp"
#include <iostream>

PaymentProcessor::PaymentProcessor()
    : m_transactionCount(0)
{
}

PaymentProcessor::~PaymentProcessor()
{
    std::cout << "Деструктор PaymentProcessor. Обработано транзакций: " 
              << m_transactionCount << "\n";
}

void PaymentProcessor::executePayment(double amount, const std::string& details)
{
    std::cout << "PaymentProcessor::executePayment вызывает виртуальную processPayment()\n";
    if (processPayment(amount, details)) {
        m_transactionCount++;
    }
}

CashPaymentProcessor::CashPaymentProcessor()
    : PaymentProcessor()
{
    std::cout << "Создан обработчик наличных платежей\n";
}

CashPaymentProcessor::~CashPaymentProcessor()
{
    std::cout << "Деструктор CashPaymentProcessor\n";
}

bool CashPaymentProcessor::processPayment(double amount, const std::string& details)
{
    std::cout << "Обработка наличного платежа: " << amount << " руб. (" << details << ")\n";
    return true;
}

bool CashPaymentProcessor::refund(double amount, const std::string& transactionId)
{
    std::cout << "Возврат наличных: " << amount << " руб. (ID: " << transactionId << ")\n";
    return true;
}

CardPaymentProcessor::CardPaymentProcessor()
    : PaymentProcessor(),
      m_processingFee(0.02)
{
    std::cout << "Создан обработчик карточных платежей (комиссия " 
              << m_processingFee * 100 << "%)\n";
}

CardPaymentProcessor::~CardPaymentProcessor()
{
    std::cout << "Деструктор CardPaymentProcessor\n";
}

bool CardPaymentProcessor::processPayment(double amount, const std::string& details)
{
    double fee = amount * m_processingFee;
    double total = amount + fee;
    std::cout << "Обработка платежа по карте: " << amount << " + " << fee 
              << " (комиссия) = " << total << " руб. (" << details << ")\n";
    return true;
}

bool CardPaymentProcessor::refund(double amount, const std::string& transactionId)
{
    std::cout << "Возврат на карту: " << amount << " руб. (ID: " 
              << transactionId << ")\n";
    return true;
}
