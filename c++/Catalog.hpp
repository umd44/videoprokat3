#pragma once
#include <vector>
#include <string>
#include <memory>

class VideoCarrier;

// Каталог видеоносителей
class Catalog
{
public:
    Catalog() = default;
    ~Catalog() = default;

    // Добавить носитель в каталог
    void addItem(std::shared_ptr<VideoCarrier> item);
    // Найти по инвентарному номеру
    std::shared_ptr<VideoCarrier> findItemByNumber(int number) const;
    // Найти по инвентарному номеру с выбросом исключения (для демонстрации throw)
    std::shared_ptr<VideoCarrier> findItemByNumberOrThrow(int number) const;
    // Найти все по названию
    std::vector<std::shared_ptr<VideoCarrier>> findItemsByTitle(const std::string& title) const;
    // Получить список доступных
    std::vector<std::shared_ptr<VideoCarrier>> getAvailableItems() const;

private:
    std::vector<std::shared_ptr<VideoCarrier>> m_items;
};
