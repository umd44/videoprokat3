#include "MediaItem.hpp"

MediaItem::MediaItem()
    : m_inventoryNumber(0),
      m_status("available")
{
}

MediaItem::MediaItem(int inventoryNumber, 
                     const std::string& title, 
                     const std::string& genre)
    : m_inventoryNumber(inventoryNumber),
      m_title(title),
      m_genre(genre),
      m_status("available")
{
}

int MediaItem::getInventoryNumber() const { return m_inventoryNumber; }
const std::string& MediaItem::getTitle() const { return m_title; }
const std::string& MediaItem::getGenre() const { return m_genre; }
const std::string& MediaItem::getStatus() const { return m_status; }

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

std::ostream& operator<<(std::ostream& os, const MediaItem& item)
{
    os << "MediaItem[#" << item.m_inventoryNumber
       << ": \"" << item.m_title
       << "\" (" << item.m_genre
       << "), статус: " << item.m_status << "]";
    return os;
}

