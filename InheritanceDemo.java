package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * Демонстрация всех требуемых концепций ООП для Java.
 * 
 * Демонстрируемые концепции:
 * 1. Производные классы (PremiumClient, CorporateClient, DVDCarrier, BluRayCarrier)
 * 2. Модификатор protected (используется в базовых и производных классах)
 * 3. Перегрузка методов с вызовом и без вызова базового класса
 * 4. Виртуальные функции (все методы в Java виртуальные по умолчанию)
 * 5. Клонирование (поверхностное и глубокое) в DVDCarrier
 * 6. Вызов конструктора базового класса с параметрами
 * 7. Абстрактные классы (Client, VideoCarrier)
 * 8. Интерфейсы (Discountable, Notifiable)
 * 9. Множественное наследование (PremiumClient extends Client implements Discountable, Notifiable)
 */
public class InheritanceDemo {
    
    /**
     * Демонстрация полиморфизма через виртуальные методы.
     * Метод принимает базовый класс, но работает с производными.
     */
    public static void demonstratePolymorphism(Client client, double amount) {
        System.out.println("\n--- Демонстрация полиморфизма ---");
        System.out.println("Клиент: " + client.getFirstName() + " " + client.getLastName());
        
        client.addToDeposit(amount);
        System.out.println("Баланс депозита: " + client.getDepositBalance());
        
        if (client instanceof Discountable) {
            Discountable discountableClient = (Discountable) client;
            System.out.println("Скидка доступна: " + discountableClient.getDiscountPercentage() + "%");
            System.out.println("Сумма со скидкой: " + discountableClient.applyDiscount(100.0));
        }
        
        if (client instanceof Notifiable) {
            Notifiable notifiableClient = (Notifiable) client;
            notifiableClient.sendNotification("Ваш депозит пополнен на " + amount);
        }
    }
    
    /**
     * Демонстрация работы с массивом базовых объектов через полиморфизм.
     */
    public static void demonstrateArrayPolymorphism(List<VideoCarrier> carriers) {
        System.out.println("\n--- Полиморфизм с массивом носителей ---");
        for (VideoCarrier carrier : carriers) {
            System.out.println("\nНоситель: " + carrier.getTitle() + " (" + carrier.getCarrierType() + ")");
            System.out.println("Цена аренды: " + carrier.getRentalPricePerDay());
            
            carrier.markAsRented();
            
            if (carrier instanceof DVDCarrier) {
                DVDCarrier dvd = (DVDCarrier) carrier;
                System.out.println("DVD диск #" + dvd.getDiskNumber() + ", регион: " + dvd.getRegion());
            } else if (carrier instanceof BluRayCarrier) {
                BluRayCarrier bluRay = (BluRayCarrier) carrier;
                System.out.println("BluRay " + (bluRay.isIs4K() ? "4K " : "") + 
                                 (bluRay.isHasHDR() ? "HDR " : "") + 
                                 bluRay.getStorageGB() + "GB");
            }
        }
    }
    
    /**
     * Демонстрация клонирования (поверхностного и глубокого).
     */
    public static void demonstrateCloning() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ КЛОНИРОВАНИЯ ===");
        
        DVDCarrier original = new DVDCarrier(500, "Inception", "Sci-Fi", 45.0, 450.0, 1, "2");
        original.addSubtitle("English");
        original.addSubtitle("Russian");
        
        System.out.println("\nОригинальный DVD:");
        System.out.println("Название: " + original.getTitle());
        System.out.println("Субтитры: " + original.getSubtitles());
        
        System.out.println("\n--- Поверхностное клонирование ---");
        DVDCarrier shallowClone = original.shallowClone();
        System.out.println("Клон создан");
        System.out.println("Субтитры клона: " + shallowClone.getSubtitles());
        
        shallowClone.addSubtitle("Spanish");
        System.out.println("\nПосле добавления Spanish в клон:");
        System.out.println("Субтитры оригинала: " + original.getSubtitles());
        System.out.println("Субтитры клона: " + shallowClone.getSubtitles());
        System.out.println("ВНИМАНИЕ: При поверхностном клонировании список разделяется!");
        
        System.out.println("\n--- Глубокое клонирование ---");
        DVDCarrier original2 = new DVDCarrier(501, "Matrix", "Sci-Fi", 50.0, 500.0, 1, "1");
        original2.addSubtitle("English");
        original2.addSubtitle("Russian");
        
        DVDCarrier deepClone = original2.deepClone();
        System.out.println("Глубокий клон создан");
        System.out.println("Субтитры клона: " + deepClone.getSubtitles());
        
        deepClone.addSubtitle("French");
        System.out.println("\nПосле добавления French в клон:");
        System.out.println("Субтитры оригинала: " + original2.getSubtitles());
        System.out.println("Субтитры клона: " + deepClone.getSubtitles());
        System.out.println("При глубоком клонировании списки независимы!");
    }
    
    /**
     * Демонстрация работы через указатели/ссылки базового и производного классов.
     */
    public static void demonstratePointerPolymorphism() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ ВИРТУАЛЬНЫХ МЕТОДОВ ЧЕРЕЗ УКАЗАТЕЛИ ===");
        
        System.out.println("\n--- Ссылка базового класса на объект производного ---");
        Client baseRef = new PremiumClient(100, "Alice", "Johnson", "+7-222", 
                                          "alice@example.com", 15.0);
        
        System.out.println("Тип ссылки: Client");
        System.out.println("Реальный тип объекта: PremiumClient");
        
        baseRef.addToDeposit(1000.0);
        System.out.println("Баланс: " + baseRef.getDepositBalance());
        
        System.out.println("\n--- Ссылка производного класса на объект производного ---");
        PremiumClient derivedRef = new PremiumClient(101, "Bob", "Smith", "+7-333",
                                                     "bob@example.com", 20.0);
        
        derivedRef.addToDeposit(1000.0);
        System.out.println("Баланс: " + derivedRef.getDepositBalance());
        System.out.println("Бонусные баллы: " + derivedRef.getLoyaltyPoints());
    }
    
    /**
     * Демонстрация перегрузки методов с вызовом и без вызова базового.
     */
    public static void demonstrateMethodOverriding() {
        System.out.println("\n=== ДЕМОНСТРАЦИЯ ПЕРЕГРУЗКИ МЕТОДОВ ===");
        
        System.out.println("\n--- Перегрузка С ВЫЗОВОМ базового метода ---");
        PremiumClient premium = new PremiumClient(200, "Charlie", "Brown", "+7-444",
                                                 "charlie@example.com", 10.0);
        System.out.println("PremiumClient.addToDeposit вызывает super.addToDeposit()");
        premium.addToDeposit(500.0);
        System.out.println("Результат: депозит пополнен + начислены бонусы");
        
        System.out.println("\n--- Перегрузка БЕЗ ВЫЗОВА базового метода ---");
        premium.addToDeposit(1000.0);
        System.out.println("Баланс: " + premium.getDepositBalance());
        System.out.println("\nPremiumClient.blockDepositFunds НЕ вызывает super.blockDepositFunds()");
        System.out.println("Полностью переопределяет логику с применением скидки");
        boolean blocked = premium.blockDepositFunds(200.0);
        System.out.println("Блокировка успешна: " + blocked);
        System.out.println("Баланс после блокировки: " + premium.getDepositBalance());
    }
    
    /**
     * Демонстрация множественного наследования через интерфейсы.
     */
    public static void demonstrateMultipleInheritance() {
        System.out.println("\n=== МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===");
        System.out.println("PremiumClient extends Client implements Discountable, Notifiable");
        
        PremiumClient client = new PremiumClient(300, "Diana", "Prince", "+7-555",
                                                "diana@example.com", 25.0);
        
        System.out.println("\nОт абстрактного класса Client:");
        System.out.println("- getFirstName(): " + client.getFirstName());
        System.out.println("- getDepositBalance(): " + client.getDepositBalance());
        
        System.out.println("\nОт интерфейса Discountable:");
        System.out.println("- getDiscountPercentage(): " + client.getDiscountPercentage() + "%");
        System.out.println("- applyDiscount(1000): " + client.applyDiscount(1000.0));
        
        System.out.println("\nОт интерфейса Notifiable:");
        System.out.println("- getPreferredNotificationMethod(): " + client.getPreferredNotificationMethod());
        client.sendNotification("Добро пожаловать в премиум-клуб!");
    }
    
    public static void main(String[] args) {
        System.out.println("╔═══════════════════════════════════════════════════════════╗");
        System.out.println("║   ДЕМОНСТРАЦИЯ КОНЦЕПЦИЙ ООП В JAVA                      ║");
        System.out.println("╚═══════════════════════════════════════════════════════════╝");
        
        demonstrateMultipleInheritance();
        
        System.out.println("\n\n=== ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА ===");
        
        Client regularClient = new ClientReal(1, "John", "Doe", "+7-100");
        Client premiumClient = new PremiumClient(2, "Jane", "Smith", "+7-200",
                                                "jane@example.com", 15.0);
        Client corporateClient = new CorporateClient(3, "Mike", "Johnson", "+7-300",
                                                     "TechCorp", 50);
        
        demonstratePolymorphism(regularClient, 1000.0);
        demonstratePolymorphism(premiumClient, 1000.0);
        demonstratePolymorphism(corporateClient, 1000.0);
        
        System.out.println("\n\n=== ДЕМОНСТРАЦИЯ С ВИДЕОНОСИТЕЛЯМИ ===");
        
        List<VideoCarrier> carriers = new ArrayList<>();
        carriers.add(new VideoCarrierReal(100, "The Godfather", "DVD", "Drama", 40.0, 400.0));
        carriers.add(new DVDCarrier(101, "Pulp Fiction", "Crime", 45.0, 450.0, 2, "1"));
        carriers.add(new BluRayCarrier(102, "Dune", "Sci-Fi", 60.0, 600.0, true, true));
        
        demonstrateArrayPolymorphism(carriers);
        
        demonstrateCloning();
        demonstratePointerPolymorphism();
        demonstrateMethodOverriding();
        
        System.out.println("\n\n╔═══════════════════════════════════════════════════════════╗");
        System.out.println("║   ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА                                  ║");
        System.out.println("╚═══════════════════════════════════════════════════════════╝");
    }
}
