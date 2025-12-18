#include "CatalogReal.hpp"
#include "VideoCarrier.hpp"
#include <algorithm>
#include <unordered_map>
#include <cwctype>

#ifdef _WIN32
#include <windows.h>
#else
#include <codecvt>
#include <locale>
#endif

CatalogReal::CatalogReal()
{
    // items инициализируется автоматически
}

CatalogReal::~CatalogReal()
{
    // В C++ не удаляем items, так как они принадлежат другим объектам
}

void CatalogReal::addItem(VideoCarrier* item)
{
    if (item != nullptr) {
        items.push_back(item);
    }
}

VideoCarrier* CatalogReal::findItemByNumber(int number)
{
    for (VideoCarrier* item : items) {
        if (item != nullptr && item->getInventoryNumber() == number) {
            return item;
        }
    }
    return nullptr;
}

std::vector<VideoCarrier*> CatalogReal::findItemsByTitle(const std::string& title)
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr && containsIgnoreCaseUtf8(item->getTitle(), title)) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::getAvailableItems()
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr && item->isAvailable()) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::findItemsByGenre(const std::string& genre)
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr) {
            if (equalsIgnoreCaseUtf8(item->getGenre(), genre)) {
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::findItemsByDirector(const std::string& director)
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr) {
            if (containsIgnoreCaseUtf8(item->getDirector(), director)) {
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::findItemsByYear(int year)
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr && item->getReleaseYear() == year) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::findItemsByCarrierType(const std::string& carrierType)
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr) {
            if (equalsIgnoreCaseUtf8(item->getCarrierType(), carrierType)) {
                result.push_back(item);
            }
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::findItemsByAgeRating(const std::string& ageRating)
{
    std::vector<VideoCarrier*> result;
    for (VideoCarrier* item : items) {
        if (item != nullptr && equalsIgnoreCaseUtf8(item->getAgeRating(), ageRating)) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<VideoCarrier*> CatalogReal::getAllItems()
{
    std::vector<VideoCarrier*> result;
    result.reserve(items.size());
    for (VideoCarrier* item : items) {
        result.push_back(item);
    }
    return result;
}

std::map<std::string, int> CatalogReal::getStatistics()
{
    std::map<std::string, int> stats;
    int available = 0, rented = 0, maintenance = 0, writtenOff = 0;
    
    for (VideoCarrier* item : items) {
        if (item != nullptr) {
            std::string status = item->getStatus();
            if (status == "available") available++;
            else if (status == "rented") rented++;
            else if (status == "maintenance") maintenance++;
            else if (status == "written_off") writtenOff++;
        }
    }
    
    stats["total"] = static_cast<int>(items.size());
    stats["available"] = available;
    stats["rented"] = rented;
    stats["maintenance"] = maintenance;
    stats["written_off"] = writtenOff;
    
    return stats;
}

std::vector<VideoCarrier*> CatalogReal::getTopRentedItems(int limit)
{
    std::vector<VideoCarrier*> sorted = items;
    std::sort(sorted.begin(), sorted.end(), 
        [](VideoCarrier* v1, VideoCarrier* v2) {
            if (v1 && v2) {
                return v2->getTotalRentals() < v1->getTotalRentals();
            }
            return false;
        });
    
    if (limit > static_cast<int>(sorted.size())) {
        limit = static_cast<int>(sorted.size());
    }
    
    std::vector<VideoCarrier*> result;
    result.reserve(limit);
    for (int i = 0; i < limit; ++i) {
        result.push_back(sorted[i]);
    }
    
    return result;
}

// Приведение UTF-8 строки к нижнему регистру через широкие символы (для корректной кириллицы)
static std::wstring toLowerWide(const std::string& s) {
    if (s.empty()) return std::wstring();

#ifdef _WIN32
    int len = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
    if (len <= 1) return std::wstring();
    std::wstring wide(static_cast<size_t>(len - 1), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, &wide[0], len);
#else
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    std::wstring wide = conv.from_bytes(s);
#endif

    for (auto& ch : wide) {
        ch = static_cast<wchar_t>(::towlower(ch));
    }
    return wide;
}

bool CatalogReal::containsIgnoreCaseUtf8(const std::string& str, const std::string& substr)
{
    std::wstring h = toLowerWide(str);
    std::wstring n = toLowerWide(substr);
    if (n.empty()) return true; // пустой запрос — все совпадения
    return h.find(n) != std::wstring::npos;
}

bool CatalogReal::equalsIgnoreCaseUtf8(const std::string& lhs, const std::string& rhs)
{
    return toLowerWide(lhs) == toLowerWide(rhs);
}

// Старый toLowerSimple больше не используется, оставлен для совместимости
std::string CatalogReal::toLowerSimple(const std::string& str)
{
    return str;
}


