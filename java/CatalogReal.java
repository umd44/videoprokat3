package videoprokat;

import java.text.Collator;
import java.text.Normalizer;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

/**
 * Реализация класса Catalog.
 * Содержит конкретную реализацию всех методов абстрактного класса Catalog.
 */
public class CatalogReal extends Catalog {

    private static final Locale RU = new Locale("ru", "RU");
    private static final Collator COLLATOR = Collator.getInstance(RU);

    static {
        COLLATOR.setStrength(Collator.PRIMARY); // нечувствительно к регистру/акцентам
    }

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
            if (item != null && containsRu(item.getTitle(), title)) {
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

    @Override
    public List<VideoCarrier> findItemsByGenre(String genre) {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && containsRu(item.getGenre(), genre)) {
                result.add(item);
            }
        }
        return result;
    }

    @Override
    public List<VideoCarrier> findItemsByDirector(String director) {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && containsRu(item.getDirector(), director)) {
                result.add(item);
            }
        }
        return result;
    }

    @Override
    public List<VideoCarrier> findItemsByYear(int year) {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && item.getReleaseYear() == year) {
                result.add(item);
            }
        }
        return result;
    }

    @Override
    public List<VideoCarrier> findItemsByCarrierType(String carrierType) {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && equalsRu(item.getCarrierType(), carrierType)) {
                result.add(item);
            }
        }
        return result;
    }

    @Override
    public List<VideoCarrier> findItemsByAgeRating(String ageRating) {
        List<VideoCarrier> result = new ArrayList<>();
        for (VideoCarrier item : items) {
            if (item != null && equalsRu(item.getAgeRating(), ageRating)) {
                result.add(item);
            }
        }
        return result;
    }

    @Override
    public List<VideoCarrier> getAllItems() {
        return new ArrayList<>(items);
    }

    @Override
    public Map<String, Integer> getStatistics() {
        Map<String, Integer> stats = new HashMap<>();
        int available = 0, rented = 0, maintenance = 0, writtenOff = 0;
        
        for (VideoCarrier item : items) {
            if (item != null) {
                String status = item.getStatus();
                if ("available".equals(status)) available++;
                else if ("rented".equals(status)) rented++;
                else if ("maintenance".equals(status)) maintenance++;
                else if ("written_off".equals(status)) writtenOff++;
            }
        }
        
        stats.put("total", items.size());
        stats.put("available", available);
        stats.put("rented", rented);
        stats.put("maintenance", maintenance);
        stats.put("written_off", writtenOff);
        
        return stats;
    }

    @Override
    public List<VideoCarrier> getTopRentedItems(int limit) {
        List<VideoCarrier> sorted = new ArrayList<>(items);
        sorted.sort(new Comparator<VideoCarrier>() {
            @Override
            public int compare(VideoCarrier v1, VideoCarrier v2) {
                return Integer.compare(v2.getTotalRentals(), v1.getTotalRentals());
            }
        });
        
        if (limit > sorted.size()) {
            limit = sorted.size();
        }
        
        return sorted.subList(0, limit);
    }

    private String normalizeRu(String s) {
        if (s == null) return "";
        // Простая нормализация - переводим в нижний регистр
        return s.toLowerCase(RU);
    }

    private boolean containsRu(String haystack, String needle) {
        String n = normalizeRu(needle == null ? "" : needle.trim());
        if (n.isEmpty()) return true; // пустой запрос — считаем совпадением
        if (haystack == null) return false;
        String h = normalizeRu(haystack);
        return h.contains(n); // подстрока, регистронезависимо, работает и на 1 символ
    }

    private boolean equalsRu(String a, String b) {
        return COLLATOR.compare(a == null ? "" : a, b == null ? "" : b) == 0;
    }
}
