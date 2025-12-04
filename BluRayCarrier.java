package videoprokat;

/**
 * BluRay-носитель - производный класс от VideoCarrier.
 * Демонстрирует наследование и использование виртуальных методов.
 */
public class BluRayCarrier extends VideoCarrier {
    
    private boolean is4K;
    private boolean hasHDR;
    private int storageGB;
    
    public BluRayCarrier() {
        super();
        this.is4K = false;
        this.hasHDR = false;
        this.storageGB = 25;
    }
    
    /**
     * Конструктор с параметрами, вызывает конструктор базового класса.
     */
    public BluRayCarrier(int inventoryNumber, String title, String genre,
                        double rentalPricePerDay, double fullPrice, boolean is4K, boolean hasHDR) {
        super(inventoryNumber, title, "BluRay", genre, rentalPricePerDay, fullPrice);
        this.is4K = is4K;
        this.hasHDR = hasHDR;
        this.storageGB = is4K ? 50 : 25;
    }
    
    /**
     * Перегрузка метода базового класса БЕЗ ВЫЗОВА базового метода.
     * Полностью переопределяет логику.
     */
    @Override
    public void markAsRented() {
        status = "rented";
        System.out.println("BluRay диск " + (is4K ? "4K " : "") + "арендован: " + title);
    }
    
    /**
     * Перегрузка с вызовом базового метода.
     */
    @Override
    public void markAsAvailable() {
        System.out.println("BluRay возвращен: " + title);
        status = "available";
    }
    
    /**
     * Использует protected поля базового класса.
     */
    protected double calculatePremiumPrice() {
        double basePrice = rentalPricePerDay;
        if (is4K) basePrice *= 1.5;
        if (hasHDR) basePrice *= 1.2;
        return basePrice;
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
        return calculatePremiumPrice();
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
    
    public boolean isIs4K() {
        return is4K;
    }
    
    public boolean isHasHDR() {
        return hasHDR;
    }
    
    public int getStorageGB() {
        return storageGB;
    }
}
