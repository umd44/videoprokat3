#pragma once
#include <vector>
#include <string>
#include <map>

class VideoCarrier;

/**
 * Абстрактный класс, описывающий каталог видеоносителей.
 * Содержит базовую структуру и методы для работы с каталогом.
 */
class Catalog
{
protected:
    std::vector<VideoCarrier*> items;

    /**
     * Конструктор по умолчанию.
     */
    Catalog() = default;

public:
    virtual ~Catalog() = default;

    /**
     * Добавить носитель в каталог.
     */
    virtual void addItem(VideoCarrier* item) = 0;

    /**
     * Найти носитель по инвентарному номеру.
     */
    virtual VideoCarrier* findItemByNumber(int number) = 0;

    /**
     * Найти все носители по названию.
     */
    virtual std::vector<VideoCarrier*> findItemsByTitle(const std::string& title) = 0;

    /**
     * Получить список доступных носителей.
     */
    virtual std::vector<VideoCarrier*> getAvailableItems() = 0;

    /**
     * Найти носители по жанру.
     */
    virtual std::vector<VideoCarrier*> findItemsByGenre(const std::string& genre) = 0;

    /**
     * Найти носители по режиссеру.
     */
    virtual std::vector<VideoCarrier*> findItemsByDirector(const std::string& director) = 0;

    /**
     * Найти носители по году выпуска.
     */
    virtual std::vector<VideoCarrier*> findItemsByYear(int year) = 0;

    /**
     * Найти носители по типу носителя.
     */
    virtual std::vector<VideoCarrier*> findItemsByCarrierType(const std::string& carrierType) = 0;

    /**
     * Найти носители по возрастному рейтингу.
     */
    virtual std::vector<VideoCarrier*> findItemsByAgeRating(const std::string& ageRating) = 0;

    /**
     * Получить все носители.
     */
    virtual std::vector<VideoCarrier*> getAllItems() = 0;

    /**
     * Получить статистику по носителям.
     */
    virtual std::map<std::string, int> getStatistics() = 0;

    /**
     * Найти топ популярных носителей.
     */
    virtual std::vector<VideoCarrier*> getTopRentedItems(int limit) = 0;
};
