# STL, Java Collections Framework и C# Collections Examples

## Таблица содержания
1. [C++ STL - Контейнеры и алгоритмы](#c-stl---контейнеры-и-алгоритмы)
2. [Java Collections Framework](#java-collections-framework)
3. [C# Collections](#c-collections)

---

# C++ STL - Контейнеры и алгоритмы

## 1. Использование контейнеров, сортировки и поиска с полиморфизмом

### Задание
Создать программу, которая:
- Использует std::vector для хранения указателей на объекты видеоносителей (базовый класс VideoCarrier)
- Сортирует видеоносители по цене аренды за день
- Находит видеоносители по жанру используя std::find_if
- Копирует найденные элементы в новый контейнер используя std::copy_if

### Реализация

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <list>
#include <map>
#include <span>
#include <string>

// Абстрактный базовый класс VideoCarrier (существующий)
class VideoCarrier {
public:
    VideoCarrier(int id, const std::string& title, const std::string& genre, double price)
        : m_id(id), m_title(title), m_genre(genre), m_rentalPrice(price) {}
    virtual ~VideoCarrier() = default;

    int getId() const { return m_id; }
    const std::string& getTitle() const { return m_title; }
    const std::string& getGenre() const { return m_genre; }
    double getRentalPrice() const { return m_rentalPrice; }
    virtual std::string getType() const = 0;

protected:
    int m_id;
    std::string m_title;
    std::string m_genre;
    double m_rentalPrice;
};

// Производные классы
class DVD : public VideoCarrier {
public:
    using VideoCarrier::VideoCarrier;
    std::string getType() const override { return "DVD"; }
};

class BluRay : public VideoCarrier {
public:
    using VideoCarrier::VideoCarrier;
    std::string getType() const override { return "BluRay"; }
};

class VHS : public VideoCarrier {
public:
    using VideoCarrier::VideoCarrier;
    std::string getType() const override { return "VHS"; }
};

// Использование различных STL контейнеров
void demonstrateContainersAndAlgorithms() {
    // 1. std::array - фиксированный размер
    std::cout << "=== std::array - фиксированный размер ===" << std::endl;
    std::array<VideoCarrier*, 3> fixedArray;
    fixedArray[0] = new DVD(1, "Matrix", "Sci-Fi", 50.0);
    fixedArray[1] = new BluRay(2, "Inception", "Sci-Fi", 60.0);
    fixedArray[2] = new VHS(3, "Jaws", "Thriller", 30.0);

    // 2. std::vector - динамический размер
    std::cout << "=== std::vector - динамический размер ===" << std::endl;
    std::vector<VideoCarrier*> videoCarriers;
    for (auto& item : fixedArray) {
        videoCarriers.push_back(item);
    }
    videoCarriers.push_back(new DVD(4, "Avatar", "Fantasy", 70.0));
    videoCarriers.push_back(new BluRay(5, "Dune", "Sci-Fi", 75.0));

    // 3. std::list - двусвязный список
    std::cout << "=== std::list - двусвязный список ===" << std::endl;
    std::list<VideoCarrier*> linkedList(videoCarriers.begin(), videoCarriers.end());

    // 4. std::map - ассоциативный контейнер
    std::cout << "=== std::map - ассоциативный контейнер ===" << std::endl;
    std::map<int, VideoCarrier*> catalogMap;
    for (auto item : videoCarriers) {
        catalogMap[item->getId()] = item;
    }

    // === СОРТИРОВКА ===
    std::cout << "\n=== СОРТИРОВКА по цене ===" << std::endl;
    std::vector<VideoCarrier*> sortedByPrice = videoCarriers;
    
    // std::sort() - сортировка
    std::sort(sortedByPrice.begin(), sortedByPrice.end(),
        [](VideoCarrier* a, VideoCarrier* b) {
            return a->getRentalPrice() < b->getRentalPrice();
        }
    );

    std::cout << "Отсортировано по цене (возрастанию):" << std::endl;
    for (const auto& item : sortedByPrice) {
        std::cout << "  " << item->getTitle() << " - $" << item->getRentalPrice() << std::endl;
    }

    // === ПОИСК ===
    std::cout << "\n=== ПОИСК ===" << std::endl;
    
    // std::find_if - поиск по условию
    std::cout << "Поиск видео дороже $60:" << std::endl;
    auto it = std::find_if(videoCarriers.begin(), videoCarriers.end(),
        [](const VideoCarrier* item) { return item->getRentalPrice() > 60.0; }
    );
    if (it != videoCarriers.end()) {
        std::cout << "  Найдено: " << (*it)->getTitle() << " - $" << (*it)->getRentalPrice() << std::endl;
    }

    // std::find - поиск по значению (для ID)
    std::cout << "\nПоиск видео с ID=3:" << std::endl;
    auto it2 = std::find_if(videoCarriers.begin(), videoCarriers.end(),
        [](const VideoCarrier* item) { return item->getId() == 3; }
    );
    if (it2 != videoCarriers.end()) {
        std::cout << "  Найдено: " << (*it2)->getTitle() << std::endl;
    }

    // === КОПИРОВАНИЕ ===
    std::cout << "\n=== КОПИРОВАНИЕ ===" << std::endl;
    
    // std::copy_if - копирование элементов по условию
    std::cout << "Копирование видео жанра 'Sci-Fi':" << std::endl;
    std::vector<VideoCarrier*> sciFiVideos;
    std::copy_if(videoCarriers.begin(), videoCarriers.end(),
        std::back_inserter(sciFiVideos),
        [](const VideoCarrier* item) { return item->getGenre() == "Sci-Fi"; }
    );

    for (const auto& item : sciFiVideos) {
        std::cout << "  " << item->getTitle() << " (тип: " << item->getType() << ")" << std::endl;
    }

    // std::copy - простое копирование
    std::cout << "\nПростое копирование в новый вектор:" << std::endl;
    std::vector<VideoCarrier*> allVideosCopy;
    std::copy(videoCarriers.begin(), videoCarriers.end(),
        std::back_inserter(allVideosCopy));

    // === УДАЛЕНИЕ ===
    std::cout << "\n=== УДАЛЕНИЕ ЭЛЕМЕНТОВ ===" << std::endl;
    
    // std::remove_if - удаление элементов по условию
    std::vector<VideoCarrier*> videosForRemoval = videoCarriers;
    auto newEnd = std::remove_if(videosForRemoval.begin(), videosForRemoval.end(),
        [](const VideoCarrier* item) { return item->getRentalPrice() < 40.0; }
    );
    videosForRemoval.erase(newEnd, videosForRemoval.end());
    
    std::cout << "После удаления видео дешевле $40:" << std::endl;
    for (const auto& item : videosForRemoval) {
        std::cout << "  " << item->getTitle() << " - $" << item->getRentalPrice() << std::endl;
    }

    // === ПОИСК MIN/MAX ===
    std::cout << "\n=== ПОИСК MIN/MAX ===" << std::endl;
    
    // std::min_element
    auto minItem = std::min_element(videoCarriers.begin(), videoCarriers.end(),
        [](const VideoCarrier* a, const VideoCarrier* b) {
            return a->getRentalPrice() < b->getRentalPrice();
        }
    );
    std::cout << "Самое дешевое видео: " << (*minItem)->getTitle() 
              << " - $" << (*minItem)->getRentalPrice() << std::endl;

    // std::max_element
    auto maxItem = std::max_element(videoCarriers.begin(), videoCarriers.end(),
        [](const VideoCarrier* a, const VideoCarrier* b) {
            return a->getRentalPrice() < b->getRentalPrice();
        }
    );
    std::cout << "Самое дорогое видео: " << (*maxItem)->getTitle() 
              << " - $" << (*maxItem)->getRentalPrice() << std::endl;

    // === std::any_of ===
    std::cout << "\n=== std::any_of ===" << std::endl;
    bool hasExpensiveVideos = std::any_of(videoCarriers.begin(), videoCarriers.end(),
        [](const VideoCarrier* item) { return item->getRentalPrice() > 100.0; }
    );
    std::cout << "Есть видео дороже $100: " << (hasExpensiveVideos ? "ДА" : "НЕТ") << std::endl;

    // === std::span - представление подмножества ===
    std::cout << "\n=== std::span - представление подмножества ===" << std::endl;
    std::span<VideoCarrier*> videoSpan(videoCarriers.data(), 3);
    std::cout << "Первые 3 видео через span:" << std::endl;
    for (const auto& item : videoSpan) {
        std::cout << "  " << item->getTitle() << std::endl;
    }

    // Очистка памяти
    for (auto item : videoCarriers) {
        delete item;
    }
}
```

---

## 2. Шаблонная функция для работы с числовыми типами

### Задание
Создать шаблонную функцию, которая:
- Не является методом класса
- Работает с числовыми типами (ограничение на компиляции)
- Вычисляет статистику по контейнеру (среднее, минимум, максимум)
- Работает с различными числовыми типами (int, double, float)

### Реализация

```cpp
#include <type_traits>
#include <vector>
#include <numeric>
#include <iostream>
#include <concepts>

// Концепция для числовых типов (C++20)
template<typename T>
concept Numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

// Шаблонная функция для вычисления статистики
template<Numeric T>
struct Statistics {
    T average;
    T minimum;
    T maximum;
    T sum;
};

template<Numeric T>
Statistics<T> calculateStatistics(const std::vector<T>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Контейнер не может быть пустым");
    }

    T sum = std::accumulate(data.begin(), data.end(), T(0));
    T average = sum / data.size();
    T minimum = *std::min_element(data.begin(), data.end());
    T maximum = *std::max_element(data.begin(), data.end());

    return {average, minimum, maximum, sum};
}

// Шаблонная функция для масштабирования значений
template<Numeric T>
std::vector<T> scaleValues(const std::vector<T>& data, T scale) {
    std::vector<T> result;
    std::transform(data.begin(), data.end(), std::back_inserter(result),
        [scale](T value) { return value * scale; }
    );
    return result;
}

// Шаблонная функция для фильтрации по диапазону
template<Numeric T>
std::vector<T> filterByRange(const std::vector<T>& data, T minVal, T maxVal) {
    std::vector<T> result;
    std::copy_if(data.begin(), data.end(), std::back_inserter(result),
        [minVal, maxVal](T value) { return value >= minVal && value <= maxVal; }
    );
    return result;
}

void demonstrateTemplateFunction() {
    std::cout << "=== Шаблонная функция с ограничениями на типы ===" << std::endl;

    // Пример с целыми числами
    std::cout << "\n--- Целые числа ---" << std::endl;
    std::vector<int> intPrices = {30, 50, 60, 70, 75, 25};
    auto intStats = calculateStatistics(intPrices);
    std::cout << "Цены: ";
    for (int price : intPrices) std::cout << price << " ";
    std::cout << std::endl;
    std::cout << "Сумма: " << intStats.sum << std::endl;
    std::cout << "Среднее: " << intStats.average << std::endl;
    std::cout << "Минимум: " << intStats.minimum << std::endl;
    std::cout << "Максимум: " << intStats.maximum << std::endl;

    // Пример с числами с плавающей точкой
    std::cout << "\n--- Числа с плавающей точкой ---" << std::endl;
    std::vector<double> doublePrices = {30.5, 50.75, 60.25, 70.0, 75.5, 25.0};
    auto doubleStats = calculateStatistics(doublePrices);
    std::cout << "Цены: ";
    for (double price : doublePrices) std::cout << price << " ";
    std::cout << std::endl;
    std::cout << "Среднее: " << doubleStats.average << std::endl;

    // Масштабирование значений
    std::cout << "\n--- Масштабирование ---" << std::endl;
    std::vector<double> scaled = scaleValues(doublePrices, 1.1);
    std::cout << "Масштабированные цены (* 1.1): ";
    for (double price : scaled) std::cout << price << " ";
    std::cout << std::endl;

    // Фильтрация по диапазону
    std::cout << "\n--- Фильтрация по диапазону [50, 70] ---" << std::endl;
    std::vector<double> filtered = filterByRange(doublePrices, 50.0, 70.0);
    std::cout << "Отфильтрованные цены: ";
    for (double price : filtered) std::cout << price << " ";
    std::cout << std::endl;
}
```

---

## 3. Шаблонный класс с шаблонными и нешаблонными методами

### Задание
Создать шаблонный класс, который:
- Имеет как шаблонные, так и нешаблонные методы
- Работает с типами, наследующими базовый класс (VideoCarrier)
- Реализует коллекцию с операциями добавления, удаления и поиска

### Реализация

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <type_traits>

// Базовый класс для элементов коллекции
class CollectionItem {
public:
    virtual ~CollectionItem() = default;
    virtual std::string getName() const = 0;
    virtual int getId() const = 0;
};

// Реализации базового класса
class VideoItem : public CollectionItem {
private:
    int m_id;
    std::string m_name;
    double m_price;
public:
    VideoItem(int id, const std::string& name, double price)
        : m_id(id), m_name(name), m_price(price) {}
    
    std::string getName() const override { return m_name; }
    int getId() const override { return m_id; }
    double getPrice() const { return m_price; }
};

class AudioItem : public CollectionItem {
private:
    int m_id;
    std::string m_name;
    std::string m_artist;
public:
    AudioItem(int id, const std::string& name, const std::string& artist)
        : m_id(id), m_name(name), m_artist(artist) {}
    
    std::string getName() const override { return m_name; }
    int getId() const override { return m_id; }
    const std::string& getArtist() const { return m_artist; }
};

// Шаблонный класс коллекции
template<typename T>
requires std::is_base_of_v<CollectionItem, T>
class Collection {
private:
    std::vector<std::unique_ptr<T>> m_items;
    std::string m_name;

public:
    // Нешаблонный конструктор
    Collection(const std::string& name) : m_name(name) {}

    // Нешаблонный метод - получить имя коллекции
    const std::string& getCollectionName() const {
        return m_name;
    }

    // Нешаблонный метод - получить размер
    size_t getSize() const {
        return m_items.size();
    }

    // Нешаблонный метод - добавить элемент
    void addItem(std::unique_ptr<T> item) {
        if (!item) {
            throw std::invalid_argument("Элемент не может быть null");
        }
        m_items.push_back(std::move(item));
    }

    // Нешаблонный метод - получить элемент по индексу
    T* getItemAt(size_t index) {
        if (index >= m_items.size()) {
            throw std::out_of_range("Индекс выходит за границы");
        }
        return m_items[index].get();
    }

    // Шаблонный метод - поиск с кастомным предикатом
    template<typename Predicate>
    T* findItem(Predicate pred) {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [&pred](const std::unique_ptr<T>& item) { return pred(*item); }
        );
        return it != m_items.end() ? it->get() : nullptr;
    }

    // Шаблонный метод - преобразование в другой тип
    template<typename OutType, typename Converter>
    std::vector<OutType> transform(Converter converter) {
        std::vector<OutType> result;
        for (const auto& item : m_items) {
            result.push_back(converter(*item));
        }
        return result;
    }

    // Шаблонный метод - фильтрация
    template<typename Predicate>
    std::vector<T*> filter(Predicate pred) {
        std::vector<T*> result;
        for (auto& item : m_items) {
            if (pred(*item)) {
                result.push_back(item.get());
            }
        }
        return result;
    }

    // Нешаблонный метод - удалить элемент по ID
    bool removeById(int id) {
        auto it = std::find_if(m_items.begin(), m_items.end(),
            [id](const std::unique_ptr<T>& item) { return item->getId() == id; }
        );
        if (it != m_items.end()) {
            m_items.erase(it);
            return true;
        }
        return false;
    }

    // Нешаблонный метод - вывести все элементы
    void printAll() const {
        std::cout << "Коллекция: " << m_name << " (размер: " << m_items.size() << ")" << std::endl;
        for (const auto& item : m_items) {
            std::cout << "  ID=" << item->getId() << ", Имя=" << item->getName() << std::endl;
        }
    }

    // Шаблонный метод - получить статистику через функцию
    template<typename StatFunc>
    auto getStatistic(StatFunc statFunc) {
        return statFunc(m_items);
    }
};

void demonstrateTemplateClass() {
    std::cout << "=== Шаблонный класс Collection ===" << std::endl;

    // Создание коллекции видео
    std::cout << "\n--- Коллекция видео ---" << std::endl;
    Collection<VideoItem> videoCollection("Мои фильмы");
    
    // Добавление видео
    videoCollection.addItem(std::make_unique<VideoItem>(1, "Matrix", 50.0));
    videoCollection.addItem(std::make_unique<VideoItem>(2, "Inception", 60.0));
    videoCollection.addItem(std::make_unique<VideoItem>(3, "Avatar", 70.0));

    videoCollection.printAll();

    // Поиск с предикатом
    std::cout << "\nПоиск видео по названию 'Matrix':" << std::endl;
    auto found = videoCollection.findItem([](const VideoItem& item) {
        return item.getName() == "Matrix";
    });
    if (found) {
        std::cout << "  Найдено: " << found->getName() << std::endl;
    }

    // Преобразование в вектор названий
    std::cout << "\nПреобразование в названия:" << std::endl;
    auto names = videoCollection.transform<std::string>(
        [](const VideoItem& item) { return item.getName(); }
    );
    for (const auto& name : names) {
        std::cout << "  " << name << std::endl;
    }

    // Фильтрация дорогих видео
    std::cout << "\nФильтрация видео дороже $55:" << std::endl;
    auto expensive = videoCollection.filter([](const VideoItem& item) {
        return item.getPrice() > 55.0;
    });
    for (auto item : expensive) {
        std::cout << "  " << item->getName() << " - $" << item->getPrice() << std::endl;
    }

    // Создание коллекции аудио
    std::cout << "\n--- Коллекция аудио ---" << std::endl;
    Collection<AudioItem> audioCollection("Мояная музыка");
    
    audioCollection.addItem(std::make_unique<AudioItem>(1, "Song1", "Artist1"));
    audioCollection.addItem(std::make_unique<AudioItem>(2, "Song2", "Artist2"));

    audioCollection.printAll();

    // Удаление элемента
    std::cout << "\nУдаление видео с ID=2..." << std::endl;
    videoCollection.removeById(2);
    videoCollection.printAll();
}
```

---

# Java Collections Framework

## 1. Использование контейнеров, сортировки и поиска с полиморфизмом

### Задание
Создать программу, которая:
- Использует ArrayList для хранения объектов видеоносителей
- Сортирует видеоносители по цене
- Использует Stream API для поиска и фильтрации
- Демонстрирует использование других контейнеров (LinkedList, HashMap, TreeSet)

### Реализация

```java
import java.util.*;
import java.util.stream.Collectors;

// Абстрактный базовый класс
abstract class VideoCarrier {
    protected int id;
    protected String title;
    protected String genre;
    protected double rentalPrice;

    public VideoCarrier(int id, String title, String genre, double rentalPrice) {
        this.id = id;
        this.title = title;
        this.genre = genre;
        this.rentalPrice = rentalPrice;
    }

    public int getId() { return id; }
    public String getTitle() { return title; }
    public String getGenre() { return genre; }
    public double getRentalPrice() { return rentalPrice; }
    public abstract String getType();
}

// Производные классы
class DVD extends VideoCarrier {
    public DVD(int id, String title, String genre, double price) {
        super(id, title, genre, price);
    }
    public String getType() { return "DVD"; }
}

class BluRay extends VideoCarrier {
    public BluRay(int id, String title, String genre, double price) {
        super(id, title, genre, price);
    }
    public String getType() { return "BluRay"; }
}

class VHS extends VideoCarrier {
    public VHS(int id, String title, String genre, double price) {
        super(id, title, genre, price);
    }
    public String getType() { return "VHS"; }
}

public class JavaCollectionsDemo {
    
    public static void demonstrateContainersAndAlgorithms() {
        System.out.println("=== Java Collections Framework - Контейнеры и алгоритмы ===");

        // 1. ArrayList - динамический массив (аналог std::vector)
        System.out.println("\n--- ArrayList (аналог std::vector) ---");
        List<VideoCarrier> videoCarriers = new ArrayList<>();
        videoCarriers.add(new DVD(1, "Matrix", "Sci-Fi", 50.0));
        videoCarriers.add(new BluRay(2, "Inception", "Sci-Fi", 60.0));
        videoCarriers.add(new VHS(3, "Jaws", "Thriller", 30.0));
        videoCarriers.add(new DVD(4, "Avatar", "Fantasy", 70.0));
        videoCarriers.add(new BluRay(5, "Dune", "Sci-Fi", 75.0));

        System.out.println("Видеоносители: ");
        for (VideoCarrier vc : videoCarriers) {
            System.out.println("  " + vc.getTitle() + " - $" + vc.getRentalPrice());
        }

        // 2. LinkedList - двусвязный список (аналог std::list)
        System.out.println("\n--- LinkedList (аналог std::list) ---");
        LinkedList<VideoCarrier> linkedList = new LinkedList<>(videoCarriers);
        System.out.println("Размер LinkedList: " + linkedList.size());

        // 3. HashMap - ассоциативный контейнер (аналог std::map)
        System.out.println("\n--- HashMap (аналог std::map) ---");
        Map<Integer, VideoCarrier> catalogMap = new HashMap<>();
        for (VideoCarrier vc : videoCarriers) {
            catalogMap.put(vc.getId(), vc);
        }
        System.out.println("Размер HashMap: " + catalogMap.size());
        System.out.println("Видео с ID=2: " + catalogMap.get(2).getTitle());

        // 4. TreeMap - отсортированный map
        System.out.println("\n--- TreeMap (отсортированный map) ---");
        Map<Integer, VideoCarrier> treeMap = new TreeMap<>(catalogMap);
        System.out.println("TreeMap отсортирован по ID: ");
        for (Map.Entry<Integer, VideoCarrier> entry : treeMap.entrySet()) {
            System.out.println("  ID=" + entry.getKey() + ": " + entry.getValue().getTitle());
        }

        // 5. HashSet - уникальные элементы (аналог std::set, но не отсортирован)
        System.out.println("\n--- HashSet (уникальные элементы) ---");
        Set<String> genres = new HashSet<>();
        for (VideoCarrier vc : videoCarriers) {
            genres.add(vc.getGenre());
        }
        System.out.println("Уникальные жанры: " + genres);

        // 6. TreeSet - отсортированное множество
        System.out.println("\n--- TreeSet (отсортированное множество) ---");
        Set<String> sortedGenres = new TreeSet<>(genres);
        System.out.println("Жанры (отсортированы): " + sortedGenres);

        // === СОРТИРОВКА ===
        System.out.println("\n=== СОРТИРОВКА ===");
        
        // Collections.sort() - аналог std::sort()
        System.out.println("Сортировка по цене (возрастанию):");
        List<VideoCarrier> sortedByPrice = new ArrayList<>(videoCarriers);
        Collections.sort(sortedByPrice, 
            Comparator.comparingDouble(VideoCarrier::getRentalPrice));
        for (VideoCarrier vc : sortedByPrice) {
            System.out.println("  " + vc.getTitle() + " - $" + vc.getRentalPrice());
        }

        // Stream API sort - современный подход
        System.out.println("\nСортировка по названию (используя Stream):");
        videoCarriers.stream()
            .sorted(Comparator.comparing(VideoCarrier::getTitle))
            .forEach(vc -> System.out.println("  " + vc.getTitle()));

        // === ПОИСК ===
        System.out.println("\n=== ПОИСК ===");
        
        // Stream.filter() - аналог std::find_if()
        System.out.println("Поиск видео дороже $60:");
        videoCarriers.stream()
            .filter(vc -> vc.getRentalPrice() > 60.0)
            .forEach(vc -> System.out.println("  " + vc.getTitle() + " - $" + vc.getRentalPrice()));

        // Stream.findFirst() - найти первый элемент
        System.out.println("\nПервое видео жанра 'Sci-Fi':");
        var firstSciFi = videoCarriers.stream()
            .filter(vc -> vc.getGenre().equals("Sci-Fi"))
            .findFirst();
        if (firstSciFi.isPresent()) {
            System.out.println("  " + firstSciFi.get().getTitle());
        }

        // === КОПИРОВАНИЕ ===
        System.out.println("\n=== КОПИРОВАНИЕ ===");
        
        // Stream.filter() + collect() - аналог std::copy_if()
        System.out.println("Копирование видео жанра 'Sci-Fi':");
        List<VideoCarrier> sciFiVideos = videoCarriers.stream()
            .filter(vc -> vc.getGenre().equals("Sci-Fi"))
            .collect(Collectors.toList());
        for (VideoCarrier vc : sciFiVideos) {
            System.out.println("  " + vc.getTitle() + " (тип: " + vc.getType() + ")");
        }

        // Stream.map() - аналог std::transform()
        System.out.println("\nПреобразование в названия:");
        List<String> titles = videoCarriers.stream()
            .map(VideoCarrier::getTitle)
            .collect(Collectors.toList());
        for (String title : titles) {
            System.out.println("  " + title);
        }

        // === УДАЛЕНИЕ ===
        System.out.println("\n=== УДАЛЕНИЕ ===");
        
        // removeIf() - аналог std::remove_if()
        System.out.println("Удаление видео дешевле $40:");
        List<VideoCarrier> videosForRemoval = new ArrayList<>(videoCarriers);
        videosForRemoval.removeIf(vc -> vc.getRentalPrice() < 40.0);
        for (VideoCarrier vc : videosForRemoval) {
            System.out.println("  " + vc.getTitle() + " - $" + vc.getRentalPrice());
        }

        // === ПОИСК MIN/MAX ===
        System.out.println("\n=== ПОИСК MIN/MAX ===");
        
        // Collections.min() - аналог std::min_element()
        VideoCarrier minPrice = Collections.min(videoCarriers,
            Comparator.comparingDouble(VideoCarrier::getRentalPrice));
        System.out.println("Самое дешевое: " + minPrice.getTitle() + " - $" + minPrice.getRentalPrice());

        // Collections.max() - аналог std::max_element()
        VideoCarrier maxPrice = Collections.max(videoCarriers,
            Comparator.comparingDouble(VideoCarrier::getRentalPrice));
        System.out.println("Самое дорогое: " + maxPrice.getTitle() + " - $" + maxPrice.getRentalPrice());

        // === anyMatch() - аналог std::any_of() ===
        System.out.println("\n=== anyMatch (аналог std::any_of) ===");
        boolean hasExpensive = videoCarriers.stream()
            .anyMatch(vc -> vc.getRentalPrice() > 100.0);
        System.out.println("Есть видео дороже $100: " + (hasExpensive ? "ДА" : "НЕТ"));

        // allMatch()
        boolean allAffordable = videoCarriers.stream()
            .allMatch(vc -> vc.getRentalPrice() < 100.0);
        System.out.println("Все видео дешевле $100: " + (allAffordable ? "ДА" : "НЕТ"));
    }
}
```

---

## 2. Шаблонная функция для работы с числовыми типами

### Задание
Создать обобщенный метод (generics), который:
- Работает с числовыми типами (используя bounds)
- Вычисляет статистику
- Использует различные типы данных (Integer, Double, Float)

### Реализация

```java
import java.util.*;
import java.util.stream.Collectors;

public class TemplateFunction {
    
    // Класс для хранения статистики
    static class Statistics<T extends Number> {
        public T average;
        public T minimum;
        public T maximum;
        public T sum;

        public Statistics(T average, T minimum, T maximum, T sum) {
            this.average = average;
            this.minimum = minimum;
            this.maximum = maximum;
            this.sum = sum;
        }

        @Override
        public String toString() {
            return String.format("Сумма: %s, Среднее: %s, Минимум: %s, Максимум: %s",
                sum, average, minimum, maximum);
        }
    }

    // Обобщенный метод для вычисления статистики (с ограничением Number)
    public static <T extends Number & Comparable<T>> Statistics<Double> calculateStatistics(List<T> data) {
        if (data.isEmpty()) {
            throw new IllegalArgumentException("Список не может быть пустым");
        }

        // Преобразуем в Double для удобства вычислений
        double sum = data.stream()
            .mapToDouble(Number::doubleValue)
            .sum();
        double average = sum / data.size();

        double min = data.stream()
            .mapToDouble(Number::doubleValue)
            .min()
            .orElseThrow();

        double max = data.stream()
            .mapToDouble(Number::doubleValue)
            .max()
            .orElseThrow();

        return new Statistics<>(average, min, max, sum);
    }

    // Обобщенный метод для масштабирования значений
    public static <T extends Number> List<Double> scaleValues(List<T> data, double scale) {
        return data.stream()
            .map(n -> n.doubleValue() * scale)
            .collect(Collectors.toList());
    }

    // Обобщенный метод для фильтрации по диапазону
    public static <T extends Number & Comparable<T>> List<T> filterByRange(
            List<T> data, T minVal, T maxVal) {
        return data.stream()
            .filter(n -> n.doubleValue() >= minVal.doubleValue() && 
                        n.doubleValue() <= maxVal.doubleValue())
            .collect(Collectors.toList());
    }

    // Обобщенный метод для вычисления суммы
    public static <T extends Number> double sum(List<T> data) {
        return data.stream()
            .mapToDouble(Number::doubleValue)
            .sum();
    }

    // Обобщенный метод для нахождения среднего
    public static <T extends Number> double average(List<T> data) {
        if (data.isEmpty()) return 0.0;
        return sum(data) / data.size();
    }

    public static void demonstrateTemplateFunction() {
        System.out.println("=== Шаблонные методы для работы с числовыми типами ===");

        // Пример с Integer
        System.out.println("\n--- Целые числа (Integer) ---");
        List<Integer> intPrices = Arrays.asList(30, 50, 60, 70, 75, 25);
        Statistics<Double> intStats = calculateStatistics(intPrices);
        System.out.println("Цены: " + intPrices);
        System.out.println("Статистика: " + intStats);

        // Пример с Double
        System.out.println("\n--- Числа с плавающей точкой (Double) ---");
        List<Double> doublePrices = Arrays.asList(30.5, 50.75, 60.25, 70.0, 75.5, 25.0);
        Statistics<Double> doubleStats = calculateStatistics(doublePrices);
        System.out.println("Цены: " + doublePrices);
        System.out.println("Статистика: " + doubleStats);

        // Масштабирование
        System.out.println("\n--- Масштабирование (* 1.1) ---");
        List<Double> scaled = scaleValues(doublePrices, 1.1);
        System.out.println("Масштабированные цены: " + scaled);

        // Фильтрация по диапазону
        System.out.println("\n--- Фильтрация по диапазону [50, 70] ---");
        List<Double> filtered = filterByRange(doublePrices, 50.0, 70.0);
        System.out.println("Отфильтрованные цены: " + filtered);

        // Вычисление суммы и среднего
        System.out.println("\n--- Вычисление суммы и среднего ---");
        System.out.println("Сумма: " + sum(intPrices));
        System.out.println("Среднее: " + average(intPrices));
    }
}
```

---

## 3. Шаблонный класс с шаблонными и нешаблонными методами

### Задание
Создать обобщенный класс (generics), который:
- Имеет как обобщенные, так и нешаблонные методы
- Работает с типами, наследующими интерфейс CollectionItem
- Реализует коллекцию с операциями

### Реализация

```java
import java.util.*;
import java.util.function.Predicate;
import java.util.function.Function;
import java.util.stream.Collectors;

// Интерфейс для элементов коллекции
interface CollectionItem {
    String getName();
    int getId();
}

// Реализации интерфейса
class VideoItem implements CollectionItem {
    private int id;
    private String name;
    private double price;

    public VideoItem(int id, String name, double price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }

    public String getName() { return name; }
    public int getId() { return id; }
    public double getPrice() { return price; }
}

class AudioItem implements CollectionItem {
    private int id;
    private String name;
    private String artist;

    public AudioItem(int id, String name, String artist) {
        this.id = id;
        this.name = name;
        this.artist = artist;
    }

    public String getName() { return name; }
    public int getId() { return id; }
    public String getArtist() { return artist; }
}

// Обобщенный класс коллекции
class Collection<T extends CollectionItem> {
    private List<T> items;
    private String name;

    // Нешаблонный конструктор
    public Collection(String name) {
        this.name = name;
        this.items = new ArrayList<>();
    }

    // Нешаблонный метод - получить имя коллекции
    public String getCollectionName() {
        return name;
    }

    // Нешаблонный метод - получить размер
    public int getSize() {
        return items.size();
    }

    // Нешаблонный метод - добавить элемент
    public void addItem(T item) {
        if (item == null) {
            throw new IllegalArgumentException("Элемент не может быть null");
        }
        items.add(item);
    }

    // Нешаблонный метод - получить элемент по индексу
    public T getItemAt(int index) {
        if (index < 0 || index >= items.size()) {
            throw new IndexOutOfBoundsException("Индекс выходит за границы");
        }
        return items.get(index);
    }

    // Обобщенный метод - поиск с предикатом
    public T findItem(Predicate<T> predicate) {
        return items.stream()
            .filter(predicate)
            .findFirst()
            .orElse(null);
    }

    // Обобщенный метод - преобразование в другой тип
    public <R> List<R> transform(Function<T, R> converter) {
        return items.stream()
            .map(converter)
            .collect(Collectors.toList());
    }

    // Обобщенный метод - фильтрация
    public List<T> filter(Predicate<T> predicate) {
        return items.stream()
            .filter(predicate)
            .collect(Collectors.toList());
    }

    // Нешаблонный метод - удалить элемент по ID
    public boolean removeById(int id) {
        return items.removeIf(item -> item.getId() == id);
    }

    // Нешаблонный метод - вывести все элементы
    public void printAll() {
        System.out.println("Коллекция: " + name + " (размер: " + items.size() + ")");
        for (T item : items) {
            System.out.println("  ID=" + item.getId() + ", Имя=" + item.getName());
        }
    }

    // Обобщенный метод - получить список всех элементов
    public List<T> getAll() {
        return new ArrayList<>(items);
    }

    // Обобщенный метод - сортировка по компаратору
    public void sort(java.util.Comparator<T> comparator) {
        Collections.sort(items, comparator);
    }
}

public class JavaTemplateClass {
    
    public static void demonstrateTemplateClass() {
        System.out.println("=== Обобщенный класс Collection (Generics) ===");

        // Создание коллекции видео
        System.out.println("\n--- Коллекция видео ---");
        Collection<VideoItem> videoCollection = new Collection<>("Мои фильмы");
        
        // Добавление видео
        videoCollection.addItem(new VideoItem(1, "Matrix", 50.0));
        videoCollection.addItem(new VideoItem(2, "Inception", 60.0));
        videoCollection.addItem(new VideoItem(3, "Avatar", 70.0));

        videoCollection.printAll();

        // Поиск с предикатом
        System.out.println("\nПоиск видео по названию 'Matrix':");
        VideoItem found = videoCollection.findItem(item -> item.getName().equals("Matrix"));
        if (found != null) {
            System.out.println("  Найдено: " + found.getName());
        }

        // Преобразование в список названий
        System.out.println("\nПреобразование в названия:");
        List<String> names = videoCollection.transform(VideoItem::getName);
        for (String name : names) {
            System.out.println("  " + name);
        }

        // Фильтрация дорогих видео
        System.out.println("\nФильтрация видео дороже $55:");
        List<VideoItem> expensive = videoCollection.filter(item -> item.getPrice() > 55.0);
        for (VideoItem item : expensive) {
            System.out.println("  " + item.getName() + " - $" + item.getPrice());
        }

        // Создание коллекции аудио
        System.out.println("\n--- Коллекция аудио ---");
        Collection<AudioItem> audioCollection = new Collection<>("Моя музыка");
        
        audioCollection.addItem(new AudioItem(1, "Song1", "Artist1"));
        audioCollection.addItem(new AudioItem(2, "Song2", "Artist2"));
        audioCollection.addItem(new AudioItem(3, "Song3", "Artist3"));

        audioCollection.printAll();

        // Преобразование в список исполнителей
        System.out.println("\nПреобразование в исполнителей:");
        List<String> artists = audioCollection.transform(AudioItem::getArtist);
        for (String artist : artists) {
            System.out.println("  " + artist);
        }

        // Сортировка по названию
        System.out.println("\nСортировка видео по названию:");
        videoCollection.sort(Comparator.comparing(VideoItem::getName));
        videoCollection.printAll();

        // Удаление элемента
        System.out.println("\nУдаление видео с ID=2...");
        videoCollection.removeById(2);
        videoCollection.printAll();
    }
}
```

---

# C# Collections

## 1. Использование контейнеров, сортировки и поиска

### Задание
Создать программу, которая:
- Использует List<T> для хранения объектов видеоносителей
- Использует LINQ для сортировки и поиска
- Демонстрирует использование других контейнеров (LinkedList<T>, Dictionary<K,V>, SortedSet<T>)

### Реализация

```csharp
using System;
using System.Collections.Generic;
using System.Linq;

// Абстрактный базовый класс
abstract class VideoCarrier
{
    public int Id { get; protected set; }
    public string Title { get; protected set; }
    public string Genre { get; protected set; }
    public double RentalPrice { get; protected set; }

    protected VideoCarrier(int id, string title, string genre, double price)
    {
        Id = id;
        Title = title;
        Genre = genre;
        RentalPrice = price;
    }

    public abstract string GetType();
}

// Производные классы
class DVD : VideoCarrier
{
    public DVD(int id, string title, string genre, double price) 
        : base(id, title, genre, price) { }
    public override string GetType() => "DVD";
}

class BluRay : VideoCarrier
{
    public BluRay(int id, string title, string genre, double price) 
        : base(id, title, genre, price) { }
    public override string GetType() => "BluRay";
}

class VHS : VideoCarrier
{
    public VHS(int id, string title, string genre, double price) 
        : base(id, title, genre, price) { }
    public override string GetType() => "VHS";
}

public class CSharpCollectionsDemo
{
    public static void DemonstrateContainersAndAlgorithms()
    {
        Console.WriteLine("=== C# Collections - Контейнеры и алгоритмы ===");

        // 1. List<T> - динамический список (аналог std::vector / ArrayList)
        Console.WriteLine("\n--- List<T> (аналог std::vector) ---");
        List<VideoCarrier> videoCarriers = new List<VideoCarrier>
        {
            new DVD(1, "Matrix", "Sci-Fi", 50.0),
            new BluRay(2, "Inception", "Sci-Fi", 60.0),
            new VHS(3, "Jaws", "Thriller", 30.0),
            new DVD(4, "Avatar", "Fantasy", 70.0),
            new BluRay(5, "Dune", "Sci-Fi", 75.0)
        };

        Console.WriteLine("Видеоносители: ");
        foreach (var vc in videoCarriers)
        {
            Console.WriteLine($"  {vc.Title} - ${vc.RentalPrice}");
        }

        // 2. LinkedList<T> - двусвязный список (аналог std::list)
        Console.WriteLine("\n--- LinkedList<T> (аналог std::list) ---");
        LinkedList<VideoCarrier> linkedList = new LinkedList<VideoCarrier>(videoCarriers);
        Console.WriteLine($"Размер LinkedList: {linkedList.Count}");

        // 3. Dictionary<K,V> - ассоциативный контейнер (аналог std::map / HashMap)
        Console.WriteLine("\n--- Dictionary<K,V> (аналог std::map) ---");
        Dictionary<int, VideoCarrier> catalogDict = new Dictionary<int, VideoCarrier>();
        foreach (var vc in videoCarriers)
        {
            catalogDict[vc.Id] = vc;
        }
        Console.WriteLine($"Размер Dictionary: {catalogDict.Count}");
        Console.WriteLine($"Видео с ID=2: {catalogDict[2].Title}");

        // 4. SortedDictionary<K,V> - отсортированный словарь
        Console.WriteLine("\n--- SortedDictionary<K,V> (отсортированный) ---");
        SortedDictionary<int, VideoCarrier> sortedDict = new SortedDictionary<int, VideoCarrier>(catalogDict);
        Console.WriteLine("Отсортировано по ID: ");
        foreach (var entry in sortedDict)
        {
            Console.WriteLine($"  ID={entry.Key}: {entry.Value.Title}");
        }

        // 5. HashSet<T> - уникальные элементы
        Console.WriteLine("\n--- HashSet<T> (уникальные элементы) ---");
        HashSet<string> genres = new HashSet<string>();
        foreach (var vc in videoCarriers)
        {
            genres.Add(vc.Genre);
        }
        Console.WriteLine($"Уникальные жанры: {string.Join(", ", genres)}");

        // 6. SortedSet<T> - отсортированное множество
        Console.WriteLine("\n--- SortedSet<T> (отсортированное множество) ---");
        SortedSet<string> sortedGenres = new SortedSet<string>(genres);
        Console.WriteLine($"Жанры (отсортированы): {string.Join(", ", sortedGenres)}");

        // === СОРТИРОВКА ===
        Console.WriteLine("\n=== СОРТИРОВКА ===");
        
        // LINQ OrderBy - аналог std::sort()
        Console.WriteLine("Сортировка по цене (возрастанию):");
        var sortedByPrice = videoCarriers.OrderBy(vc => vc.RentalPrice);
        foreach (var vc in sortedByPrice)
        {
            Console.WriteLine($"  {vc.Title} - ${vc.RentalPrice}");
        }

        // LINQ OrderByDescending - сортировка по убыванию
        Console.WriteLine("\nСортировка по цене (убыванию):");
        var sortedByPriceDesc = videoCarriers.OrderByDescending(vc => vc.RentalPrice);
        foreach (var vc in sortedByPriceDesc)
        {
            Console.WriteLine($"  {vc.Title} - ${vc.RentalPrice}");
        }

        // === ПОИСК ===
        Console.WriteLine("\n=== ПОИСК ===");
        
        // LINQ Where - аналог std::find_if() / filter()
        Console.WriteLine("Поиск видео дороже $60:");
        var expensive = videoCarriers.Where(vc => vc.RentalPrice > 60.0);
        foreach (var vc in expensive)
        {
            Console.WriteLine($"  {vc.Title} - ${vc.RentalPrice}");
        }

        // LINQ First - найти первый элемент
        Console.WriteLine("\nПервое видео жанра 'Sci-Fi':");
        var firstSciFi = videoCarriers.FirstOrDefault(vc => vc.Genre == "Sci-Fi");
        if (firstSciFi != null)
        {
            Console.WriteLine($"  {firstSciFi.Title}");
        }

        // === КОПИРОВАНИЕ ===
        Console.WriteLine("\n=== КОПИРОВАНИЕ ===");
        
        // LINQ Where + ToList - аналог std::copy_if()
        Console.WriteLine("Копирование видео жанра 'Sci-Fi':");
        var sciFiVideos = videoCarriers.Where(vc => vc.Genre == "Sci-Fi").ToList();
        foreach (var vc in sciFiVideos)
        {
            Console.WriteLine($"  {vc.Title} (тип: {vc.GetType()})");
        }

        // LINQ Select - аналог std::transform()
        Console.WriteLine("\nПреобразование в названия:");
        var titles = videoCarriers.Select(vc => vc.Title).ToList();
        foreach (var title in titles)
        {
            Console.WriteLine($"  {title}");
        }

        // === УДАЛЕНИЕ ===
        Console.WriteLine("\n=== УДАЛЕНИЕ ===");
        
        // RemoveAll - аналог std::remove_if()
        Console.WriteLine("Удаление видео дешевле $40:");
        List<VideoCarrier> videosForRemoval = new List<VideoCarrier>(videoCarriers);
        videosForRemoval.RemoveAll(vc => vc.RentalPrice < 40.0);
        foreach (var vc in videosForRemoval)
        {
            Console.WriteLine($"  {vc.Title} - ${vc.RentalPrice}");
        }

        // === ПОИСК MIN/MAX ===
        Console.WriteLine("\n=== ПОИСК MIN/MAX ===");
        
        // LINQ Min / Max - аналог std::min_element() / std::max_element()
        var minPrice = videoCarriers.Min(vc => vc.RentalPrice);
        var minItem = videoCarriers.First(vc => vc.RentalPrice == minPrice);
        Console.WriteLine($"Самое дешевое: {minItem.Title} - ${minPrice}");

        var maxPrice = videoCarriers.Max(vc => vc.RentalPrice);
        var maxItem = videoCarriers.First(vc => vc.RentalPrice == maxPrice);
        Console.WriteLine($"Самое дорогое: {maxItem.Title} - ${maxPrice}");

        // === Any() - аналог std::any_of() ===
        Console.WriteLine("\n=== Any() (аналог std::any_of) ===");
        bool hasExpensive = videoCarriers.Any(vc => vc.RentalPrice > 100.0);
        Console.WriteLine($"Есть видео дороже $100: {(hasExpensive ? "ДА" : "НЕТ")}");

        // All() - все ли элементы удовлетворяют условию
        bool allAffordable = videoCarriers.All(vc => vc.RentalPrice < 100.0);
        Console.WriteLine($"Все видео дешевле $100: {(allAffordable ? "ДА" : "НЕТ")}");
    }
}
```

---

## 2. Обобщенные методы для работы с числовыми типами

### Задание
Создать обобщенные методы, которые:
- Работают с числовыми типами
- Вычисляют статистику
- Используют различные типовые параметры

### Реализация

```csharp
using System;
using System.Collections.Generic;
using System.Linq;

public class TemplateFunction
{
    // Класс для хранения статистики
    public class Statistics<T> where T : struct, IComparable<T>, IFormattable
    {
        public double Average { get; set; }
        public double Minimum { get; set; }
        public double Maximum { get; set; }
        public double Sum { get; set; }

        public override string ToString()
        {
            return $"Сумма: {Sum}, Среднее: {Average:F2}, Минимум: {Minimum}, Максимум: {Maximum}";
        }
    }

    // Обобщенный метод для вычисления статистики
    public static Statistics<T> CalculateStatistics<T>(List<T> data) 
        where T : struct, IComparable<T>, IFormattable
    {
        if (data.Count == 0)
        {
            throw new ArgumentException("Список не может быть пустым");
        }

        // Преобразуем в decimal для удобства вычислений
        var values = data.Select(n => Convert.ToDecimal(n)).ToList();
        
        decimal sum = values.Sum();
        decimal average = sum / data.Count;
        decimal minimum = values.Min();
        decimal maximum = values.Max();

        return new Statistics<T>
        {
            Sum = (double)sum,
            Average = (double)average,
            Minimum = (double)minimum,
            Maximum = (double)maximum
        };
    }

    // Обобщенный метод для масштабирования значений
    public static List<double> ScaleValues<T>(List<T> data, double scale) 
        where T : struct, IComparable<T>, IFormattable
    {
        return data.Select(n => Convert.ToDouble(n) * scale).ToList();
    }

    // Обобщенный метод для фильтрации по диапазону
    public static List<T> FilterByRange<T>(List<T> data, T minVal, T maxVal) 
        where T : struct, IComparable<T>, IFormattable
    {
        double min = Convert.ToDouble(minVal);
        double max = Convert.ToDouble(maxVal);
        
        return data.Where(n => Convert.ToDouble(n) >= min && Convert.ToDouble(n) <= max).ToList();
    }

    // Обобщенный метод для вычисления суммы
    public static double Sum<T>(List<T> data) 
        where T : struct, IComparable<T>, IFormattable
    {
        return data.Select(n => Convert.ToDouble(n)).Sum();
    }

    // Обобщенный метод для вычисления среднего
    public static double Average<T>(List<T> data) 
        where T : struct, IComparable<T>, IFormattable
    {
        if (data.Count == 0) return 0.0;
        return Sum(data) / data.Count;
    }

    public static void DemonstrateTemplateFunction()
    {
        Console.WriteLine("=== Обобщенные методы для работы с числовыми типами ===");

        // Пример с int
        Console.WriteLine("\n--- Целые числа (int) ---");
        List<int> intPrices = new List<int> { 30, 50, 60, 70, 75, 25 };
        var intStats = CalculateStatistics(intPrices);
        Console.WriteLine($"Цены: {string.Join(", ", intPrices)}");
        Console.WriteLine($"Статистика: {intStats}");

        // Пример с double
        Console.WriteLine("\n--- Числа с плавающей точкой (double) ---");
        List<double> doublePrices = new List<double> { 30.5, 50.75, 60.25, 70.0, 75.5, 25.0 };
        var doubleStats = CalculateStatistics(doublePrices);
        Console.WriteLine($"Цены: {string.Join(", ", doublePrices)}");
        Console.WriteLine($"Статистика: {doubleStats}");

        // Масштабирование
        Console.WriteLine("\n--- Масштабирование (* 1.1) ---");
        var scaled = ScaleValues(doublePrices, 1.1);
        Console.WriteLine($"Масштабированные цены: {string.Join(", ", scaled.Select(p => $"{p:F2}"))}");

        // Фильтрация по диапазону
        Console.WriteLine("\n--- Фильтрация по диапазону [50, 70] ---");
        var filtered = FilterByRange(doublePrices, 50.0, 70.0);
        Console.WriteLine($"Отфильтрованные цены: {string.Join(", ", filtered)}");

        // Вычисление суммы и среднего
        Console.WriteLine("\n--- Вычисление суммы и среднего ---");
        Console.WriteLine($"Сумма: {Sum(intPrices)}");
        Console.WriteLine($"Среднее: {Average(intPrices):F2}");
    }
}
```

---

## 3. Обобщенный класс с обобщенными и необобщенными методами

### Задание
Создать обобщенный класс, который:
- Имеет как обобщенные, так и необобщенные методы
- Работает с типами, наследующими интерфейс CollectionItem
- Реализует коллекцию с операциями

### Реализация

```csharp
using System;
using System.Collections.Generic;
using System.Linq;

// Интерфейс для элементов коллекции
interface ICollectionItem
{
    string Name { get; }
    int Id { get; }
}

// Реализации интерфейса
class VideoItem : ICollectionItem
{
    public int Id { get; }
    public string Name { get; }
    public double Price { get; }

    public VideoItem(int id, string name, double price)
    {
        Id = id;
        Name = name;
        Price = price;
    }
}

class AudioItem : ICollectionItem
{
    public int Id { get; }
    public string Name { get; }
    public string Artist { get; }

    public AudioItem(int id, string name, string artist)
    {
        Id = id;
        Name = name;
        Artist = artist;
    }
}

// Обобщенный класс коллекции
public class Collection<T> where T : ICollectionItem
{
    private List<T> items;
    private string name;

    // Необобщенный конструктор
    public Collection(string name)
    {
        this.name = name;
        this.items = new List<T>();
    }

    // Необобщенный метод - получить имя коллекции
    public string GetCollectionName() => name;

    // Необобщенный метод - получить размер
    public int GetSize() => items.Count;

    // Необобщенный метод - добавить элемент
    public void AddItem(T item)
    {
        if (item == null)
        {
            throw new ArgumentNullException(nameof(item), "Элемент не может быть null");
        }
        items.Add(item);
    }

    // Необобщенный метод - получить элемент по индексу
    public T GetItemAt(int index)
    {
        if (index < 0 || index >= items.Count)
        {
            throw new IndexOutOfRangeException("Индекс выходит за границы");
        }
        return items[index];
    }

    // Обобщенный метод - поиск с предикатом
    public T FindItem(Func<T, bool> predicate)
    {
        return items.FirstOrDefault(predicate);
    }

    // Обобщенный метод - преобразование в другой тип
    public List<TResult> Transform<TResult>(Func<T, TResult> converter)
    {
        return items.Select(converter).ToList();
    }

    // Обобщенный метод - фильтрация
    public List<T> Filter(Func<T, bool> predicate)
    {
        return items.Where(predicate).ToList();
    }

    // Необобщенный метод - удалить элемент по ID
    public bool RemoveById(int id)
    {
        var item = items.FirstOrDefault(i => i.Id == id);
        if (item != null)
        {
            items.Remove(item);
            return true;
        }
        return false;
    }

    // Необобщенный метод - вывести все элементы
    public void PrintAll()
    {
        Console.WriteLine($"Коллекция: {name} (размер: {items.Count})");
        foreach (var item in items)
        {
            Console.WriteLine($"  ID={item.Id}, Имя={item.Name}");
        }
    }

    // Обобщенный метод - получить список всех элементов
    public List<T> GetAll() => new List<T>(items);

    // Обобщенный метод - сортировка по компаратору
    public void Sort(Comparison<T> comparison)
    {
        items.Sort(comparison);
    }
}

public class CSharpTemplateClass
{
    public static void DemonstrateTemplateClass()
    {
        Console.WriteLine("=== Обобщенный класс Collection<T> ===");

        // Создание коллекции видео
        Console.WriteLine("\n--- Коллекция видео ---");
        Collection<VideoItem> videoCollection = new Collection<VideoItem>("Мои фильмы");
        
        // Добавление видео
        videoCollection.AddItem(new VideoItem(1, "Matrix", 50.0));
        videoCollection.AddItem(new VideoItem(2, "Inception", 60.0));
        videoCollection.AddItem(new VideoItem(3, "Avatar", 70.0));

        videoCollection.PrintAll();

        // Поиск с предикатом
        Console.WriteLine("\nПоиск видео по названию 'Matrix':");
        var found = videoCollection.FindItem(item => item.Name == "Matrix");
        if (found != null)
        {
            Console.WriteLine($"  Найдено: {found.Name}");
        }

        // Преобразование в список названий
        Console.WriteLine("\nПреобразование в названия:");
        var names = videoCollection.Transform<string>(item => item.Name);
        foreach (var name in names)
        {
            Console.WriteLine($"  {name}");
        }

        // Фильтрация дорогих видео
        Console.WriteLine("\nФильтрация видео дороже $55:");
        var expensive = videoCollection.Filter(item => item.Price > 55.0);
        foreach (var item in expensive)
        {
            Console.WriteLine($"  {item.Name} - ${item.Price}");
        }

        // Создание коллекции аудио
        Console.WriteLine("\n--- Коллекция аудио ---");
        Collection<AudioItem> audioCollection = new Collection<AudioItem>("Моя музыка");
        
        audioCollection.AddItem(new AudioItem(1, "Song1", "Artist1"));
        audioCollection.AddItem(new AudioItem(2, "Song2", "Artist2"));
        audioCollection.AddItem(new AudioItem(3, "Song3", "Artist3"));

        audioCollection.PrintAll();

        // Преобразование в список исполнителей
        Console.WriteLine("\nПреобразование в исполнителей:");
        var artists = audioCollection.Transform<string>(item => item.Artist);
        foreach (var artist in artists)
        {
            Console.WriteLine($"  {artist}");
        }

        // Сортировка по названию
        Console.WriteLine("\nСортировка видео по названию:");
        videoCollection.Sort((a, b) => a.Name.CompareTo(b.Name));
        videoCollection.PrintAll();

        // Удаление элемента
        Console.WriteLine("\nУдаление видео с ID=2...");
        videoCollection.RemoveById(2);
        videoCollection.PrintAll();
    }
}
```

---

---

# Производные классы и полиморфизм

## Требование: Использование производных классов в контейнерах

### Назначение производных классов

В проекте видеопроката необходимы различные типы клиентов с разными привилегиями и скидками, а также различные типы видеоносителей с разными характеристиками.

### Java: Производные классы Client

#### 1. PremiumClient - Премиальный клиент

**Назначение**: Клиент с системой лояльности, скидками и предпочтениями в уведомлениях.

**Характеристики**:
- Расширяет ClientReal
- Реализует интерфейсы Discountable и Notifiable
- Имеет собственные методы для работы с баллами лояльности

**Пример использования в контейнере**:

```java
// Создание списка различных типов клиентов
List<Client> clients = new ArrayList<>();
clients.add(new ClientReal(1, "John", "Doe", "+1-111-1111"));
clients.add(new PremiumClient(2, "Jane", "Smith", "+1-222-2222", "jane@example.com", 15.0));
clients.add(new CorporateClient(3, "Bob", "Johnson", "+1-333-3333", "TechCorp", "12345", 150));
clients.add(new StudentClient(4, "Alice", "Brown", "+1-444-4444", "State University", "STU123", "CS", "alice@uni.edu"));
clients.add(new VIPClient(5, "David", "Wilson", "+1-555-5555", "platinum", "david@example.com", "John Manager"));

// Применение скидок для клиентов, которые их поддерживают
System.out.println("=== Применение скидок ===");
for (Client client : clients) {
    if (client instanceof Discountable) {
        Discountable discountableClient = (Discountable) client;
        double originalPrice = 100.0;
        double discountedPrice = discountableClient.applyDiscount(originalPrice);
        System.out.printf("%s: $%.2f -> $%.2f (%.1f%% скидка)%n",
            client.getFirstName(),
            originalPrice,
            discountedPrice,
            discountableClient.getDiscountPercentage());
    }
}

// Отправка уведомлений для клиентов, которые их поддерживают
System.out.println("\n=== Отправка уведомлений ===");
for (Client client : clients) {
    if (client instanceof Notifiable) {
        Notifiable notifiableClient = (Notifiable) client;
        notifiableClient.sendNotification("Добро пожаловать в видеопрокат! Используйте код WELCOME для получения скидки.");
    }
}

// Сортировка по типу клиента
System.out.println("\n=== Сортировка по типу ===");
List<Client> premiumClients = new ArrayList<>();
for (Client client : clients) {
    if (client instanceof Discountable) {
        premiumClients.add(client);
    }
}
System.out.println("Премиальные клиенты: " + premiumClients.size());

// Поиск премиального клиента по скидке
System.out.println("\n=== Поиск клиента с максимальной скидкой ===");
Client maxDiscountClient = null;
double maxDiscount = 0.0;
for (Client client : clients) {
    if (client instanceof Discountable) {
        double discount = ((Discountable) client).getDiscountPercentage();
        if (discount > maxDiscount) {
            maxDiscount = discount;
            maxDiscountClient = client;
        }
    }
}
if (maxDiscountClient != null) {
    System.out.println("Клиент с максимальной скидкой: " + maxDiscountClient.getFirstName() + 
                       " (скидка: " + maxDiscount + "%)");
}

// Копирование премиальных клиентов в новый список
System.out.println("\n=== Копирование премиальных клиентов (Stream API) ===");
List<Client> vipClientsList = clients.stream()
    .filter(c -> c instanceof PremiumClient || c instanceof VIPClient)
    .collect(Collectors.toList());
System.out.println("ВИП клиентов: " + vipClientsList.size());
for (Client vip : vipClientsList) {
    System.out.println("  - " + vip.getFirstName() + " " + vip.getLastName());
}
```

#### 2. CorporateClient - Корпоративный клиент

**Назначение**: Клиент от компании с корпоративными скидками.

**Характеристики**:
- Расширяет ClientReal
- Реализует интерфейс Discountable
- Скидка зависит от размера компании

#### 3. StudentClient - Студентский клиент

**Назначение**: Студент с льготными скидками и валидацией.

**Характеристики**:
- Расширяет ClientReal
- Реализует интерфейсы Discountable и Notifiable
- Скидка может быть отозвана при потере статуса студента

#### 4. VIPClient - ВИП клиент

**Назначение**: Премиальный ВИП клиент с максимальными привилегиями.

**Характеристики**:
- Расширяет ClientReal
- Реализует интерфейсы Discountable и Notifiable
- Имеет уровни (platinum, gold, silver)
- Накопление кэшбека

### Java: Производные классы VideoCarrier

#### PremiumVideoCarrier - Премиальный видеоноситель

**Назначение**: Видеоноситель в формате 4K/Ultra HD с особыми характеристиками.

**Пример использования в контейнере**:

```java
// Создание каталога с различными видеоносителями
List<VideoCarrier> catalog = new ArrayList<>();
catalog.add(new VideoCarrierReal(1, "Matrix", "DVD", "Sci-Fi", 50.0, 500.0));
catalog.add(new VideoCarrierReal(2, "Avatar", "BluRay", "Fantasy", 60.0, 600.0));
catalog.add(new PremiumVideoCarrier(3, "Dune 4K", "BluRay", "Sci-Fi", 80.0, 800.0, "4K Ultra HD", "Dolby Vision, HDR10, Atmos Sound"));
catalog.add(new VideoCarrierReal(4, "Inception", "DVD", "Sci-Fi", 55.0, 550.0));
catalog.add(new PremiumVideoCarrier(5, "Blade Runner 2049", "BluRay", "Sci-Fi", 85.0, 850.0, "4K Ultra HD", "Award-winning cinematography, Dolby Vision"));

// Поиск премиальных видео
System.out.println("=== Поиск премиальных видео ===");
List<VideoCarrier> premiumVideos = catalog.stream()
    .filter(v -> v instanceof PremiumVideoCarrier)
    .collect(Collectors.toList());
System.out.println("Премиальных видео: " + premiumVideos.size());

// Сортировка по цене
System.out.println("\n=== Сортировка по цене аренды ===");
List<VideoCarrier> sortedByPrice = new ArrayList<>(catalog);
Collections.sort(sortedByPrice, Comparator.comparingDouble(VideoCarrier::getRentalPricePerDay));
for (VideoCarrier video : sortedByPrice) {
    String type = video instanceof PremiumVideoCarrier ? "[PREMIUM]" : "[STANDARD]";
    System.out.printf("%s %s - $%.2f/day%n", type, video.getTitle(), video.getRentalPricePerDay());
}

// Фильтрация по типу и жанру
System.out.println("\n=== Фильтрация: Sci-Fi видео дороже $60 ===");
List<VideoCarrier> expensiveSciFi = catalog.stream()
    .filter(v -> "Sci-Fi".equals(v.getGenre()))
    .filter(v -> v.getRentalPricePerDay() > 60.0)
    .collect(Collectors.toList());
for (VideoCarrier video : expensiveSciFi) {
    System.out.println("  - " + video.getTitle() + " ($" + video.getRentalPricePerDay() + "/day)");
}

// min/max элементы
System.out.println("\n=== Минимум и максимум ===");
VideoCarrier cheapest = Collections.min(catalog, Comparator.comparingDouble(VideoCarrier::getRentalPricePerDay));
VideoCarrier expensive = Collections.max(catalog, Comparator.comparingDouble(VideoCarrier::getRentalPricePerDay));
System.out.println("Самое дешевое: " + cheapest.getTitle());
System.out.println("Самое дорогое: " + expensive.getTitle());

// any_of - есть ли дорогое видео
System.out.println("\n=== Проверка наличия дорогого видео ===");
boolean hasExpensiveVideo = catalog.stream().anyMatch(v -> v.getRentalPricePerDay() > 80.0);
System.out.println("Есть видео дороже $80: " + hasExpensiveVideo);
```

### C++ эквивалент с STL

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

// Различные типы клиентов
class ClientBase {
public:
    virtual ~ClientBase() = default;
    virtual std::string getName() const = 0;
    virtual double getDiscount() const = 0;
};

class RegularClient : public ClientBase {
private:
    std::string name;
public:
    RegularClient(const std::string& n) : name(n) {}
    std::string getName() const override { return name; }
    double getDiscount() const override { return 0.0; }
};

class PremiumClientCpp : public ClientBase {
private:
    std::string name;
    double discount;
public:
    PremiumClientCpp(const std::string& n, double d) : name(n), discount(d) {}
    std::string getName() const override { return name; }
    double getDiscount() const override { return discount; }
};

void demonstrateDerivedClassesWithSTL() {
    std::cout << "=== STL: Производные классы в контейнерах ===" << std::endl;

    // std::vector указателей на базовый класс
    std::vector<std::unique_ptr<ClientBase>> clients;
    clients.push_back(std::make_unique<RegularClient>("John Doe"));
    clients.push_back(std::make_unique<PremiumClientCpp>("Jane Smith", 15.0));
    clients.push_back(std::make_unique<RegularClient>("Bob Johnson"));
    clients.push_back(std::make_unique<PremiumClientCpp>("Alice Brown", 25.0));

    // Применение скидок (работает полиморфно)
    std::cout << "\n--- Применение скидок ---" << std::endl;
    for (const auto& client : clients) {
        std::cout << client->getName() << ": $" 
                  << (100.0 * (1.0 - client->getDiscount() / 100.0)) 
                  << " (скидка " << client->getDiscount() << "%)" << std::endl;
    }

    // std::find_if - найти первого премиального клиента
    std::cout << "\n--- Поиск премиального клиента ---" << std::endl;
    auto premiumClient = std::find_if(clients.begin(), clients.end(),
        [](const std::unique_ptr<ClientBase>& c) { return c->getDiscount() > 0.0; }
    );
    if (premiumClient != clients.end()) {
        std::cout << "Найден: " << (*premiumClient)->getName() << std::endl;
    }

    // std::copy_if - копировать всех премиальных клиентов
    std::cout << "\n--- Копирование премиальных клиентов ---" << std::endl;
    std::vector<std::string> premiumNames;
    for (const auto& client : clients) {
        if (client->getDiscount() > 0.0) {
            premiumNames.push_back(client->getName());
        }
    }
    for (const auto& name : premiumNames) {
        std::cout << "  - " << name << std::endl;
    }

    // std::max_element - найти клиента с максимальной скидкой
    std::cout << "\n--- Максимальная скидка ---" << std::endl;
    auto maxClient = std::max_element(clients.begin(), clients.end(),
        [](const std::unique_ptr<ClientBase>& a, const std::unique_ptr<ClientBase>& b) {
            return a->getDiscount() < b->getDiscount();
        }
    );
    if (maxClient != clients.end()) {
        std::cout << "Клиент с максимальной скидкой: " << (*maxClient)->getName() 
                  << " (" << (*maxClient)->getDiscount() << "%)" << std::endl;
    }

    // std::sort - сортировка по скидке
    std::cout << "\n--- Сортировка по скидке ---" << std::endl;
    std::vector<ClientBase*> sortedClients;
    for (auto& client : clients) {
        sortedClients.push_back(client.get());
    }
    std::sort(sortedClients.begin(), sortedClients.end(),
        [](ClientBase* a, ClientBase* b) {
            return a->getDiscount() < b->getDiscount();
        }
    );
    for (const auto& client : sortedClients) {
        std::cout << "  " << client->getName() << " - " << client->getDiscount() << "% скидка" << std::endl;
    }

    // std::any_of - есть ли скидка больше 20%
    std::cout << "\n--- Проверка: есть ли скидка > 20% ---" << std::endl;
    bool hasHighDiscount = std::any_of(clients.begin(), clients.end(),
        [](const std::unique_ptr<ClientBase>& c) { return c->getDiscount() > 20.0; }
    );
    std::cout << "Есть скидка > 20%: " << (hasHighDiscount ? "ДА" : "НЕТ") << std::endl;
}
```

---

# Заключение

В этом документе продемонстрированы:

1. **Контейнеры и алгоритмы**
   - Использование различных контейнеров (array, vector/ArrayList, list/LinkedList, map/HashMap)
   - Сортировка, поиск, копирование и удаление элементов
   - Работа с полиморфизмом в контейнерах
   - Использование производных классов в контейнерах базовых типов

2. **Шаблонные функции**
   - Ограничения типов на уровне компиляции (concepts в C++, bounds в Java/C#)
   - Работа с числовыми типами
   - Обобщенные операции над данными

3. **Шаблонные классы**
   - Сочетание шаблонных и нешаблонных методов
   - Работа с наследованием и полиморфизмом
   - CRUD операции в обобщенной коллекции

4. **Производные классы и полиморфизм**
   - Множество производных классов (PremiumClient, CorporateClient, StudentClient, VIPClient, PremiumVideoCarrier)
   - Реализация интерфейсов (Discountable, Notifiable)
   - Хранение производных объектов в контейнерах базовых типов
   - Полиморфное использование объектов через базовые типы

Все примеры демонстрируют лучшие практики для каждого языка:
- **C++**: использование STL, концепций (C++20), умных указателей и полиморфизма
- **Java**: использование Collections Framework, Stream API, интерфейсов и наследования
- **C#**: использование LINQ, обобщенных типов и полиморфизма
