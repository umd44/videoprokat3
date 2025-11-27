#pragma once
#include <string>
#include <stdexcept>

// Базовый класс исключений для видеопроката
class VideoRentalException : public std::runtime_error
{
public:
    VideoRentalException(const std::string& message) 
        : std::runtime_error(message) 
    {
    }
};

// Исключение для недостатка средств
class InsufficientFundsException : public VideoRentalException
{
public:
    InsufficientFundsException(double required, double available)
        : VideoRentalException("Недостаточно средств. Требуется: " + 
                              std::to_string(required) + 
                              ", доступно: " + std::to_string(available)),
          m_required(required),
          m_available(available)
    {
    }
    
    double getRequired() const { return m_required; }
    double getAvailable() const { return m_available; }

private:
    double m_required;
    double m_available;
};

// Исключение для некорректных данных
class InvalidDataException : public VideoRentalException
{
public:
    InvalidDataException(const std::string& field, const std::string& reason)
        : VideoRentalException("Некорректные данные: " + field + " - " + reason),
          m_field(field),
          m_reason(reason)
    {
    }
    
    const std::string& getField() const { return m_field; }
    const std::string& getReason() const { return m_reason; }

private:
    std::string m_field;
    std::string m_reason;
};

// Исключение для отсутствия элемента
class ItemNotFoundException : public VideoRentalException
{
public:
    ItemNotFoundException(const std::string& itemType, int id)
        : VideoRentalException("Элемент не найден: " + itemType + " с ID " + std::to_string(id)),
          m_itemType(itemType),
          m_id(id)
    {
    }
    
    const std::string& getItemType() const { return m_itemType; }
    int getId() const { return m_id; }

private:
    std::string m_itemType;
    int m_id;
};



