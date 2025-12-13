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
    protected int releaseYear;
    protected String director;
    protected String ageRating;
    protected String description;
    protected double rentalPricePerDay;
    protected double fullPrice;
    protected String status;
    protected int totalRentals;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    protected VideoCarrier() {
        this.inventoryNumber = 0;
        this.title = "";
        this.carrierType = "";
        this.genre = "";
        this.releaseYear = 0;
        this.director = "";
        this.ageRating = "0+";
        this.description = "";
        this.rentalPricePerDay = 0.0;
        this.fullPrice = 0.0;
        this.status = "available";
        this.totalRentals = 0;
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
        this.releaseYear = 0;
        this.director = "";
        this.ageRating = "0+";
        this.description = "";
        this.rentalPricePerDay = rentalPricePerDay;
        this.fullPrice = fullPrice;
        this.status = "available";
        this.totalRentals = 0;
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
     */
    public abstract void markAsRented();

    /**
     * Пометить носитель как доступный.
     */
    public abstract void markAsAvailable();

    /**
     * Получить год выпуска.
     */
    public abstract int getReleaseYear();

    /**
     * Получить режиссера/разработчика.
     */
    public abstract String getDirector();

    /**
     * Получить возрастной рейтинг.
     */
    public abstract String getAgeRating();

    /**
     * Получить описание.
     */
    public abstract String getDescription();

    /**
     * Получить количество аренд.
     */
    public abstract int getTotalRentals();

    /**
     * Установить год выпуска.
     */
    public abstract void setReleaseYear(int year);

    /**
     * Установить режиссера/разработчика.
     */
    public abstract void setDirector(String director);

    /**
     * Установить возрастной рейтинг.
     */
    public abstract void setAgeRating(String ageRating);

    /**
     * Установить описание.
     */
    public abstract void setDescription(String description);

    /**
     * Увеличить счетчик аренд.
     */
    public abstract void incrementRentals();

    /**
     * Установить статус носителя.
     */
    public abstract void setStatus(String status);
}