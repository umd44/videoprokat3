#pragma once
#include <vector>
#include <string>

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
    Rental* createRental(Client* client, const std::vector<VideoCarrier*>& items, int days,
                         const std::string& rentalDate, const std::string& plannedReturnDate);
    // Обработать возврат, вернуть итог к оплате
    double processReturn(Rental* rental, int overdueDays);
    // Получить список просроченных (упрощенно)
    std::vector<Rental*> getOverdueRentals(const std::string& currentDate) const;

private:
    std::vector<Rental*> m_activeRentals;
    FinancialCalculator* m_calculator;
};
