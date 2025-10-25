#pragma once
#include <vector>
#include <string>

class VideoCarrier;

// Каталог видеоносителей
class Catalog
{
public:
    Catalog() = default;
    ~Catalog() = default;

    // Добавить носитель в каталог
    void addItem(VideoCarrier* item);
    // Найти по инвентарному номеру
    VideoCarrier* findItemByNumber(int number) const;
    // Найти все по названию
    std::vector<VideoCarrier*> findItemsByTitle(const std::string& title) const;
    // Получить список доступных
    std::vector<VideoCarrier*> getAvailableItems() const;

private:
    std::vector<VideoCarrier*> m_items;
};
