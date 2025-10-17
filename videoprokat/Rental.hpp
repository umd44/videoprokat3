#pragma once
#include <string>
#include <vector>

class VideoCarrier;
class Client;
class FinancialCalculator;

class Rental
{
public:
    Rental();
    Rental(int rentalId,
           Client* client,
           const std::vector<VideoCarrier*>& items,
           const std::string& rentalDate,
           const std::string& plannedReturnDate);
    ~Rental() = default;

    int getRentalId() const;
    Client* getClient() const;
    const std::vector<VideoCarrier*>& getItems() const;
    const std::string& getRentalDate() const;
    const std::string& getPlannedReturnDate() const;
    double getDepositAmount() const;
    double getRentalCost() const;
    const std::string& getStatus() const;

    void setCalculatedAmounts(const FinancialCalculator& calc, int days);
    double closeRental(double overdueFine);

private:
    int m_rentalId;
    Client* m_client;
    std::vector<VideoCarrier*> m_items;
    std::string m_rentalDate;
    std::string m_plannedReturnDate;
    double m_depositAmount;
    double m_rentalCost;
    std::string m_status; // "active" or "closed"
};
