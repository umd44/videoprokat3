#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class VideoCarrier;
class Client;
class FinancialCalculator;

// Одна аренда
class Rental
{
public:
    // Дружественная функция для вывода объекта в поток
    // Позволяет использовать: std::cout << rental;
    friend std::ostream& operator<<(std::ostream& os, const Rental& rental);
    
    // Перегрузка операторов сравнения и присваивания
    // Оператор равенства: сравнивает аренды по ID (с проверкой на сравнение с самим собой через this)
    bool operator==(const Rental& other) const;
    // Оператор "меньше": для сортировки аренд по ID
    bool operator<(const Rental& other) const;
    // Оператор +=: добавляет носитель к аренде (возвращает ссылку на себя через this)
    Rental& operator+=(std::shared_ptr<VideoCarrier> item);
    // Метод для обновления статуса с возвратом ссылки на себя (method chaining)
    Rental& setStatus(const std::string& status);
    
    // Пустая аренда
    Rental();
    // Аренда с основными данными
    Rental(int rentalId,
           std::shared_ptr<Client> client,
           const std::vector<std::shared_ptr<VideoCarrier>>& items,
           const std::string& rentalDate,
           const std::string& plannedReturnDate);
    ~Rental() = default;

    // Идентификатор аренды
    int getRentalId() const;
    // Клиент
    std::shared_ptr<Client> getClient() const;
    // Список носителей
    const std::vector<std::shared_ptr<VideoCarrier>>& getItems() const;
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
    std::shared_ptr<Client> m_client;
    std::vector<std::shared_ptr<VideoCarrier>> m_items;
    std::string m_rentalDate;
    std::string m_plannedReturnDate;
    double m_depositAmount;
    double m_rentalCost;
    std::string m_status;
};
