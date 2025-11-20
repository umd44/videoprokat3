#include "ReportGenerator.hpp"
#include "Rental.hpp"
#include "VideoCarrier.hpp"
#include <sstream>

std::string ReportGenerator::generateFinancialReport(const std::string& from, const std::string& to) const
{
    // Конкатенация строк через ostringstream
    std::ostringstream oss;
    oss << "Финансовый отчет с " << from << " по " << to;
    
    // Поиск подстроки в дате
    std::string result = oss.str();
    if (result.find("2025") != std::string::npos) {
        result += " (текущий год)";
    }
    
    return result;
}

std::vector<std::string> ReportGenerator::generatePopularityReport(const std::vector<std::shared_ptr<Rental>>& rentals) const
{
    std::vector<std::string> lines;
    lines.push_back("Popularity report (demo)");
    lines.push_back("Total rentals: " + std::to_string(rentals.size()));
    return lines;
}

std::string ReportGenerator::generateInventoryReport(const std::vector<std::shared_ptr<VideoCarrier>>& items) const
{
    // Работа со строками: конкатенация, поиск, форматирование
    std::ostringstream oss;
    std::string header = "Доступные элементы:";
    oss << header;
    
    for (const auto& it : items) {
        if (it) {
            // Конкатенация строк через оператор +
            std::string itemLine = "\n" + std::to_string(it->getInventoryNumber()) + " - " + it->getTitle();
            
            // Поиск подстроки в названии
            if (it->getTitle().find("DVD") != std::string::npos || 
                it->getCarrierType().find("DVD") != std::string::npos) {
                itemLine += " [DVD]";
            }
            
            oss << itemLine;
        }
    }
    
    return oss.str();
}
