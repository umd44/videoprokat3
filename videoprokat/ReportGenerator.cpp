#include "ReportGenerator.hpp"
#include "Rental.hpp"
#include "VideoCarrier.hpp"

#include <sstream>

std::string ReportGenerator::generateFinancialReport(const std::string& from, const std::string& to) const
{
    std::ostringstream oss;
    oss << "Финансовый отчет с " << from << " по " << to;
    return oss.str();
}

std::vector<std::string> ReportGenerator::generatePopularityReport(const std::vector<Rental*>& rentals) const
{
    std::vector<std::string> lines;
    lines.push_back("Popularity report (demo)");
    lines.push_back("Total rentals: " + std::to_string(rentals.size()));
    return lines;
}

std::string ReportGenerator::generateInventoryReport(const std::vector<VideoCarrier*>& items) const
{
    std::ostringstream oss;
    oss << "Доступные элементы:";
    for (const auto* it : items) {
        if (it) {
            oss << "\n" << it->getInventoryNumber() << " - " << it->getTitle();
        }
    }
    return oss.str();
}
