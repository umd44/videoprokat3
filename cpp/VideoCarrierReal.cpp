#include "VideoCarrierReal.hpp"

VideoCarrierReal::VideoCarrierReal()
    : VideoCarrier()
{
}

VideoCarrierReal::VideoCarrierReal(int inventoryNumber, const std::string& title, const std::string& carrierType, const std::string& genre,
                                   double rentalPricePerDay, double fullPrice)
    : VideoCarrier(inventoryNumber, title, carrierType, genre, rentalPricePerDay, fullPrice)
{
}

VideoCarrierReal::~VideoCarrierReal()
{
}

int VideoCarrierReal::getInventoryNumber()
{
    return inventoryNumber;
}

std::string VideoCarrierReal::getTitle()
{
    return title;
}

std::string VideoCarrierReal::getCarrierType()
{
    return carrierType;
}

std::string VideoCarrierReal::getGenre()
{
    return genre;
}

double VideoCarrierReal::getRentalPricePerDay()
{
    return rentalPricePerDay;
}

double VideoCarrierReal::getFullPrice()
{
    return fullPrice;
}

std::string VideoCarrierReal::getStatus()
{
    return status;
}

bool VideoCarrierReal::isAvailable()
{
    return status == "available";
}

void VideoCarrierReal::markAsRented()
{
    status = "rented";
}

void VideoCarrierReal::markAsAvailable()
{
    status = "available";
}

int VideoCarrierReal::getReleaseYear()
{
    return releaseYear;
}

std::string VideoCarrierReal::getDirector()
{
    return director;
}

std::string VideoCarrierReal::getAgeRating()
{
    return ageRating;
}

std::string VideoCarrierReal::getDescription()
{
    return description;
}

int VideoCarrierReal::getTotalRentals()
{
    return totalRentals;
}

void VideoCarrierReal::setReleaseYear(int year)
{
    this->releaseYear = year;
}

void VideoCarrierReal::setDirector(const std::string& director)
{
    this->director = director;
}

void VideoCarrierReal::setAgeRating(const std::string& ageRating)
{
    this->ageRating = ageRating;
}

void VideoCarrierReal::setDescription(const std::string& description)
{
    this->description = description;
}

void VideoCarrierReal::incrementRentals()
{
    this->totalRentals++;
}

void VideoCarrierReal::setStatus(const std::string& status)
{
    this->status = status;
}



