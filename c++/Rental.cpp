#include "Rental.hpp"
#include "VideoCarrier.hpp"
#include "Client.hpp"
#include "FinancialCalculator.hpp"

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

// Пример 6: Использование this для проверки сравнения объекта с самим собой
// Оптимизация: если сравниваем объект с самим собой, сразу возвращаем true
bool Rental::operator==(const Rental& other) const
{
    // Используем this для проверки: не сравниваем ли объект с самим собой?
    if (this == &other) {  // Сравниваем указатели - если это один и тот же объект
        return true;       // Сразу возвращаем true (оптимизация производительности)
    }
    // Если это разные объекты, сравниваем по логике (по ID)
    return m_rentalId == other.m_rentalId;
}

// Перегрузка оператора "меньше"
// Используется для сортировки аренд по ID
bool Rental::operator<(const Rental& other) const
{
    return m_rentalId < other.m_rentalId;
}

// Пример 7: Возврат ссылки на себя через this для цепочки вызовов (operator+=)
// Использование this позволяет создавать цепочки: rental += item1 += item2
Rental& Rental::operator+=(std::shared_ptr<VideoCarrier> item)
{
    if (item && m_status == "active") {
        // Проверяем, нет ли уже такого носителя
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
    // Возвращаем ссылку на текущий объект через разыменование this
    // Это позволяет использовать оператор в цепочке: rental += item1 += item2
    return *this;  // *this - разыменовываем указатель this, получаем ссылку на объект
}

// Пример 8: Method chaining - возврат ссылки на себя через this
// Позволяет создавать цепочки вызовов: rental.setStatus("closed").closeRental(0)
Rental& Rental::setStatus(const std::string& status)
{
    m_status = status;
    return *this;  // Возвращаем ссылку на текущий объект через разыменование this
}

// Реализация дружественной функции operator<<
// Имеет прямой доступ к приватным членам для эффективного форматирования
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
