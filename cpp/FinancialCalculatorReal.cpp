#include "FinancialCalculatorReal.hpp"
#include "VideoCarrier.hpp"

const double FinancialCalculatorReal::DEPOSIT_RATE = 0.2; // 20% от полной стоимости
const double FinancialCalculatorReal::PENALTY_PER_DAY = 5.0; // штраф за день просрочки

FinancialCalculatorReal::FinancialCalculatorReal()
    : FinancialCalculator()
{
}

FinancialCalculatorReal::~FinancialCalculatorReal()
{
}

double FinancialCalculatorReal::calculateDeposit(const std::vector<VideoCarrier*>& items)
{
    double sum = 0.0;
    for (VideoCarrier* item : items) {
        if (item != nullptr) {
            sum += item->getFullPrice() * DEPOSIT_RATE;
        }
    }
    return sum;
}

double FinancialCalculatorReal::calculateRentalCost(const std::vector<VideoCarrier*>& items, int days)
{
    if (days < 0) {
        days = 0;
    }
    double sum = 0.0;
    for (VideoCarrier* item : items) {
        if (item != nullptr) {
            sum += item->getRentalPricePerDay() * days;
        }
    }
    return sum;
}

double FinancialCalculatorReal::calculateOverdueFine(int days)
{
    if (days <= 0) {
        return 0.0;
    }
    return days * PENALTY_PER_DAY;
}



