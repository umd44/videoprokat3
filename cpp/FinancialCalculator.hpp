#pragma once
#include <vector>
#include <string>

class VideoCarrier;

/**
 * Абстрактный класс, описывающий финансовый калькулятор.
 * Содержит базовую структуру и методы для финансовых расчетов.
 */
class FinancialCalculator
{
protected:
    /**
     * Конструктор по умолчанию.
     */
    FinancialCalculator() = default;

public:
    virtual ~FinancialCalculator() = default;

    /**
     * Рассчитать сумму залога для списка носителей.
     */
    virtual double calculateDeposit(const std::vector<VideoCarrier*>& items) = 0;

    /**
     * Рассчитать стоимость аренды за указанное количество дней.
     */
    virtual double calculateRentalCost(const std::vector<VideoCarrier*>& items, int days) = 0;

    /**
     * Рассчитать штраф за просрочку.
     */
    virtual double calculateOverdueFine(int days) = 0;
};
