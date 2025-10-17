#pragma once
#include <vector>
#include <string>

class VideoCarrier;

class Catalog
{
public:
    Catalog() = default;
    ~Catalog() = default;

    void addItem(VideoCarrier* item);
    VideoCarrier* findItemByNumber(int number) const;
    std::vector<VideoCarrier*> findItemsByTitle(const std::string& title) const;
    std::vector<VideoCarrier*> getAvailableItems() const;

private:
    std::vector<VideoCarrier*> m_items;
};
