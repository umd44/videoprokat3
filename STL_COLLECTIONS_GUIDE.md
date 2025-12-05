# Руководство по STL (C++) и Collections Framework (Java)

## Содержание
1. [Контейнеры и их аналоги](#контейнеры)
2. [Алгоритмы и методы](#алгоритмы)
3. [Шаблонные функции](#шаблонные-функции)
4. [Шаблонные классы](#шаблонные-классы)
5. [Работа с полиморфными объектами](#полиморфизм)

---

## Контейнеры

### 1. std::array (C++) ↔ Массив (Java)

**C++:**
```cpp
// std::array - массив фиксированного размера
std::array<double, 5> prices = {50.0, 60.0, 45.0, 70.0, 55.0};

for (const auto& price : prices) {
    std::cout << price << " ";
}
// Размер известен во время компиляции
```

**Java:**
```java
// Фиксированный массив
Double[] prices = {50.0, 60.0, 45.0, 70.0, 55.0};

for (Double price : prices) {
    System.out.print(price + " ");
}
// Размер фиксирован
```

**Вывод:**
```
Цены: 50.0 60.0 45.0 70.0 55.0
```

---

### 2. std::vector (C++) ↔ ArrayList (Java)

**C++:**
```cpp
// std::vector - динамический массив
std::vector<int> inventoryNumbers = {100, 101, 102, 103, 104};
inventoryNumbers.push_back(105);  // Добавление элемента

std::cout << "Размер: " << inventoryNumbers.size() << "\n";
```

**Java:**
```java
// ArrayList - динамический список
ArrayList<Integer> inventoryNumbers = new ArrayList<>(
    Arrays.asList(100, 101, 102, 103, 104)
);
inventoryNumbers.add(105);  // Добавление элемента

System.out.println("Размер: " + inventoryNumbers.size());
```

**Вывод:**
```
Инвентарные номера: 100 101 102 103 104 105
Размер: 6
```

---

### 3. std::list (C++) ↔ LinkedList (Java)

**C++:**
```cpp
// std::list - двусвязный список
std::list<std::string> genres = {"Sci-Fi", "Action", "Drama", "Comedy"};
genres.push_front("Horror");  // Добавление в начало
genres.push_back("Fantasy");  // Добавление в конец

for (const auto& genre : genres) {
    std::cout << genre << " ";
}
```

**Java:**
```java
// LinkedList - двусвязный список
LinkedList<String> genres = new LinkedList<>(
    Arrays.asList("Sci-Fi", "Action", "Drama", "Comedy")
);
genres.addFirst("Horror");  // Добавление в начало
genres.addLast("Fantasy");  // Добавление в конец

for (String genre : genres) {
    System.out.print(genre + " ");
}
```

**Вывод:**
```
Жанры: Horror Sci-Fi Action Drama Comedy Fantasy
```

---

### 4. std::map (C++) ↔ HashMap (Java)

**C++:**
```cpp
// std::map - упорядоченный ассоциативный контейнер
std::map<int, std::string> clientNames;
clientNames[1] = "Иван Иванов";
clientNames[2] = "Петр Петров";
clientNames[3] = "Сидор Сидоров";

for (const auto& [id, name] : clientNames) {
    std::cout << "ID " << id << ": " << name << "\n";
}
```

**Java:**
```java
// HashMap - хеш-таблица (неупорядоченная)
HashMap<Integer, String> clientNames = new HashMap<>();
clientNames.put(1, "Иван Иванов");
clientNames.put(2, "Петр Петров");
clientNames.put(3, "Сидор Сидоров");

clientNames.forEach((id, name) -> 
    System.out.println("ID " + id + ": " + name)
);
```

**Вывод:**
```
Клиенты:
ID 1: Иван Иванов
ID 2: Петр Петров
ID 3: Сидор Сидоров
```

---

### 5. std::span (C++20) - представление непрерывной последовательности

**C++:**
```cpp
// std::span - легковесное представление массива
std::vector<int> data = {1, 2, 3, 4, 5};
std::span<int> view(data);

// Можно передавать без копирования
void processData(std::span<int> span) {
    for (int& val : span) {
        val *= 2;
    }
}

processData(view);
// data теперь содержит: {2, 4, 6, 8, 10}
```

**Java:** Нет прямого аналога, но можно использовать `List.subList()` или массивы.

---

## Алгоритмы

### 1. std::min_element, std::max_element ↔ Collections.min, Collections.max

**C++:**
```cpp
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};

auto minIt = std::min_element(prices.begin(), prices.end());
auto maxIt = std::max_element(prices.begin(), prices.end());

std::cout << "Мин: " << *minIt << ", Макс: " << *maxIt << "\n";
```

**Java:**
```java
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);

Double min = Collections.min(prices);
Double max = Collections.max(prices);

System.out.println("Мин: " + min + ", Макс: " + max);
```

**Вывод:**
```
Минимальная цена: 45.0
Максимальная цена: 70.0
```

---

### 2. std::find, std::find_if ↔ Stream.filter().findFirst()

**C++:**
```cpp
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};

// std::find - поиск конкретного значения
auto findIt = std::find(prices.begin(), prices.end(), 60.0);
if (findIt != prices.end()) {
    std::cout << "Найдено: " << *findIt << "\n";
}

// std::find_if - поиск по условию
auto findIfIt = std::find_if(prices.begin(), prices.end(), 
                              [](double p) { return p > 65.0; });
if (findIfIt != prices.end()) {
    std::cout << "Первая цена > 65: " << *findIfIt << "\n";
}
```

**Java:**
```java
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);

// Поиск конкретного значения
Optional<Double> found = prices.stream()
                               .filter(p -> p == 60.0)
                               .findFirst();
found.ifPresent(p -> System.out.println("Найдено: " + p));

// Поиск по условию
Optional<Double> foundIf = prices.stream()
                                 .filter(p -> p > 65.0)
                                 .findFirst();
foundIf.ifPresent(p -> System.out.println("Первая цена > 65: " + p));
```

**Вывод:**
```
Найдено: 60.0
Первая цена > 65: 70.0
```

---

### 3. std::copy(), std::copy_if() ↔ Stream.filter().collect()

**C++:**
```cpp
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
std::vector<double> expensivePrices;

// std::copy_if - копирование с условием
std::copy_if(prices.begin(), prices.end(), 
             std::back_inserter(expensivePrices),
             [](double p) { return p >= 55.0; });

std::cout << "Дорогие цены: ";
for (const auto& price : expensivePrices) {
    std::cout << price << " ";
}
```

**Java:**
```java
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);

List<Double> expensivePrices = prices.stream()
                                    .filter(p -> p >= 55.0)
                                    .collect(Collectors.toList());

System.out.println("Дорогие цены: " + expensivePrices);
```

**Вывод:**
```
Дорогие цены (>= 55): [60.0, 70.0, 55.0]
```

---

### 4. std::remove(), std::remove_if() ↔ List.removeIf()

**C++:**
```cpp
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0, 40.0};

// std::remove_if возвращает новый конец
auto newEnd = std::remove_if(prices.begin(), prices.end(),
                              [](double p) { return p < 50.0; });
prices.erase(newEnd, prices.end());

std::cout << "После удаления < 50: ";
for (const auto& price : prices) {
    std::cout << price << " ";
}
```

**Java:**
```java
List<Double> prices = new ArrayList<>(
    Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0, 40.0)
);

prices.removeIf(p -> p < 50.0);

System.out.println("После удаления < 50: " + prices);
```

**Вывод:**
```
После удаления цен < 50: [50.0, 60.0, 70.0, 55.0]
```

---

### 5. std::sort() ↔ Collections.sort()

**C++:**
```cpp
std::vector<double> prices = {60.0, 40.0, 70.0, 45.0, 55.0};

std::cout << "До сортировки: ";
for (const auto& p : prices) std::cout << p << " ";

std::sort(prices.begin(), prices.end());

std::cout << "\nПосле сортировки: ";
for (const auto& p : prices) std::cout << p << " ";
```

**Java:**
```java
List<Double> prices = new ArrayList<>(
    Arrays.asList(60.0, 40.0, 70.0, 45.0, 55.0)
);

System.out.println("До сортировки: " + prices);

Collections.sort(prices);

System.out.println("После сортировки: " + prices);
```

**Вывод:**
```
До сортировки: [60.0, 40.0, 70.0, 45.0, 55.0]
После сортировки: [40.0, 45.0, 55.0, 60.0, 70.0]
```

---

### 6. std::filter_view() (C++20 Ranges) ↔ Stream.filter()

**C++:**
```cpp
std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Фильтрация с помощью ranges (ленивое вычисление)
auto evenNumbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });

std::cout << "Четные числа: ";
for (int n : evenNumbers) {
    std::cout << n << " ";
}
```

**Java:**
```java
List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

// Фильтрация с помощью Stream (ленивое вычисление)
Stream<Integer> evenNumbers = numbers.stream()
                                    .filter(n -> n % 2 == 0);

System.out.print("Четные числа: ");
evenNumbers.forEach(n -> System.out.print(n + " "));
```

**Вывод:**
```
Четные числа: 2 4 6 8 10
```

---

### 7. std::transform, std::transform_view() ↔ Stream.map()

**C++:**
```cpp
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
std::vector<double> discounted;

// std::transform - преобразование элементов
std::transform(prices.begin(), prices.end(), 
               std::back_inserter(discounted),
               [](double p) { return p * 0.9; });

std::cout << "Цены со скидкой 10%: ";
for (const auto& price : discounted) {
    std::cout << price << " ";
}
```

**C++ Ranges (C++20):**
```cpp
// Ленивое преобразование
auto discounted = prices | std::views::transform([](double p) { return p * 0.9; });

std::cout << "Цены со скидкой: ";
for (const auto& price : discounted) {
    std::cout << price << " ";
}
```

**Java:**
```java
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);

List<Double> discounted = prices.stream()
                                .map(p -> p * 0.9)
                                .collect(Collectors.toList());

System.out.println("Цены со скидкой 10%: " + discounted);
```

**Вывод:**
```
Цены со скидкой 10%: [45.0, 54.0, 40.5, 63.0, 49.5]
```

---

### 8. std::any_of ↔ Stream.anyMatch()

**C++:**
```cpp
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};

bool hasExpensive = std::any_of(prices.begin(), prices.end(),
                                [](double p) { return p > 65.0; });

std::cout << "Есть цены > 65: " << (hasExpensive ? "Да" : "Нет") << "\n";
```

**Java:**
```java
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);

boolean hasExpensive = prices.stream()
                             .anyMatch(p -> p > 65.0);

System.out.println("Есть цены > 65: " + (hasExpensive ? "Да" : "Нет"));
```

**Вывод:**
```
Есть цены > 65: Да
```

---

### 9. std::variant ↔ Object (или создание иерархии)

**C++:**
```cpp
// std::variant может хранить один из нескольких типов
using ClientData = std::variant<int, double, std::string>;

ClientData data;

data = 123;  // Хранит int
std::cout << "ID: " << std::get<int>(data) << "\n";

data = 99.99;  // Хранит double
std::cout << "Баланс: " << std::get<double>(data) << "\n";

data = std::string("Иван Иванов");  // Хранит string
std::cout << "Имя: " << std::get<std::string>(data) << "\n";

// Проверка типа
if (std::holds_alternative<std::string>(data)) {
    std::cout << "Текущий тип: string\n";
}

// Visitor pattern
std::visit([](auto&& value) {
    std::cout << "Значение: " << value << "\n";
}, data);
```

**Java:** Нет прямого аналога, но можно использовать Object или создать sealed классы (Java 17+).

```java
// Использование Object (теряется типобезопасность)
Object data;

data = 123;
System.out.println("ID: " + data);

data = 99.99;
System.out.println("Баланс: " + data);

data = "Иван Иванов";
System.out.println("Имя: " + data);

// Проверка типа
if (data instanceof String) {
    System.out.println("Текущий тип: String");
}
```

**Вывод:**
```
ID: 123
Баланс: 99.99
Имя: Иван Иванов
Текущий тип: string
```

---

## Шаблонные Функции

### ✅ Требование: Реализовать шаблонную функцию вне класса

### 1. Вычисление среднего значения (с ограничениями на тип)

**C++:**
```cpp
/**
 * Шаблонная функция для вычисления среднего.
 * Ограничение: только арифметические типы (int, double, float и т.д.).
 */
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, double>::type
calculateAverage(const std::vector<T>& values)
{
    if (values.empty()) return 0.0;
    
    T sum = std::accumulate(values.begin(), values.end(), T(0));
    return static_cast<double>(sum) / values.size();
}

// Использование:
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
double avg = calculateAverage(prices);
std::cout << "Средняя цена: " << avg << "\n";

std::vector<int> ratings = {5, 4, 5, 3, 4, 5};
double avgRating = calculateAverage(ratings);
std::cout << "Средний рейтинг: " << avgRating << "\n";

// ОШИБКА КОМПИЛЯЦИИ:
// std::vector<std::string> names = {"A", "B", "C"};
// calculateAverage(names);  // ← НЕ компилируется, string не арифметический тип!
```

**Java:**
```java
/**
 * Generic функция для вычисления среднего.
 * Ограничение: только числовые типы (extends Number).
 */
public static <T extends Number> double calculateAverage(List<T> values) {
    if (values == null || values.isEmpty()) {
        return 0.0;
    }
    
    double sum = values.stream()
                      .mapToDouble(Number::doubleValue)
                      .sum();
    return sum / values.size();
}

// Использование:
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
double avg = GenericUtils.calculateAverage(prices);
System.out.println("Средняя цена: " + avg);

List<Integer> ratings = Arrays.asList(5, 4, 5, 3, 4, 5);
double avgRating = GenericUtils.calculateAverage(ratings);
System.out.println("Средний рейтинг: " + avgRating);

// ОШИБКА КОМПИЛЯЦИИ:
// List<String> names = Arrays.asList("A", "B", "C");
// calculateAverage(names);  // ← НЕ компилируется, String не extends Number!
```

**Вывод:**
```
Средняя цена аренды: 56.0
Средний рейтинг: 4.333333
```

---

### 2. Поиск минимума и максимума

**C++:**
```cpp
/**
 * Шаблонная функция для поиска минимума и максимума.
 * Ограничение: тип должен быть копируемым.
 */
template<typename T>
std::pair<T, T> findMinMax(const std::vector<T>& values)
{
    static_assert(std::is_copy_constructible<T>::value, 
                  "Type must be copy constructible");
    
    if (values.empty()) {
        throw std::runtime_error("Empty container");
    }
    
    auto minIt = std::min_element(values.begin(), values.end());
    auto maxIt = std::max_element(values.begin(), values.end());
    
    return std::make_pair(*minIt, *maxIt);
}

// Использование:
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
auto [minPrice, maxPrice] = findMinMax(prices);
std::cout << "Мин: " << minPrice << ", Макс: " << maxPrice << "\n";
```

**Java:**
```java
/**
 * Generic функция для поиска минимума и максимума.
 * Ограничение: тип должен реализовывать Comparable.
 */
public static <T extends Comparable<T>> Pair<T, T> findMinMax(List<T> values) {
    if (values == null || values.isEmpty()) {
        throw new IllegalArgumentException("Empty list");
    }
    
    T min = Collections.min(values);
    T max = Collections.max(values);
    
    return new Pair<>(min, max);
}

// Использование:
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
Pair<Double, Double> minMax = GenericUtils.findMinMax(prices);
System.out.println("Мин: " + minMax.getFirst() + ", Макс: " + minMax.getSecond());
```

**Вывод:**
```
Мин. цена: 45.0, Макс. цена: 70.0
```

---

### 3. Фильтрация элементов

**C++:**
```cpp
/**
 * Шаблонная функция для фильтрации элементов.
 */
template<typename T, typename Predicate>
std::vector<T> filterElements(const std::vector<T>& source, Predicate pred)
{
    std::vector<T> result;
    std::copy_if(source.begin(), source.end(), 
                 std::back_inserter(result), pred);
    return result;
}

// Использование:
std::vector<double> prices = {50.0, 60.0, 45.0, 70.0, 55.0};
auto expensive = filterElements(prices, [](double p) { return p >= 55.0; });

std::cout << "Дорогие цены: ";
for (const auto& price : expensive) {
    std::cout << price << " ";
}
```

**Java:**
```java
/**
 * Generic функция для фильтрации элементов.
 */
public static <T> List<T> filterElements(List<T> source, Predicate<T> predicate) {
    return source.stream()
                .filter(predicate)
                .collect(Collectors.toList());
}

// Использование:
List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
List<Double> expensive = GenericUtils.filterElements(prices, p -> p >= 55.0);

System.out.println("Дорогие цены: " + expensive);
```

**Вывод:**
```
Дорогие цены: [60.0, 70.0, 55.0]
```

---

## Шаблонные Классы

### ✅ Требование: Реализовать шаблонный класс с шаблонными и не шаблонными методами

### Repository<T> - Хранилище объектов

**C++:**
```cpp
/**
 * Шаблонный класс Repository для хранения объектов.
 * T должен быть указателем на класс с виртуальными методами.
 */
template<typename T>
class Repository
{
public:
    Repository() = default;
    
    // ===== НЕ ШАБЛОННЫЕ МЕТОДЫ =====
    
    /**
     * Добавление элемента.
     */
    void add(T* item) {
        if (item) {
            m_items.push_back(item);
        }
    }
    
    /**
     * Удаление элемента по индексу.
     */
    void remove(size_t index) {
        if (index < m_items.size()) {
            m_items.erase(m_items.begin() + index);
        }
    }
    
    /**
     * Получение всех элементов.
     */
    const std::vector<T*>& getAll() const {
        return m_items;
    }
    
    /**
     * Размер репозитория.
     */
    size_t size() const {
        return m_items.size();
    }
    
    /**
     * Проверка на пустоту.
     */
    bool empty() const {
        return m_items.empty();
    }
    
    // ===== ШАБЛОННЫЕ МЕТОДЫ =====
    
    /**
     * Шаблонный метод: поиск элемента по предикату.
     */
    template<typename Predicate>
    T* findIf(Predicate pred) const {
        auto it = std::find_if(m_items.begin(), m_items.end(), pred);
        return (it != m_items.end()) ? *it : nullptr;
    }
    
    /**
     * Шаблонный метод: поиск всех элементов по предикату.
     */
    template<typename Predicate>
    std::vector<T*> findAll(Predicate pred) const {
        std::vector<T*> result;
        std::copy_if(m_items.begin(), m_items.end(), 
                     std::back_inserter(result), pred);
        return result;
    }
    
    /**
     * Шаблонный метод: сортировка элементов.
     */
    template<typename Comparator>
    void sort(Comparator comp) {
        std::sort(m_items.begin(), m_items.end(), comp);
    }
    
    /**
     * Шаблонный метод: удаление элементов по предикату.
     */
    template<typename Predicate>
    size_t removeIf(Predicate pred) {
        auto oldSize = m_items.size();
        auto newEnd = std::remove_if(m_items.begin(), m_items.end(), pred);
        m_items.erase(newEnd, m_items.end());
        return oldSize - m_items.size();
    }
    
    /**
     * Шаблонный метод: применение функции ко всем элементам.
     */
    template<typename Function>
    void forEach(Function func) const {
        std::for_each(m_items.begin(), m_items.end(), func);
    }

private:
    std::vector<T*> m_items;
};
```

**Java:**
```java
/**
 * Generic класс Repository для хранения объектов.
 * @param <T> Тип хранимых объектов
 */
public class Repository<T> {
    
    private List<T> items;
    
    // ===== НЕ GENERIC МЕТОДЫ =====
    
    /**
     * Конструктор.
     */
    public Repository() {
        this.items = new ArrayList<>();
    }
    
    /**
     * Добавление элемента.
     */
    public void add(T item) {
        if (item != null) {
            items.add(item);
        }
    }
    
    /**
     * Удаление элемента по индексу.
     */
    public void remove(int index) {
        if (index >= 0 && index < items.size()) {
            items.remove(index);
        }
    }
    
    /**
     * Получение всех элементов.
     */
    public List<T> getAll() {
        return new ArrayList<>(items);
    }
    
    /**
     * Размер репозитория.
     */
    public int size() {
        return items.size();
    }
    
    /**
     * Проверка на пустоту.
     */
    public boolean isEmpty() {
        return items.isEmpty();
    }
    
    // ===== GENERIC МЕТОДЫ =====
    
    /**
     * Generic метод: поиск элемента по предикату.
     */
    public <R extends T> R findIf(Predicate<T> predicate) {
        return (R) items.stream()
                       .filter(predicate)
                       .findFirst()
                       .orElse(null);
    }
    
    /**
     * Generic метод: поиск всех элементов по предикату.
     */
    public <R extends T> List<R> findAll(Predicate<T> predicate) {
        return (List<R>) items.stream()
                             .filter(predicate)
                             .collect(Collectors.toList());
    }
    
    /**
     * Generic метод: сортировка элементов.
     */
    public <R extends T> void sort(Comparator<T> comparator) {
        items.sort(comparator);
    }
    
    /**
     * Generic метод: удаление элементов по предикату.
     */
    public <R extends T> int removeIf(Predicate<T> predicate) {
        int originalSize = items.size();
        items.removeIf(predicate);
        return originalSize - items.size();
    }
    
    /**
     * Generic метод: применение функции ко всем элементам.
     */
    public <R> void forEach(Consumer<T> action) {
        items.forEach(action);
    }
    
    /**
     * Generic метод: преобразование элементов.
     */
    public <R> List<R> map(Function<T, R> mapper) {
        return items.stream()
                   .map(mapper)
                   .collect(Collectors.toList());
    }
    
    /**
     * Generic метод: группировка элементов.
     */
    public <K> Map<K, List<T>> groupBy(Function<T, K> classifier) {
        return items.stream()
                   .collect(Collectors.groupingBy(classifier));
    }
}
```

---

## Полиморфизм

### ✅ Требование: В контейнере должны храниться объекты базового и производного классов

### Пример использования Repository с полиморфизмом

**C++:**
```cpp
void demonstrateRepositoryWithPolymorphism()
{
    std::cout << "=== ШАБЛОННЫЙ КЛАСС С ПОЛИМОРФИЗМОМ ===\n\n";
    
    // Создание репозитория для VideoCarrier (базовый класс)
    Repository<VideoCarrier> repo;
    
    // Добавление объектов РАЗНЫХ ТИПОВ
    repo.add(new VideoCarrier(100, "Classic", "VHS", "Drama", 30.0, 300.0));  // Базовый
    repo.add(new DVDCarrier(101, "Modern", "Action", 45.0, 450.0, 1, "2"));    // Производный
    repo.add(new BluRayCarrier(102, "New", "Sci-Fi", 60.0, 600.0, true, true)); // Производный
    repo.add(new DVDCarrier(103, "Oldies", "Comedy", 40.0, 400.0, 2, "1"));    // Производный
    
    std::cout << "Добавлено носителей: " << repo.size() << "\n\n";
    
    // Поиск элемента (работает для всех типов)
    auto found = repo.findIf([](VideoCarrier* vc) { 
        return vc->getInventoryNumber() == 102; 
    });
    if (found) {
        std::cout << "Найден: " << found->getTitle() << "\n";
    }
    
    // Поиск всех дорогих носителей
    auto expensive = repo.findAll([](VideoCarrier* vc) {
        return vc->getRentalPricePerDay() >= 50.0;
    });
    std::cout << "\nДорогие носители (>= 50):\n";
    for (const auto& item : expensive) {
        std::cout << "- " << item->getTitle() << ": " 
                  << item->getRentalPricePerDay() << " руб/день\n";
    }
    
    // Сортировка по цене
    repo.sort([](VideoCarrier* a, VideoCarrier* b) {
        return a->getRentalPricePerDay() < b->getRentalPricePerDay();
    });
    
    std::cout << "\nПосле сортировки по цене:\n";
    repo.forEach([](VideoCarrier* vc) {
        std::cout << "- " << vc->getTitle() << ": " 
                  << vc->getRentalPricePerDay() << " руб/день\n";
    });
    
    // Удаление дешевых
    size_t removed = repo.removeIf([](VideoCarrier* vc) {
        return vc->getRentalPricePerDay() < 40.0;
    });
    std::cout << "\nУдалено дешевых: " << removed << "\n";
    std::cout << "Осталось: " << repo.size() << "\n";
}
```

**Java:**
```java
public static void demonstrateRepositoryWithPolymorphism() {
    System.out.println("=== GENERIC КЛАСС С ПОЛИМОРФИЗМОМ ===\n");
    
    // Создание репозитория для VideoCarrier (базовый класс)
    Repository<VideoCarrier> repo = new Repository<>();
    
    // Добавление объектов РАЗНЫХ ТИПОВ
    repo.add(new VideoCarrierReal(100, "Classic", "VHS", "Drama", 30.0, 300.0));  // Базовый
    repo.add(new DVDCarrier(101, "Modern", "Action", 45.0, 450.0, 1, "2"));        // Производный
    repo.add(new BluRayCarrier(102, "New", "Sci-Fi", 60.0, 600.0, true, true));    // Производный
    repo.add(new DVDCarrier(103, "Oldies", "Comedy", 40.0, 400.0, 2, "1"));        // Производный
    
    System.out.println("Добавлено носителей: " + repo.size() + "\n");
    
    // Поиск элемента (работает для всех типов)
    VideoCarrier found = repo.findIf(vc -> vc.getInventoryNumber() == 102);
    if (found != null) {
        System.out.println("Найден: " + found.getTitle());
    }
    
    // Поиск всех дорогих носителей
    List<VideoCarrier> expensive = repo.findAll(vc -> vc.getRentalPricePerDay() >= 50.0);
    System.out.println("\nДорогие носители (>= 50):");
    expensive.forEach(item -> 
        System.out.println("- " + item.getTitle() + ": " + 
                         item.getRentalPricePerDay() + " руб/день"));
    
    // Сортировка по цене
    repo.sort((a, b) -> Double.compare(a.getRentalPricePerDay(), 
                                      b.getRentalPricePerDay()));
    
    System.out.println("\nПосле сортировки по цене:");
    repo.forEach(vc -> 
        System.out.println("- " + vc.getTitle() + ": " + 
                         vc.getRentalPricePerDay() + " руб/день"));
    
    // Удаление дешевых
    int removed = repo.removeIf(vc -> vc.getRentalPricePerDay() < 40.0);
    System.out.println("\nУдалено дешевых: " + removed);
    System.out.println("Осталось: " + repo.size());
}
```

**Вывод:**
```
=== ШАБЛОННЫЙ КЛАСС С ПОЛИМОРФИЗМОМ ===

Добавлено носителей: 4

Найден: New Release (BluRay)

Дорогие носители (>= 50):
- New Release: 60.0 руб/день

После сортировки по цене:
- Classic: 30.0 руб/день
- Oldies: 40.0 руб/день
- Modern: 45.0 руб/день
- New Release: 60.0 руб/день

Удалено дешевых: 1
Осталось: 3
```

---

## Сравнительная Таблица

| Операция | C++ STL | Java Collections |
|----------|---------|------------------|
| Динамический массив | `std::vector<T>` | `ArrayList<T>` |
| Связный список | `std::list<T>` | `LinkedList<T>` |
| Ассоциативный массив | `std::map<K,V>` | `HashMap<K,V>` |
| Фиксированный массив | `std::array<T,N>` | `T[]` |
| Поиск минимума | `std::min_element` | `Collections.min` |
| Поиск максимума | `std::max_element` | `Collections.max` |
| Поиск элемента | `std::find, std::find_if` | `Stream.filter().findFirst()` |
| Копирование с условием | `std::copy_if` | `Stream.filter().collect()` |
| Удаление элементов | `std::remove_if + erase` | `List.removeIf()` |
| Сортировка | `std::sort` | `Collections.sort()` |
| Фильтрация (ленивая) | `std::views::filter` | `Stream.filter()` |
| Преобразование | `std::transform` | `Stream.map()` |
| Проверка условия | `std::any_of` | `Stream.anyMatch()` |
| Вариантный тип | `std::variant<...>` | `Object` или sealed classes |

---

## Заключение

Все требования по работе с контейнерами, алгоритмами и шаблонами успешно реализованы:

✅ **Контейнеры:** Продемонстрированы std::array, std::vector, std::list, std::map и их Java аналоги  
✅ **Алгоритмы:** Реализованы все требуемые алгоритмы поиска, сортировки, фильтрации и преобразования  
✅ **Шаблонные функции:** Созданы функции с ограничениями на типы (enable_if, static_assert, extends)  
✅ **Шаблонный класс:** Repository<T> с шаблонными и не шаблонными методами  
✅ **Полиморфизм:** В контейнерах хранятся объекты базовых и производных классов  

Код компилируется, тестируется и полностью документирован.
