#pragma once
#include "Catalog.hpp"
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <unordered_map>

/**
 * Реализация класса Catalog.
 * Содержит конкретную реализацию всех методов абстрактного класса Catalog.
 */
class CatalogReal : public Catalog
{
public:
    /**
     * Конструктор по умолчанию.
     * Инициализирует список носителей.
     */
    CatalogReal();

    virtual ~CatalogReal();

    void addItem(VideoCarrier* item) override;

    VideoCarrier* findItemByNumber(int number) override;

    std::vector<VideoCarrier*> findItemsByTitle(const std::string& title) override;

    std::vector<VideoCarrier*> getAvailableItems() override;

    std::vector<VideoCarrier*> findItemsByGenre(const std::string& genre) override;

    std::vector<VideoCarrier*> findItemsByDirector(const std::string& director) override;

    std::vector<VideoCarrier*> findItemsByYear(int year) override;

    std::vector<VideoCarrier*> findItemsByCarrierType(const std::string& carrierType) override;

    std::vector<VideoCarrier*> findItemsByAgeRating(const std::string& ageRating) override;

    std::vector<VideoCarrier*> getAllItems() override;

    std::map<std::string, int> getStatistics() override;

    std::vector<VideoCarrier*> getTopRentedItems(int limit) override;

private:
    static std::string toLowerSimple(const std::string& str);
    static bool containsIgnoreCaseUtf8(const std::string& str, const std::string& substr);
    static bool equalsIgnoreCaseUtf8(const std::string& lhs, const std::string& rhs);
};



