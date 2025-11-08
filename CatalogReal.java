package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * Реализация класса Catalog.
 * Содержит конкретную реализацию всех методов абстрактного класса Catalog.
 */
public class CatalogReal extends Catalog {

    /**
     * Конструктор по умолчанию.
     * Инициализирует список носителей.
     */
    public CatalogReal() {
        this.items = new ArrayList<>();
    }

    @Override
    public void addItem(VideoCarrier item) {
        if (item != null) {
            items.add(item);
        }
    }

    @Override
    public VideoCarrier findItemByNumber(int number) {
        for (VideoCarrier item : items) {
            if (item != null && item.getInventoryNumber() == number) {
                return item;
            }
        }
        return null;
    }

    @Override
    public List<VideoCarrier> findItemsByTitle(String title) {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && item.getTitle().equals(title)) {
                result.add(item);
            }
        }
        return result;
    }

    @Override
    public List<VideoCarrier> getAvailableItems() {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && item.isAvailable()) {
                result.add(item);
            }
        }
        return result;
    }

    /**
     * Деконструктор (финализатор).
     * Вызывается перед удалением объекта сборщиком мусора.
     */
    @Override
    protected void finalize() throws Throwable {
        try {
            if (items != null) {
                items.clear();
            }
        } finally {
            super.finalize();
        }
    }
}
