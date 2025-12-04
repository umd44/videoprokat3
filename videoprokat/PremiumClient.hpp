#pragma once
#include "Client.hpp"
#include <iostream>

/**
 * Премиум-клиент - производный класс от Client.
 * Демонстрирует:
 * - Наследование
 * - Использование protected
 * - Перегрузку методов
 * - Вызов конструктора базового класса
 * - Перегрузку оператора присваивания
 */
class PremiumClient : public Client
{
public:
    PremiumClient();
    
    /**
     * Конструктор с параметрами - демонстрирует вызов конструктора базового класса.
     */
    PremiumClient(int clientId,
                  const std::string& firstName,
                  const std::string& lastName,
                  const std::string& phoneNumber,
                  const std::string& email,
                  double discountPercentage);
    
    /**
     * Конструктор копирования УДАЛЕН для демонстрации.
     */
    PremiumClient(const PremiumClient&) = delete;
    
    /**
     * Виртуальный деструктор.
     */
    virtual ~PremiumClient();
    
    /**
     * Перегрузка оператора присваивания для присваивания базового класса производному.
     */
    PremiumClient& operator=(const Client& base);
    
    /**
     * Виртуальная функция - перегрузка С ВЫЗОВОМ базового метода.
     */
    virtual void addToDeposit(double amount) override;
    
    /**
     * Виртуальная функция - перегрузка БЕЗ ВЫЗОВА базового метода.
     */
    virtual bool blockDepositFunds(double amount) override;
    
    double getDiscountPercentage() const;
    int getLoyaltyPoints() const;
    const std::string& getEmail() const;
    
    double applyDiscount(double amount) const;
    void sendNotification(const std::string& message) const;

protected:
    /**
     * Защищенный метод - демонстрация использования protected.
     */
    void updateLoyalty(double rentalAmount);
    
    double m_discountPercentage;
    int m_loyaltyPoints;
    std::string m_email;
};
