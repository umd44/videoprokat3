package videoprokat;

import java.util.List;

/**
 * Абстрактный класс, описывающий менеджер аренды.
 * Содержит базовую структуру и методы для управления арендами.
 */
public abstract class RentalManager {

    protected List<Rental> activeRentals;
    protected FinancialCalculator calculator;

    /**
     * Конструктор по умолчанию.
     */
    protected RentalManager() {
        // Инициализация выполняется в реализации
    }

    /**
     * Создать новую аренду.
     */
    public abstract Rental createRental(Client client, List<VideoCarrier> items, int days,
                                        String rentalDate, String plannedReturnDate);

    /**
     * Обработать возврат аренды.
     */
    public abstract double processReturn(Rental rental, int overdueDays);

    /**
     * Обработать возврат аренды с учетом повреждений.
     */
    public abstract double processReturnWithDamage(Rental rental, int overdueDays, 
                                                    VideoCarrier damagedItem, 
                                                    String damageType, 
                                                    double damageCompensation);

    /**
     * Получить список просроченных аренд.
     */
    public abstract List<Rental> getOverdueRentals(String currentDate);

    /**
     * Получить список всех активных аренд.
     */
    public abstract List<Rental> getActiveRentals();

    /**
     * Закрыть менеджер и освободить ресурсы.
     */
    public abstract void close();
}