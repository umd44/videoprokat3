#pragma once
#include <string>
#include <iostream>
#include "MediaItem.hpp"

// Видеоноситель (DVD, BluRay и т.д.) - конкретная реализация MediaItem
class VideoCarrier : public MediaItem
{
public:
    friend std::ostream& operator<<(std::ostream& os, const VideoCarrier& carrier);
    
    VideoCarrier();
    VideoCarrier(int inventoryNumber,
                 const std::string& title,
                 const std::string& carrierType,
                 const std::string& genre,
                 double rentalPricePerDay,
                 double fullPrice);
    // Конструктор копирования
    VideoCarrier(const VideoCarrier& other);
    
    virtual ~VideoCarrier() = default;
    
    virtual std::string getMediaType() const override;
    
    const std::string& getCarrierType() const;
    double getRentalPricePerDay() const;
    double getFullPrice() const;
    VideoCarrier& alignPricingWith(const VideoCarrier& reference);
    
    // Сложение цен аренды двух носителей
    double operator+(const VideoCarrier& other) const;

    static void configureDefaultPricing(double rentalPricePerDay, double fullPrice);
    static double getDefaultRentalPricePerDay();
    static double getDefaultFullPrice();

private:
    std::string m_carrierType;
    double m_rentalPricePerDay;
    double m_fullPrice;

    static double s_defaultRentalPricePerDay;
    static double s_defaultFullPrice;
};
