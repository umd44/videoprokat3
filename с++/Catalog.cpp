#include "Catalog.hpp"
#include "VideoCarrier.hpp"
#include "VideoRentalException.hpp"
#include <algorithm>

// Добавляет носитель в каталог, если он не nullptr
void Catalog::addItem(std::shared_ptr<VideoCarrier> item)
{
    if (item) {
        m_items.push_back(item);
    }
}

// Ищет носитель по инвентарному номеру, возвращает nullptr если не найден
std::shared_ptr<VideoCarrier> Catalog::findItemByNumber(int number) const
{
    for (const auto& item : m_items) {
        if (item && item->getInventoryNumber() == number) {
            return item;
        }
    }
    return nullptr;
}

// Ищет носитель по номеру, выбрасывает исключение если не найден
std::shared_ptr<VideoCarrier> Catalog::findItemByNumberOrThrow(int number) const
{
    for (const auto& item : m_items) {
        if (item && item->getInventoryNumber() == number) {
            return item;
        }
    }
    
    throw ItemNotFoundException("VideoCarrier", number);
}

std::vector<std::shared_ptr<VideoCarrier>> Catalog::findItemsByTitle(const std::string& title) const
{
    std::vector<std::shared_ptr<VideoCarrier>> result;
    for (const auto& item : m_items) {
        if (item && item->getTitle() == title) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<std::shared_ptr<VideoCarrier>> Catalog::getAvailableItems() const
{
    std::vector<std::shared_ptr<VideoCarrier>> result;
    for (const auto& item : m_items) {
        if (item && item->isAvailable()) {
            result.push_back(item);
        }
    }
    return result;
}
