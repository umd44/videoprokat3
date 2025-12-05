package videoprokat;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Демонстрационный класс для показа работы производных классов и их использования в контейнерах.
 * Показывает полиморфизм, работу с интерфейсами и использование STL-подобных контейнеров.
 */
public class DerivedClassesDemo {

    /**
     * Демонстрация использования производных классов в контейнерах (ArrayList).
     */
    public static void demonstrateDerivedClientsInContainers() {
        System.out.println("=== Демонстрация производных классов Client в контейнерах ===\n");

        // Создание списка различных типов клиентов (полиморфизм)
        List<Client> allClients = new ArrayList<>();
        allClients.add(new ClientReal(1, "John", "Doe", "+1-111-1111"));
        allClients.add(new PremiumClient(2, "Jane", "Smith", "+1-222-2222", "jane@example.com", 15.0));
        allClients.add(new CorporateClient(3, "Bob", "Johnson", "+1-333-3333", "TechCorp", "12345", 150));
        allClients.add(new StudentClient(4, "Alice", "Brown", "+1-444-4444", "State University", "STU123", "CS", "alice@uni.edu"));
        allClients.add(new ClientReal(5, "Charlie", "Williams", "+1-555-5555"));
        allClients.add(new VIPClient(6, "David", "Wilson", "+1-666-6666", "platinum", "david@example.com", "John Manager"));
        allClients.add(new CorporateClient(7, "Eve", "Taylor", "+1-777-7777", "MegaCorp", "67890", 500));

        System.out.println("Всего клиентов в системе: " + allClients.size());
        System.out.println();

        // === СОРТИРОВКА И КЛАССИФИКАЦИЯ ===
        System.out.println("=== Классификация клиентов по типам ===");
        long premiumCount = allClients.stream().filter(c -> c instanceof PremiumClient).count();
        long corporateCount = allClients.stream().filter(c -> c instanceof CorporateClient).count();
        long studentCount = allClients.stream().filter(c -> c instanceof StudentClient).count();
        long vipCount = allClients.stream().filter(c -> c instanceof VIPClient).count();
        long regularCount = allClients.stream()
            .filter(c -> !(c instanceof PremiumClient) && !(c instanceof CorporateClient) && 
                         !(c instanceof StudentClient) && !(c instanceof VIPClient))
            .count();

        System.out.println("  Обычные клиенты: " + regularCount);
        System.out.println("  Премиальные клиенты: " + premiumCount);
        System.out.println("  Корпоративные клиенты: " + corporateCount);
        System.out.println("  Студенческие клиенты: " + studentCount);
        System.out.println("  ВИП клиенты: " + vipCount);
        System.out.println();

        // === ПРИМЕНЕНИЕ СКИДОК ===
        System.out.println("=== Применение скидок (Discountable интерфейс) ===");
        double basePrice = 100.0;
        for (Client client : allClients) {
            if (client instanceof Discountable) {
                Discountable discountable = (Discountable) client;
                double discount = discountable.getDiscountPercentage();
                double finalPrice = discountable.applyDiscount(basePrice);
                System.out.printf("  %s %s: $%.2f -> $%.2f (%.1f%% скидка)%n",
                    client.getFirstName(),
                    client.getLastName(),
                    basePrice,
                    finalPrice,
                    discount);
            } else {
                System.out.printf("  %s %s: $%.2f (нет скидки)%n",
                    client.getFirstName(),
                    client.getLastName(),
                    basePrice);
            }
        }
        System.out.println();

        // === ОТПРАВКА УВЕДОМЛЕНИЙ ===
        System.out.println("=== Отправка уведомлений (Notifiable интерфейс) ===");
        String message = "Добро пожаловать! Используйте код WELCOME15 для скидки.";
        for (Client client : allClients) {
            if (client instanceof Notifiable) {
                Notifiable notifiable = (Notifiable) client;
                System.out.print("  ");
                notifiable.sendNotification(message);
            }
        }
        System.out.println();

        // === ПОИСК (find_if) ===
        System.out.println("=== Поиск VIP клиентов ===");
        List<Client> vipClients = allClients.stream()
            .filter(c -> c instanceof VIPClient)
            .collect(Collectors.toList());
        System.out.println("Найдено VIP клиентов: " + vipClients.size());
        for (Client client : vipClients) {
            VIPClient vip = (VIPClient) client;
            System.out.printf("  - %s %s (уровень: %s)%n", client.getFirstName(), client.getLastName(), vip.getVipTier());
        }
        System.out.println();

        // === КОПИРОВАНИЕ (copy_if) ===
        System.out.println("=== Копирование премиальных клиентов ===");
        List<Client> premiumAndVIP = allClients.stream()
            .filter(c -> c instanceof Discountable && (c instanceof PremiumClient || c instanceof VIPClient))
            .collect(Collectors.toList());
        System.out.println("Премиальные и VIP клиенты: " + premiumAndVIP.size());
        for (Client client : premiumAndVIP) {
            if (client instanceof Discountable) {
                Discountable d = (Discountable) client;
                System.out.printf("  - %s %s (скидка: %.1f%%)%n", client.getFirstName(), client.getLastName(), d.getDiscountPercentage());
            }
        }
        System.out.println();

        // === ПОИСК MAX СКИДКИ ===
        System.out.println("=== Клиент с максимальной скидкой ===");
        Client maxDiscountClient = null;
        double maxDiscount = 0.0;
        for (Client client : allClients) {
            if (client instanceof Discountable) {
                double discount = ((Discountable) client).getDiscountPercentage();
                if (discount > maxDiscount) {
                    maxDiscount = discount;
                    maxDiscountClient = client;
                }
            }
        }
        if (maxDiscountClient != null) {
            System.out.printf("  %s %s (скидка: %.1f%%)%n",
                maxDiscountClient.getFirstName(),
                maxDiscountClient.getLastName(),
                maxDiscount);
        }
        System.out.println();

        // === ИСПОЛЬЗОВАНИЕ LINKED LIST ===
        System.out.println("=== Использование LinkedList для быстрого удаления ===");
        LinkedList<Client> linkedClients = new LinkedList<>(allClients);
        System.out.println("Размер LinkedList: " + linkedClients.size());
        linkedClients.removeFirst();
        System.out.println("После удаления первого: " + linkedClients.size());
        System.out.println();

        // === ИСПОЛЬЗОВАНИЕ MAP ===
        System.out.println("=== Использование HashMap для быстрого поиска по ID ===");
        Map<Integer, Client> clientMap = new HashMap<>();
        for (Client client : allClients) {
            clientMap.put(client.getClientId(), client);
        }
        Client found = clientMap.get(6);
        if (found != null) {
            System.out.println("Найден клиент с ID=6: " + found.getFirstName() + " " + found.getLastName());
        }
        System.out.println();

        // === ИСПОЛЬЗОВАНИЕ TREEMAP ===
        System.out.println("=== Использование TreeMap (отсортированный по ID) ===");
        Map<Integer, Client> sortedMap = new TreeMap<>(clientMap);
        System.out.println("Первые 3 клиента (отсортированы по ID):");
        sortedMap.entrySet().stream()
            .limit(3)
            .forEach(e -> System.out.printf("  ID=%d: %s %s%n", e.getKey(), e.getValue().getFirstName(), e.getValue().getLastName()));
        System.out.println();
    }

    /**
     * Демонстрация использования производных видеоносителей в контейнерах.
     */
    public static void demonstrateDerivedVideoCarriersInContainers() {
        System.out.println("\n=== Демонстрация производных классов VideoCarrier в контейнерах ===\n");

        // Создание каталога с различными видеоносителями
        List<VideoCarrier> catalog = new ArrayList<>();
        catalog.add(new VideoCarrierReal(1, "Matrix", "DVD", "Sci-Fi", 50.0, 500.0));
        catalog.add(new VideoCarrierReal(2, "Avatar", "BluRay", "Fantasy", 60.0, 600.0));
        catalog.add(new PremiumVideoCarrier(3, "Dune 4K", "BluRay", "Sci-Fi", 80.0, 800.0, "4K Ultra HD", "Dolby Vision, HDR10, Atmos Sound"));
        catalog.add(new VideoCarrierReal(4, "Inception", "DVD", "Sci-Fi", 55.0, 550.0));
        catalog.add(new PremiumVideoCarrier(5, "Blade Runner 2049", "BluRay", "Sci-Fi", 85.0, 850.0, "4K Ultra HD", "Award-winning cinematography"));
        catalog.add(new VideoCarrierReal(6, "Interstellar", "BluRay", "Sci-Fi", 70.0, 700.0));
        catalog.add(new PremiumVideoCarrier(7, "Oppenheimer 4K", "BluRay", "Drama", 90.0, 900.0, "4K Ultra HD", "Oscar winner in 4K"));

        System.out.println("Всего видеоносителей в каталоге: " + catalog.size());
        System.out.println();

        // === КЛАССИФИКАЦИЯ ===
        System.out.println("=== Классификация видеоносителей ===");
        long premiumCount = catalog.stream().filter(v -> v instanceof PremiumVideoCarrier).count();
        long standardCount = catalog.size() - premiumCount;
        System.out.println("  Стандартные: " + standardCount);
        System.out.println("  Премиальные: " + premiumCount);
        System.out.println();

        // === СОРТИРОВКА ПО ЦЕНЕ ===
        System.out.println("=== Сортировка по цене аренды ===");
        List<VideoCarrier> sortedByPrice = new ArrayList<>(catalog);
        Collections.sort(sortedByPrice, Comparator.comparingDouble(VideoCarrier::getRentalPricePerDay));
        for (VideoCarrier video : sortedByPrice) {
            String type = video instanceof PremiumVideoCarrier ? "[PREMIUM]" : "[STANDARD]";
            System.out.printf("  %s %s - $%.2f/день%n", type, video.getTitle(), video.getRentalPricePerDay());
        }
        System.out.println();

        // === ФИЛЬТРАЦИЯ ===
        System.out.println("=== Фильтрация: Sci-Fi видео дороже $60 ===");
        List<VideoCarrier> expensiveSciFi = catalog.stream()
            .filter(v -> "Sci-Fi".equals(v.getGenre()))
            .filter(v -> v.getRentalPricePerDay() > 60.0)
            .collect(Collectors.toList());
        for (VideoCarrier video : expensiveSciFi) {
            System.out.printf("  - %s ($%.2f/день)%n", video.getTitle(), video.getRentalPricePerDay());
        }
        System.out.println();

        // === ПОИСК ПРЕМИАЛЬНЫХ ВИДЕО ===
        System.out.println("=== Поиск всех премиальных видео (find_if) ===");
        List<VideoCarrier> premiumVideos = catalog.stream()
            .filter(v -> v instanceof PremiumVideoCarrier)
            .collect(Collectors.toList());
        System.out.println("Найдено премиальных видео: " + premiumVideos.size());
        for (VideoCarrier video : premiumVideos) {
            PremiumVideoCarrier pv = (PremiumVideoCarrier) video;
            System.out.printf("  - %s (%s) - Формат: %s%n", video.getTitle(), video.getCarrierType(), pv.getFormat());
        }
        System.out.println();

        // === MIN/MAX ЭЛЕМЕНТЫ ===
        System.out.println("=== Минимум и максимум по цене ===");
        VideoCarrier cheapest = Collections.min(catalog, Comparator.comparingDouble(VideoCarrier::getRentalPricePerDay));
        VideoCarrier expensive = Collections.max(catalog, Comparator.comparingDouble(VideoCarrier::getRentalPricePerDay));
        System.out.println("  Самое дешевое: " + cheapest.getTitle() + " ($" + cheapest.getRentalPricePerDay() + "/день)");
        System.out.println("  Самое дорогое: " + expensive.getTitle() + " ($" + expensive.getRentalPricePerDay() + "/день)");
        System.out.println();

        // === ANY_OF ===
        System.out.println("=== Проверка: есть ли дорогое видео (any_of) ===");
        boolean hasExpensive = catalog.stream().anyMatch(v -> v.getRentalPricePerDay() > 80.0);
        System.out.println("  Есть видео дороже $80: " + (hasExpensive ? "ДА" : "НЕТ"));
        System.out.println();

        // === ИСПОЛЬЗОВАНИЕ HASHSET ===
        System.out.println("=== Использование HashSet для уникальных жанров ===");
        Set<String> genres = new HashSet<>();
        for (VideoCarrier video : catalog) {
            genres.add(video.getGenre());
        }
        System.out.println("  Жанры: " + genres);
        System.out.println();

        // === ИСПОЛЬЗОВАНИЕ TREESET ===
        System.out.println("=== Использование TreeSet (отсортированные жанры) ===");
        Set<String> sortedGenres = new TreeSet<>(genres);
        System.out.println("  Жанры (отсортированы): " + sortedGenres);
        System.out.println();

        // === ИСПОЛЬЗОВАНИЕ TREEMAP ===
        System.out.println("=== Использование TreeMap (видео по ID) ===");
        Map<Integer, VideoCarrier> catalogMap = new TreeMap<>();
        for (VideoCarrier video : catalog) {
            catalogMap.put(video.getInventoryNumber(), video);
        }
        catalogMap.forEach((id, video) -> System.out.printf("  ID=%d: %s%n", id, video.getTitle()));
        System.out.println();
    }

    /**
     * Главный метод программы.
     */
    public static void main(String[] args) {
        System.out.println("\n" + "=".repeat(70));
        System.out.println("ДЕМОНСТРАЦИЯ ПРОИЗВОДНЫХ КЛАССОВ И КОНТЕЙНЕРОВ");
        System.out.println("=".repeat(70) + "\n");

        demonstrateDerivedClientsInContainers();
        demonstrateDerivedVideoCarriersInContainers();

        System.out.println("\n" + "=".repeat(70));
        System.out.println("ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА");
        System.out.println("=".repeat(70) + "\n");
    }
}
