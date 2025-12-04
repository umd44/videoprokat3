package videoprokat;

/**
 * Абстрактный класс, описывающий видеоноситель (диск/кассета).
 * Содержит базовую структуру и методы для работы с видеоносителем.
 */
public abstract class VideoCarrier {

    protected int inventoryNumber;
    protected String title;
    protected String carrierType;
    protected String genre;
    protected double rentalPricePerDay;
    protected double fullPrice;
    protected String status;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    protected VideoCarrier() {
        this.inventoryNumber = 0;
        this.title = "";
        this.carrierType = "";
        this.genre = "";
        this.rentalPricePerDay = 0.0;
        this.fullPrice = 0.0;
        this.status = "available";
    }

    /**
     * Конструктор с параметрами.
     */
    protected VideoCarrier(int inventoryNumber, String title, String carrierType, String genre,
                           double rentalPricePerDay, double fullPrice) {
        this.inventoryNumber = inventoryNumber;
        this.title = title;
        this.carrierType = carrierType;
        this.genre = genre;
        this.rentalPricePerDay = rentalPricePerDay;
        this.fullPrice = fullPrice;
        this.status = "available";
    }

    /**
     * Получить инвентарный номер.
     */
    public abstract int getInventoryNumber();

    /**
     * Получить название фильма.
     */
    public abstract String getTitle();

    /**
     * Получить тип носителя.
     */
    public abstract String getCarrierType();

    /**
     * Получить жанр.
     */
    public abstract String getGenre();

    /**
     * Получить цену аренды за день.
     */
    public abstract double getRentalPricePerDay();

    /**
     * Получить полную стоимость.
     */
    public abstract double getFullPrice();

    /**
     * Получить статус носителя.
     */
    public abstract String getStatus();

    /**
     * Проверить, доступен ли носитель для аренды.
     */
    public abstract boolean isAvailable();

    /**
     * Пометить носитель как арендованный.
     * Не абстрактный метод с реализацией по умолчанию для возможности переопределения.
     */
    public void markAsRented() {
        status = "rented";
    }

    /**
     * Пометить носитель как доступный.
     * Не абстрактный метод с реализацией по умолчанию для возможности переопределения.
     */
    public void markAsAvailable() {
        status = "available";
    }
}