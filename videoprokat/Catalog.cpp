#include "Catalog.hpp"
#include "VideoCarrier.hpp"

#include <algorithm>

void Catalog::addItem(VideoCarrier* item)
{
    if (item) m_items.push_back(item);
}

VideoCarrier* Catalog::findItemByNumber(int number) const
{
    for (auto* item : m_items) {
        if (item && item->getInventoryNumber() == number) return item;
    }
    return nullptr;
}

std::vector<VideoCarrier*> Catalog::findItemsByTitle(const std::string& title) const
{
    std::vector<VideoCarrier*> result;
    for (auto* item : m_items) {
        if (item && item->getTitle() == title) result.push_back(item);
    }
    return result;
}

std::vector<VideoCarrier*> Catalog::getAvailableItems() const
{
    std::vector<VideoCarrier*> result;
    for (auto* item : m_items) {
        if (item && item->isAvailable()) result.push_back(item);
    }
    return result;
}
