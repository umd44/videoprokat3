package videoprokat;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

/**
 * Интерактивное консольное приложение для системы видеопроката.
 * Предоставляет полный функционал через текстовое меню.
 */
public class VideoprokatInteractiveApp {

    private static Scanner scanner = new Scanner(System.in);
    private static User currentUser = null;
    private static Catalog catalog = new CatalogReal();
    private static RentalManager rentalManager = new RentalManagerReal();
    private static ReportGenerator reportGenerator = new ReportGeneratorReal();
    private static List<Client> clients = new ArrayList<>();
    private static List<User> users = new ArrayList<>();
    private static int nextClientId = 1001;
    private static int nextInventoryNumber = 2001;

    public static void main(String[] args) {
        initializeSystem();
        showWelcomeScreen();
        
        if (login()) {
            mainMenu();
        }
        
        cleanup();
        System.out.println("\n╔════════════════════════════════════════════════════╗");
        System.out.println("║  Спасибо за использование системы видеопроката!   ║");
        System.out.println("╚════════════════════════════════════════════════════╝\n");
    }

    private static void initializeSystem() {
        // Создание пользователей системы
        users.add(new UserReal(1, "operator", "1234", "Operator", "Иванов Иван Иванович"));
        users.add(new UserReal(2, "senior", "5678", "Senior Operator", "Петров Петр Петрович"));
        users.add(new UserReal(3, "admin", "admin", "Administrator", "Сидоров Сидор Сидорович"));

        // Добавление тестовых клиентов
        ClientReal client1 = new ClientReal(nextClientId++, "Алексей", "Смирнов", "+7-925-123-45-67");
        client1.setMiddleName("Николаевич");
        client1.setEmail("smirnov@mail.ru");
        client1.setPassport("4512", "789456");
        client1.setBirthDate("1990-05-15");
        client1.setRegistrationDate("2024-01-10");
        client1.addBonusPoints(50);
        clients.add(client1);

        ClientReal client2 = new ClientReal(nextClientId++, "Мария", "Иванова", "+7-916-987-65-43");
        client2.setMiddleName("Петровна");
        client2.setEmail("ivanova@gmail.com");
        client2.setPassport("4513", "654321");
        client2.setBirthDate("1995-08-22");
        client2.setRegistrationDate("2024-03-15");
        client2.addBonusPoints(120);
        clients.add(client2);

        // Добавление видеоносителей в каталог
        addMovieToCatalog("Матрица", "Blu-ray", "Фантастика", 1999, "Вачовски", "16+", 
            "Программист Томас Андерсон узнаёт правду о реальности", 100.0, 800.0);
        addMovieToCatalog("Интерстеллар", "Blu-ray", "Фантастика", 2014, "Кристофер Нолан", "12+",
            "Команда исследователей отправляется в космос", 120.0, 900.0);
        addMovieToCatalog("Зеленая миля", "DVD", "Драма", 1999, "Фрэнк Дарабонт", "16+",
            "История о начальнике охраны в тюрьме", 80.0, 500.0);
        addMovieToCatalog("Властелин колец", "Blu-ray", "Фэнтези", 2001, "Питер Джексон", "12+",
            "Эпическая история о Средиземье", 110.0, 850.0);
        addMovieToCatalog("Чужой", "DVD", "Ужасы", 1979, "Ридли Скотт", "18+",
            "Команда космического корабля встречает внеземную форму жизни", 90.0, 600.0);
    }

    private static void addMovieToCatalog(String title, String type, String genre, int year,
                                           String director, String ageRating, String description,
                                           double pricePerDay, double fullPrice) {
        VideoCarrierReal movie = new VideoCarrierReal(nextInventoryNumber++, title, type, genre,
            pricePerDay, fullPrice);
        movie.setReleaseYear(year);
        movie.setDirector(director);
        movie.setAgeRating(ageRating);
        movie.setDescription(description);
        catalog.addItem(movie);
    }

    private static void showWelcomeScreen() {
        clearScreen();
        System.out.println("\n╔════════════════════════════════════════════════════════════════╗");
        System.out.println("║                                                                ║");
        System.out.println("║     ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА                       ║");
        System.out.println("║     Локальная многопользовательская система                   ║");
        System.out.println("║     Версия 2.0                                                 ║");
        System.out.println("║                                                                ║");
        System.out.println("╚════════════════════════════════════════════════════════════════╝\n");
    }

    private static boolean login() {
        System.out.println("\n═══ ВХОД В СИСТЕМУ ═══\n");
        System.out.println("Доступные пользователи для входа:");
        System.out.println("  1. operator / 1234 (Оператор)");
        System.out.println("  2. senior / 5678 (Старший оператор)");
        System.out.println("  3. admin / admin (Администратор)");
        System.out.println();

        int attempts = 0;
        while (attempts < 3) {
            System.out.print("Логин: ");
            String username = scanner.nextLine().trim();
            
            System.out.print("Пароль: ");
            String password = scanner.nextLine().trim();

            for (User user : users) {
                if (user.getUsername().equals(username) && user.checkPassword(password)) {
                    currentUser = user;
                    System.out.println("\n✓ Вход выполнен успешно!");
                    System.out.println("Добро пожаловать, " + user.getFullName());
                    System.out.println("Ваша роль: " + user.getRole());
                    pause();
                    return true;
                }
            }

            attempts++;
            System.out.println("\n✗ Неверный логин или пароль. Попыток осталось: " + (3 - attempts));
        }

        System.out.println("\n✗ Превышено количество попыток входа. Доступ заблокирован.");
        return false;
    }

    private static void mainMenu() {
        while (true) {
            clearScreen();
            showHeader();

            System.out.println("\n╔════════════════════════════════════════════════════════════════╗");
            System.out.println("║                       ГЛАВНОЕ МЕНЮ                             ║");
            System.out.println("╚════════════════════════════════════════════════════════════════╝\n");

            System.out.println("  1. Управление видеоносителями");
            System.out.println("  2. Управление клиентами");
            System.out.println("  3. Оформление аренды");
            System.out.println("  4. Обработка возврата");
            System.out.println("  5. Отчеты и статистика");
            System.out.println("  6. Управление пользователями" + 
                (currentUser.hasPermission("manage_users") ? "" : " [НЕДОСТУПНО]"));
            System.out.println("  0. Выход из системы");
            System.out.println();

            int choice = readInt("Выберите пункт меню: ");

            switch (choice) {
                case 1:
                    videoCarriersMenu();
                    break;
                case 2:
                    clientsMenu();
                    break;
                case 3:
                    createRentalMenu();
                    break;
                case 4:
                    processReturnMenu();
                    break;
                case 5:
                    reportsMenu();
                    break;
                case 6:
                    if (currentUser.hasPermission("manage_users")) {
                        usersMenu();
                    } else {
                        System.out.println("\n✗ У вас нет прав для доступа к этому разделу.");
                        pause();
                    }
                    break;
                case 0:
                    return;
                default:
                    System.out.println("\n✗ Неверный выбор. Попробуйте снова.");
                    pause();
            }
        }
    }

    private static void videoCarriersMenu() {
        while (true) {
            clearScreen();
            showHeader();
            System.out.println("\n═══ УПРАВЛЕНИЕ ВИДЕОНОСИТЕЛЯМИ ═══\n");

            System.out.println("  1. Просмотр всех носителей");
            System.out.println("  2. Поиск носителей");
            System.out.println("  3. Добавить новый носитель" + 
                (currentUser.hasPermission("edit_items") ? "" : " [НЕДОСТУПНО]"));
            System.out.println("  4. Статистика каталога");
            System.out.println("  0. Назад");
            System.out.println();

            int choice = readInt("Выберите пункт меню: ");

            switch (choice) {
                case 1:
                    viewAllCarriers();
                    break;
                case 2:
                    searchCarriersMenu();
                    break;
                case 3:
                    if (currentUser.hasPermission("edit_items")) {
                        addNewCarrier();
                    } else {
                        System.out.println("\n✗ Недостаточно прав.");
                        pause();
                    }
                    break;
                case 4:
                    showCatalogStatistics();
                    break;
                case 0:
                    return;
                default:
                    System.out.println("\n✗ Неверный выбор.");
                    pause();
            }
        }
    }

    private static void viewAllCarriers() {
        clearScreen();
        System.out.println("\n═══ ВСЕ ВИДЕОНОСИТЕЛИ ═══\n");

        List<VideoCarrier> items = catalog.getAllItems();
        if (items.isEmpty()) {
            System.out.println("Каталог пуст.");
        } else {
            System.out.println(String.format("%-6s %-25s %-10s %-15s %-8s %-10s", 
                "№", "Название", "Тип", "Жанр", "Год", "Статус"));
            System.out.println("─".repeat(90));

            for (VideoCarrier item : items) {
                System.out.println(String.format("%-6d %-25s %-10s %-15s %-8d %-10s",
                    item.getInventoryNumber(),
                    truncate(item.getTitle(), 25),
                    item.getCarrierType(),
                    item.getGenre(),
                    item.getReleaseYear(),
                    getStatusRussian(item.getStatus())));
            }
            System.out.println("\nВсего носителей: " + items.size());
        }
        pause();
    }

    private static void searchCarriersMenu() {
        clearScreen();
        System.out.println("\n═══ ПОИСК ВИДЕОНОСИТЕЛЕЙ ═══\n");

        System.out.println("  1. Поиск по названию");
        System.out.println("  2. Поиск по жанру");
        System.out.println("  3. Поиск по режиссеру");
        System.out.println("  4. Поиск по году выпуска");
        System.out.println("  5. Поиск по типу носителя");
        System.out.println("  6. Только доступные");
        System.out.println("  0. Назад");
        System.out.println();

        int choice = readInt("Выберите критерий поиска: ");

        List<VideoCarrier> results = new ArrayList<>();

        switch (choice) {
            case 1:
                System.out.print("Введите название: ");
                String title = scanner.nextLine().trim();
                results = catalog.findItemsByTitle(title);
                break;
            case 2:
                System.out.print("Введите жанр: ");
                String genre = scanner.nextLine().trim();
                results = catalog.findItemsByGenre(genre);
                break;
            case 3:
                System.out.print("Введите имя режиссера: ");
                String director = scanner.nextLine().trim();
                results = catalog.findItemsByDirector(director);
                break;
            case 4:
                int year = readInt("Введите год выпуска: ");
                results = catalog.findItemsByYear(year);
                break;
            case 5:
                System.out.print("Введите тип (DVD/Blu-ray): ");
                String type = scanner.nextLine().trim();
                results = catalog.findItemsByCarrierType(type);
                break;
            case 6:
                results = catalog.getAvailableItems();
                break;
            case 0:
                return;
            default:
                System.out.println("\n✗ Неверный выбор.");
                pause();
                return;
        }

        System.out.println("\n═══ РЕЗУЛЬТАТЫ ПОИСКА ═══\n");
        if (results.isEmpty()) {
            System.out.println("Ничего не найдено.");
        } else {
            for (VideoCarrier item : results) {
                displayCarrierDetails(item);
                System.out.println();
            }
            System.out.println("Найдено носителей: " + results.size());
        }
        pause();
    }

    private static void addNewCarrier() {
        clearScreen();
        System.out.println("\n═══ ДОБАВЛЕНИЕ НОВОГО НОСИТЕЛЯ ═══\n");

        System.out.print("Название: ");
        String title = scanner.nextLine().trim();

        System.out.print("Тип (DVD/Blu-ray): ");
        String type = scanner.nextLine().trim();

        System.out.print("Жанр: ");
        String genre = scanner.nextLine().trim();

        int year = readInt("Год выпуска: ");

        System.out.print("Режиссер: ");
        String director = scanner.nextLine().trim();

        System.out.print("Возрастной рейтинг (0+/6+/12+/16+/18+): ");
        String ageRating = scanner.nextLine().trim();

        double pricePerDay = readDouble("Стоимость проката (руб/день): ");
        double fullPrice = readDouble("Полная стоимость: ");

        System.out.print("Описание: ");
        String description = scanner.nextLine().trim();

        addMovieToCatalog(title, type, genre, year, director, ageRating, description, 
            pricePerDay, fullPrice);

        System.out.println("\n✓ Носитель успешно добавлен! Инвентарный номер: " + (nextInventoryNumber - 1));
        pause();
    }

    private static void showCatalogStatistics() {
        clearScreen();
        System.out.println("\n═══ СТАТИСТИКА КАТАЛОГА ═══\n");

        Map<String, Integer> stats = catalog.getStatistics();

        System.out.println("Всего носителей:       " + stats.get("total"));
        System.out.println("Доступных:             " + stats.get("available"));
        System.out.println("Арендованных:          " + stats.get("rented"));
        System.out.println("На реставрации:        " + stats.get("maintenance"));
        System.out.println("Списанных:             " + stats.get("written_off"));

        System.out.println("\n═══ ТОП ПОПУЛЯРНЫХ НОСИТЕЛЕЙ ═══\n");

        List<VideoCarrier> topItems = catalog.getTopRentedItems(5);
        int rank = 1;
        for (VideoCarrier item : topItems) {
            System.out.println(rank++ + ". " + item.getTitle() + " - " + 
                item.getTotalRentals() + " аренд");
        }

        pause();
    }

    private static void clientsMenu() {
        while (true) {
            clearScreen();
            showHeader();
            System.out.println("\n═══ УПРАВЛЕНИЕ КЛИЕНТАМИ ═══\n");

            System.out.println("  1. Просмотр всех клиентов");
            System.out.println("  2. Поиск клиента");
            System.out.println("  3. Регистрация нового клиента");
            System.out.println("  4. Заблокировать/разблокировать клиента" +
                (currentUser.hasPermission("edit_client_status") ? "" : " [НЕДОСТУПНО]"));
            System.out.println("  0. Назад");
            System.out.println();

            int choice = readInt("Выберите пункт меню: ");

            switch (choice) {
                case 1:
                    viewAllClients();
                    break;
                case 2:
                    searchClient();
                    break;
                case 3:
                    registerNewClient();
                    break;
                case 4:
                    if (currentUser.hasPermission("edit_client_status")) {
                        blockUnblockClient();
                    } else {
                        System.out.println("\n✗ Недостаточно прав.");
                        pause();
                    }
                    break;
                case 0:
                    return;
                default:
                    System.out.println("\n✗ Неверный выбор.");
                    pause();
            }
        }
    }

    private static void viewAllClients() {
        clearScreen();
        System.out.println("\n═══ ВСЕ КЛИЕНТЫ ═══\n");

        if (clients.isEmpty()) {
            System.out.println("Клиенты отсутствуют.");
        } else {
            System.out.println(String.format("%-6s %-30s %-18s %-12s %-10s", 
                "ID", "ФИО", "Телефон", "Бонусы", "Статус"));
            System.out.println("─".repeat(90));

            for (Client client : clients) {
                String fullName = client.getLastName() + " " + client.getFirstName() + 
                    " " + client.getMiddleName();
                System.out.println(String.format("%-6d %-30s %-18s %-12d %-10s",
                    client.getClientId(),
                    truncate(fullName, 30),
                    client.getPhoneNumber(),
                    client.getBonusPoints(),
                    client.isBlacklisted() ? "БЛОКИРОВАН" : "Активен"));
            }
            System.out.println("\nВсего клиентов: " + clients.size());
        }
        pause();
    }

    private static void searchClient() {
        clearScreen();
        System.out.println("\n═══ ПОИСК КЛИЕНТА ═══\n");

        System.out.println("  1. Поиск по ID");
        System.out.println("  2. Поиск по телефону");
        System.out.println("  3. Поиск по фамилии");
        System.out.println("  0. Назад");
        System.out.println();

        int choice = readInt("Выберите критерий поиска: ");

        Client found = null;

        switch (choice) {
            case 1:
                int id = readInt("Введите ID клиента: ");
                found = findClientById(id);
                break;
            case 2:
                System.out.print("Введите телефон: ");
                String phone = scanner.nextLine().trim();
                found = findClientByPhone(phone);
                break;
            case 3:
                System.out.print("Введите фамилию: ");
                String lastName = scanner.nextLine().trim();
                List<Client> matches = findClientsByLastName(lastName);
                if (matches.isEmpty()) {
                    System.out.println("\n✗ Клиенты не найдены.");
                } else {
                    System.out.println("\nНайдено клиентов: " + matches.size());
                    for (Client c : matches) {
                        displayClientDetails(c);
                        System.out.println();
                    }
                }
                pause();
                return;
            case 0:
                return;
            default:
                System.out.println("\n✗ Неверный выбор.");
                pause();
                return;
        }

        if (found != null) {
            displayClientDetails(found);
        } else {
            System.out.println("\n✗ Клиент не найден.");
        }
        pause();
    }

    private static void registerNewClient() {
        clearScreen();
        System.out.println("\n═══ РЕГИСТРАЦИЯ НОВОГО КЛИЕНТА ═══\n");

        System.out.print("Фамилия: ");
        String lastName = scanner.nextLine().trim();

        System.out.print("Имя: ");
        String firstName = scanner.nextLine().trim();

        System.out.print("Отчество: ");
        String middleName = scanner.nextLine().trim();

        System.out.print("Телефон: ");
        String phone = scanner.nextLine().trim();

        System.out.print("Email (опционально): ");
        String email = scanner.nextLine().trim();

        System.out.print("Серия паспорта: ");
        String passportSeries = scanner.nextLine().trim();

        System.out.print("Номер паспорта: ");
        String passportNumber = scanner.nextLine().trim();

        System.out.print("Дата рождения (ГГГГ-ММ-ДД): ");
        String birthDate = scanner.nextLine().trim();

        System.out.print("Адрес: ");
        String address = scanner.nextLine().trim();

        ClientReal newClient = new ClientReal(nextClientId++, firstName, lastName, phone);
        newClient.setMiddleName(middleName);
        newClient.setEmail(email);
        newClient.setPassport(passportSeries, passportNumber);
        newClient.setBirthDate(birthDate);
        newClient.setAddress(address);
        newClient.setRegistrationDate(getCurrentDate());

        clients.add(newClient);

        System.out.println("\n✓ Клиент успешно зарегистрирован! ID: " + newClient.getClientId());
        pause();
    }

    private static void blockUnblockClient() {
        clearScreen();
        System.out.println("\n═══ БЛОКИРОВКА/РАЗБЛОКИРОВКА КЛИЕНТА ═══\n");

        int id = readInt("Введите ID клиента: ");
        Client client = findClientById(id);

        if (client == null) {
            System.out.println("\n✗ Клиент не найден.");
            pause();
            return;
        }

        displayClientDetails(client);

        System.out.println("\nТекущий статус: " + 
            (client.isBlacklisted() ? "ЗАБЛОКИРОВАН" : "Активен"));

        if (client.isBlacklisted()) {
            System.out.print("\nРазблокировать клиента? (да/нет): ");
            String answer = scanner.nextLine().trim().toLowerCase();
            if (answer.equals("да") || answer.equals("yes")) {
                client.setBlacklisted(false);
                client.setBlacklistReason("");
                System.out.println("\n✓ Клиент разблокирован.");
            }
        } else {
            System.out.print("\nЗаблокировать клиента? (да/нет): ");
            String answer = scanner.nextLine().trim().toLowerCase();
            if (answer.equals("да") || answer.equals("yes")) {
                System.out.print("Причина блокировки: ");
                String reason = scanner.nextLine().trim();
                client.setBlacklisted(true);
                client.setBlacklistReason(reason);
                System.out.println("\n✓ Клиент заблокирован.");
            }
        }
        pause();
    }

    private static void createRentalMenu() {
        clearScreen();
        System.out.println("\n═══ ОФОРМЛЕНИЕ АРЕНДЫ ═══\n");

        // Шаг 1: Выбор клиента
        int clientId = readInt("Введите ID клиента: ");
        Client client = findClientById(clientId);

        if (client == null) {
            System.out.println("\n✗ Клиент не найден.");
            pause();
            return;
        }

        if (client.isBlacklisted()) {
            System.out.println("\n✗ Клиент заблокирован: " + client.getBlacklistReason());
            pause();
            return;
        }

        displayClientDetails(client);

        // Шаг 2: Выбор носителей
        List<VideoCarrier> selectedItems = new ArrayList<>();
        System.out.println("\n═══ ВЫБОР НОСИТЕЛЕЙ ═══");

        while (true) {
            int invNumber = readInt("\nВведите инвентарный номер носителя (0 - завершить выбор): ");
            if (invNumber == 0) break;

            VideoCarrier item = catalog.findItemByNumber(invNumber);
            if (item == null) {
                System.out.println("✗ Носитель не найден.");
            } else if (!item.isAvailable()) {
                System.out.println("✗ Носитель недоступен. Статус: " + 
                    getStatusRussian(item.getStatus()));
            } else {
                selectedItems.add(item);
                System.out.println("✓ Добавлено: " + item.getTitle());
            }
        }

        if (selectedItems.isEmpty()) {
            System.out.println("\n✗ Не выбрано ни одного носителя.");
            pause();
            return;
        }

        // Шаг 3: Параметры аренды
        int days = readInt("\nКоличество дней аренды: ");
        if (days <= 0) {
            System.out.println("\n✗ Неверное количество дней.");
            pause();
            return;
        }

        String rentalDate = getCurrentDate();
        String returnDate = addDays(rentalDate, days);

        // Шаг 4: Расчет стоимости
        double deposit = 0;
        double rentalCost = 0;

        System.out.println("\n═══ РАСЧЕТ СТОИМОСТИ ═══\n");
        System.out.println(String.format("%-30s %15s %15s", "Носитель", "Залог", "Стоимость"));
        System.out.println("─".repeat(65));

        for (VideoCarrier item : selectedItems) {
            double itemDeposit = item.getFullPrice();
            double itemCost = item.getRentalPricePerDay() * days;
            deposit += itemDeposit;
            rentalCost += itemCost;

            System.out.println(String.format("%-30s %15.2f %15.2f",
                truncate(item.getTitle(), 30), itemDeposit, itemCost));
        }

        System.out.println("─".repeat(65));
        System.out.println(String.format("%-30s %15.2f %15.2f", "ИТОГО:", deposit, rentalCost));
        System.out.println(String.format("%-30s %31.2f", "К ОПЛАТЕ:", deposit + rentalCost));

        // Шаг 5: Подтверждение
        System.out.print("\nПодтвердить оформление аренды? (да/нет): ");
        String confirm = scanner.nextLine().trim().toLowerCase();

        if (confirm.equals("да") || confirm.equals("yes")) {
            Rental rental = rentalManager.createRental(client, selectedItems, days, 
                rentalDate, returnDate);
            
            if (rental != null) {
                System.out.println("\n✓ Аренда успешно оформлена!");
                System.out.println("ID аренды: " + rental.getRentalId());
                System.out.println("Дата возврата: " + returnDate);
            } else {
                System.out.println("\n✗ Ошибка при оформлении аренды.");
            }
        } else {
            System.out.println("\n✗ Оформление отменено.");
        }
        pause();
    }

    private static void processReturnMenu() {
        clearScreen();
        System.out.println("\n═══ ОБРАБОТКА ВОЗВРАТА ═══\n");

        List<Rental> activeRentals = rentalManager.getActiveRentals();
        
        if (activeRentals.isEmpty()) {
            System.out.println("Нет активных аренд.");
            pause();
            return;
        }

        System.out.println("Активные аренды:\n");
        System.out.println(String.format("%-8s %-25s %-15s %-15s", 
            "ID", "Клиент", "Дата выдачи", "План. возврат"));
        System.out.println("─".repeat(70));

        for (Rental rental : activeRentals) {
            Client client = rental.getClient();
            System.out.println(String.format("%-8d %-25s %-15s %-15s",
                rental.getRentalId(),
                truncate(client.getLastName() + " " + client.getFirstName(), 25),
                rental.getRentalDate(),
                rental.getPlannedReturnDate()));
        }

        int rentalId = readInt("\nВведите ID аренды для возврата (0 - отмена): ");
        if (rentalId == 0) return;

        Rental rental = findRentalById(activeRentals, rentalId);
        if (rental == null) {
            System.out.println("\n✗ Аренда не найдена.");
            pause();
            return;
        }

        System.out.println("\n═══ ИНФОРМАЦИЯ ОБ АРЕНДЕ ═══");
        System.out.println("Клиент: " + rental.getClient().getFirstName() + " " + 
            rental.getClient().getLastName());
        System.out.println("Носителей: " + rental.getItems().size());
        System.out.println("План. возврат: " + rental.getPlannedReturnDate());

        int overdueDays = readInt("\nКоличество дней просрочки (0 если в срок): ");

        System.out.print("Есть повреждения? (да/нет): ");
        String hasDamage = scanner.nextLine().trim().toLowerCase();

        double totalReturn;

        if (hasDamage.equals("да") || hasDamage.equals("yes")) {
            System.out.println("\n═══ ОЦЕНКА ПОВРЕЖДЕНИЙ ═══");
            
            for (int i = 0; i < rental.getItems().size(); i++) {
                VideoCarrier item = rental.getItems().get(i);
                System.out.println((i + 1) + ". " + item.getTitle());
            }

            int itemIndex = readInt("\nНомер поврежденного носителя: ") - 1;
            if (itemIndex < 0 || itemIndex >= rental.getItems().size()) {
                System.out.println("\n✗ Неверный номер.");
                pause();
                return;
            }

            VideoCarrier damagedItem = rental.getItems().get(itemIndex);
            
            System.out.println("\nТип повреждения:");
            System.out.println("  1. Незначительное (царапины)");
            System.out.println("  2. Критическое (утеря/серьезная порча)");
            int damageType = readInt("Выбор: ");

            String damageTypeName;
            double compensation;

            if (damageType == 1) {
                damageTypeName = "minor";
                compensation = readDouble("Сумма компенсации: ");
            } else {
                damageTypeName = "critical";
                compensation = damagedItem.getFullPrice();
                System.out.println("Компенсация (полная стоимость): " + compensation);
            }

            totalReturn = rentalManager.processReturnWithDamage(rental, overdueDays, 
                damagedItem, damageTypeName, compensation);

            System.out.println("\n✓ Возврат обработан с учетом повреждений.");
            System.out.println("Статус носителя: " + getStatusRussian(damagedItem.getStatus()));
        } else {
            totalReturn = rentalManager.processReturn(rental, overdueDays);
            System.out.println("\n✓ Возврат обработан успешно.");
        }

        System.out.println("\nСумма к возврату клиенту: " + String.format("%.2f", totalReturn) + " руб.");
        
        if (overdueDays > 0) {
            System.out.println("Штраф за просрочку: " + 
                String.format("%.2f", rental.getDepositAmount() - totalReturn) + " руб.");
        }

        pause();
    }

    private static void reportsMenu() {
        while (true) {
            clearScreen();
            showHeader();
            System.out.println("\n═══ ОТЧЕТЫ И СТАТИСТИКА ═══\n");

            System.out.println("  1. Финансовый отчет");
            System.out.println("  2. Отчет по клиентам");
            System.out.println("  3. Топ популярных носителей");
            System.out.println("  4. Отчет по просрочкам");
            System.out.println("  5. Дашборд текущего дня" +
                (currentUser.hasPermission("view_all_reports") ? "" : " [НЕДОСТУПНО]"));
            System.out.println("  0. Назад");
            System.out.println();

            int choice = readInt("Выберите пункт меню: ");

            switch (choice) {
                case 1:
                    showFinancialReport();
                    break;
                case 2:
                    showClientReport();
                    break;
                case 3:
                    showTopItemsReport();
                    break;
                case 4:
                    showOverdueReport();
                    break;
                case 5:
                    if (currentUser.hasPermission("view_all_reports")) {
                        showDailyDashboard();
                    } else {
                        System.out.println("\n✗ Недостаточно прав.");
                        pause();
                    }
                    break;
                case 0:
                    return;
                default:
                    System.out.println("\n✗ Неверный выбор.");
                    pause();
            }
        }
    }

    private static void showFinancialReport() {
        clearScreen();
        System.out.println(reportGenerator.generateFinancialReport("2025-01-01", "2025-12-31"));
        pause();
    }

    private static void showClientReport() {
        clearScreen();
        System.out.println(reportGenerator.generateClientReport(clients));
        pause();
    }

    private static void showTopItemsReport() {
        clearScreen();
        List<VideoCarrier> topItems = catalog.getTopRentedItems(10);
        System.out.println(reportGenerator.generateTopItemsReport(topItems));
        pause();
    }

    private static void showOverdueReport() {
        clearScreen();
        List<Rental> overdueRentals = rentalManager.getOverdueRentals(getCurrentDate());
        System.out.println(reportGenerator.generateOverdueReport(overdueRentals));
        pause();
    }

    private static void showDailyDashboard() {
        clearScreen();
        Map<String, Integer> stats = catalog.getStatistics();
        String dashboard = reportGenerator.generateDailyDashboard(
            rentalManager.getActiveRentals().size(),
            rentalManager.getOverdueRentals(getCurrentDate()).size(),
            0.0,  // Требует расширения для реального подсчета
            clients.size(),
            stats
        );
        System.out.println(dashboard);
        pause();
    }

    private static void usersMenu() {
        clearScreen();
        System.out.println("\n═══ УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ ═══\n");

        System.out.println("Список пользователей системы:\n");
        System.out.println(String.format("%-5s %-20s %-25s %-20s %-10s",
            "ID", "Логин", "ФИО", "Роль", "Статус"));
        System.out.println("─".repeat(85));

        for (User user : users) {
            System.out.println(String.format("%-5d %-20s %-25s %-20s %-10s",
                user.getUserId(),
                user.getUsername(),
                truncate(user.getFullName(), 25),
                user.getRole(),
                user.isActive() ? "Активен" : "Неактивен"));
        }

        pause();
    }

    // Вспомогательные методы

    private static void showHeader() {
        System.out.println("\n╔════════════════════════════════════════════════════════════════╗");
        System.out.println("║  Пользователь: " + String.format("%-45s", currentUser.getFullName()) + " ║");
        System.out.println("║  Роль: " + String.format("%-53s", currentUser.getRole()) + " ║");
        System.out.println("╚════════════════════════════════════════════════════════════════╝");
    }

    private static void clearScreen() {
        try {
            if (System.getProperty("os.name").contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            } else {
                System.out.print("\033[H\033[2J");
                System.out.flush();
            }
        } catch (Exception e) {
            // Если не удалось очистить экран, просто добавим пустые строки
            for (int i = 0; i < 50; i++) System.out.println();
        }
    }

    private static void pause() {
        System.out.print("\nНажмите Enter для продолжения...");
        scanner.nextLine();
    }

    private static int readInt(String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                String input = scanner.nextLine().trim();
                return Integer.parseInt(input);
            } catch (NumberFormatException e) {
                System.out.println("✗ Введите корректное число.");
            }
        }
    }

    private static double readDouble(String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                String input = scanner.nextLine().trim();
                return Double.parseDouble(input);
            } catch (NumberFormatException e) {
                System.out.println("✗ Введите корректное число.");
            }
        }
    }

    private static String truncate(String str, int maxLength) {
        if (str == null) return "";
        return str.length() <= maxLength ? str : str.substring(0, maxLength - 3) + "...";
    }

    private static String getStatusRussian(String status) {
        switch (status) {
            case "available": return "Доступен";
            case "rented": return "Арендован";
            case "maintenance": return "Реставрация";
            case "written_off": return "Списан";
            default: return status;
        }
    }

    private static String getCurrentDate() {
        return "2025-01-18";  // Для демонстрации используем фиксированную дату
    }

    private static String addDays(String date, int days) {
        // Упрощенная реализация для демонстрации
        return "2025-01-" + (18 + days);
    }

    private static Client findClientById(int id) {
        for (Client client : clients) {
            if (client.getClientId() == id) return client;
        }
        return null;
    }

    private static Client findClientByPhone(String phone) {
        for (Client client : clients) {
            if (client.getPhoneNumber().equals(phone)) return client;
        }
        return null;
    }

    private static List<Client> findClientsByLastName(String lastName) {
        List<Client> results = new ArrayList<>();
        for (Client client : clients) {
            if (client.getLastName().toLowerCase().contains(lastName.toLowerCase())) {
                results.add(client);
            }
        }
        return results;
    }

    private static Rental findRentalById(List<Rental> rentals, int id) {
        for (Rental rental : rentals) {
            if (rental.getRentalId() == id) return rental;
        }
        return null;
    }

    private static void displayCarrierDetails(VideoCarrier item) {
        System.out.println("─".repeat(70));
        System.out.println("Инв. №: " + item.getInventoryNumber());
        System.out.println("Название: " + item.getTitle());
        System.out.println("Тип: " + item.getCarrierType() + " | Жанр: " + item.getGenre());
        System.out.println("Год: " + item.getReleaseYear() + " | Режиссер: " + item.getDirector());
        System.out.println("Возраст: " + item.getAgeRating());
        System.out.println("Стоимость проката: " + item.getRentalPricePerDay() + " руб/день");
        System.out.println("Полная стоимость: " + item.getFullPrice() + " руб");
        System.out.println("Статус: " + getStatusRussian(item.getStatus()));
        System.out.println("Всего аренд: " + item.getTotalRentals());
    }

    private static void displayClientDetails(Client client) {
        System.out.println("\n─".repeat(70));
        System.out.println("ID: " + client.getClientId());
        System.out.println("ФИО: " + client.getLastName() + " " + client.getFirstName() + 
            " " + client.getMiddleName());
        System.out.println("Телефон: " + client.getPhoneNumber());
        System.out.println("Email: " + client.getEmail());
        System.out.println("Паспорт: " + client.getPassportSeries() + " " + 
            client.getPassportNumber());
        System.out.println("Дата рождения: " + client.getBirthDate());
        System.out.println("Бонусы: " + client.getBonusPoints());
        System.out.println("Статус: " + (client.isBlacklisted() ? "ЗАБЛОКИРОВАН" : "Активен"));
        if (client.isBlacklisted()) {
            System.out.println("Причина: " + client.getBlacklistReason());
        }
        System.out.println("─".repeat(70));
    }

    private static void cleanup() {
        rentalManager.close();
        scanner.close();
    }
}
