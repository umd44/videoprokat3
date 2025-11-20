#pragma once
#include <string>
#include <vector>
#include <memory>

class Rental;
class VideoCarrier;

// Генерирует различные отчеты: финансовые, по популярности, по складу
class ReportGenerator
{
public:
    ReportGenerator() = default;
    ~ReportGenerator() = default;

    std::string generateFinancialReport(const std::string& from, const std::string& to) const;
    std::vector<std::string> generatePopularityReport(const std::vector<std::shared_ptr<Rental>>& rentals) const;
    std::string generateInventoryReport(const std::vector<std::shared_ptr<VideoCarrier>>& items) const;
};
