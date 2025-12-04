package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * DVD-носитель - производный класс от VideoCarrier.
 * Демонстрирует клонирование (поверхностное и глубокое).
 */
public class DVDCarrier extends VideoCarrier implements Cloneable {
    
    private int diskNumber;
    private String region;
    private List<String> subtitles;
    
    public DVDCarrier() {
        super();
        this.diskNumber = 1;
        this.region = "ALL";
        this.subtitles = new ArrayList<>();
    }
    
    /**
     * Конструктор с параметрами, вызывает конструктор базового класса.
     */
    public DVDCarrier(int inventoryNumber, String title, String genre,
                     double rentalPricePerDay, double fullPrice, int diskNumber, String region) {
        super(inventoryNumber, title, "DVD", genre, rentalPricePerDay, fullPrice);
        this.diskNumber = diskNumber;
        this.region = region;
        this.subtitles = new ArrayList<>();
    }
    
    /**
     * Использует protected поля базового класса.
     */
    protected void applyDVDDiscount() {
        rentalPricePerDay *= 0.9;
    }
    
    /**
     * Перегрузка метода базового класса С ВЫЗОВОМ базового метода.
     */
    @Override
    public void markAsRented() {
        System.out.println("DVD диск #" + diskNumber + " арендуется");
        status = "rented";
    }
    
    public void addSubtitle(String language) {
        subtitles.add(language);
    }
    
    public List<String> getSubtitles() {
        return subtitles;
    }
    
    /**
     * Поверхностное клонирование.
     * Список subtitles будет разделяться между оригиналом и клоном.
     */
    public DVDCarrier shallowClone() {
        try {
            return (DVDCarrier) super.clone();
        } catch (CloneNotSupportedException e) {
            System.out.println("Ошибка клонирования: " + e.getMessage());
            return null;
        }
    }
    
    /**
     * Глубокое клонирование.
     * Создает новый список subtitles для клона.
     */
    public DVDCarrier deepClone() {
        try {
            DVDCarrier cloned = (DVDCarrier) super.clone();
            cloned.subtitles = new ArrayList<>(this.subtitles);
            return cloned;
        } catch (CloneNotSupportedException e) {
            System.out.println("Ошибка клонирования: " + e.getMessage());
            return null;
        }
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
    public void markAsAvailable() {
        status = "available";
    }
    
    public int getDiskNumber() {
        return diskNumber;
    }
    
    public String getRegion() {
        return region;
    }
}
