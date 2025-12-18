#pragma once
#include "Rental.hpp"
#include <vector>

class Client;
class VideoCarrier;
class FinancialCalculator;

/**
 * Реализация класса Rental.
 * Содержит конкретную реализацию всех методов абстрактного класса Rental.
 */
class RentalReal : public Rental
{
public:
    /**
     * Конструктор по умолчанию.
     */
    RentalReal();

    /**
     * Конструктор с параметрами.
     */
    RentalReal(int rentalId, Client* client, const std::vector<VideoCarrier*>& items,
               const std::string& rentalDate, const std::string& plannedReturnDate);

    virtual ~RentalReal();

    int getRentalId() override;
    Client* getClient() override;
    std::vector<VideoCarrier*> getItems() override;
    std::string getRentalDate() override;
    std::string getPlannedReturnDate() override;
    double getDepositAmount() override;
    double getRentalCost() override;
    double getTotalCost() override;
    std::string getStatus() override;
    void setCalculatedAmounts(FinancialCalculator* calculator, int days) override;
    double closeRental(double overdueFine) override;
};



