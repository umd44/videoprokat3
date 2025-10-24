#pragma once
#include <string>
#include <vector>

class VideoCarrier;
class Client;
class FinancialCalculator;

// Одна аренда
class Rental
{
public:
    // Пустая аренда
    Rental();
    // Аренда с основными данными
    Rental(int rentalId,
           Client* client,
           const std::vector<VideoCarrier*>& items,
           const std::string& rentalDate,
           const std::string& plannedReturnDate);
    ~Rental() = default;

    // Идентификатор аренды
    int getRentalId() const;
    // Клиент
    Client* getClient() const;
    // Список носителей
    const std::vector<VideoCarrier*>& getItems() const;
    // Дата выдачи
    const std::string& getRentalDate() const;
    // Плановая дата возврата
    const std::string& getPlannedReturnDate() const;
    // Залог
    double getDepositAmount() const;
    // Стоимость аренды
    double getRentalCost() const;
    // Статус (active/closed)
    const std::string& getStatus() const;

    // Рассчитать суммы по калькулятору
    void setCalculatedAmounts(const FinancialCalculator& calc, int days);
    // Закрыть аренду и вернуть итог к оплате
    double closeRental(double overdueFine);

private:
    int m_rentalId;
    Client* m_client;
    std::vector<VideoCarrier*> m_items;
    std::string m_rentalDate;
    std::string m_plannedReturnDate;
    double m_depositAmount;
    double m_rentalCost;
    std::string m_status;
};
