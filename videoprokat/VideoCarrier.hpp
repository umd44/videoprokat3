#pragma once
#include <string>

class VideoCarrier
{
public:
    VideoCarrier();
    VideoCarrier(int inventoryNumber,
                 const std::string& title,
                 const std::string& carrierType,
                 const std::string& genre,
                 double rentalPricePerDay,
                 double fullPrice);
    ~VideoCarrier() = default;

    int getInventoryNumber() const;
    const std::string& getTitle() const;
    const std::string& getCarrierType() const;
    const std::string& getGenre() const;
    double getRentalPricePerDay() const;
    double getFullPrice() const;
    const std::string& getStatus() const;

    bool isAvailable() const;
    void markAsRented();
    void markAsAvailable();

private:
    int m_inventoryNumber;
    std::string m_title;
    std::string m_carrierType;
    std::string m_genre;
    double m_rentalPricePerDay;
    double m_fullPrice;
    std::string m_status;
};
