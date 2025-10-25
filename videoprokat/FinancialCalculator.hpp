#pragma once
#include <vector>
class VideoCarrier;

// Простой финансовый калькулятор
class FinancialCalculator
{
public:
    FinancialCalculator() = default;
    ~FinancialCalculator() = default;

    // Сумма залога для списка носителей
    double calculateDeposit(const std::vector<VideoCarrier*>& items) const;
    // Стоимость аренды за N дней
    double calculateRentalCost(const std::vector<VideoCarrier*>& items, int days) const;
    // Штраф за просрочку (по дням)
    double calculateOverdueFine(int days) const;
};
