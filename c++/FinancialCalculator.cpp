#include "FinancialCalculator.hpp"
#include "VideoCarrier.hpp"
#include "VideoRentalException.hpp"

#include <vector>

namespace {
    constexpr double deposit = 0.2; // 20% от полной стоимости
    constexpr double penalty = 5.0; // штраф за день просрочки
}

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

// Пример 2: Использование throw для выбрасывания исключения при отрицательных значениях
double FinancialCalculator::calculateOverdueFine(int days) const
{
    // Проверка на отрицательное значение и выброс исключения
    if (days < 0) {
        // ИНСТРУКЦИЯ THROW - выбрасываем исключение при некорректных данных
        throw InvalidDataException("days", "количество дней не может быть отрицательным");
    }
    
    if (days <= 0) return 0.0;
    return static_cast<double>(days) * penalty;
}
