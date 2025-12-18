#pragma once
#include <string>
#include <vector>

class Client;
class VideoCarrier;
class FinancialCalculator;

/**
 * Абстрактный класс, описывающий аренду.
 * Содержит базовую структуру и методы для работы с арендой.
 */
class Rental
{
protected:
    int rentalId;
    Client* client;
    std::vector<VideoCarrier*> items;
    std::string rentalDate;
    std::string plannedReturnDate;
    double depositAmount;
    double rentalCost;
    std::string status;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    Rental();

    /**
     * Конструктор с параметрами.
     */
    Rental(int rentalId, Client* client, const std::vector<VideoCarrier*>& items,
           const std::string& rentalDate, const std::string& plannedReturnDate);

public:
    virtual ~Rental() = default;

    /**
     * Получить идентификатор аренды.
     */
    virtual int getRentalId() = 0;

    /**
     * Получить клиента.
     */
    virtual Client* getClient() = 0;

    /**
     * Получить список носителей.
     */
    virtual std::vector<VideoCarrier*> getItems() = 0;

    /**
     * Получить дату выдачи.
     */
    virtual std::string getRentalDate() = 0;

    /**
     * Получить плановую дату возврата.
     */
    virtual std::string getPlannedReturnDate() = 0;

    /**
     * Получить сумму залога.
     */
    virtual double getDepositAmount() = 0;

    /**
     * Получить стоимость аренды.
     */
    virtual double getRentalCost() = 0;

    /**
     * Получить итоговую сумму к оплате (залог + аренда).
     */
    virtual double getTotalCost() = 0;

    /**
     * Получить статус аренды.
     */
    virtual std::string getStatus() = 0;

    /**
     * Установить рассчитанные суммы с помощью калькулятора.
     */
    virtual void setCalculatedAmounts(FinancialCalculator* calculator, int days) = 0;

    /**
     * Закрыть аренду и вернуть итоговую сумму к оплате.
     */
    virtual double closeRental(double overdueFine) = 0;
};
