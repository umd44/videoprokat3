#pragma once
#include <vector>
#include <string>

class Client;
class VideoCarrier;
class Rental;
class FinancialCalculator;

class RentalManager
{
public:
    RentalManager();
    ~RentalManager();

    Rental* createRental(Client* client, const std::vector<VideoCarrier*>& items, int days,
                         const std::string& rentalDate, const std::string& plannedReturnDate);
    double processReturn(Rental* rental, int overdueDays);
    std::vector<Rental*> getOverdueRentals(const std::string& currentDate) const; // simplified

private:
    std::vector<Rental*> m_activeRentals;
    FinancialCalculator* m_calculator; // owned simple pointer for demo
};
