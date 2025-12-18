#pragma once
#include "ReportGenerator.hpp"
#include <string>
#include <vector>
#include <map>

class Rental;
class VideoCarrier;
class Client;

/**
 * Реализация класса ReportGenerator.
 * Содержит конкретную реализацию всех методов абстрактного класса ReportGenerator.
 */
class ReportGeneratorReal : public ReportGenerator
{
public:
    /**
     * Конструктор по умолчанию.
     */
    ReportGeneratorReal();

    virtual ~ReportGeneratorReal();

    std::string generateFinancialReport(const std::string& from, const std::string& to) override;

    std::vector<std::string> generatePopularityReport(const std::vector<Rental*>& rentals) override;

    std::string generateInventoryReport(const std::vector<VideoCarrier*>& items) override;

    std::string generateOverdueReport(const std::vector<Rental*>& overdueRentals) override;

    std::string generateClientReport(const std::vector<Client*>& clients) override;

    std::string generateTopItemsReport(const std::vector<VideoCarrier*>& topItems) override;

    std::string generateDailyDashboard(int activeRentals, int overdueRentals, 
                                       double dailyRevenue, int clientsServed,
                                       const std::map<std::string, int>& statistics) override;
};



