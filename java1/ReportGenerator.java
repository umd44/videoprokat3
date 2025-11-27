package videoprokat;

import java.util.List;

/**
 * Абстрактный класс, описывающий генератор отчетов.
 * Содержит базовую структуру и методы для генерации отчетов.
 */
public abstract class ReportGenerator {

    /**
     * Конструктор по умолчанию.
     */
    protected ReportGenerator() {
    }

    /**
     * Сгенерировать финансовый отчет за период.
     */
    public abstract String generateFinancialReport(String from, String to);

    /**
     * Сгенерировать отчет о популярности.
     */
    public abstract List<String> generatePopularityReport(List<Rental> rentals);

    /**
     * Сгенерировать отчет об инвентаре.
     */
    public abstract String generateInventoryReport(List<VideoCarrier> items);
}