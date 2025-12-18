#include "RentalReal.hpp"
#include "Client.hpp"
#include "VideoCarrier.hpp"
#include "FinancialCalculator.hpp"

RentalReal::RentalReal()
{
    items.clear();
}

RentalReal::RentalReal(int rentalId, Client* client, const std::vector<VideoCarrier*>& items,
                       const std::string& rentalDate, const std::string& plannedReturnDate)
    : Rental(rentalId, client, items, rentalDate, plannedReturnDate)
{
}

RentalReal::~RentalReal()
{
    // В C++ не удаляем items, так как они принадлежат другим объектам
    items.clear();
}

int RentalReal::getRentalId()
{
    return rentalId;
}

Client* RentalReal::getClient()
{
    return client;
}

std::vector<VideoCarrier*> RentalReal::getItems()
{
    return items;
}

std::string RentalReal::getRentalDate()
{
    return rentalDate;
}

std::string RentalReal::getPlannedReturnDate()
{
    return plannedReturnDate;
}

double RentalReal::getDepositAmount()
{
    return depositAmount;
}

double RentalReal::getRentalCost()
{
    return rentalCost;
}

double RentalReal::getTotalCost()
{
    return depositAmount + rentalCost;
}

std::string RentalReal::getStatus()
{
    return status;
}

void RentalReal::setCalculatedAmounts(FinancialCalculator* calculator, int days)
{
    if (calculator != nullptr) {
        depositAmount = calculator->calculateDeposit(items);
        rentalCost = calculator->calculateRentalCost(items, days);
    }
}

double RentalReal::closeRental(double overdueFine)
{
    status = "closed";
    return rentalCost + overdueFine;
}

