#include "DVDCarrier.hpp"
#include <iostream>

DVDCarrier::DVDCarrier()
    : VideoCarrier(),
      m_diskNumber(1),
      m_region("ALL"),
      m_subtitles(new std::vector<std::string>())
{
}

DVDCarrier::DVDCarrier(int inventoryNumber,
                       const std::string& title,
                       const std::string& genre,
                       double rentalPricePerDay,
                       double fullPrice,
                       int diskNumber,
                       const std::string& region)
    : VideoCarrier(inventoryNumber, title, "DVD", genre, rentalPricePerDay, fullPrice),
      m_diskNumber(diskNumber),
      m_region(region),
      m_subtitles(new std::vector<std::string>())
{
    std::cout << "Создан DVD носитель: " << title << " (диск #" << diskNumber << ")\n";
}

DVDCarrier::DVDCarrier(const DVDCarrier& other)
    : VideoCarrier(other),
      m_diskNumber(other.m_diskNumber),
      m_region(other.m_region),
      m_subtitles(new std::vector<std::string>(*other.m_subtitles))
{
    std::cout << "Конструктор копирования DVDCarrier (глубокое копирование)\n";
}

DVDCarrier::~DVDCarrier()
{
    std::cout << "Деструктор DVDCarrier для " << m_title << "\n";
    delete m_subtitles;
}

void DVDCarrier::markAsRented()
{
    std::cout << "DVD диск #" << m_diskNumber << " арендуется\n";
    m_status = "rented";
}

void DVDCarrier::applyDVDDiscount()
{
    m_rentalPricePerDay *= 0.9;
}

void DVDCarrier::addSubtitle(const std::string& language)
{
    m_subtitles->push_back(language);
}

const std::vector<std::string>& DVDCarrier::getSubtitles() const
{
    return *m_subtitles;
}

int DVDCarrier::getDiskNumber() const
{
    return m_diskNumber;
}

const std::string& DVDCarrier::getRegion() const
{
    return m_region;
}

DVDCarrier* DVDCarrier::shallowClone() const
{
    DVDCarrier* clone = new DVDCarrier();
    clone->m_inventoryNumber = this->m_inventoryNumber;
    clone->m_title = this->m_title;
    clone->m_carrierType = this->m_carrierType;
    clone->m_genre = this->m_genre;
    clone->m_rentalPricePerDay = this->m_rentalPricePerDay;
    clone->m_fullPrice = this->m_fullPrice;
    clone->m_status = this->m_status;
    
    clone->m_diskNumber = this->m_diskNumber;
    clone->m_region = this->m_region;
    
    delete clone->m_subtitles;
    clone->m_subtitles = this->m_subtitles;
    
    std::cout << "Поверхностное клонирование DVDCarrier\n";
    return clone;
}

DVDCarrier* DVDCarrier::deepClone() const
{
    return new DVDCarrier(*this);
}
