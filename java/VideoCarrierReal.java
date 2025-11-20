package videoprokat;

/**
 * Реализация класса VideoCarrier.
 * Содержит конкретную реализацию всех методов абстрактного класса VideoCarrier.
 */
public class VideoCarrierReal extends VideoCarrier {

    /**
     * Конструктор по умолчанию.
     */
    public VideoCarrierReal() {
        super();
    }

    /**
     * Конструктор с параметрами.
     */
    public VideoCarrierReal(int inventoryNumber, String title, String carrierType, String genre,
                            double rentalPricePerDay, double fullPrice) {
        super(inventoryNumber, title, carrierType, genre, rentalPricePerDay, fullPrice);
    }

    @Override
    public int getInventoryNumber() {
        return inventoryNumber;
    }

    @Override
    public String getTitle() {
        return title;
    }

    @Override
    public String getCarrierType() {
        return carrierType;
    }

    @Override
    public String getGenre() {
        return genre;
    }

    @Override
    public double getRentalPricePerDay() {
        return rentalPricePerDay;
    }

    @Override
    public double getFullPrice() {
        return fullPrice;
    }

    @Override
    public String getStatus() {
        return status;
    }

    @Override
    public boolean isAvailable() {
        return "available".equals(status);
    }

    @Override
    public void markAsRented() {
        status = "rented";
    }

    @Override
    public void markAsAvailable() {
        status = "available";
    }

    /**
     * Деконструктор (финализатор).
     * Вызывается перед удалением объекта сборщиком мусора.
     */
    @Override
    protected void finalize() throws Throwable {
        try {
            // Освобождение ресурсов (если необходимо)
        } finally {
            super.finalize();
        }
    }
}
