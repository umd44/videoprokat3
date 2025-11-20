#include "VideoCarrier.hpp"

double VideoCarrier::s_defaultRentalPricePerDay = 25.0;
double VideoCarrier::s_defaultFullPrice = 250.0;

VideoCarrier::VideoCarrier()
    : MediaItem(),
      m_carrierType(""),
      m_rentalPricePerDay(s_defaultRentalPricePerDay),
      m_fullPrice(s_defaultFullPrice)
{
}

VideoCarrier::VideoCarrier(int inventoryNumber,
                           const std::string& title,
                           const std::string& carrierType,
                           const std::string& genre,
                           double rentalPricePerDay,
                           double fullPrice)
    : MediaItem(inventoryNumber, title, genre),
      m_carrierType(carrierType),
      m_rentalPricePerDay(rentalPricePerDay),
      m_fullPrice(fullPrice)
{
}

// Конструктор копирования - создает копию носителя
VideoCarrier::VideoCarrier(const VideoCarrier& other)
    : MediaItem(other.m_inventoryNumber, other.m_title, other.m_genre),
      m_carrierType(other.m_carrierType),
      m_rentalPricePerDay(other.m_rentalPricePerDay),
      m_fullPrice(other.m_fullPrice)
{
    m_status = other.m_status;
}

std::string VideoCarrier::getMediaType() const
{
    return "VideoCarrier";
}

const std::string& VideoCarrier::getCarrierType() const { return m_carrierType; }
double VideoCarrier::getRentalPricePerDay() const { return m_rentalPricePerDay; }
double VideoCarrier::getFullPrice() const { return m_fullPrice; }

VideoCarrier& VideoCarrier::alignPricingWith(const VideoCarrier& reference)
{
    if (this == &reference) {
        return *this;
    }
    this->m_rentalPricePerDay = reference.m_rentalPricePerDay;
    this->m_fullPrice = reference.m_fullPrice;
    return *this;
}

void VideoCarrier::configureDefaultPricing(double rentalPricePerDay, double fullPrice)
{
    if (rentalPricePerDay > 0.0) {
        s_defaultRentalPricePerDay = rentalPricePerDay;
    }
    if (fullPrice > 0.0) {
        s_defaultFullPrice = fullPrice;
    }
}

double VideoCarrier::getDefaultRentalPricePerDay()
{
    return s_defaultRentalPricePerDay;
}

double VideoCarrier::getDefaultFullPrice()
{
    return s_defaultFullPrice;
}

// Складывает цены аренды двух носителей (удобно для расчета общей стоимости)
double VideoCarrier::operator+(const VideoCarrier& other) const
{
    return m_rentalPricePerDay + other.m_rentalPricePerDay;
}

std::ostream& operator<<(std::ostream& os, const VideoCarrier& carrier)
{
    os << "VideoCarrier[#"
       << carrier.m_inventoryNumber
       << ": \"" << carrier.m_title
       << "\" (" << carrier.m_carrierType
       << ", " << carrier.m_genre
       << "), цена: " << carrier.m_rentalPricePerDay
       << "/день, полная: " << carrier.m_fullPrice
       << ", статус: " << carrier.m_status << "]";
    return os;
}
