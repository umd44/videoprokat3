#pragma once
#include "VideoCarrier.hpp"

/**
 * Реализация класса VideoCarrier.
 * Содержит конкретную реализацию всех методов абстрактного класса VideoCarrier.
 */
class VideoCarrierReal : public VideoCarrier
{
public:
    /**
     * Конструктор по умолчанию.
     */
    VideoCarrierReal();

    /**
     * Конструктор с параметрами.
     */
    VideoCarrierReal(int inventoryNumber, const std::string& title, const std::string& carrierType, const std::string& genre,
                     double rentalPricePerDay, double fullPrice);

    virtual ~VideoCarrierReal();

    int getInventoryNumber() override;
    std::string getTitle() override;
    std::string getCarrierType() override;
    std::string getGenre() override;
    double getRentalPricePerDay() override;
    double getFullPrice() override;
    std::string getStatus() override;
    bool isAvailable() override;
    void markAsRented() override;
    void markAsAvailable() override;
    int getReleaseYear() override;
    std::string getDirector() override;
    std::string getAgeRating() override;
    std::string getDescription() override;
    int getTotalRentals() override;
    void setReleaseYear(int year) override;
    void setDirector(const std::string& director) override;
    void setAgeRating(const std::string& ageRating) override;
    void setDescription(const std::string& description) override;
    void incrementRentals() override;
    void setStatus(const std::string& status) override;
};



