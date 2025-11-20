#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class VideoCarrier;
class Client;
class FinancialCalculator;

// Представляет одну аренду с клиентом и списком носителей
class Rental
{
public:
    friend std::ostream& operator<<(std::ostream& os, const Rental& rental);
    
    // Сравнение аренд по стоимости
    bool operator>(const Rental& other) const;
    // Добавление носителя к аренде
    Rental& operator+=(std::shared_ptr<VideoCarrier> item);
    // Доступ к носителям по индексу
    std::shared_ptr<VideoCarrier> operator[](size_t index) const;
    Rental& setStatus(const std::string& status);
    
    Rental();
    Rental(int rentalId,
           std::shared_ptr<Client> client,
           const std::vector<std::shared_ptr<VideoCarrier>>& items,
           const std::string& rentalDate,
           const std::string& plannedReturnDate);
    // Конструктор копирования
    Rental(const Rental& other);
    ~Rental() = default;

    int getRentalId() const;
    std::shared_ptr<Client> getClient() const;
    const std::vector<std::shared_ptr<VideoCarrier>>& getItems() const;
    const std::string& getRentalDate() const;
    const std::string& getPlannedReturnDate() const;
    double getDepositAmount() const;
    double getRentalCost() const;
    const std::string& getStatus() const;

    void setCalculatedAmounts(const FinancialCalculator& calc, int days);
    double closeRental(double overdueFine);

private:
    int m_rentalId;
    std::shared_ptr<Client> m_client;
    std::vector<std::shared_ptr<VideoCarrier>> m_items;
    std::string m_rentalDate;
    std::string m_plannedReturnDate;
    double m_depositAmount;
    double m_rentalCost;
    std::string m_status;
};
