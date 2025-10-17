#pragma once
#include <vector>
class VideoCarrier;

class FinancialCalculator
{
public:
    FinancialCalculator() = default;
    ~FinancialCalculator() = default;

    double calculateDeposit(const std::vector<VideoCarrier*>& items) const;
    double calculateRentalCost(const std::vector<VideoCarrier*>& items, int days) const;
    double calculateOverdueFine(int days) const;
};
