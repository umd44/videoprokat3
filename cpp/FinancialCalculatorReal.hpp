#pragma once
#include "FinancialCalculator.hpp"
#include <vector>

class VideoCarrier;

/**
 * Реализация класса FinancialCalculator.
 * Содержит конкретную реализацию всех методов абстрактного класса FinancialCalculator.
 */
class FinancialCalculatorReal : public FinancialCalculator
{
private:
    static const double DEPOSIT_RATE; // 20% от полной стоимости
    static const double PENALTY_PER_DAY; // штраф за день просрочки

public:
    /**
     * Конструктор по умолчанию.
     */
    FinancialCalculatorReal();

    virtual ~FinancialCalculatorReal();

    double calculateDeposit(const std::vector<VideoCarrier*>& items) override;

    double calculateRentalCost(const std::vector<VideoCarrier*>& items, int days) override;

    double calculateOverdueFine(int days) override;
};



