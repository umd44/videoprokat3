#include "FinancialCalculator.hpp"
#include "VideoCarrier.hpp"
#include "VideoRentalException.hpp"

#include <vector>

namespace {
    constexpr double deposit = 0.2;  // Залог составляет 20% от полной стоимости
}

constexpr double penalty = 5.0;  // Штраф за каждый день просрочки

double FinancialCalculator::calculateDeposit(const std::vector<std::shared_ptr<VideoCarrier>>& items) const
{
    double sum = 0.0;
    for (const auto& item : items) {
        if (item) {
            sum += item->getFullPrice() * deposit;
        }
    }
    return sum;
}

double FinancialCalculator::calculateRentalCost(const std::vector<std::shared_ptr<VideoCarrier>>& items, int days) const
{
    if (days < 0) days = 0;
    double sum = 0.0;
    for (const auto& item : items) {
        if (item) {
            sum += item->getRentalPricePerDay() * days;
        }
    }
    return sum;
}

double FinancialCalculator::calculateOverdueFine(int days) const
{
    if (days < 0) {
        throw InvalidDataException("days", "количество дней не может быть отрицательным");
    }
    
    if (days <= 0) return 0.0;
    return static_cast<double>(days) * penalty;
}

// Умножает стоимость на коэффициент (для применения скидок/надбавок)
double operator*(double cost, const FinancialCalculator& calc)
{
    return cost * penalty;  // Используем стандартный коэффициент штрафа
}
