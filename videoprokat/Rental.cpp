#include "Rental.hpp"
#include "VideoCarrier.hpp"
#include "FinancialCalculator.hpp"

Rental::Rental()
    : m_rentalId(0), m_client(nullptr), m_depositAmount(0.0), m_rentalCost(0.0), m_status("active")
{
}

Rental::Rental(int rentalId,
               Client* client,
               const std::vector<VideoCarrier*>& items,
               const std::string& rentalDate,
               const std::string& plannedReturnDate)
    : m_rentalId(rentalId),
      m_client(client),
      m_items(items),
      m_rentalDate(rentalDate),
      m_plannedReturnDate(plannedReturnDate),
      m_depositAmount(0.0),
      m_rentalCost(0.0),
      m_status("active")
{
}

int Rental::getRentalId() const { return m_rentalId; }
Client* Rental::getClient() const { return m_client; }
const std::vector<VideoCarrier*>& Rental::getItems() const { return m_items; }
const std::string& Rental::getRentalDate() const { return m_rentalDate; }
const std::string& Rental::getPlannedReturnDate() const { return m_plannedReturnDate; }
double Rental::getDepositAmount() const { return m_depositAmount; }
double Rental::getRentalCost() const { return m_rentalCost; }
const std::string& Rental::getStatus() const { return m_status; }

void Rental::setCalculatedAmounts(const FinancialCalculator& calc, int days)
{
    m_depositAmount = calc.calculateDeposit(m_items);
    m_rentalCost = calc.calculateRentalCost(m_items, days);
}

double Rental::closeRental(double overdueFine)
{
    m_status = "closed";
    return m_rentalCost + overdueFine; // return amount to charge
}
