#pragma once
#include <string>
#include <vector>

class Rental;
class VideoCarrier;

// Генератор простых текстовых отчетов
class ReportGenerator
{
public:
    ReportGenerator() = default;
    ~ReportGenerator() = default;

    // Финансовый отчет за период
    std::string generateFinancialReport(const std::string& from, const std::string& to) const;
    // Простейший отчет о популярности
    std::vector<std::string> generatePopularityReport(const std::vector<Rental*>& rentals) const;
    // Список доступных элементов каталога
    std::string generateInventoryReport(const std::vector<VideoCarrier*>& items) const;
};
