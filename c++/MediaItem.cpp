#include "MediaItem.hpp"

// Конструктор по умолчанию базового класса
MediaItem::MediaItem()
    : m_inventoryNumber(0),
      m_status("available")
{
}

// Конструктор с параметрами базового класса
MediaItem::MediaItem(int inventoryNumber, 
                     const std::string& title, 
                     const std::string& genre)
    : m_inventoryNumber(inventoryNumber),
      m_title(title),
      m_genre(genre),
      m_status("available")
{
}

// Перегрузка оператора равенства
bool MediaItem::operator==(const MediaItem& other) const
{
    return m_inventoryNumber == other.m_inventoryNumber;
}

// Перегрузка оператора "меньше"
bool MediaItem::operator<(const MediaItem& other) const
{
    return m_inventoryNumber < other.m_inventoryNumber;
}

// Геттеры
int MediaItem::getInventoryNumber() const { return m_inventoryNumber; }
const std::string& MediaItem::getTitle() const { return m_title; }
const std::string& MediaItem::getGenre() const { return m_genre; }
const std::string& MediaItem::getStatus() const { return m_status; }

// Методы управления статусом
bool MediaItem::isAvailable() const
{
    return m_status == "available";
}

void MediaItem::markAsRented()
{
    m_status = "rented";
}

void MediaItem::markAsAvailable()
{
    m_status = "available";
}

// Реализация дружественной функции operator<< для базового класса
std::ostream& operator<<(std::ostream& os, const MediaItem& item)
{
    os << "MediaItem[#" << item.m_inventoryNumber
       << ": \"" << item.m_title
       << "\" (" << item.m_genre
       << "), статус: " << item.m_status << "]";
    return os;
}

