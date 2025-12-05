package videoprokat;

import java.util.*;
import java.util.stream.*;
import java.util.function.*;

/**
 * Демонстрация Java Collections Framework и Generics.
 */
public class CollectionsDemo {
    
    public static void demonstrateCollections() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ JAVA COLLECTIONS ===\n");
        
        // 1. ArrayList - аналог std::vector
        System.out.println("1. ArrayList (аналог std::vector):");
        ArrayList<Double> prices = new ArrayList<>(Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0));
        prices.add(65.0);
        System.out.println("   Цены аренды: " + prices);
        System.out.println("   Размер: " + prices.size());
        
        // 2. LinkedList - аналог std::list
        System.out.println("\n2. LinkedList (аналог std::list):");
        LinkedList<String> genres = new LinkedList<>(Arrays.asList("Sci-Fi", "Action", "Drama", "Comedy"));
        genres.addFirst("Horror");
        System.out.println("   Жанры: " + genres);
        
        // 3. HashMap - аналог std::map
        System.out.println("\n3. HashMap (аналог std::map):");
        HashMap<Integer, String> clientNames = new HashMap<>();
        clientNames.put(1, "Иван Иванов");
        clientNames.put(2, "Петр Петров");
        clientNames.put(3, "Сидор Сидоров");
        System.out.println("   Клиенты:");
        clientNames.forEach((id, name) -> 
            System.out.println("   ID " + id + ": " + name));
        
        // 4. Нет прямого аналога std::array, но можно использовать массив
        System.out.println("\n4. Фиксированный массив (аналог std::array):");
        Double[] fixedPrices = {50.0, 60.0, 45.0, 70.0, 55.0};
        System.out.println("   Цены: " + Arrays.toString(fixedPrices));
    }
    
    public static void demonstrateStreamOperations() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ STREAM API ===\n");
        
        List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0, 40.0);
        
        // Collections.min, Collections.max (аналог std::min_element, std::max_element)
        System.out.println("1. Поиск минимума и максимума:");
        Double minPrice = Collections.min(prices);
        Double maxPrice = Collections.max(prices);
        System.out.println("   Минимальная цена: " + minPrice);
        System.out.println("   Максимальная цена: " + maxPrice);
        
        // Stream.filter + findFirst (аналог std::find, std::find_if)
        System.out.println("\n2. Поиск элементов:");
        Optional<Double> found = prices.stream()
                                      .filter(p -> p == 60.0)
                                      .findFirst();
        found.ifPresent(p -> System.out.println("   Найдена цена: " + p));
        
        Optional<Double> foundIf = prices.stream()
                                        .filter(p -> p > 65.0)
                                        .findFirst();
        foundIf.ifPresent(p -> System.out.println("   Первая цена > 65.0: " + p));
        
        // Stream.filter + collect (аналог std::copy_if)
        System.out.println("\n3. Копирование с условием:");
        List<Double> expensivePrices = prices.stream()
                                            .filter(p -> p >= 55.0)
                                            .collect(Collectors.toList());
        System.out.println("   Дорогие цены (>= 55): " + expensivePrices);
        
        // removeIf (аналог std::remove_if + erase)
        System.out.println("\n4. Удаление элементов:");
        List<Double> pricesCopy = new ArrayList<>(prices);
        pricesCopy.removeIf(p -> p < 50.0);
        System.out.println("   После удаления цен < 50: " + pricesCopy);
        
        // Collections.sort (аналог std::sort)
        System.out.println("\n5. Сортировка:");
        List<Double> unsorted = new ArrayList<>(Arrays.asList(60.0, 40.0, 70.0, 45.0, 55.0));
        System.out.println("   До сортировки: " + unsorted);
        Collections.sort(unsorted);
        System.out.println("   После сортировки: " + unsorted);
        
        // Stream.map (аналог std::transform)
        System.out.println("\n6. Преобразование элементов:");
        List<Double> discounted = prices.stream()
                                       .map(p -> p * 0.9)
                                       .collect(Collectors.toList());
        System.out.println("   Цены со скидкой 10%: " + discounted);
        
        // Stream.anyMatch (аналог std::any_of)
        System.out.println("\n7. Проверка условий:");
        boolean hasExpensive = prices.stream()
                                    .anyMatch(p -> p > 65.0);
        System.out.println("   Есть цены > 65: " + (hasExpensive ? "Да" : "Нет"));
        
        // Stream.allMatch
        boolean allPositive = prices.stream()
                                   .allMatch(p -> p > 0);
        System.out.println("   Все цены положительные: " + (allPositive ? "Да" : "Нет"));
    }
    
    public static void demonstrateGenericFunctions() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ GENERIC ФУНКЦИЙ ===\n");
        
        // Вычисление среднего значения
        System.out.println("1. Generic функция calculateAverage:");
        List<Double> prices = Arrays.asList(50.0, 60.0, 45.0, 70.0, 55.0);
        double avgPrice = GenericUtils.calculateAverage(prices);
        System.out.println("   Средняя цена аренды: " + avgPrice);
        
        List<Integer> ratings = Arrays.asList(5, 4, 5, 3, 4, 5);
        double avgRating = GenericUtils.calculateAverage(ratings);
        System.out.println("   Средний рейтинг: " + avgRating);
        
        // Поиск минимума и максимума
        System.out.println("\n2. Generic функция findMinMax:");
        GenericUtils.Pair<Double, Double> minMax = GenericUtils.findMinMax(prices);
        System.out.println("   Мин. цена: " + minMax.getFirst() + 
                          ", Макс. цена: " + minMax.getSecond());
        
        // Фильтрация
        System.out.println("\n3. Generic функция filterElements:");
        List<Double> expensive = GenericUtils.filterElements(prices, p -> p >= 55.0);
        System.out.println("   Дорогие цены: " + expensive);
        
        // Преобразование
        System.out.println("\n4. Generic функция transformElements:");
        List<Double> discounted = GenericUtils.transformElements(prices, p -> p * 0.85);
        System.out.println("   Цены со скидкой 15%: " + discounted);
        
        // Подсчет
        System.out.println("\n5. Generic функция countIf:");
        long expensiveCount = GenericUtils.countIf(prices, p -> p > 50.0);
        System.out.println("   Количество цен > 50: " + expensiveCount);
        
        // Проверка any_of
        System.out.println("\n6. Generic функция anyOf:");
        boolean hasVeryExpensive = GenericUtils.anyOf(prices, p -> p > 100.0);
        System.out.println("   Есть цены > 100: " + (hasVeryExpensive ? "Да" : "Нет"));
    }
    
    public static void demonstrateRepositoryWithPolymorphism() {
        System.out.println("\n=== GENERIC КЛАСС С ПОЛИМОРФИЗМОМ ===\n");
        
        System.out.println("1. Repository<VideoCarrier> с базовыми и производными классами:");
        
        // Создание репозитория
        Repository<VideoCarrier> repo = new Repository<>();
        
        // Добавление объектов разных типов
        repo.add(new VideoCarrierReal(100, "Classic", "VHS", "Drama", 30.0, 300.0));
        repo.add(new DVDCarrier(101, "Modern", "Action", 45.0, 450.0, 1, "2"));
        repo.add(new BluRayCarrier(102, "New Release", "Sci-Fi", 60.0, 600.0, true, true));
        repo.add(new DVDCarrier(103, "Oldies", "Comedy", 40.0, 400.0, 2, "1"));
        
        System.out.println("   Добавлено носителей: " + repo.size());
        
        // Поиск элемента
        System.out.println("\n2. Поиск элемента с номером 102:");
        VideoCarrier found = repo.findIf(vc -> vc.getInventoryNumber() == 102);
        if (found != null) {
            System.out.println("   Найден: " + found.getTitle() + 
                             " (" + found.getCarrierType() + ")");
        }
        
        // Поиск всех элементов по условию
        System.out.println("\n3. Поиск всех дорогих носителей (>= 50):");
        List<VideoCarrier> expensive = repo.findAll(vc -> vc.getRentalPricePerDay() >= 50.0);
        System.out.println("   Найдено: " + expensive.size() + " носителей");
        expensive.forEach(item -> 
            System.out.println("   - " + item.getTitle() + ": " + 
                             item.getRentalPricePerDay() + " руб/день"));
        
        // Сортировка
        System.out.println("\n4. Сортировка по цене:");
        repo.sort((a, b) -> Double.compare(a.getRentalPricePerDay(), 
                                          b.getRentalPricePerDay()));
        System.out.println("   После сортировки:");
        repo.forEach(vc -> 
            System.out.println("   - " + vc.getTitle() + ": " + 
                             vc.getRentalPricePerDay() + " руб/день"));
        
        // Удаление по условию
        System.out.println("\n5. Удаление дешевых носителей (< 40):");
        int removed = repo.removeIf(vc -> vc.getRentalPricePerDay() < 40.0);
        System.out.println("   Удалено: " + removed + " носителей");
        System.out.println("   Осталось: " + repo.size() + " носителей");
        
        // Группировка
        System.out.println("\n6. Группировка по типу носителя:");
        Map<String, List<VideoCarrier>> grouped = repo.groupBy(VideoCarrier::getCarrierType);
        grouped.forEach((type, items) -> 
            System.out.println("   " + type + ": " + items.size() + " шт."));
        
        // Преобразование
        System.out.println("\n7. Извлечение названий:");
        List<String> titles = repo.map(VideoCarrier::getTitle);
        System.out.println("   Названия: " + titles);
    }
    
    public static void demonstrateAdvancedStreams() {
        System.out.println("\n=== ПРОДВИНУТЫЕ ОПЕРАЦИИ STREAM ===\n");
        
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        
        // Фильтрация (аналог std::filter_view)
        System.out.println("1. Фильтрация (четные числа):");
        List<Integer> evenNumbers = numbers.stream()
                                          .filter(n -> n % 2 == 0)
                                          .collect(Collectors.toList());
        System.out.println("   Четные числа: " + evenNumbers);
        
        // Преобразование (аналог std::transform_view)
        System.out.println("\n2. Преобразование (умножение на 2):");
        List<Integer> doubled = numbers.stream()
                                      .map(n -> n * 2)
                                      .collect(Collectors.toList());
        System.out.println("   Удвоенные числа: " + doubled);
        
        // Комбинирование операций
        System.out.println("\n3. Комбинирование фильтра и преобразования:");
        List<Integer> result = numbers.stream()
                                     .filter(n -> n > 5)
                                     .map(n -> n * n)
                                     .collect(Collectors.toList());
        System.out.println("   Квадраты чисел > 5: " + result);
        
        // Reduce (свертка)
        System.out.println("\n4. Reduce - вычисление суммы:");
        int sum = numbers.stream()
                        .reduce(0, Integer::sum);
        System.out.println("   Сумма чисел: " + sum);
        
        // FlatMap (разворачивание)
        System.out.println("\n5. FlatMap - разворачивание вложенных списков:");
        List<List<Integer>> nested = Arrays.asList(
            Arrays.asList(1, 2, 3),
            Arrays.asList(4, 5, 6),
            Arrays.asList(7, 8, 9)
        );
        List<Integer> flattened = nested.stream()
                                        .flatMap(List::stream)
                                        .collect(Collectors.toList());
        System.out.println("   Развернутый список: " + flattened);
    }
    
    public static void main(String[] args) {
        System.out.println("╔═══════════════════════════════════════════════════════════╗");
        System.out.println("║   ДЕМОНСТРАЦИЯ COLLECTIONS И GENERICS JAVA                ║");
        System.out.println("╚═══════════════════════════════════════════════════════════╝");
        
        demonstrateCollections();
        demonstrateStreamOperations();
        demonstrateGenericFunctions();
        demonstrateRepositoryWithPolymorphism();
        demonstrateAdvancedStreams();
        
        System.out.println("\n╔═══════════════════════════════════════════════════════════╗");
        System.out.println("║   ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА                                  ║");
        System.out.println("╚═══════════════════════════════════════════════════════════╝");
    }
}
