#pragma once
#include <vector>
#include <string>
#include <memory>

class Client;
class VideoCarrier;
class Rental;
class FinancialCalculator;

// Менеджер аренды
class RentalManager
{
public:
    RentalManager();
    ~RentalManager();

    // Создать аренду
    std::shared_ptr<Rental> createRental(std::shared_ptr<Client> client, const std::vector<std::shared_ptr<VideoCarrier>>& items, int days,
                         const std::string& rentalDate, const std::string& plannedReturnDate);
    // Обработать возврат, вернуть итог к оплате
    double processReturn(std::shared_ptr<Rental> rental, int overdueDays);
    // Получить список просроченных (упрощенно)
    std::vector<std::shared_ptr<Rental>> getOverdueRentals(const std::string& currentDate) const;

private:
    std::vector<std::shared_ptr<Rental>> m_activeRentals;
    std::unique_ptr<FinancialCalculator> m_calculator;
};
