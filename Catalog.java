package videoprokat;

import java.util.List;

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
}