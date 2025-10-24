#include "FinancialCalculator.hpp"
#include "VideoCarrier.hpp"

#include <vector>

namespace {
    constexpr double deposit = 0.2; // 20% от полной стоимости
    constexpr double penalty = 5.0; // штраф за день просрочки
}

double FinancialCalculator::calculateDeposit(const std::vector<VideoCarrier*>& items) const
{
    double sum = 0.0;
    for (const auto* item : items) {
        if (item) {
            sum += item->getFullPrice() * deposit;
        }
    }
    return sum;
}

double FinancialCalculator::calculateRentalCost(const std::vector<VideoCarrier*>& items, int days) const
{
    if (days < 0) days = 0;
    double sum = 0.0;
    for (const auto* item : items) {
        if (item) {
            sum += item->getRentalPricePerDay() * days;
        }
    }
    return sum;
}

double FinancialCalculator::calculateOverdueFine(int days) const
{
    if (days <= 0) return 0.0;
    return static_cast<double>(days) * penalty;
}
