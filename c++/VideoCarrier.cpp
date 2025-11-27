#include "VideoCarrier.hpp"

double VideoCarrier::s_defaultRentalPricePerDay = 25.0;
double VideoCarrier::s_defaultFullPrice = 250.0;

// Конструктор по умолчанию производного класса
// ВЫЗЫВАЕТ конструктор по умолчанию базового класса MediaItem()
// Порядок выполнения: сначала вызывается конструктор базового класса, потом инициализируются поля производного
VideoCarrier::VideoCarrier()
    : MediaItem(),  // ЯВНЫЙ вызов конструктора базового класса по умолчанию
      m_carrierType(""),
      m_rentalPricePerDay(s_defaultRentalPricePerDay),
      m_fullPrice(s_defaultFullPrice)
{
}

// Конструктор с параметрами производного класса
// ВЫЗЫВАЕТ конструктор базового класса MediaItem с параметрами
// Это демонстрация вызова конструктора базового класса из конструктора дочернего класса!
VideoCarrier::VideoCarrier(int inventoryNumber,
                           const std::string& title,
                           const std::string& carrierType,
                           const std::string& genre,
                           double rentalPricePerDay,
                           double fullPrice)
    : MediaItem(inventoryNumber, title, genre),  // ВЫЗОВ конструктора базового класса
      // Порядок важен: сначала базовый класс, потом производный!
      m_carrierType(carrierType),
      m_rentalPricePerDay(rentalPricePerDay),
      m_fullPrice(fullPrice)
{
    // Тело конструктора выполняется ПОСЛЕ инициализации всех полей
    // К этому моменту базовый класс уже полностью инициализирован
}

// Переопределение чисто виртуального метода из базового класса
std::string VideoCarrier::getMediaType() const
{
    return "VideoCarrier";
}

// Методы базового класса (getInventoryNumber, getTitle, getGenre, getStatus, 
// isAvailable, markAsRented, markAsAvailable, operator==, operator<) 
// наследуются из MediaItem и доступны автоматически

// Только специфичные для VideoCarrier методы
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

// Реализация дружественной функции operator<<
// Имеет доступ к защищенным членам базового класса (m_inventoryNumber, m_title, m_genre, m_status)
// и приватным членам производного класса (m_carrierType, m_rentalPricePerDay, m_fullPrice)
std::ostream& operator<<(std::ostream& os, const VideoCarrier& carrier)
{
    os << "VideoCarrier[#"
       << carrier.m_inventoryNumber  // Защищенный член базового класса - доступен через friend
       << ": \"" << carrier.m_title  // Защищенный член базового класса
       << "\" (" << carrier.m_carrierType  // Приватный член производного класса
       << ", " << carrier.m_genre  // Защищенный член базового класса
       << "), цена: " << carrier.m_rentalPricePerDay
       << "/день, полная: " << carrier.m_fullPrice
       << ", статус: " << carrier.m_status << "]";  // Защищенный член базового класса
    return os;
}
