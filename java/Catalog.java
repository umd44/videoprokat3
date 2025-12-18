package videoprokat;

import java.util.List;
import java.util.Map;

/**
 * Абстрактный класс, описывающий каталог видеоносителей.
 * Содержит базовую структуру и методы для работы с каталогом.
 */
public abstract class Catalog {

    protected List<VideoCarrier> items;

    /**
     * Конструктор по умолчанию.
     */
    protected Catalog() {
        // Инициализация коллекции выполняется в реализации
    }

    /**
     * Добавить носитель в каталог.
     */
    public abstract void addItem(VideoCarrier item);

    /**
     * Найти носитель по инвентарному номеру.
     */
    public abstract VideoCarrier findItemByNumber(int number);

    /**
     * Найти все носители по названию.
     */
    public abstract List<VideoCarrier> findItemsByTitle(String title);

    /**
     * Получить список доступных носителей.
     */
    public abstract List<VideoCarrier> getAvailableItems();

    /**
     * Найти носители по жанру.
     */
    public abstract List<VideoCarrier> findItemsByGenre(String genre);

    /**
     * Найти носители по режиссеру.
     */
    public abstract List<VideoCarrier> findItemsByDirector(String director);

    /**
     * Найти носители по году выпуска.
     */
    public abstract List<VideoCarrier> findItemsByYear(int year);

    /**
     * Найти носители по типу носителя.
     */
    public abstract List<VideoCarrier> findItemsByCarrierType(String carrierType);

    /**
     * Найти носители по возрастному рейтингу.
     */
    public abstract List<VideoCarrier> findItemsByAgeRating(String ageRating);

    /**
     * Получить все носители.
     */
    public abstract List<VideoCarrier> getAllItems();

    /**
     * Получить статистику по носителям.
     */
    public abstract Map<String, Integer> getStatistics();

    /**
     * Найти топ популярных носителей.
     */
    public abstract List<VideoCarrier> getTopRentedItems(int limit);
}