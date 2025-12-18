#pragma once
#include <vector>
#include <string>

class Client;
class VideoCarrier;
class Rental;
class FinancialCalculator;

/**
 * Абстрактный класс, описывающий менеджер аренды.
 * Содержит базовую структуру и методы для управления арендами.
 */
class RentalManager
{
protected:
    std::vector<Rental*> activeRentals;
    FinancialCalculator* calculator;

    /**
     * Конструктор по умолчанию.
     */
    RentalManager();

public:
    virtual ~RentalManager() = default;

    /**
     * Создать новую аренду.
     */
    virtual Rental* createRental(Client* client, const std::vector<VideoCarrier*>& items, int days,
                                 const std::string& rentalDate, const std::string& plannedReturnDate) = 0;

    /**
     * Обработать возврат аренды.
     */
    virtual double processReturn(Rental* rental, int overdueDays) = 0;

    /**
     * Обработать возврат аренды с учетом повреждений.
     */
    virtual double processReturnWithDamage(Rental* rental, int overdueDays, 
                                           VideoCarrier* damagedItem, 
                                           const std::string& damageType, 
                                           double damageCompensation) = 0;

    /**
     * Получить список просроченных аренд.
     */
    virtual std::vector<Rental*> getOverdueRentals(const std::string& currentDate) = 0;

    /**
     * Получить список всех активных аренд.
     */
    virtual std::vector<Rental*> getActiveRentals() = 0;

    /**
     * Закрыть менеджер и освободить ресурсы.
     */
    virtual void close() = 0;
};
