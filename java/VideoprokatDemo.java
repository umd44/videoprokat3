package videoprokat;

import java.util.ArrayList;
import java.util.List;

/**
 * Демонстрационный класс для показа работы системы видеопроката.
 */
public class VideoprokatDemo {

    private static Client staticClient;
    private static VideoCarrier staticItem;

    static {
        staticClient = new ClientReal(1, "Ivan", "Ivanov", "+7-000");
        staticItem = new VideoCarrierReal(100, "Matrix", "DVD", "Sci-Fi", 50.0, 500.0);
        System.out.println("=== Статическая инициализация выполнена ===");
    }

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
        System.out.println();

        // Создание аренды
        System.out.println("6. СОЗДАНИЕ АРЕНДЫ:");
        RentalManager manager = new RentalManagerReal();
        List<VideoCarrier> itemsForRental = new ArrayList<>();
        itemsForRental.add(catalog.findItemByNumber(100));
        itemsForRental.add(catalog.findItemByNumber(101));

        Rental rental = manager.createRental(referenceClient, itemsForRental, 3,
                "2025-10-15", "2025-10-18");
        if (rental != null) {
            System.out.println("   Аренда создана. Стоимость=" + rental.getRentalCost()
                    + ", депозит=" + rental.getDepositAmount());
        }
        System.out.println();

        // Обработка возврата
        System.out.println("7. ОБРАБОТКА ВОЗВРАТА:");
        double total = manager.processReturn(rental, 2);
        System.out.println("   Возврат выполнен. Итого к оплате=" + total);
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
        System.out.println();

        // 10. Использование оператора this
        System.out.println("10. ИСПОЛЬЗОВАНИЕ ОПЕРАТОРА this:");
        
        System.out.println("   10.1. Использование this() для вызова конструктора:");
        ClientReal clientWithId = new ClientReal(999);
        System.out.println("   Создан клиент через this(): ID=" + clientWithId.getClientId() 
                          + ", Имя=" + clientWithId.getFirstName());
        System.out.println();

        System.out.println("   10.2. Использование this для различения полей от параметров:");
        ClientReal client1 = new ClientReal(1001, "Anna", "Sidorova", "+7-222");
        System.out.println("   Создан клиент: " + client1.getFirstName() + " " + client1.getLastName());
        System.out.println();

        System.out.println("   10.3. Использование this для цепочки вызовов:");
        ClientReal fluentClient = new ClientReal(1002)
                .setFirstName("Maria")
                .setLastName("Kozlova")
                .setPhoneNumber("+7-333")
                .addDeposit(1000.0);
        System.out.println("   Создан клиент через цепочку вызовов:");
        System.out.println("   " + fluentClient.getFirstName() + " " + fluentClient.getLastName() 
                          + ", Телефон: " + fluentClient.getPhoneNumber()
                          + ", Депозит: " + fluentClient.getDepositBalance());
        System.out.println();

        System.out.println("   10.4. Использование this для сравнения объектов:");
        ClientReal client2 = new ClientReal(1001, "Different", "Name", "+7-444");
        System.out.println("   client1.isSameAs(client2): " + client1.isSameAs(client2) 
                          + " (одинаковый ID)");
        System.out.println("   client1.isSameInstance(client1): " + client1.isSameInstance(client1) 
                          + " (тот же объект)");
        System.out.println("   client1.isSameInstance(client2): " + client1.isSameInstance(client2) 
                          + " (разные объекты)");
        System.out.println();

        System.out.println("   10.5. Использование this для передачи текущего объекта:");
        ClientReal selfClient = new ClientReal(1003, "Self", "Reference", "+7-555");
        boolean isSelf = selfClient.isSameInstance(selfClient);
        System.out.println("   Передача this в метод isSameInstance: " + isSelf);
        System.out.println();

        // 11. Статические поля и методы
        System.out.println("11. СТАТИЧЕСКИЕ ПОЛЯ И МЕТОДЫ:");
        
        // 11.1. Использование статической константы
        System.out.println("   11.1. Использование статической константы:");
        System.out.println("   Максимальное количество клиентов: " + ClientReal.MAX_CLIENTS);
        System.out.println();

        // 11.2. Вызов статического метода без создания объекта
        System.out.println("   11.2. Вызов статического метода без создания объекта:");
        int initialCount = ClientReal.getTotalClientsCreated();
        System.out.println("   Количество созданных клиентов (до создания новых): " + initialCount);
        System.out.println("   Можно создать нового клиента: " + ClientReal.canCreateNewClient());
        System.out.println();

        // 11.3. Изменение статического поля при создании объектов
        System.out.println("   11.3. Изменение статического поля при создании объектов:");
        ClientReal staticDemoClient1 = new ClientReal(2001, "Static", "Demo1", "+7-666");
        System.out.println("   Создан клиент 1. Всего клиентов: " + ClientReal.getTotalClientsCreated());
        ClientReal staticDemoClient2 = new ClientReal(2002, "Static", "Demo2", "+7-777");
        System.out.println("   Создан клиент 2. Всего клиентов: " + ClientReal.getTotalClientsCreated());
        ClientReal staticDemoClient3 = new ClientReal(2003, "Static", "Demo3", "+7-888");
        System.out.println("   Создан клиент 3. Всего клиентов: " + ClientReal.getTotalClientsCreated());
        System.out.println("   Статическое поле общее для всех экземпляров класса!");
        System.out.println();

        // 11.4. Использование статического метода для работы со статическим полем в другом классе
        System.out.println("   11.4. Использование статического метода в RentalManagerReal:");
        int nextRentalId = RentalManagerReal.getNextRentalId();
        System.out.println("   Следующий доступный ID аренды (без создания объекта): " + nextRentalId);
        System.out.println("   Статический метод работает со статическим полем nextId");
        System.out.println();

        // 11.5. Демонстрация того, что статические поля общие для всех экземпляров
        System.out.println("   11.5. Статические поля общие для всех экземпляров:");
        System.out.println("   staticDemoClient1 и staticDemoClient2 видят одно значение:");
        System.out.println("   getTotalClientsCreated() = " + ClientReal.getTotalClientsCreated());
        System.out.println("   (независимо от того, через какой объект или класс вызывается)");
        System.out.println();

        // 12. Обработка исключений
        System.out.println("12. ОБРАБОТКА ИСКЛЮЧЕНИЙ:");
        
        System.out.println("   12.1. Использование try-catch:");
        try {
            ClientReal invalidClient = new ClientReal(0, "", "", "");
            invalidClient.validateClientData();
            System.out.println("   Клиент валиден (это не должно выводиться)");
        } catch (InvalidClientException e) {
            System.out.println("   Перехвачено исключение: " + e.getMessage());
        }
        System.out.println();

        System.out.println("   12.2. Использование try-catch-finally:");
        ClientReal clientForFinally = null;
        try {
            clientForFinally = new ClientReal(3001, "TryCatch", "Demo", "+7-999");
            clientForFinally.blockDepositFundsWithException(5000.0);
            System.out.println("   Средства заблокированы (это не должно выводиться)");
        } catch (InsufficientDepositException e) {
            System.out.println("   Перехвачено исключение: " + e.getMessage());
            System.out.println("   Требуется: " + e.getRequiredAmount() + ", доступно: " + e.getAvailableAmount());
        } finally {
            System.out.println("   Блок finally выполнен");
            if (clientForFinally != null) {
                System.out.println("   Клиент создан: " + clientForFinally.getFirstName());
            }
        }
        System.out.println();

        System.out.println("   12.3. Множественные catch блоки:");
        try {
            Catalog catalogForException = new CatalogReal();
            VideoCarrier notFound = catalogForException.findItemByNumberWithException(99999);
            System.out.println("   Элемент найден (это не должно выводиться)");
        } catch (ItemNotFoundException e) {
            System.out.println("   Перехвачено ItemNotFoundException: " + e.getMessage());
            System.out.println("   Номер элемента: " + e.getItemNumber());
        } catch (Exception e) {
            System.out.println("   Перехвачено общее исключение: " + e.getMessage());
        }
        System.out.println();

        System.out.println("   12.4. Обработка исключений при создании аренды:");
        RentalManager managerForException = new RentalManagerReal();
        try {
            Rental invalidRental = ((RentalManagerReal) managerForException)
                    .createRentalWithException(null, itemsForRental, 3, "2025-10-15", "2025-10-18");
            System.out.println("   Аренда создана (это не должно выводиться)");
        } catch (RentalException e) {
            System.out.println("   Перехвачено RentalException: " + e.getMessage());
            if (e.getCause() != null) {
                System.out.println("   Причина: " + e.getCause().getMessage());
            }
        }
        System.out.println();

        System.out.println("   12.5. Успешная обработка с try-catch:");
        try {
            ClientReal validClient = new ClientReal(3002, "Valid", "Client", "+7-888");
            validClient.addToDeposit(1000.0);
            validClient.blockDepositFundsWithException(500.0);
            System.out.println("   Средства успешно заблокированы");
            System.out.println("   Остаток на депозите: " + validClient.getDepositBalance());
        } catch (InsufficientDepositException e) {
            System.out.println("   Ошибка: " + e.getMessage() + " (это не должно выводиться)");
        } catch (IllegalArgumentException e) {
            System.out.println("   Ошибка валидации: " + e.getMessage() + " (это не должно выводиться)");
        }
        System.out.println();

        System.out.println("   12.6. Вложенные try-catch блоки:");
        try {
            try {
                ClientReal nestedClient = new ClientReal(3003, "", "Nested", "+7-777");
                nestedClient.validateClientData();
            } catch (InvalidClientException e) {
                System.out.println("   Внутренний catch: " + e.getMessage());
                throw new RentalException("Ошибка при валидации клиента для аренды", e);
            }
        } catch (RentalException e) {
            System.out.println("   Внешний catch: " + e.getMessage());
            if (e.getCause() != null) {
                System.out.println("   Причина: " + e.getCause().getMessage());
            }
        }
        System.out.println();

        System.out.println("   12.7. Обработка стандартных исключений:");
        try {
            int[] numbers = {10, 20, 30};
            int index = 5;
            int result = numbers[index] / 0;
            System.out.println("   Результат: " + result + " (это не должно выводиться)");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("   Перехвачено ArrayIndexOutOfBoundsException: " + e.getMessage());
        } catch (ArithmeticException e) {
            System.out.println("   Перехвачено ArithmeticException: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("   Перехвачено общее исключение: " + e.getClass().getSimpleName());
        }
        System.out.println();

        System.out.println("=== Завершено ===");
    }
}