#include "Catalog.hpp"
#include "VideoCarrier.hpp"
#include "VideoRentalException.hpp"

#include <algorithm>

void Catalog::addItem(std::shared_ptr<VideoCarrier> item)
{
    if (item) m_items.push_back(item);
}

std::shared_ptr<VideoCarrier> Catalog::findItemByNumber(int number) const
{
    for (const auto& item : m_items) {
        if (item && item->getInventoryNumber() == number) return item;
    }
    return nullptr;
}

// Пример 4: Использование throw при отсутствии элемента
std::shared_ptr<VideoCarrier> Catalog::findItemByNumberOrThrow(int number) const
{
    for (const auto& item : m_items) {
        if (item && item->getInventoryNumber() == number) {
            return item;
        }
    }
    
    // ИНСТРУКЦИЯ THROW - выбрасываем исключение, если элемент не найден
    throw ItemNotFoundException("VideoCarrier", number);
}

std::vector<std::shared_ptr<VideoCarrier>> Catalog::findItemsByTitle(const std::string& title) const
{
    std::vector<std::shared_ptr<VideoCarrier>> result;
    for (const auto& item : m_items) {
        if (item && item->getTitle() == title) result.push_back(item);
    }
    return result;
}

std::vector<std::shared_ptr<VideoCarrier>> Catalog::getAvailableItems() const
{
    std::vector<std::shared_ptr<VideoCarrier>> result;
    for (const auto& item : m_items) {
        if (item && item->isAvailable()) result.push_back(item);
    }
    return result;
}
