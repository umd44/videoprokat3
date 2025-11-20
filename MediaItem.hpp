#pragma once
#include <string>
#include <iostream>

// Базовый класс для всех медиа-элементов в системе
class MediaItem
{
public:
    friend std::ostream& operator<<(std::ostream& os, const MediaItem& item);
    
    MediaItem();
    MediaItem(int inventoryNumber, 
              const std::string& title, 
              const std::string& genre);
    
    virtual ~MediaItem() = default;
    
    int getInventoryNumber() const;
    const std::string& getTitle() const;
    const std::string& getGenre() const;
    const std::string& getStatus() const;
    
    bool isAvailable() const;
    void markAsRented();
    void markAsAvailable();
    
    virtual std::string getMediaType() const = 0;

protected:
    int m_inventoryNumber;
    std::string m_title;
    std::string m_genre;
    std::string m_status;
};

