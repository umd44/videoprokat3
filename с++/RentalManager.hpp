#pragma once
#include <vector>
#include <string>
#include <memory>

class Client;
class VideoCarrier;
class Rental;
class FinancialCalculator;

// Управляет процессом аренды: создание, возврат, отслеживание просрочек
class RentalManager
{
public:
    RentalManager();
    ~RentalManager();

    std::shared_ptr<Rental> createRental(std::shared_ptr<Client> client, const std::vector<std::shared_ptr<VideoCarrier>>& items, int days,
                         const std::string& rentalDate, const std::string& plannedReturnDate);
    double processReturn(std::shared_ptr<Rental> rental, int overdueDays);
    std::vector<std::shared_ptr<Rental>> getOverdueRentals(const std::string& currentDate) const;

private:
    std::vector<std::shared_ptr<Rental>> m_activeRentals;
    std::unique_ptr<FinancialCalculator> m_calculator;
};
