package videoprokat;

import java.util.List;

/**
 * Абстрактный класс, описывающий финансовый калькулятор.
 * Содержит базовую структуру и методы для финансовых расчетов.
 */
public abstract class FinancialCalculator {

    /**
     * Конструктор по умолчанию.
     */
    protected FinancialCalculator() {
    }

    /**
     * Рассчитать сумму залога для списка носителей.
     */
    public abstract double calculateDeposit(List<VideoCarrier> items);

    /**
     * Рассчитать стоимость аренды за указанное количество дней.
     */
    public abstract double calculateRentalCost(List<VideoCarrier> items, int days);

    /**
     * Рассчитать штраф за просрочку.
     */
    public abstract double calculateOverdueFine(int days);
}