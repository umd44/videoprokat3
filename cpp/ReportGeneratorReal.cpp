#include "ReportGeneratorReal.hpp"
#include "Rental.hpp"
#include "VideoCarrier.hpp"
#include "Client.hpp"
#include <sstream>
#include <iomanip>

ReportGeneratorReal::ReportGeneratorReal()
    : ReportGenerator()
{
}

ReportGeneratorReal::~ReportGeneratorReal()
{
}

std::string ReportGeneratorReal::generateFinancialReport(const std::string& from, const std::string& to)
{
    return "Финансовый отчет с " + from + " по " + to;
}

std::vector<std::string> ReportGeneratorReal::generatePopularityReport(const std::vector<Rental*>& rentals)
{
    std::vector<std::string> lines;
    lines.push_back("Popularity report (demo)");
    lines.push_back("Total rentals: " + std::to_string(static_cast<int>(rentals.size())));
    return lines;
}

std::string ReportGeneratorReal::generateInventoryReport(const std::vector<VideoCarrier*>& items)
{
    std::ostringstream builder;
    builder << "Доступные элементы:";
    if (!items.empty()) {
        for (VideoCarrier* item : items) {
            if (item != nullptr) {
                builder << "\n" << item->getInventoryNumber() << " - " << item->getTitle();
            }
        }
    }
    return builder.str();
}

std::string ReportGeneratorReal::generateOverdueReport(const std::vector<Rental*>& overdueRentals)
{
    std::ostringstream builder;
    builder << "=== ОТЧЕТ ПО ПРОСРОЧКАМ ===\n";
    if (overdueRentals.empty()) {
        builder << "Просроченных аренд нет\n";
    } else {
        builder << "Всего просроченных аренд: " << static_cast<int>(overdueRentals.size()) << "\n\n";
        for (Rental* rental : overdueRentals) {
            if (rental != nullptr) {
                Client* client = rental->getClient();
                builder << "Аренда #" << rental->getRentalId()
                       << " | Клиент: " << client->getFirstName()
                       << " " << client->getLastName()
                       << " | Тел: " << client->getPhoneNumber()
                       << " | План.возврат: " << rental->getPlannedReturnDate()
                       << "\n";
            }
        }
    }
    return builder.str();
}

std::string ReportGeneratorReal::generateClientReport(const std::vector<Client*>& clients)
{
    std::ostringstream builder;
    builder << "=== ОТЧЕТ ПО КЛИЕНТАМ ===\n";
    if (clients.empty()) {
        builder << "Клиенты отсутствуют\n";
    } else {
        builder << "Всего клиентов: " << static_cast<int>(clients.size()) << "\n\n";
        int active = 0, blacklisted = 0;
        for (Client* client : clients) {
            if (client != nullptr) {
                if (client->isBlacklisted()) {
                    blacklisted++;
                } else {
                    active++;
                }
            }
        }
        builder << "Активных: " << active << " | В черном списке: " << blacklisted << "\n";
    }
    return builder.str();
}

std::string ReportGeneratorReal::generateTopItemsReport(const std::vector<VideoCarrier*>& topItems)
{
    std::ostringstream builder;
    builder << "=== ТОП ПОПУЛЯРНЫХ НОСИТЕЛЕЙ ===\n";
    if (topItems.empty()) {
        builder << "Нет данных о популярности\n";
    } else {
        int rank = 1;
        for (VideoCarrier* item : topItems) {
            if (item != nullptr) {
                builder << rank++ << ". " << item->getTitle()
                       << " (" << item->getGenre() << ")"
                       << " - " << item->getTotalRentals() << " аренд\n";
            }
        }
    }
    return builder.str();
}

std::string ReportGeneratorReal::generateDailyDashboard(int activeRentals, int overdueRentals, 
                                                         double dailyRevenue, int clientsServed,
                                                         const std::map<std::string, int>& statistics)
{
    std::ostringstream builder;
    builder << "\n";
    builder << "╔══════════════════════════════════════════════════════╗\n";
    builder << "║         ДАШБОРД ТЕКУЩЕГО ДНЯ (для руководителя)     ║\n";
    builder << "╠══════════════════════════════════════════════════════╣\n";
    builder << "║ Активных аренд:           " << std::setw(26) << activeRentals << " ║\n";
    builder << "║ Просроченных возвратов:   " << std::setw(26) << overdueRentals << " ║\n";
    builder << "║ Доход за день:            " << std::setw(22) << std::fixed << std::setprecision(2) << dailyRevenue << " руб ║\n";
    builder << "║ Обслужено клиентов:       " << std::setw(26) << clientsServed << " ║\n";
    builder << "╠══════════════════════════════════════════════════════╣\n";
    builder << "║                СТАТИСТИКА НОСИТЕЛЕЙ                  ║\n";
    builder << "╠══════════════════════════════════════════════════════╣\n";
    
    auto totalIt = statistics.find("total");
    auto availableIt = statistics.find("available");
    auto rentedIt = statistics.find("rented");
    auto maintenanceIt = statistics.find("maintenance");
    auto writtenOffIt = statistics.find("written_off");
    
    builder << "║ Всего носителей:          " << std::setw(26) << (totalIt != statistics.end() ? totalIt->second : 0) << " ║\n";
    builder << "║ Доступных:                " << std::setw(26) << (availableIt != statistics.end() ? availableIt->second : 0) << " ║\n";
    builder << "║ Арендованных:             " << std::setw(26) << (rentedIt != statistics.end() ? rentedIt->second : 0) << " ║\n";
    builder << "║ На реставрации:           " << std::setw(26) << (maintenanceIt != statistics.end() ? maintenanceIt->second : 0) << " ║\n";
    builder << "║ Списанных:                " << std::setw(26) << (writtenOffIt != statistics.end() ? writtenOffIt->second : 0) << " ║\n";
    
    builder << "╚══════════════════════════════════════════════════════╝\n";
    return builder.str();
}

