#include "VideoCarrier.hpp"
#include <iostream>

VideoCarrier::VideoCarrier()
    : m_inventoryNumber(0),
      m_rentalPricePerDay(0.0),
      m_fullPrice(0.0),
      m_status("available")
{
}

VideoCarrier::VideoCarrier(int inventoryNumber,
                           const std::string& title,
                           const std::string& carrierType,
                           const std::string& genre,
                           double rentalPricePerDay,
                           double fullPrice)
    : m_inventoryNumber(inventoryNumber),
      m_title(title),
      m_carrierType(carrierType),
      m_genre(genre),
      m_rentalPricePerDay(rentalPricePerDay),
      m_fullPrice(fullPrice),
      m_status("available")
{
}

VideoCarrier::~VideoCarrier()
{
    std::cout << "Деструктор VideoCarrier для " << m_title << "\n";
}

int VideoCarrier::getInventoryNumber() const { return m_inventoryNumber; }
const std::string& VideoCarrier::getTitle() const { return m_title; }
const std::string& VideoCarrier::getCarrierType() const { return m_carrierType; }
const std::string& VideoCarrier::getGenre() const { return m_genre; }
double VideoCarrier::getRentalPricePerDay() const { return m_rentalPricePerDay; }
double VideoCarrier::getFullPrice() const { return m_fullPrice; }
const std::string& VideoCarrier::getStatus() const { return m_status; }

bool VideoCarrier::isAvailable() const
{
    return m_status == "available";
}

void VideoCarrier::markAsRented()
{
    m_status = "rented";
}

void VideoCarrier::markAsAvailable()
{
    m_status = "available";
}
