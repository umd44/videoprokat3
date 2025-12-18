package videoprokat;

import java.util.List;
import java.util.Map;

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

    /**
     * Сгенерировать отчет по просрочкам.
     */
    public abstract String generateOverdueReport(List<Rental> overdueRentals);

    /**
     * Сгенерировать отчет по клиентам.
     */
    public abstract String generateClientReport(List<Client> clients);

    /**
     * Сгенерировать отчет по топ носителям.
     */
    public abstract String generateTopItemsReport(List<VideoCarrier> topItems);

    /**
     * Сгенерировать дашборд текущего дня.
     */
    public abstract String generateDailyDashboard(int activeRentals, int overdueRentals, 
                                                   double dailyRevenue, int clientsServed,
                                                   Map<String, Integer> statistics);
}