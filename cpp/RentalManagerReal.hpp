#pragma once
#include "RentalManager.hpp"
#include <vector>
#include <string>

class Client;
class VideoCarrier;
class Rental;

/**
 * Реализация класса RentalManager.
 * Содержит конкретную реализацию всех методов абстрактного класса RentalManager.
 */
class RentalManagerReal : public RentalManager
{
private:
    static int nextId;

public:
    /**
     * Конструктор по умолчанию.
     * Инициализирует список активных аренд и калькулятор.
     */
    RentalManagerReal();

    virtual ~RentalManagerReal();

    Rental* createRental(Client* client, const std::vector<VideoCarrier*>& items, int days,
                         const std::string& rentalDate, const std::string& plannedReturnDate) override;

    double processReturn(Rental* rental, int overdueDays) override;

    double processReturnWithDamage(Rental* rental, int overdueDays, 
                                   VideoCarrier* damagedItem, 
                                   const std::string& damageType, 
                                   double damageCompensation) override;

    std::vector<Rental*> getOverdueRentals(const std::string& currentDate) override;

    std::vector<Rental*> getActiveRentals() override;

    void close() override;
};



