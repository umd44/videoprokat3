#pragma once
#include <vector>
#include <memory>

class VideoCarrier;

// Калькулятор для финансовых операций: залог, стоимость аренды, штрафы
class FinancialCalculator
{
public:
    FinancialCalculator() = default;
    ~FinancialCalculator() = default;

    double calculateDeposit(const std::vector<std::shared_ptr<VideoCarrier>>& items) const;
    double calculateRentalCost(const std::vector<std::shared_ptr<VideoCarrier>>& items, int days) const;
    double calculateOverdueFine(int days) const;
    
    // Умножение стоимости на коэффициент (скидка/надбавка)
    friend double operator*(double cost, const FinancialCalculator& calc);
};
