#include "RentalManager.hpp"
#include "Rental.hpp"
#include "Client.hpp"
#include "VideoCarrier.hpp"
#include "FinancialCalculator.hpp"
#include "VideoRentalException.hpp"

// Создает менеджер с собственным калькулятором
RentalManager::RentalManager()
    : m_calculator(std::make_unique<FinancialCalculator>())
{
}

RentalManager::~RentalManager()
{
}

// Создает новую аренду с проверкой всех условий
std::shared_ptr<Rental> RentalManager::createRental(std::shared_ptr<Client> client, const std::vector<std::shared_ptr<VideoCarrier>>& items, int days,
                                    const std::string& rentalDate, const std::string& plannedReturnDate)
{
    if (!client) {
        throw InvalidDataException("client", "клиент не может быть nullptr");
    }
    
    if (items.empty()) {
        throw InvalidDataException("items", "список носителей не может быть пустым");
    }
    
    if (days <= 0) {
        throw InvalidDataException("days", "количество дней должно быть положительным");
    }
    
    if (client->getIsBlacklisted()) {
        throw InvalidDataException("client", "клиент находится в черном списке");
    }
    
    // Генерируем уникальный ID для аренды
    static int nextId = 1;
    auto rental = std::make_shared<Rental>(nextId++, client, items, rentalDate, plannedReturnDate);
    rental->setCalculatedAmounts(*m_calculator, days);
    
    // Помечаем все носители как арендованные
    for (const auto& item : items) {
        if (item) item->markAsRented();
    }
    
    m_activeRentals.push_back(rental);
    return rental;
}

// Обрабатывает возврат аренды, освобождает носители и считает итоговую сумму
double RentalManager::processReturn(std::shared_ptr<Rental> rental, int overdueDays)
{
    if (!rental) return 0.0;
    
    double fine = m_calculator->calculateOverdueFine(overdueDays);
    
    // Освобождаем все носители
    for (const auto& item : rental->getItems()) {
        if (item) item->markAsAvailable();
    }
    
    double total = rental->closeRental(fine);
    return total;
}

std::vector<std::shared_ptr<Rental>> RentalManager::getOverdueRentals(const std::string& /*currentDate*/) const
{
    std::vector<std::shared_ptr<Rental>> result;
    for (const auto& r : m_activeRentals) {
        if (r && r->getStatus() == std::string("active")) {
            result.push_back(r);
        }
    }
    return result;
}
