package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * Демонстрационный класс для показа работы системы видеопроката.
 * Демонстрирует различные способы инициализации и работы с объектами.
 */
public class VideoprokatDemo {

    // Статическая инициализация объектов
    private static Client staticClient;
    private static VideoCarrier staticItem;

    // Статический блок инициализации
    static {
        staticClient = new ClientReal(1, "Ivan", "Ivanov", "+7-000");
        staticItem = new VideoCarrierReal(100, "Matrix", "DVD", "Sci-Fi", 50.0, 500.0);
        System.out.println("=== Статическая инициализация выполнена ===");
    }

    /**
     * Главный метод программы.
     * Демонстрирует различные способы работы с объектами.
     */
    public static void main(String[] args) {
        System.out.println("\n=== Демонстрация работы системы видеопроката ===\n");

        // 1. Динамическая инициализация объектов с помощью оператора new
        System.out.println("1. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ (оператор new):");
        Client dynamicClient = new ClientReal(2, "Petr", "Petrov", "+7-111");
        VideoCarrier dynamicItem = new VideoCarrierReal(101, "Interstellar", "BluRay", "Sci-Fi", 60.0, 600.0);
        System.out.println("   Создан клиент: " + dynamicClient.getFirstName() + " " + dynamicClient.getLastName());
        System.out.println("   Создан носитель: " + dynamicItem.getTitle());
        System.out.println();

        // 2. Работа по ссылкам (в Java все переменные объектов - это ссылки)
        System.out.println("2. РАБОТА ПО ССЫЛКАМ:");
        Client referenceClient = dynamicClient; // ссылка на тот же объект
        VideoCarrier pointerItem = dynamicItem;  // ссылка на тот же объект
        System.out.println("   referenceClient указывает на: " + referenceClient.getFirstName());
        System.out.println("   pointerItem указывает на: " + pointerItem.getTitle());
        // Изменение через одну ссылку отражается в другой
        referenceClient.setBlacklisted(true);
        System.out.println("   После изменения через referenceClient, dynamicClient.isBlacklisted() = " 
                          + dynamicClient.isBlacklisted());
        System.out.println();

        // 3. Динамический массив объектов класса (ArrayList)
        System.out.println("3. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ КЛАССА (ArrayList):");
        List<VideoCarrier> objectArray = new ArrayList<>();
        objectArray.add(new VideoCarrierReal(200, "Alien", "DVD", "Horror", 40.0, 400.0));
        objectArray.add(new VideoCarrierReal(201, "Alien 2", "DVD", "Horror", 40.0, 400.0));
        System.out.println("   Размер динамического массива: " + objectArray.size());
        for (int i = 0; i < objectArray.size(); i++) {
            System.out.println("   Элемент " + i + ": " + objectArray.get(i).getTitle());
        }
        System.out.println();

        // 4. Массив динамических объектов класса (массив ссылок на объекты)
        System.out.println("4. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ КЛАССА (массив ссылок):");
        VideoCarrier[] pointerArray = new VideoCarrier[2];
        pointerArray[0] = new VideoCarrierReal(300, "Avatar", "BluRay", "Fantasy", 70.0, 700.0);
        pointerArray[1] = new VideoCarrierReal(301, "Avatar 2", "BluRay", "Fantasy", 80.0, 800.0);
        System.out.println("   Размер массива: " + pointerArray.length);
        for (int i = 0; i < pointerArray.length; i++) {
            System.out.println("   Элемент " + i + ": " + pointerArray[i].getTitle());
        }
        System.out.println();

        // Заполнение каталога
        System.out.println("5. РАБОТА С КАТАЛОГОМ:");
        Catalog catalog = new CatalogReal();
        catalog.addItem(staticItem);  // статический объект
        catalog.addItem(pointerItem);  // ссылка на динамический объект
        for (int i = 0; i < objectArray.size(); i++) {
            catalog.addItem(objectArray.get(i));  // из динамического массива
        }
        for (int i = 0; i < pointerArray.length; i++) {
            catalog.addItem(pointerArray[i]);  // из массива динамических объектов
        }
        System.out.println("   Каталог заполнен");
        System.out.println("   Всего добавлено носителей: " + CatalogReal.getTotalItemsAdded());
        System.out.println("   Всего создано клиентов: " + ClientReal.getTotalClientsCreated());
        System.out.println();

        // Создание аренды
        System.out.println("6. СОЗДАНИЕ АРЕНДЫ:");
        RentalManager manager = new RentalManagerReal();
        List<VideoCarrier> itemsForRental = new ArrayList<>();
        itemsForRental.add(catalog.findItemByNumber(100));
        itemsForRental.add(catalog.findItemByNumber(101));

        Rental rental = null;
        try {
            rental = manager.createRental(referenceClient, itemsForRental, 3,
                    "2025-10-15", "2025-10-18");
            System.out.println("   Аренда создана. Стоимость=" + rental.getRentalCost()
                    + ", депозит=" + rental.getDepositAmount());
        } catch (RentalOperationException ex) {
            System.out.println("   Ошибка создания аренды: " + ex.getMessage());
        }
        System.out.println();

        // Демонстрация обработки ошибочной ситуации
        try {
            manager.createRental(null, itemsForRental, 3,
                    "2025-10-15", "2025-10-18");
        } catch (RentalOperationException ex) {
            System.out.println("   Ожидаемая ошибка при создании аренды: " + ex.getMessage());
        }
        System.out.println();

        // Обработка возврата
        System.out.println("7. ОБРАБОТКА ВОЗВРАТА:");
        try {
            double total = manager.processReturn(rental, 2);
            System.out.println("   Возврат выполнен. Итого к оплате=" + total);
        } catch (RentalOperationException ex) {
            System.out.println("   Ошибка при возврате: " + ex.getMessage());
        }
        System.out.println();

        // Генерация отчетов
        System.out.println("8. ГЕНЕРАЦИЯ ОТЧЕТОВ:");
        ReportGenerator reportGenerator = new ReportGeneratorReal();
        System.out.println("   " + reportGenerator.generateFinancialReport("2025-10-01", "2025-10-31"));
        System.out.println("   " + reportGenerator.generateInventoryReport(catalog.getAvailableItems()));
        System.out.println();

        // Демонстрация работы сборщика мусора (аналог delete в C++)
        System.out.println("9. ОСВОБОЖДЕНИЕ ПАМЯТИ (аналог delete в C++):");
        System.out.println("   Присваивание null ссылкам для освобождения памяти");
        // В Java явное удаление не требуется, но можно явно очистить ссылки
        for (int i = 0; i < pointerArray.length; i++) {
            pointerArray[i] = null;  // освобождение ссылок
        }
        dynamicClient = null;  // освобождение ссылки
        dynamicItem = null;    // освобождение ссылки
        System.out.println("   Ссылки очищены. Сборщик мусора автоматически удалит объекты");
        System.out.println();

        // Закрытие менеджера
        manager.close();
        System.out.println("=== Демонстрация завершена ===");
    }
}