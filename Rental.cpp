#include "Rental.hpp"
#include "VideoCarrier.hpp"
#include "Client.hpp"
#include "FinancialCalculator.hpp"

// Конструктор по умолчанию - создает пустую аренду
Rental::Rental()
    : m_rentalId(0), m_client(nullptr), m_depositAmount(0.0), m_rentalCost(0.0), m_status("active")
{
}

Rental::Rental(int rentalId,
               std::shared_ptr<Client> client,
               const std::vector<std::shared_ptr<VideoCarrier>>& items,
               const std::string& rentalDate,
               const std::string& plannedReturnDate)
    : m_rentalId(rentalId),
      m_client(client),
      m_items(items),
      m_rentalDate(rentalDate),
      m_plannedReturnDate(plannedReturnDate),
      m_depositAmount(0.0),
      m_rentalCost(0.0),
      m_status("active")
{
}

// Конструктор копирования - создает копию аренды с теми же указателями
Rental::Rental(const Rental& other)
    : m_rentalId(other.m_rentalId),
      m_client(other.m_client),
      m_items(other.m_items),
      m_rentalDate(other.m_rentalDate),
      m_plannedReturnDate(other.m_plannedReturnDate),
      m_depositAmount(other.m_depositAmount),
      m_rentalCost(other.m_rentalCost),
      m_status(other.m_status)
{
}

int Rental::getRentalId() const { return m_rentalId; }
std::shared_ptr<Client> Rental::getClient() const { return m_client; }
const std::vector<std::shared_ptr<VideoCarrier>>& Rental::getItems() const { return m_items; }
const std::string& Rental::getRentalDate() const { return m_rentalDate; }
const std::string& Rental::getPlannedReturnDate() const { return m_plannedReturnDate; }
double Rental::getDepositAmount() const { return m_depositAmount; }
double Rental::getRentalCost() const { return m_rentalCost; }
const std::string& Rental::getStatus() const { return m_status; }

void Rental::setCalculatedAmounts(const FinancialCalculator& calc, int days)
{
    m_depositAmount = calc.calculateDeposit(m_items);
    m_rentalCost = calc.calculateRentalCost(m_items, days);
}

double Rental::closeRental(double overdueFine)
{
    m_status = "closed";
    return m_rentalCost + overdueFine;
}

// Сравнивает аренды по стоимости (для сортировки)
bool Rental::operator>(const Rental& other) const
{
    return m_rentalCost > other.m_rentalCost;
}

// Добавляет носитель к активной аренде, если его еще нет
Rental& Rental::operator+=(std::shared_ptr<VideoCarrier> item)
{
    if (item && m_status == "active") {
        bool exists = false;
        for (const auto& existingItem : m_items) {
            if (existingItem && existingItem->getInventoryNumber() == item->getInventoryNumber()) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            m_items.push_back(item);
            item->markAsRented();
        }
    }
    return *this;
}

Rental& Rental::setStatus(const std::string& status)
{
    m_status = status;
    return *this;
}

// Доступ к носителям по индексу, возвращает nullptr при выходе за границы
std::shared_ptr<VideoCarrier> Rental::operator[](size_t index) const
{
    if (index < m_items.size()) {
        return m_items[index];
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Rental& rental)
{
    os << "Rental[ID: " << rental.m_rentalId;
    
    // Выводим информацию о клиенте
    if (rental.m_client) {
        os << ", клиент: " << rental.m_client->getFirstName() 
           << " " << rental.m_client->getLastName()
           << " (ID: " << rental.m_client->getClientId() << ")";
    } else {
        os << ", клиент: [нет]";
    }
    
    os << ", носителей: " << rental.m_items.size()
       << ", дата выдачи: " << rental.m_rentalDate
       << ", возврат: " << rental.m_plannedReturnDate
       << ", залог: " << rental.m_depositAmount
       << ", стоимость: " << rental.m_rentalCost
       << ", статус: " << rental.m_status << "]";
    
    return os;
}
