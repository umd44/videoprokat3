#pragma once
#include <string>
#include <iostream>

// Базовый класс для всех медиа-элементов
class MediaItem
{
public:
    // Дружественная функция для вывода объекта в поток
    friend std::ostream& operator<<(std::ostream& os, const MediaItem& item);
    
    // Конструкторы базового класса
    MediaItem();  // Конструктор по умолчанию
    MediaItem(int inventoryNumber, 
              const std::string& title, 
              const std::string& genre);
    
    // Виртуальный деструктор (важно для полиморфизма)
    virtual ~MediaItem() = default;
    
    // Перегрузка операторов сравнения
    bool operator==(const MediaItem& other) const;
    bool operator<(const MediaItem& other) const;
    
    // Геттеры базового класса
    int getInventoryNumber() const;
    const std::string& getTitle() const;
    const std::string& getGenre() const;
    const std::string& getStatus() const;
    
    // Базовые методы
    bool isAvailable() const;
    void markAsRented();
    void markAsAvailable();
    
    // Виртуальный метод для получения типа (для полиморфизма)
    virtual std::string getMediaType() const = 0;  // Чисто виртуальный метод

protected:
    // Защищенные члены - доступны производным классам
    int m_inventoryNumber;
    std::string m_title;
    std::string m_genre;
    std::string m_status;
};

