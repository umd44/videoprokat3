#pragma once
#include <string>

// Видеоноситель (диск/кассета)
class VideoCarrier
{
public:
    // Пустой носитель
    VideoCarrier();
    // Носитель с данными
    VideoCarrier(int inventoryNumber,
                 const std::string& title,
                 const std::string& carrierType,
                 const std::string& genre,
                 double rentalPricePerDay,
                 double fullPrice);
    
    /**
     * Виртуальный деструктор для корректного удаления производных классов.
     */
    virtual ~VideoCarrier();

    // Инвентарный номер
    int getInventoryNumber() const;
    // Название
    const std::string& getTitle() const;
    // Тип носителя (DVD/BluRay)
    const std::string& getCarrierType() const;
    // Жанр
    const std::string& getGenre() const;
    // Цена аренды за день
    double getRentalPricePerDay() const;
    // Полная стоимость
    double getFullPrice() const;
    // Статус (available/rented)
    const std::string& getStatus() const;

    // Доступен ли для аренды
    bool isAvailable() const;
    
    /**
     * Виртуальные методы для демонстрации полиморфизма.
     */
    // Пометить как арендованный
    virtual void markAsRented();
    // Пометить как доступный
    virtual void markAsAvailable();

protected:
    int m_inventoryNumber;
    std::string m_title;
    std::string m_carrierType;
    std::string m_genre;
    double m_rentalPricePerDay;
    double m_fullPrice;
    std::string m_status;
};
