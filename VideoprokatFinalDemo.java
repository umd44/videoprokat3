package videoprokat;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Финальная демонстрационная программа системы видеопроката.
 * Реализует полный цикл работы с расширенной функциональностью:
 * - Многопользовательская система с ролями
 * - Расширенный учет клиентов и носителей
 * - Поиск по различным критериям
 * - Обработка повреждений и штрафов
 * - Детальная отчетность
 */
public class VideoprokatFinalDemo {

    public static void main(String[] args) {
        System.out.println("\n╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║  ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА - ФИНАЛЬНАЯ ВЕРСИЯ     ║");
        System.out.println("║  Локальная многопользовательская клиент-серверная система   ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝\n");

        printSectionHeader("1. ИНИЦИАЛИЗАЦИЯ СИСТЕМЫ И ПОЛЬЗОВАТЕЛЕЙ");
        
        User operator = new UserReal(1, "operator1", "pass123", "Operator", "Иванов Иван Иванович");
        User seniorOperator = new UserReal(2, "senior1", "pass456", "Senior Operator", "Петров Петр Петрович");
        User admin = new UserReal(3, "admin", "admin123", "Administrator", "Сидоров Сидор Сидорович");
        
        System.out.println("✓ Создан пользователь: " + operator.getFullName() + " [" + operator.getRole() + "]");
        System.out.println("✓ Создан пользователь: " + seniorOperator.getFullName() + " [" + seniorOperator.getRole() + "]");
        System.out.println("✓ Создан пользователь: " + admin.getFullName() + " [" + admin.getRole() + "]");
        
        System.out.println("\nПроверка прав доступа:");
        System.out.println("  Оператор может создавать аренды: " + 
            operator.hasPermission("create_rental"));
        System.out.println("  Оператор может управлять пользователями: " + 
            operator.hasPermission("manage_users"));
        System.out.println("  Старший оператор может применять скидки: " + 
            seniorOperator.hasPermission("apply_discount"));
        System.out.println("  Администратор может управлять пользователями: " + 
            admin.hasPermission("manage_users"));

        printSectionHeader("2. РЕГИСТРАЦИЯ КЛИЕНТОВ С ПОЛНЫМИ ДАННЫМИ");
        
        List<Client> clients = new ArrayList<>();
        
        ClientReal client1 = new ClientReal(1001, "Алексей", "Смирнов", "+7-925-123-45-67");
        client1.setMiddleName("Николаевич");
        client1.setEmail("smirnov@mail.ru");
        client1.setPassport("4512", "789456");
        client1.setAddress("г. Москва, ул. Ленина, д. 10, кв. 5");
        client1.setBirthDate("1990-05-15");
        client1.setRegistrationDate("2024-01-10");
        client1.addBonusPoints(50);
        clients.add(client1);
        
        ClientReal client2 = new ClientReal(1002, "Мария", "Иванова", "+7-916-987-65-43");
        client2.setMiddleName("Петровна");
        client2.setEmail("ivanova@gmail.com");
        client2.setPassport("4513", "654321");
        client2.setAddress("г. Москва, пр. Мира, д. 25, кв. 100");
        client2.setBirthDate("1995-08-22");
        client2.setRegistrationDate("2024-03-15");
        client2.addBonusPoints(120);
        clients.add(client2);
        
        ClientReal client3 = new ClientReal(1003, "Дмитрий", "Козлов", "+7-903-555-12-34");
        client3.setMiddleName("Владимирович");
        client3.setPassport("4514", "111222");
        client3.setAddress("г. Москва, ул. Победы, д. 7");
        client3.setBirthDate("1988-12-05");
        client3.setRegistrationDate("2023-11-20");
        client3.setBlacklisted(true);
        client3.setBlacklistReason("Просрочка более 7 дней, порча имущества");
        client3.setStatus("Blacklisted");
        clients.add(client3);
        
        System.out.println("✓ Клиент #" + client1.getClientId() + ": " + 
            client1.getLastName() + " " + client1.getFirstName() + " " + client1.getMiddleName());
        System.out.println("  Паспорт: " + client1.getPassportSeries() + " " + 
            client1.getPassportNumber() + " | Email: " + client1.getEmail());
        System.out.println("  Бонусы: " + client1.getBonusPoints() + " | Статус: " + client1.getStatus());
        
        System.out.println("\n✓ Клиент #" + client2.getClientId() + ": " + 
            client2.getLastName() + " " + client2.getFirstName() + " " + client2.getMiddleName());
        System.out.println("  Паспорт: " + client2.getPassportSeries() + " " + 
            client2.getPassportNumber() + " | Email: " + client2.getEmail());
        System.out.println("  Бонусы: " + client2.getBonusPoints() + " | Статус: " + client2.getStatus());
        
        System.out.println("\n✓ Клиент #" + client3.getClientId() + ": " + 
            client3.getLastName() + " " + client3.getFirstName() + " " + client3.getMiddleName());
        System.out.println("  Статус: ЗАБЛОКИРОВАН");
        System.out.println("  Причина: " + client3.getBlacklistReason());

        printSectionHeader("3. ЗАПОЛНЕНИЕ КАТАЛОГА ВИДЕОНОСИТЕЛЕЙ");
        
        Catalog catalog = new CatalogReal();
        
        addMovieToCatalog(catalog, 2001, "Матрица", "Blu-ray", "Фантастика", 1999, 
            "Вачовски", "16+", "Программист Томас Андерсон узнаёт правду о реальности", 100.0, 800.0);
        
        addMovieToCatalog(catalog, 2002, "Интерстеллар", "Blu-ray", "Фантастика", 2014, 
            "Кристофер Нолан", "12+", "Команда исследователей отправляется в космос", 120.0, 900.0);
        
        addMovieToCatalog(catalog, 2003, "Зеленая миля", "DVD", "Драма", 1999, 
            "Фрэнк Дарабонт", "16+", "История о начальнике охраны в тюрьме", 80.0, 500.0);
        
        addMovieToCatalog(catalog, 2004, "Властелин колец", "Blu-ray", "Фэнтези", 2001, 
            "Питер Джексон", "12+", "Эпическая история о Средиземье", 110.0, 850.0);
        
        addMovieToCatalog(catalog, 2005, "Чужой", "DVD", "Ужасы", 1979, 
            "Ридли Скотт", "18+", "Команда космического корабля встречает внеземную форму жизни", 90.0, 600.0);
        
        addMovieToCatalog(catalog, 2006, "Аватар", "Blu-ray", "Фэнтези", 2009, 
            "Джеймс Кэмерон", "12+", "История о планете Пандора", 130.0, 950.0);
        
        addMovieToCatalog(catalog, 2007, "Титаник", "DVD", "Мелодрама", 1997, 
            "Джеймс Кэмерон", "12+", "История любви на борту легендарного корабля", 70.0, 450.0);
        
        addMovieToCatalog(catalog, 2008, "Криминальное чтиво", "DVD", "Триллер", 1994, 
            "Квентин Тарантино", "18+", "Переплетение нескольких криминальных историй", 85.0, 550.0);
        
        System.out.println("✓ В каталог добавлено " + catalog.getAllItems().size() + " носителей");

        printSectionHeader("4. ДЕМОНСТРАЦИЯ СИСТЕМЫ ПОИСКА");
        
        System.out.println("Поиск по жанру 'Фантастика':");
        List<VideoCarrier> sciFiMovies = catalog.findItemsByGenre("Фантастика");
        for (VideoCarrier movie : sciFiMovies) {
            System.out.println("  • " + movie.getTitle() + " (" + movie.getReleaseYear() + 
                ") - " + movie.getDirector());
        }
        
        System.out.println("\nПоиск по режиссеру 'Джеймс Кэмерон':");
        List<VideoCarrier> cameronMovies = catalog.findItemsByDirector("Кэмерон");
        for (VideoCarrier movie : cameronMovies) {
            System.out.println("  • " + movie.getTitle() + " [" + movie.getCarrierType() + "]");
        }
        
        System.out.println("\nПоиск по типу носителя 'Blu-ray':");
        List<VideoCarrier> blurayMovies = catalog.findItemsByCarrierType("Blu-ray");
        System.out.println("  Найдено: " + blurayMovies.size() + " фильмов на Blu-ray");
        
        System.out.println("\nПоиск по возрастному рейтингу '12+':");
        List<VideoCarrier> age12Movies = catalog.findItemsByAgeRating("12+");
        for (VideoCarrier movie : age12Movies) {
            System.out.println("  • " + movie.getTitle());
        }

        printSectionHeader("5. ОФОРМЛЕНИЕ АРЕНДЫ");
        
        RentalManager manager = new RentalManagerReal();
        
        List<VideoCarrier> rental1Items = new ArrayList<>();
        rental1Items.add(catalog.findItemByNumber(2001));
        rental1Items.add(catalog.findItemByNumber(2002));
        
        Rental rental1 = manager.createRental(client1, rental1Items, 3, 
            "2025-01-15", "2025-01-18");
        
        System.out.println("✓ Аренда #" + rental1.getRentalId() + " создана");
        System.out.println("  Клиент: " + client1.getFirstName() + " " + client1.getLastName());
        System.out.println("  Носители: " + rental1.getItems().size() + " шт.");
        System.out.println("  Стоимость аренды: " + rental1.getRentalCost() + " руб.");
        System.out.println("  Залог: " + rental1.getDepositAmount() + " руб.");
        System.out.println("  Итого к оплате: " + (rental1.getRentalCost() + rental1.getDepositAmount()) + " руб.");
        System.out.println("  Период: " + rental1.getRentalDate() + " → " + rental1.getPlannedReturnDate());
        
        List<VideoCarrier> rental2Items = new ArrayList<>();
        rental2Items.add(catalog.findItemByNumber(2003));
        
        Rental rental2 = manager.createRental(client2, rental2Items, 5, 
            "2025-01-14", "2025-01-19");
        
        System.out.println("\n✓ Аренда #" + rental2.getRentalId() + " создана");
        System.out.println("  Клиент: " + client2.getFirstName() + " " + client2.getLastName());
        System.out.println("  Носитель: " + rental2Items.get(0).getTitle());
        System.out.println("  Стоимость аренды: " + rental2.getRentalCost() + " руб.");
        System.out.println("  Залог: " + rental2.getDepositAmount() + " руб.");

        printSectionHeader("6. ОБРАБОТКА ВОЗВРАТА БЕЗ ПРОБЛЕМ");
        
        System.out.println("Возврат аренды #" + rental1.getRentalId() + " в срок:");
        double refund1 = manager.processReturn(rental1, 0);
        System.out.println("✓ Возврат выполнен успешно");
        System.out.println("  Просрочка: нет");
        System.out.println("  Штраф: 0 руб.");
        System.out.println("  Сумма к возврату: " + refund1 + " руб.");
        System.out.println("  Статус носителей: Доступны");

        printSectionHeader("7. ОБРАБОТКА ВОЗВРАТА С ПРОСРОЧКОЙ");
        
        System.out.println("Возврат аренды #" + rental2.getRentalId() + " с просрочкой:");
        int overdueDays = 2;
        System.out.println("  Просрочка: " + overdueDays + " дня");
        System.out.println("  Тариф проката: " + rental2Items.get(0).getRentalPricePerDay() + " руб/день");
        System.out.println("  Расчет штрафа: " + rental2Items.get(0).getRentalPricePerDay() + 
            " × 2 × " + overdueDays + " = " + 
            (rental2Items.get(0).getRentalPricePerDay() * 2 * overdueDays) + " руб.");
        
        double refund2 = manager.processReturn(rental2, overdueDays);
        System.out.println("✓ Возврат выполнен");
        System.out.println("  Сумма к возврату: " + refund2 + " руб.");

        printSectionHeader("8. ОБРАБОТКА ВОЗВРАТА С ПОВРЕЖДЕНИЯМИ");
        
        List<VideoCarrier> rental3Items = new ArrayList<>();
        VideoCarrier damagedMovie = catalog.findItemByNumber(2004);
        rental3Items.add(damagedMovie);
        rental3Items.add(catalog.findItemByNumber(2005));
        
        Rental rental3 = manager.createRental(client2, rental3Items, 3, 
            "2025-01-16", "2025-01-19");
        
        System.out.println("Создана аренда #" + rental3.getRentalId());
        System.out.println("Клиент возвращает носители с повреждением:");
        System.out.println("  Поврежденный носитель: " + damagedMovie.getTitle());
        System.out.println("  Тип повреждения: Незначительное (царапины на диске)");
        System.out.println("  Компенсация: 200 руб.");
        
        double refund3 = manager.processReturnWithDamage(rental3, 0, damagedMovie, 
            "minor", 200.0);
        
        System.out.println("✓ Возврат обработан");
        System.out.println("  Сумма к возврату: " + refund3 + " руб.");
        System.out.println("  Статус поврежденного носителя: " + damagedMovie.getStatus());
        
        System.out.println("\nОбработка критического повреждения:");
        
        List<VideoCarrier> rental4Items = new ArrayList<>();
        VideoCarrier lostMovie = catalog.findItemByNumber(2006);
        rental4Items.add(lostMovie);
        
        Rental rental4 = manager.createRental(client1, rental4Items, 2, 
            "2025-01-17", "2025-01-19");
        
        System.out.println("Создана аренда #" + rental4.getRentalId());
        System.out.println("  Носитель: " + lostMovie.getTitle());
        System.out.println("  Полная стоимость: " + lostMovie.getFullPrice() + " руб.");
        System.out.println("\nКлиент потерял носитель:");
        System.out.println("  Тип повреждения: Критическое (утеря)");
        System.out.println("  Компенсация: " + lostMovie.getFullPrice() + " руб. (полная стоимость)");
        
        double refund4 = manager.processReturnWithDamage(rental4, 0, lostMovie, 
            "critical", lostMovie.getFullPrice());
        
        System.out.println("✓ Возврат обработан");
        System.out.println("  Сумма к возврату: " + refund4 + " руб.");
        System.out.println("  Статус носителя: " + lostMovie.getStatus() + " (списан)");

        printSectionHeader("9. СТАТИСТИКА И ОТЧЕТНОСТЬ");
        
        Map<String, Integer> stats = catalog.getStatistics();
        System.out.println("Статистика каталога:");
        System.out.println("  Всего носителей: " + stats.get("total"));
        System.out.println("  Доступных: " + stats.get("available"));
        System.out.println("  Арендованных: " + stats.get("rented"));
        System.out.println("  На реставрации: " + stats.get("maintenance"));
        System.out.println("  Списанных: " + stats.get("written_off"));
        
        System.out.println("\nТоп популярных носителей:");
        List<VideoCarrier> topItems = catalog.getTopRentedItems(5);
        int rank = 1;
        for (VideoCarrier item : topItems) {
            System.out.println("  " + rank++ + ". " + item.getTitle() + 
                " - " + item.getTotalRentals() + " аренд");
        }

        printSectionHeader("10. ГЕНЕРАЦИЯ ОТЧЕТОВ");
        
        ReportGenerator reportGen = new ReportGeneratorReal();
        
        System.out.println(reportGen.generateClientReport(clients));
        
        System.out.println(reportGen.generateTopItemsReport(topItems));
        
        System.out.println(reportGen.generateOverdueReport(manager.getOverdueRentals("2025-01-20")));

        printSectionHeader("11. ДАШБОРД ДЛЯ РУКОВОДИТЕЛЯ");
        
        String dashboard = reportGen.generateDailyDashboard(
            manager.getActiveRentals().size(),
            0,
            rental1.getRentalCost() + rental2.getRentalCost() + rental3.getRentalCost() + rental4.getRentalCost(),
            clients.size(),
            stats
        );
        System.out.println(dashboard);

        printSectionHeader("12. ЗАВЕРШЕНИЕ РАБОТЫ СИСТЕМЫ");
        
        System.out.println("✓ Освобождение ресурсов менеджера аренды");
        manager.close();
        
        System.out.println("✓ Очистка ссылок на объекты");
        System.out.println("✓ Все операции завершены успешно");
        
        System.out.println("\n╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║          ДЕМОНСТРАЦИЯ СИСТЕМЫ ЗАВЕРШЕНА УСПЕШНО             ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝\n");
    }

    private static void printSectionHeader(String title) {
        System.out.println("\n" + "=".repeat(70));
        System.out.println(title);
        System.out.println("=".repeat(70) + "\n");
    }

    private static void addMovieToCatalog(Catalog catalog, int invNumber, String title, 
                                           String type, String genre, int year, 
                                           String director, String ageRating, 
                                           String description, double pricePerDay, 
                                           double fullPrice) {
        VideoCarrierReal movie = new VideoCarrierReal(invNumber, title, type, genre, 
            pricePerDay, fullPrice);
        movie.setReleaseYear(year);
        movie.setDirector(director);
        movie.setAgeRating(ageRating);
        movie.setDescription(description);
        catalog.addItem(movie);
        
        System.out.println("  ✓ #" + invNumber + " | " + title + " (" + year + ") [" + type + 
            "] | " + genre + " | " + ageRating + " | " + pricePerDay + " руб/день");
    }
}
