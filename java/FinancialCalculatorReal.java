package videoprokat;

import java.util.List;

/**
 * Реализация класса FinancialCalculator.
 * Содержит конкретную реализацию всех методов абстрактного класса FinancialCalculator.
 */
public class FinancialCalculatorReal extends FinancialCalculator {

    private static final double DEPOSIT_RATE = 0.2; // 20% от полной стоимости
    private static final double PENALTY_PER_DAY = 5.0; // штраф за день просрочки

    /**
     * Конструктор по умолчанию.
     */
    public FinancialCalculatorReal() {
        super();
    }

    @Override
    public double calculateDeposit(List<VideoCarrier> items) {
        double sum = 0.0;
        for (VideoCarrier item : items) {
            if (item != null) {
                sum += item.getFullPrice() * DEPOSIT_RATE;
            }
        }
        return sum;
    }

    @Override
    public double calculateRentalCost(List<VideoCarrier> items, int days) {
        if (days < 0) {
            days = 0;
        }
        double sum = 0.0;
        for (VideoCarrier item : items) {
            if (item != null) {
                sum += item.getRentalPricePerDay() * days;
            }
        }
        return sum;
    }

    @Override
    public double calculateOverdueFine(int days) {
        if (days <= 0) {
            return 0.0;
        }
        return days * PENALTY_PER_DAY;
    }
}
