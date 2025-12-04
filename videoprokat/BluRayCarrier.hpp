#pragma once
#include "VideoCarrier.hpp"

/**
 * BluRay-носитель - производный класс от VideoCarrier.
 * Демонстрирует наследование и виртуальные функции.
 */
class BluRayCarrier : public VideoCarrier
{
public:
    BluRayCarrier();
    
    /**
     * Конструктор с параметрами - вызывает конструктор базового класса.
     */
    BluRayCarrier(int inventoryNumber,
                  const std::string& title,
                  const std::string& genre,
                  double rentalPricePerDay,
                  double fullPrice,
                  bool is4K,
                  bool hasHDR);
    
    /**
     * Конструктор копирования УДАЛЕН для демонстрации.
     */
    BluRayCarrier(const BluRayCarrier&) = delete;
    
    /**
     * Виртуальный деструктор.
     */
    virtual ~BluRayCarrier();
    
    /**
     * Перегрузка виртуальной функции БЕЗ ВЫЗОВА базового метода.
     */
    virtual void markAsRented() override;
    
    /**
     * Перегрузка виртуальной функции С ВЫЗОВОМ базового метода.
     */
    virtual void markAsAvailable() override;
    
    bool isIs4K() const;
    bool hasHDR() const;
    int getStorageGB() const;

protected:
    /**
     * Защищенный метод - использует protected поля базового класса.
     */
    double calculatePremiumPrice() const;
    
    bool m_is4K;
    bool m_hasHDR;
    int m_storageGB;
};
