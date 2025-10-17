#include "RentalManager.hpp"
#include "Rental.hpp"
#include "Client.hpp"
#include "VideoCarrier.hpp"
#include "FinancialCalculator.hpp"

RentalManager::RentalManager()
    : m_calculator(new FinancialCalculator())
{
}

RentalManager::~RentalManager()
{
    for (auto* r : m_activeRentals) {
        delete r;
    }
    delete m_calculator;
}

Rental* RentalManager::createRental(Client* client, const std::vector<VideoCarrier*>& items, int days,
                                    const std::string& rentalDate, const std::string& plannedReturnDate)
{
    if (!client || items.empty() || days <= 0) return nullptr;
    static int nextId = 1;
    Rental* rental = new Rental(nextId++, client, items, rentalDate, plannedReturnDate);
    rental->setCalculatedAmounts(*m_calculator, days);
    for (auto* item : items) {
        if (item) item->markAsRented();
    }
    m_activeRentals.push_back(rental);
    return rental;
}

double RentalManager::processReturn(Rental* rental, int overdueDays)
{
    if (!rental) return 0.0;
    double fine = m_calculator->calculateOverdueFine(overdueDays);
    for (auto* item : rental->getItems()) {
        if (item) item->markAsAvailable();
    }
    double total = rental->closeRental(fine);
    return total;
}

std::vector<Rental*> RentalManager::getOverdueRentals(const std::string& /*currentDate*/) const
{
    std::vector<Rental*> result;
    for (auto* r : m_activeRentals) {
        if (r && r->getStatus() == std::string("active")) {
            result.push_back(r);
        }
    }
    return result;
}
