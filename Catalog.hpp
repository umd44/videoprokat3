#pragma once
#include <vector>
#include <string>
#include <memory>

class VideoCarrier;

// Каталог для хранения и поиска видеоносителей
class Catalog
{
public:
    Catalog() = default;
    ~Catalog() = default;

    void addItem(std::shared_ptr<VideoCarrier> item);
    std::shared_ptr<VideoCarrier> findItemByNumber(int number) const;
    std::shared_ptr<VideoCarrier> findItemByNumberOrThrow(int number) const;
    std::vector<std::shared_ptr<VideoCarrier>> findItemsByTitle(const std::string& title) const;
    std::vector<std::shared_ptr<VideoCarrier>> getAvailableItems() const;

private:
    std::vector<std::shared_ptr<VideoCarrier>> m_items;
};
