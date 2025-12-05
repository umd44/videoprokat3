package videoprokat;

/**
 * Интерфейс для объектов, которые могут получать скидки.
 * Определяет методы для применения скидок к сумме.
 */
public interface Discountable {
    /**
     * Применить скидку к сумме.
     * @param amount - исходная сумма
     * @return сумма с учетом скидки
     */
    double applyDiscount(double amount);

    /**
     * Получить процент скидки.
     * @return процент скидки
     */
    double getDiscountPercentage();
}
