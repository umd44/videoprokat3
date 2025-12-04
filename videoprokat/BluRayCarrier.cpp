#include "BluRayCarrier.hpp"
#include <iostream>

BluRayCarrier::BluRayCarrier()
    : VideoCarrier(),
      m_is4K(false),
      m_hasHDR(false),
      m_storageGB(25)
{
}

BluRayCarrier::BluRayCarrier(int inventoryNumber,
                             const std::string& title,
                             const std::string& genre,
                             double rentalPricePerDay,
                             double fullPrice,
                             bool is4K,
                             bool hasHDR)
    : VideoCarrier(inventoryNumber, title, "BluRay", genre, rentalPricePerDay, fullPrice),
      m_is4K(is4K),
      m_hasHDR(hasHDR),
      m_storageGB(is4K ? 50 : 25)
{
    std::cout << "Создан BluRay носитель: " << title 
              << (is4K ? " (4K)" : "") << (hasHDR ? " (HDR)" : "") << "\n";
}

BluRayCarrier::~BluRayCarrier()
{
    std::cout << "Деструктор BluRayCarrier для " << m_title << "\n";
}

void BluRayCarrier::markAsRented()
{
    m_status = "rented";
    std::cout << "BluRay диск " << (m_is4K ? "4K " : "") 
              << "арендован: " << m_title << "\n";
}

void BluRayCarrier::markAsAvailable()
{
    std::cout << "BluRay возвращен: " << m_title << "\n";
    VideoCarrier::markAsAvailable();
}

double BluRayCarrier::calculatePremiumPrice() const
{
    double basePrice = m_rentalPricePerDay;
    if (m_is4K) basePrice *= 1.5;
    if (m_hasHDR) basePrice *= 1.2;
    return basePrice;
}

bool BluRayCarrier::isIs4K() const
{
    return m_is4K;
}

bool BluRayCarrier::hasHDR() const
{
    return m_hasHDR;
}

int BluRayCarrier::getStorageGB() const
{
    return m_storageGB;
}
