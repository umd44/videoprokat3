package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * Реализация класса ReportGenerator.
 * Содержит конкретную реализацию всех методов абстрактного класса ReportGenerator.
 */
public class ReportGeneratorReal extends ReportGenerator {

    /**
     * Конструктор по умолчанию.
     */
    public ReportGeneratorReal() {
        super();
    }

    @Override
    public String generateFinancialReport(String from, String to) {
        return "Финансовый отчет с " + from + " по " + to;
    }

    @Override
    public List<String> generatePopularityReport(List<Rental> rentals) {
        List<String> lines = new ArrayList<>();
        lines.add("Popularity report (demo)");
        lines.add("Total rentals: " + (rentals == null ? 0 : rentals.size()));
        return lines;
    }

    @Override
    public String generateInventoryReport(List<VideoCarrier> items) {
        StringBuilder builder = new StringBuilder("Доступные элементы:");
        if (items != null) {
            for (VideoCarrier item : items) {
                if (item != null) {
                    builder.append("\n")
                           .append(item.getInventoryNumber())
                           .append(" - ")
                           .append(item.getTitle());
                }
            }
        }
        return builder.toString();
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
