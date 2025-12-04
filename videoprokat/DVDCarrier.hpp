#pragma once
#include "VideoCarrier.hpp"
#include <vector>

/**
 * DVD-носитель - производный класс от VideoCarrier.
 * Демонстрирует клонирование (поверхностное и глубокое).
 */
class DVDCarrier : public VideoCarrier
{
public:
    DVDCarrier();
    
    /**
     * Конструктор с параметрами - вызывает конструктор базового класса.
     */
    DVDCarrier(int inventoryNumber,
               const std::string& title,
               const std::string& genre,
               double rentalPricePerDay,
               double fullPrice,
               int diskNumber,
               const std::string& region);
    
    /**
     * Конструктор копирования для глубокого клонирования.
     */
    DVDCarrier(const DVDCarrier& other);
    
    /**
     * Виртуальный деструктор.
     */
    virtual ~DVDCarrier();
    
    /**
     * Виртуальная функция - перегрузка базового метода.
     */
    virtual void markAsRented() override;
    
    void addSubtitle(const std::string& language);
    const std::vector<std::string>& getSubtitles() const;
    
    int getDiskNumber() const;
    const std::string& getRegion() const;
    
    /**
     * Поверхностное клонирование - использует copy constructor по умолчанию.
     */
    DVDCarrier* shallowClone() const;
    
    /**
     * Глубокое клонирование - создает копию вектора субтитров.
     */
    DVDCarrier* deepClone() const;

protected:
    /**
     * Защищенный метод - демонстрация использования protected.
     */
    void applyDVDDiscount();
    
    int m_diskNumber;
    std::string m_region;
    std::vector<std::string>* m_subtitles;
};
