#pragma once
#include <string>
#include <vector>
#include <map>

class Rental;
class VideoCarrier;
class Client;

/**
 * Абстрактный класс, описывающий генератор отчетов.
 * Содержит базовую структуру и методы для генерации отчетов.
 */
class ReportGenerator
{
protected:
    /**
     * Конструктор по умолчанию.
     */
    ReportGenerator() = default;

public:
    virtual ~ReportGenerator() = default;

    /**
     * Сгенерировать финансовый отчет за период.
     */
    virtual std::string generateFinancialReport(const std::string& from, const std::string& to) = 0;

    /**
     * Сгенерировать отчет о популярности.
     */
    virtual std::vector<std::string> generatePopularityReport(const std::vector<Rental*>& rentals) = 0;

    /**
     * Сгенерировать отчет об инвентаре.
     */
    virtual std::string generateInventoryReport(const std::vector<VideoCarrier*>& items) = 0;

    /**
     * Сгенерировать отчет по просрочкам.
     */
    virtual std::string generateOverdueReport(const std::vector<Rental*>& overdueRentals) = 0;

    /**
     * Сгенерировать отчет по клиентам.
     */
    virtual std::string generateClientReport(const std::vector<Client*>& clients) = 0;

    /**
     * Сгенерировать отчет по топ носителям.
     */
    virtual std::string generateTopItemsReport(const std::vector<VideoCarrier*>& topItems) = 0;

    /**
     * Сгенерировать дашборд текущего дня.
     */
    virtual std::string generateDailyDashboard(int activeRentals, int overdueRentals, 
                                               double dailyRevenue, int clientsServed,
                                               const std::map<std::string, int>& statistics) = 0;
};
