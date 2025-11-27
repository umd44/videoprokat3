#pragma once
#include <string>
#include <iostream>
#include "MediaItem.hpp"

// Видеоноситель (диск/кассета) - производный класс от MediaItem
class VideoCarrier : public MediaItem
{
public:
    // Дружественная функция для вывода объекта в поток
    // Позволяет использовать: std::cout << videoCarrier;
    friend std::ostream& operator<<(std::ostream& os, const VideoCarrier& carrier);
    
    // Конструкторы производного класса
    // Конструктор по умолчанию - вызывает конструктор базового класса
    VideoCarrier();
    
    // Конструктор с параметрами - ВЫЗЫВАЕТ конструктор базового класса MediaItem
    // Демонстрация вызова конструктора базового класса из конструктора дочернего
    VideoCarrier(int inventoryNumber,
                 const std::string& title,
                 const std::string& carrierType,
                 const std::string& genre,
                 double rentalPricePerDay,
                 double fullPrice);
    
    // Виртуальный деструктор
    virtual ~VideoCarrier() = default;
    
    // Переопределение чисто виртуального метода из базового класса
    virtual std::string getMediaType() const override;
    
    // Специфичные для VideoCarrier методы (базовые методы наследуются)
    // Тип носителя (DVD/BluRay)
    const std::string& getCarrierType() const;
    double getRentalPricePerDay() const;
    double getFullPrice() const;
    VideoCarrier& alignPricingWith(const VideoCarrier& reference);

    // Статическое API для демонстрации единых настроек цены
    static void configureDefaultPricing(double rentalPricePerDay, double fullPrice);
    static double getDefaultRentalPricePerDay();
    static double getDefaultFullPrice();

private:
    // Только специфичные для VideoCarrier поля
    // Базовые поля (m_inventoryNumber, m_title, m_genre, m_status) наследуются из MediaItem
    std::string m_carrierType;
    double m_rentalPricePerDay;
    double m_fullPrice;

    static double s_defaultRentalPricePerDay;
    static double s_defaultFullPrice;
};
