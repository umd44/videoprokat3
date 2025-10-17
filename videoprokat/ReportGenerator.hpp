#pragma once
#include <string>
#include <vector>

class Rental;
class VideoCarrier;

class ReportGenerator
{
public:
    ReportGenerator() = default;
    ~ReportGenerator() = default;

    std::string generateFinancialReport(const std::string& from, const std::string& to) const;
    std::vector<std::string> generatePopularityReport(const std::vector<Rental*>& rentals) const;
    std::string generateInventoryReport(const std::vector<VideoCarrier*>& items) const;
};
