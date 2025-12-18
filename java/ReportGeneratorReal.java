package videoprokat;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.time.temporal.ChronoUnit;

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

    @Override
    public String generateOverdueReport(List<Rental> overdueRentals) {
        StringBuilder builder = new StringBuilder("=== ОТЧЕТ ПО ПРОСРОЧКАМ ===\n");
        if (overdueRentals == null || overdueRentals.isEmpty()) {
            builder.append("Просроченных аренд нет\n");
        } else {
            builder.append("Всего просроченных аренд: ").append(overdueRentals.size()).append("\n\n");
            for (Rental rental : overdueRentals) {
                if (rental != null) {
                    Client client = rental.getClient();
                    String plannedInfo = rental.getPlannedReturnDate();
                    if (plannedInfo != null && !plannedInfo.isEmpty()) {
                        try {
                            LocalDate plannedDate = LocalDate.parse(plannedInfo);
                            LocalDate today = LocalDate.now();
                            long diff = ChronoUnit.DAYS.between(today, plannedDate);
                            if (diff > 0) {
                                plannedInfo = diff + " дн. осталось";
                            } else if (diff < 0) {
                                plannedInfo = "просрочено на " + Math.abs(diff) + " дн.";
                            } else {
                                plannedInfo = "сегодня";
                            }
                        } catch (DateTimeParseException e) {
                            // оставляем исходное значение, если формат даты неожиданный
                        }
                    }
                    builder.append("Аренда #").append(rental.getRentalId())
                           .append(" | Клиент: ").append(client.getFirstName())
                           .append(" ").append(client.getLastName())
                           .append(" | Тел: ").append(client.getPhoneNumber())
                           .append(" | План.возврат: ").append(plannedInfo)
                           .append("\n");
                }
            }
        }
        return builder.toString();
    }

    @Override
    public String generateClientReport(List<Client> clients) {
        StringBuilder builder = new StringBuilder("=== ОТЧЕТ ПО КЛИЕНТАМ ===\n");
        if (clients == null || clients.isEmpty()) {
            builder.append("Клиенты отсутствуют\n");
        } else {
            builder.append("Всего клиентов: ").append(clients.size()).append("\n\n");
            int active = 0, blacklisted = 0;
            for (Client client : clients) {
                if (client != null) {
                    if (client.isBlacklisted()) {
                        blacklisted++;
                    } else {
                        active++;
                    }
                }
            }
            builder.append("Активных: ").append(active)
                   .append(" | В черном списке: ").append(blacklisted).append("\n");
        }
        return builder.toString();
    }

    @Override
    public String generateTopItemsReport(List<VideoCarrier> topItems) {
        StringBuilder builder = new StringBuilder("=== ТОП ПОПУЛЯРНЫХ НОСИТЕЛЕЙ ===\n");
        if (topItems == null || topItems.isEmpty()) {
            builder.append("Нет данных о популярности\n");
        } else {
            int rank = 1;
            for (VideoCarrier item : topItems) {
                if (item != null) {
                    builder.append(rank++).append(". ")
                           .append(item.getTitle())
                           .append(" (").append(item.getGenre()).append(")")
                           .append(" - ").append(item.getTotalRentals()).append(" аренд\n");
                }
            }
        }
        return builder.toString();
    }

    @Override
    public String generateDailyDashboard(int activeRentals, int overdueRentals, 
                                          double dailyRevenue, int clientsServed,
                                          Map<String, Integer> statistics) {
        StringBuilder builder = new StringBuilder("\n");
        builder.append("╔══════════════════════════════════════════════════════╗\n");
        builder.append("║         ДАШБОРД ТЕКУЩЕГО ДНЯ (для руководителя)     ║\n");
        builder.append("╠══════════════════════════════════════════════════════╣\n");
        builder.append(String.format("║ Активных аренд:           %26d ║\n", activeRentals));
        builder.append(String.format("║ Просроченных возвратов:   %26d ║\n", overdueRentals));
        builder.append(String.format("║ Доход за день:            %22.2f руб ║\n", dailyRevenue));
        builder.append(String.format("║ Обслужено клиентов:       %26d ║\n", clientsServed));
        builder.append("╠══════════════════════════════════════════════════════╣\n");
        builder.append("║                СТАТИСТИКА НОСИТЕЛЕЙ                  ║\n");
        builder.append("╠══════════════════════════════════════════════════════╣\n");
        
        if (statistics != null) {
            builder.append(String.format("║ Всего носителей:          %26d ║\n", 
                statistics.getOrDefault("total", 0)));
            builder.append(String.format("║ Доступных:                %26d ║\n", 
                statistics.getOrDefault("available", 0)));
            builder.append(String.format("║ Арендованных:             %26d ║\n", 
                statistics.getOrDefault("rented", 0)));
            builder.append(String.format("║ На реставрации:           %26d ║\n", 
                statistics.getOrDefault("maintenance", 0)));
            builder.append(String.format("║ Списанных:                %26d ║\n", 
                statistics.getOrDefault("written_off", 0)));
        }
        
        builder.append("╚══════════════════════════════════════════════════════╝\n");
        return builder.toString();
    }
}
