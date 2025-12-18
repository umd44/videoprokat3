#include "RentalManagerReal.hpp"
#include "RentalReal.hpp"
#include "Client.hpp"
#include "VideoCarrier.hpp"
#include "FinancialCalculatorReal.hpp"
#include <algorithm>

int RentalManagerReal::nextId = 1;

RentalManagerReal::RentalManagerReal()
    : RentalManager()
{
    this->activeRentals.clear();
    this->calculator = new FinancialCalculatorReal();
}

RentalManagerReal::~RentalManagerReal()
{
    close();
}

Rental* RentalManagerReal::createRental(Client* client, const std::vector<VideoCarrier*>& items, int days,
                                         const std::string& rentalDate, const std::string& plannedReturnDate)
{
    if (client == nullptr || items.empty() || days <= 0) {
        return nullptr;
    }

    std::vector<VideoCarrier*> safeItems = items;
    Rental* rental = new RentalReal(nextId++, client, safeItems, rentalDate, plannedReturnDate);
    rental->setCalculatedAmounts(calculator, days);

    for (VideoCarrier* item : safeItems) {
        if (item != nullptr) {
            item->markAsRented();
        }
    }

    activeRentals.push_back(rental);
    return rental;
}

double RentalManagerReal::processReturn(Rental* rental, int overdueDays)
{
    if (rental == nullptr) {
        return 0.0;
    }

    double fine = calculator->calculateOverdueFine(overdueDays);

    for (VideoCarrier* item : rental->getItems()) {
        if (item != nullptr) {
            item->markAsAvailable();
            item->incrementRentals();
        }
    }

    double total = rental->closeRental(fine);

    // Удаляем из активных аренд
    auto it = std::find(activeRentals.begin(), activeRentals.end(), rental);
    if (it != activeRentals.end()) {
        activeRentals.erase(it);
    }

    return total;
}

double RentalManagerReal::processReturnWithDamage(Rental* rental, int overdueDays, 
                                                   VideoCarrier* damagedItem, 
                                                   const std::string& damageType, 
                                                   double damageCompensation)
{
    if (rental == nullptr) {
        return 0.0;
    }

    double fine = calculator->calculateOverdueFine(overdueDays);

    for (VideoCarrier* item : rental->getItems()) {
        if (item != nullptr) {
            if (item == damagedItem) {
                if (damageType == "critical") {
                    item->setStatus("written_off");
                } else if (damageType == "minor") {
                    item->setStatus("maintenance");
                } else {
                    item->markAsAvailable();
                }
            } else {
                item->markAsAvailable();
            }
            item->incrementRentals();
        }
    }

    double total = rental->closeRental(fine + damageCompensation);

    // Удаляем из активных аренд
    auto it = std::find(activeRentals.begin(), activeRentals.end(), rental);
    if (it != activeRentals.end()) {
        activeRentals.erase(it);
    }

    return total;
}

std::vector<Rental*> RentalManagerReal::getOverdueRentals(const std::string& currentDate)
{
    std::vector<Rental*> result;
    for (Rental* rental : activeRentals) {
        if (rental != nullptr && rental->getStatus() == "active") {
            result.push_back(rental);
        }
    }
    return result;
}

std::vector<Rental*> RentalManagerReal::getActiveRentals()
{
    std::vector<Rental*> result;
    result.reserve(activeRentals.size());
    for (Rental* rental : activeRentals) {
        result.push_back(rental);
    }
    return result;
}

void RentalManagerReal::close()
{
    if (activeRentals.size() > 0) {
        for (Rental* rental : activeRentals) {
            delete rental;
        }
        activeRentals.clear();
    }
    if (calculator != nullptr) {
        delete calculator;
        calculator = nullptr;
    }
}



