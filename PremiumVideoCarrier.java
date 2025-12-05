package videoprokat;

/**
 * Премиальный видеоноситель (например, 4K Ultra HD).
 * Имеет повышенную цену и специальный статус.
 * Наследует VideoCarrier.
 */
public class PremiumVideoCarrier extends VideoCarrierReal {

    private String format; // 4K, Ultra HD, Dolby Vision, и т.д.
    private boolean hasSpecialFeatures;
    private String specialFeaturesDescription;

    /**
     * Конструктор премиального видеоносителя.
     * @param inventoryNumber - инвентарный номер
     * @param title - название
     * @param carrierType - тип носителя (DVD, BluRay, и т.д.)
     * @param genre - жанр
     * @param rentalPricePerDay - цена аренды за день
     * @param fullPrice - полная стоимость
     * @param format - формат видео (4K, Ultra HD и т.д.)
     * @param specialFeaturesDescription - описание специальных функций
     */
    public PremiumVideoCarrier(int inventoryNumber, String title, String carrierType,
                              String genre, double rentalPricePerDay, double fullPrice,
                              String format, String specialFeaturesDescription) {
        super(inventoryNumber, title, carrierType, genre, rentalPricePerDay, fullPrice);
        this.format = format;
        this.specialFeaturesDescription = specialFeaturesDescription;
        this.hasSpecialFeatures = specialFeaturesDescription != null && !specialFeaturesDescription.isEmpty();
    }

    /**
     * Получить формат видео.
     * @return формат (4K, Ultra HD и т.д.)
     */
    public String getFormat() {
        return format;
    }

    /**
     * Установить формат видео.
     * @param format - новый формат
     */
    public void setFormat(String format) {
        this.format = format;
    }

    /**
     * Проверить, есть ли специальные функции.
     * @return true, если есть специальные функции
     */
    public boolean hasSpecialFeatures() {
        return hasSpecialFeatures;
    }

    /**
     * Получить описание специальных функций.
     * @return описание функций
     */
    public String getSpecialFeaturesDescription() {
        return specialFeaturesDescription;
    }

    /**
     * Установить описание специальных функций.
     * @param description - новое описание
     */
    public void setSpecialFeaturesDescription(String description) {
        this.specialFeaturesDescription = description;
        this.hasSpecialFeatures = description != null && !description.isEmpty();
    }

    /**
     * Получить дополнительную информацию о премиальном видеоносителе.
     * @return информация
     */
    public String getPremiumInfo() {
        return String.format("Premium [%s] - %s, Format: %s, Features: %s",
                carrierType, title, format, specialFeaturesDescription);
    }

    /**
     * Получить рекомендуемую цену проката с премиальной надбавкой.
     * @param premiumMultiplier - множитель надбавки (например, 1.5 для 50% надбавки)
     * @return цена с надбавкой
     */
    public double getPremiumRentalPrice(double premiumMultiplier) {
        return rentalPricePerDay * premiumMultiplier;
    }
}
