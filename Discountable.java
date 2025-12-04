package videoprokat;

/**
 * Интерфейс для объектов, которые поддерживают скидки.
 * Демонстрирует использование интерфейсов в Java.
 */
public interface Discountable {
    
    /**
     * Получить размер скидки в процентах.
     */
    double getDiscountPercentage();
    
    /**
     * Применить скидку к сумме.
     */
    double applyDiscount(double amount);
    
    /**
     * Проверить, доступна ли скидка.
     */
    boolean isDiscountAvailable();
}
