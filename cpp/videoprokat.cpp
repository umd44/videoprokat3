#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <clocale>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>
#include <regex>
#include <fstream>
#include <filesystem>
#include <codecvt>
#include <cwctype>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include "ClientReal.hpp"
#include "VideoCarrierReal.hpp"
#include "CatalogReal.hpp"
#include "FinancialCalculatorReal.hpp"
#include "RentalReal.hpp"
#include "RentalManagerReal.hpp"
#include "ReportGeneratorReal.hpp"
#include "UserReal.hpp"

    // Настройка кодировки консоли для корректного отображения текста
void setupConsoleEncoding() {
#ifdef _WIN32
    // Переводим консоль «Виндовс» в ЮТФ-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    // Важно: привязка локали убрана, чтобы избежать проблем с кодировками при чтении/записи файлов
}

class VideoprokatInteractiveApp {
private:
    User* currentUser;
    Catalog* catalog;
    RentalManager* rentalManager;
    ReportGenerator* reportGenerator;
    std::vector<Client*> clients;
    std::vector<User*> users;
    int nextClientId;
    int nextInventoryNumber;
    double dailyRevenue;

public:
    VideoprokatInteractiveApp() 
        : currentUser(nullptr), nextClientId(1001), nextInventoryNumber(2001), dailyRevenue(0.0) {
        catalog = new CatalogReal();
        rentalManager = new RentalManagerReal();
        reportGenerator = new ReportGeneratorReal();
    }

    ~VideoprokatInteractiveApp() {
        cleanup();
    }

    // Точка входа приложения
    void run() {
        setupConsoleEncoding();  // Настраиваем консоль под ЮТФ-8
        initializeSystem();       // Загружаем данные из файлов
        showWelcomeScreen();      // Показываем приветствие
        
        // Авторизация пользователя
        if (login()) {
            mainMenu();  // Переходим в главное меню после успешного входа
        }
        
        // Сообщение при выходе
        std::cout << "\n╔════════════════════════════════════════════════════╗\n";
        std::cout << "║  Спасибо за использование системы видеопроката!    ║\n";
        std::cout << "╚════════════════════════════════════════════════════╝\n\n";
    }

private:
    // Инициализация системы: загрузка данных из текстовых файлов или создание данных по умолчанию
    void initializeSystem() {
        // Загружаем пользователей из текстовой БД
        loadUsersFromFile();

        // Если файла нет или он пуст — создаём пользователей по умолчанию
        if (users.empty()) {
            createDefaultUsers();
        }

        // Загружаем клиентов и каталог видеоносителей из текстовых файлов
        loadDataFromFiles();

        // Загружаем финансовые данные (выручка и т.п.)
        loadFinancialDataFromFile();

        // Если файлы пустые (первый запуск) — создаём тестовые данные
        if (clients.empty() && catalog->getAllItems().empty()) {
            createTestData();
        }
    }
    
    void createDefaultUsers() {
        users.push_back(new UserReal(1, "operator", "1234", "Operator", "Иванов Иван Иванович"));
        users.push_back(new UserReal(2, "senior", "5678", "Senior Operator", "Петров Петр Петрович"));
        users.push_back(new UserReal(3, "admin", "admin", "Administrator", "Сидоров Сидор Сидорович"));
    }
    
    void createTestData() {
        ClientReal* client1 = new ClientReal(nextClientId++, "Алексей", "Смирнов", "+7-925-123-45-67");
        client1->setMiddleName("Николаевич");
        client1->setEmail("smirnov@mail.ru");
        client1->setPassport("4512", "789456");
        client1->setBirthDate("1990-05-15");
        client1->setRegistrationDate("2024-01-10");
        client1->addBonusPoints(50);
        clients.push_back(client1);

        ClientReal* client2 = new ClientReal(nextClientId++, "Мария", "Иванова", "+7-916-987-65-43");
        client2->setMiddleName("Петровна");
        client2->setEmail("ivanova@gmail.com");
        client2->setPassport("4513", "654321");
        client2->setBirthDate("1995-08-22");
        client2->setRegistrationDate("2024-03-15");
        client2->addBonusPoints(120);
        clients.push_back(client2);

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

    void addMovieToCatalog(const std::string& title, const std::string& type, const std::string& genre, 
                          int year, const std::string& director, const std::string& ageRating, 
                          const std::string& description, double pricePerDay, double fullPrice) {
        VideoCarrierReal* movie = new VideoCarrierReal(nextInventoryNumber++, title, type, genre, 
            pricePerDay, fullPrice);
        movie->setReleaseYear(year);
        movie->setDirector(director);
        movie->setAgeRating(ageRating);
        movie->setDescription(description);
        catalog->addItem(movie);
    }

    void showWelcomeScreen() {
        clearScreen();
        std::cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
        std::cout << "║                                                                ║\n";
        std::cout << "║     ИНФОРМАЦИОННАЯ СИСТЕМА ВИДЕОПРОКАТА                        ║\n";
        std::cout << "║     Локальная многопользовательская система                    ║\n";
        std::cout << "║                                                                ║\n";
        std::cout << "╚════════════════════════════════════════════════════════════════╝\n\n";
    }

    bool login() {
        std::cout << "\n═══ ВХОД В СИСТЕМУ ═══\n\n";
        std::cout << "Доступные пользователи для входа:\n";
        std::cout << "  1. operator / 1234 (Оператор)\n";
        std::cout << "  2. senior / 5678 (Старший оператор)\n";
        std::cout << "  3. admin / admin (Администратор)\n\n";

        int attempts = 0;
        while (attempts < 3) {
            std::string username, password;
            std::cout << "Логин: ";
            std::getline(std::cin, username);
            
            std::cout << "Пароль: ";
            std::getline(std::cin, password);

            for (User* user : users) {
                if (user->getUsername() == username && user->checkPassword(password)) {
                    currentUser = user;
                    std::cout << "\n✓ Вход выполнен успешно!\n";
                    std::cout << "Добро пожаловать, " << user->getFullName() << "\n";
                    std::cout << "Ваша роль: " << user->getRole() << "\n";
                    pause();
                    return true;
                }
            }

            attempts++;
            std::cout << "\n✗ Неверный логин или пароль. Попыток осталось: " << (3 - attempts) << "\n";
        }

        std::cout << "\n✗ Превышено количество попыток входа. Доступ заблокирован.\n";
        return false;
    }

    void mainMenu() {
        while (true) {
            clearScreen();
            showHeader();

            std::cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
            std::cout << "║                       ГЛАВНОЕ МЕНЮ                             ║\n";
            std::cout << "╚════════════════════════════════════════════════════════════════╝\n\n";

            std::cout << "  1. Управление видеоносителями\n";
            std::cout << "  2. Управление клиентами\n";
            std::cout << "  3. Оформление аренды\n";
            std::cout << "  4. Обработка возврата\n";
            std::cout << "  5. Отчеты и статистика\n";
            std::cout << "  6. Управление пользователями" 
                << (currentUser->hasPermission("manage_users") ? "" : " [НЕДОСТУПНО]") << "\n";
            std::cout << "  0. Выход из системы\n\n";

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
                    if (currentUser->hasPermission("manage_users")) {
                        usersMenu();
                    } else {
                        std::cout << "\n✗ У вас нет прав для доступа к этому разделу.\n";
                        pause();
                    }
                    break;
                case 0:
                    return;
                default:
                    std::cout << "\n✗ Неверный выбор. Попробуйте снова.\n";
                    pause();
            }
        }
    }

    void videoCarriersMenu() {
        while (true) {
            clearScreen();
            showHeader();
            std::cout << "\n═══ УПРАВЛЕНИЕ ВИДЕОНОСИТЕЛЯМИ ═══\n\n";

            std::cout << "  1. Просмотр всех носителей\n";
            std::cout << "  2. Поиск носителей\n";
            std::cout << "  3. Добавить новый носитель" 
                << (currentUser->hasPermission("edit_items") ? "" : " [НЕДОСТУПНО]") << "\n";
            std::cout << "  4. Статистика каталога\n";
            std::cout << "  0. Назад\n\n";

            int choice = readInt("Выберите пункт меню: ");

            switch (choice) {
                case 1:
                    viewAllCarriers();
                    break;
                case 2:
                    searchCarriersMenu();
                    break;
                case 3:
                    if (currentUser->hasPermission("edit_items")) {
                        addNewCarrier();
                    } else {
                        std::cout << "\n✗ Недостаточно прав.\n";
                        pause();
                    }
                    break;
                case 4:
                    showCatalogStatistics();
                    break;
                case 0:
                    return;
                default:
                    std::cout << "\n✗ Неверный выбор.\n";
                    pause();
            }
        }
    }

    void viewAllCarriers() {
        clearScreen();
        std::cout << "\n═══ ВСЕ ВИДЕОНОСИТЕЛИ ═══\n\n";

        auto items = catalog->getAllItems();
        if (items.empty()) {
            std::cout << "Каталог пуст.\n";
        } else {
            // Формат вывода делаем таким же, как в списке клиентов: фиксированные ширины столбцов и общая ширина 90
            const int W_NUM = 6;
            const int W_TITLE = 30;
            const int W_TYPE = 12;
            const int W_GENRE = 16;
            const int W_YEAR = 6;
            const int W_STATUS = 14;

            // Важно: std::setw() считает байты, а не "видимую ширину" строк в ЮТФ-8.
            // Для кириллицы это ломает колонки. Печатаем ячейки вручную по ширине ЮТФ-8.
            printCellRight("№", W_NUM);           std::cout << " ";
            printCellLeft("Название", W_TITLE);   std::cout << " ";
            printCellLeft("Тип", W_TYPE);         std::cout << " ";
            printCellLeft("Жанр", W_GENRE);       std::cout << " ";
            printCellLeft("Год", W_YEAR);         std::cout << " ";
            printCellLeft("Статус", W_STATUS);    std::cout << "\n";
            std::cout << std::string(90, '-') << "\n";

            for (auto item : items) {
                if (item) {
                    printCellRight(std::to_string(item->getInventoryNumber()), W_NUM); std::cout << " ";
                    printCellLeft(item->getTitle(), W_TITLE);                         std::cout << " ";
                    printCellLeft(item->getCarrierType(), W_TYPE);                    std::cout << " ";
                    printCellLeft(item->getGenre(), W_GENRE);                         std::cout << " ";
                    printCellRight(std::to_string(item->getReleaseYear()), W_YEAR);  std::cout << " ";
                    printCellLeft(getStatusRussian(item->getStatus()), W_STATUS);    std::cout << "\n";
                }
            }
            std::cout << "\nВсего носителей: " << items.size() << "\n";
        }
        
        waitForBackPrompt("\n" + std::string(90, '-') + "\nНажмите Enter или 0 для возврата в меню...");
    }

    void searchCarriersMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n═══ ПОИСК ВИДЕОНОСИТЕЛЕЙ ═══\n\n";

            std::cout << "  1. Поиск по названию\n";
            std::cout << "  2. Поиск по жанру\n";
            std::cout << "  3. Поиск по режиссеру\n";
            std::cout << "  4. Поиск по году выпуска\n";
            std::cout << "  5. Поиск по типу носителя\n";
            std::cout << "  6. Только доступные\n";
            std::cout << "  0. Назад\n\n";

            int choice = readInt("Выберите критерий поиска: ");

            std::vector<VideoCarrier*> results;

            switch (choice) {
                case 1: {
                    std::string title;
                    std::cout << "Введите название: ";
                    std::getline(std::cin, title);
                    results = catalog->findItemsByTitle(trim(title));
                    break;
                }
                case 2: {
                    std::string genre;
                    std::cout << "Введите жанр: ";
                    std::getline(std::cin, genre);
                    results = catalog->findItemsByGenre(trim(genre));
                    break;
                }
                case 3: {
                    std::string director;
                    std::cout << "Введите имя режиссера: ";
                    std::getline(std::cin, director);
                    results = catalog->findItemsByDirector(trim(director));
                    break;
                }
                case 4: {
                    int year = readInt("Введите год выпуска: ");
                    results = catalog->findItemsByYear(year);
                    break;
                }
                case 5: {
                    std::string type;
                    std::cout << "Введите тип (DVD/Blu-ray): ";
                    std::getline(std::cin, type);
                    results = catalog->findItemsByCarrierType(trim(type));
                    break;
                }
                case 6:
                    results = catalog->getAvailableItems();
                    break;
                case 0:
                    return;
                default:
                    std::cout << "\n✗ Неверный выбор.\n";
                    pause();
                    return;
            }

            std::cout << "\n═══ РЕЗУЛЬТАТЫ ПОИСКА ═══\n\n";
            if (results.empty()) {
                std::cout << "Ничего не найдено.\n";
            } else {
                for (auto item : results) {
                    if (item) {
                        displayCarrierDetails(item);
                        std::cout << "\n";
                    }
                }
                std::cout << "Найдено носителей: " << results.size() << "\n";
            }

            std::cout << "\n0. Назад\n1. Новый поиск (Enter — назад)\n";
            std::string actionLine;
            std::getline(std::cin, actionLine);
            if (actionLine.empty() || actionLine == "0") {
                return;
            }
            if (actionLine == "1") {
                continue;
            }
            return;
        }
    }

    void addNewCarrier() {
        clearScreen();
        std::cout << "\n═══ ДОБАВЛЕНИЕ НОВОГО НОСИТЕЛЯ ═══\n\n";

        std::string title, type, genre, director, ageRating, description;
        int year;
        double pricePerDay, fullPrice;

        std::cout << "Название: ";
        std::getline(std::cin, title);
        if (title.empty()) {
            std::cout << "\n✗ Название не может быть пустым.\n";
            pause();
            return;
        }

        std::cout << "Тип (DVD/Blu-ray): ";
        std::getline(std::cin, type);
        if (type != "DVD" && type != "Blu-ray") {
            std::cout << "\n✗ Тип должен быть 'DVD' или 'Blu-ray'.\n";
            pause();
            return;
        }

        std::cout << "Жанр: ";
        std::getline(std::cin, genre);
        if (genre.empty()) {
            std::cout << "\n✗ Жанр не может быть пустым.\n";
            pause();
            return;
        }

        year = readInt("Год выпуска: ");
        if (year < 1880 || year > 2100) {
            std::cout << "\n✗ Год должен быть между 1880 и 2100.\n";
            pause();
            return;
        }

        std::cout << "Режиссер: ";
        std::getline(std::cin, director);
        if (director.empty()) {
            std::cout << "\n✗ Режиссер не может быть пустым.\n";
            pause();
            return;
        }

        std::cout << "Возрастной рейтинг (0+/6+/12+/16+/18+): ";
        std::getline(std::cin, ageRating);
        if (ageRating != "0+" && ageRating != "6+" && ageRating != "12+" && 
            ageRating != "16+" && ageRating != "18+") {
            std::cout << "\n✗ Рейтинг должен быть одним из: 0+, 6+, 12+, 16+, 18+\n";
            pause();
            return;
        }

        pricePerDay = readDouble("Стоимость проката (руб/день): ");
        if (pricePerDay <= 0) {
            std::cout << "\n✗ Стоимость проката должна быть больше нуля.\n";
            pause();
            return;
        }

        fullPrice = readDouble("Полная стоимость: ");
        if (fullPrice <= 0) {
            std::cout << "\n✗ Полная стоимость должна быть больше нуля.\n";
            pause();
            return;
        }

        std::cout << "Описание: ";
        std::getline(std::cin, description);
        if (description.empty()) {
            std::cout << "\n✗ Описание не может быть пустым.\n";
            pause();
            return;
        }

        addMovieToCatalog(title, type, genre, year, director, ageRating, description, 
            pricePerDay, fullPrice);

        // Сохраняем обновлённый каталог в текстовую БД сразу после добавления
        saveVideoCarriersToFile();

        std::cout << "\n✓ Носитель успешно добавлен! Инвентарный номер: " << (nextInventoryNumber - 1) << "\n";

        // Ждём клавишу «Ввод» или 0 для возврата в меню
        waitForBackPrompt("\n" + std::string(60, '-') + "\nНажмите Enter или введите 0 для возврата в меню...\n");
    }

    void showCatalogStatistics() {
        clearScreen();
        std::cout << "\n═══ СТАТИСТИКА КАТАЛОГА ═══\n\n";

        auto stats = catalog->getStatistics();

        std::cout << "Всего носителей:       " << stats["total"] << "\n";
        std::cout << "Доступных:             " << stats["available"] << "\n";
        std::cout << "Арендованных:          " << stats["rented"] << "\n";
        std::cout << "На реставрации:        " << stats["maintenance"] << "\n";
        std::cout << "Списанных:             " << stats["written_off"] << "\n";

        std::cout << "\n═══ ТОП ПОПУЛЯРНЫХ НОСИТЕЛЕЙ ═══\n\n";

        auto topItems = catalog->getTopRentedItems(5);
        int rank = 1;
        for (auto item : topItems) {
            if (item) {
                std::cout << rank++ << ". " << item->getTitle() << " - " 
                    << item->getTotalRentals() << " аренд\n";
            }
        }

        pause();
    }

    void clientsMenu() {
        while (true) {
            clearScreen();
            showHeader();
            std::cout << "\n═══ УПРАВЛЕНИЕ КЛИЕНТАМИ ═══\n\n";

            std::cout << "  1. Просмотр всех клиентов\n";
            std::cout << "  2. Поиск клиента\n";
            std::cout << "  3. Регистрация нового клиента\n";
            std::cout << "  4. Заблокировать/разблокировать клиента"
                << (currentUser->hasPermission("edit_client_status") ? "" : " [НЕДОСТУПНО]") << "\n";
            std::cout << "  0. Назад\n\n";

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
                    if (currentUser->hasPermission("edit_client_status")) {
                        blockUnblockClient();
                    } else {
                        std::cout << "\n✗ Недостаточно прав.\n";
                        pause();
                    }
                    break;
                case 0:
                    return;
                default:
                    std::cout << "\n✗ Неверный выбор.\n";
                    pause();
            }
        }
    }

    void viewAllClients() {
        clearScreen();
        std::cout << "\n═══ ВСЕ КЛИЕНТЫ ═══\n\n";

        if (clients.empty()) {
            std::cout << "Клиенты отсутствуют.\n";
        } else {
            std::cout << std::setw(6) << "ID" << " " << std::setw(30) << "ФИО" << " " 
                << std::setw(18) << "Телефон" << " " << std::setw(12) << "Бонусы" << " " 
                << std::setw(10) << "Статус" << "\n";
            std::cout << std::string(90, '-') << "\n";

            for (auto client : clients) {
                if (client) {
                    std::string fullName = client->getLastName() + " " + client->getFirstName() + 
                        " " + client->getMiddleName();
                    std::cout << std::setw(6) << client->getClientId() << " " 
                        << std::setw(30) << truncate(fullName, 30) << " "
                        << std::setw(18) << client->getPhoneNumber() << " "
                        << std::setw(12) << client->getBonusPoints() << " "
                        << std::setw(10) << (client->isBlacklisted() ? "БЛОКИРОВАН" : "Активен") << "\n";
                }
            }
            std::cout << "\nВсего клиентов: " << clients.size() << "\n";
        }
        
        waitForBackPrompt("\n" + std::string(90, '-') + "\nНажмите Enter или 0 для возврата в меню...");
    }

    void searchClient() {
        clearScreen();
        std::cout << "\n═══ ПОИСК КЛИЕНТА ═══\n\n";

        std::cout << "  1. Поиск по ID\n";
        std::cout << "  2. Поиск по телефону\n";
        std::cout << "  3. Поиск по фамилии\n";
        std::cout << "  0. Назад\n\n";

        int choice = readInt("Выберите критерий поиска: ");

        Client* found = nullptr;

        switch (choice) {
            case 1: {
                int id = readInt("Введите ID клиента: ");
                found = findClientById(id);
                break;
            }
            case 2: {
                std::string phone;
                std::cout << "Введите телефон: ";
                std::getline(std::cin, phone);
                found = findClientByPhone(phone);
                break;
            }
            case 3: {
                std::string lastName;
                std::cout << "Введите фамилию: ";
                std::getline(std::cin, lastName);
                auto matches = findClientsByLastName(lastName);
                if (matches.empty()) {
                    std::cout << "\n✗ Клиенты не найдены.\n";
                } else {
                    std::cout << "\nНайдено клиентов: " << matches.size() << "\n";
                    for (auto c : matches) {
                        displayClientDetails(c);
                        std::cout << "\n";
                    }
                }
                pause();
                return;
            }
            case 0:
                return;
            default:
                std::cout << "\n✗ Неверный выбор.\n";
                pause();
                return;
        }

        if (found != nullptr) {
            displayClientDetails(found);
        } else {
            std::cout << "\n✗ Клиент не найден.\n";
        }
        pause();
    }

    void registerNewClient() {
        clearScreen();
        std::cout << "\n═══ РЕГИСТРАЦИЯ НОВОГО КЛИЕНТА ═══\n\n";

        std::string lastName, firstName, middleName, phone, email, passportSeries, passportNumber, 
                    birthDate, address;

        std::cout << "Фамилия: ";
        std::getline(std::cin, lastName);
        if (lastName.empty()) {
            std::cout << "\n✗ Фамилия не может быть пустой.\n";
            pause();
            return;
        }

        std::cout << "Имя: ";
        std::getline(std::cin, firstName);
        if (firstName.empty()) {
            std::cout << "\n✗ Имя не может быть пустым.\n";
            pause();
            return;
        }

        std::cout << "Отчество: ";
        std::getline(std::cin, middleName);

        std::cout << "Телефон: ";
        std::getline(std::cin, phone);
        if (phone.empty()) {
            std::cout << "\n✗ Некорректный номер телефона.\n";
            pause();
            return;
        }

        std::cout << "Email (опционально): ";
        std::getline(std::cin, email);

        std::cout << "Серия паспорта: ";
        std::getline(std::cin, passportSeries);
        if (passportSeries.empty() || passportSeries.length() != 4 || !std::all_of(passportSeries.begin(), passportSeries.end(), ::isdigit)) {
            std::cout << "\n✗ Серия паспорта должна содержать 4 цифры.\n";
            pause();
            return;
        }

        std::cout << "Номер паспорта: ";
        std::getline(std::cin, passportNumber);
        if (passportNumber.empty() || passportNumber.length() != 6 || !std::all_of(passportNumber.begin(), passportNumber.end(), ::isdigit)) {
            std::cout << "\n✗ Номер паспорта должен содержать 6 цифр.\n";
            pause();
            return;
        }

        std::cout << "Дата рождения (ГГГГ-ММ-ДД): ";
        std::getline(std::cin, birthDate);
        if (!birthDate.empty() && !std::regex_match(birthDate, std::regex("^\\d{4}-\\d{2}-\\d{2}$"))) {
            std::cout << "\n✗ Некорректный формат даты. Используйте ГГГГ-ММ-ДД.\n";
            pause();
            return;
        }

        std::cout << "Адрес: ";
        std::getline(std::cin, address);

        ClientReal* newClient = new ClientReal(nextClientId++, firstName, lastName, phone);
        newClient->setMiddleName(middleName);
        newClient->setEmail(email);
        newClient->setPassport(passportSeries, passportNumber);
        newClient->setBirthDate(birthDate);
        newClient->setAddress(address);
        newClient->setRegistrationDate(getCurrentDate());

        clients.push_back(newClient);
        // Сразу сохраняем обновлённый список клиентов в файл
        saveClientsToFile();

        std::cout << "\n✓ Клиент успешно зарегистрирован! ID: " << newClient->getClientId() << "\n";
        waitForBackPrompt("\n" + std::string(60, '-') + "\nНажмите Enter или 0 для возврата в меню...");
    }

    void blockUnblockClient() {
        clearScreen();
        std::cout << "\n═══ БЛОКИРОВКА/РАЗБЛОКИРОВКА КЛИЕНТА ═══\n\n";

        int id = readInt("Введите ID клиента: ");
        Client* client = findClientById(id);

        if (client == nullptr) {
            std::cout << "\n✗ Клиент не найден.\n";
            pause();
            return;
        }

        displayClientDetails(client);

        std::cout << "\nТекущий статус: " 
            << (client->isBlacklisted() ? "ЗАБЛОКИРОВАН" : "Активен") << "\n";

        if (client->isBlacklisted()) {
            std::string answer;
            std::cout << "\nРазблокировать клиента? (y/n): ";
            std::getline(std::cin, answer);
            if (!answer.empty() && (answer[0] == 'y' || answer[0] == 'Y')) {
                client->setBlacklisted(false);
                client->setBlacklistReason("");
                // Сохраняем обновлённые данные клиента в текстовую БД
                saveClientsToFile();
                std::cout << "\n✓ Клиент разблокирован.\n";
                // Ждём клавишу «Ввод» или 0 для возврата в меню
                waitForBackPrompt("\nНажмите Enter или введите 0 для возврата в меню...\n");
                return;
            }
        } else {
            std::string answer;
            std::cout << "\nЗаблокировать клиента? (y/n): ";
            std::getline(std::cin, answer);
            if (!answer.empty() && (answer[0] == 'y' || answer[0] == 'Y')) {
                std::string reason;
                std::cout << "Причина блокировки: ";
                std::getline(std::cin, reason);
                client->setBlacklisted(true);
                client->setBlacklistReason(reason);
                // Сохраняем обновлённые данные клиента в текстовую БД
                saveClientsToFile();
                std::cout << "\n✓ Клиент заблокирован.\n";
                // Ждём клавишу «Ввод» или 0 для возврата в меню
                waitForBackPrompt("\nНажмите Enter или введите 0 для возврата в меню...\n");
                return;
            }
        }
        pause();
    }

    void createRentalMenu() {
        clearScreen();
        std::cout << "\n═══ ОФОРМЛЕНИЕ АРЕНДЫ ═══\n\n";

        int clientId = readInt("Введите ID клиента: ");
        Client* client = findClientById(clientId);

        if (client == nullptr) {
            std::cout << "\n✗ Клиент не найден.\n";
            pause();
            return;
        }

        if (client->isBlacklisted()) {
            std::cout << "\n✗ Клиент заблокирован: " << client->getBlacklistReason() << "\n";
            pause();
            return;
        }

        displayClientDetails(client);

        std::vector<VideoCarrier*> selectedItems;
        std::cout << "\n═══ ВЫБОР НОСИТЕЛЕЙ ═══\n";

        while (true) {
            int invNumber = readInt("\nВведите инвентарный номер носителя (0 - завершить выбор): ");
            if (invNumber == 0) break;

            VideoCarrier* item = catalog->findItemByNumber(invNumber);
            if (item == nullptr) {
                std::cout << "✗ Носитель не найден.\n";
            } else if (!item->isAvailable()) {
                std::cout << "✗ Носитель недоступен. Статус: " 
                    << getStatusRussian(item->getStatus()) << "\n";
            } else {
                selectedItems.push_back(item);
                std::cout << "✓ Добавлено: " << item->getTitle() << "\n";
            }
        }

        if (selectedItems.empty()) {
            std::cout << "\n✗ Не выбрано ни одного носителя.\n";
            pause();
            return;
        }

        int days = readInt("\nКоличество дней аренды: ");
        if (days <= 0) {
            std::cout << "\n✗ Неверное количество дней.\n";
            pause();
            return;
        }

        std::string rentalDate = getCurrentDate();
        std::string returnDate = addDays(rentalDate, days);

        double deposit = 0;
        double rentalCost = 0;

        std::cout << "\n═══ РАСЧЕТ СТОИМОСТИ ═══\n\n";
        std::cout << std::setw(30) << "Носитель" << " " << std::setw(15) << "Залог" 
            << " " << std::setw(15) << "Стоимость" << "\n";
        std::cout << std::string(65, '-') << "\n";

        for (auto item : selectedItems) {
            double itemDeposit = item->getFullPrice();
            double itemCost = item->getRentalPricePerDay() * days;
            deposit += itemDeposit;
            rentalCost += itemCost;

            std::cout << std::setw(30) << truncate(item->getTitle(), 30) << " " 
                << std::setw(15) << std::fixed << std::setprecision(2) << itemDeposit << " "
                << std::setw(15) << itemCost << "\n";
        }

        std::cout << std::string(65, '-') << "\n";
        std::cout << std::setw(30) << "ИТОГО:" << " " << std::setw(15) << deposit 
            << " " << std::setw(15) << rentalCost << "\n";
        std::cout << std::setw(30) << "К ОПЛАТЕ:" << " " << std::setw(31) 
            << (deposit + rentalCost) << "\n";

        std::string confirm;
        std::cout << "\nПодтвердить оформление аренды? (y/n): ";
        std::getline(std::cin, confirm);

        if (!confirm.empty() && (confirm[0] == 'y' || confirm[0] == 'Y')) {
            Rental* rental = rentalManager->createRental(client, selectedItems, days, 
                rentalDate, returnDate);
            
            if (rental != nullptr) {
                // Обновляем дневной доход при создании аренды
                dailyRevenue += rental->getTotalCost();
                
                std::cout << "\n✓ Аренда успешно оформлена!\n";
                std::cout << "ID аренды: " << rental->getRentalId() << "\n";
                std::cout << "Дата возврата: " << returnDate << "\n";
                std::cout << "Сумма к оплате: " << std::fixed << std::setprecision(2) 
                    << rental->getTotalCost() << " руб.\n";

                // Логируем оформление аренды в файл rentals_si.txt
                logRental(rental, selectedItems, client, days);
                
                // Сохраняем финансовые данные
                saveFinancialDataToFile("financial_data.txt");
            } else {
                std::cout << "\n✗ Ошибка при оформлении аренды.\n";
            }
        } else {
            std::cout << "\n✗ Оформление отменено.\n";
        }
        pause();
    }

    void processReturnMenu() {
        clearScreen();
        std::cout << "\n═══ ОБРАБОТКА ВОЗВРАТА ═══\n\n";

        auto activeRentals = rentalManager->getActiveRentals();
        
        if (activeRentals.empty()) {
            std::cout << "Нет активных аренд.\n";
            pause();
            return;
        }

        std::cout << "Активные аренды:\n\n";
        std::cout << std::setw(8) << "ID" << " " << std::setw(25) << "Клиент" << " " 
            << std::setw(15) << "Дата выдачи" << " " << std::setw(15) << "План. возврат" << "\n";
        std::cout << std::string(70, '-') << "\n";

        for (auto rental : activeRentals) {
            Client* client = rental->getClient();
            if (client) {
                std::cout << std::setw(8) << rental->getRentalId() << " " 
                    << std::setw(25) << truncate(client->getLastName() + " " + client->getFirstName(), 25) << " "
                    << std::setw(15) << rental->getRentalDate() << " "
                    << std::setw(15) << rental->getPlannedReturnDate() << "\n";
            }
        }

        int rentalId = readInt("\nВведите ID аренды для возврата (0 - отмена): ");
        if (rentalId == 0) return;

        Rental* rental = findRentalById(activeRentals, rentalId);
        if (rental == nullptr) {
            std::cout << "\n✗ Аренда не найдена.\n";
            pause();
            return;
        }

        std::cout << "\n═══ ИНФОРМАЦИЯ ОБ АРЕНДЕ ═══\n";
        Client* client = rental->getClient();
        if (client) {
            std::cout << "Клиент: " << client->getFirstName() << " " << client->getLastName() << "\n";
        }
        std::cout << "Носителей: " << rental->getItems().size() << "\n";
        std::cout << "План. возврат: " << rental->getPlannedReturnDate() << "\n";

        int overdueDays = readInt("\nКоличество дней просрочки (0 если в срок): ");

        std::string hasDamage;
        std::cout << "Есть повреждения? (y/n): ";
        std::getline(std::cin, hasDamage);

        double totalReturn;
        bool damageProcessed = false;

        if (!hasDamage.empty() && (hasDamage[0] == 'y' || hasDamage[0] == 'Y')) {
            std::cout << "\n═══ ОЦЕНКА ПОВРЕЖДЕНИЙ ═══\n";
            
            auto items = rental->getItems();
            for (size_t i = 0; i < items.size(); i++) {
                VideoCarrier* item = items[i];
                if (item) {
                    std::cout << (i + 1) << ". " << item->getTitle() << "\n";
                }
            }

            int itemIndex = readInt("\nНомер поврежденного носителя: ") - 1;
            auto items2 = rental->getItems();
            if (itemIndex < 0 || itemIndex >= static_cast<int>(items2.size())) {
                std::cout << "\n✗ Неверный номер.\n";
                pause();
                return;
            }

            VideoCarrier* damagedItem = items2[itemIndex];
            
            std::cout << "\nТип повреждения:\n";
            std::cout << "  1. Незначительное (царапины)\n";
            std::cout << "  2. Критическое (утеря/серьезная порча)\n";
            int damageType = readInt("Выбор: ");

            std::string damageTypeName;
            double compensation;

            if (damageType == 1) {
                damageTypeName = "minor";
                compensation = readDouble("Сумма компенсации: ");
            } else {
                damageTypeName = "critical";
                compensation = damagedItem->getFullPrice();
                std::cout << "Компенсация (полная стоимость): " << compensation << "\n";
            }

            totalReturn = rentalManager->processReturnWithDamage(rental, overdueDays, 
                damagedItem, damageTypeName, compensation);

            std::cout << "\n✓ Возврат обработан с учетом повреждений.\n";
            std::cout << "Статус носителя: " << getStatusRussian(damagedItem->getStatus()) << "\n";
            damageProcessed = true;
        } else {
            totalReturn = rentalManager->processReturn(rental, overdueDays);
            std::cout << "\n✓ Возврат обработан успешно.\n";
        }

        std::cout << "\nСумма к возврату клиенту: " << std::fixed << std::setprecision(2) 
            << totalReturn << " руб.\n";
        
        if (overdueDays > 0) {
            std::cout << "Штраф за просрочку: " << std::fixed << std::setprecision(2)
                << (rental->getDepositAmount() - totalReturn) << " руб.\n";
        }

        // Подтверждение фиксации возврата
        std::string confirm;
        std::cout << "\nПодтвердить обработку возврата? (y/n): ";
        std::getline(std::cin, confirm);
        if (!confirm.empty() && (confirm[0] != 'y' && confirm[0] != 'Y')) {
            std::cout << "\n✗ Возврат отменен.\n";
            waitForBackPrompt("\nНажмите Enter или введите 0 для возврата в меню...\n");
            return;
        }

        // Логируем возврат и обновляем дневной доход
        logReturn(rental, overdueDays, totalReturn, damageProcessed);
        dailyRevenue += totalReturn;

        // Сохраняем финансовые данные
        saveFinancialDataToFile("financial_data.txt");

        // В менеджере аренда уже убрана из списка activeRentals — безопасно удалить объект здесь
        delete rental;

        waitForBackPrompt("\n" + std::string(60, '-') + "\nНажмите Enter или введите 0 для возврата в меню...\n");
    }

    void reportsMenu() {
        while (true) {
            clearScreen();
            showHeader();
            std::cout << "\n═══ ОТЧЕТЫ И СТАТИСТИКА ═══\n\n";

            std::cout << "  1. Финансовый отчет\n";
            std::cout << "  2. Отчет по клиентам\n";
            std::cout << "  3. Топ популярных носителей\n";
            std::cout << "  4. Отчет по просрочкам\n";
            std::cout << "  5. Дашборд текущего дня"
                << (currentUser->hasPermission("view_all_reports") ? "" : " [НЕДОСТУПНО]") << "\n";
            std::cout << "  6. Сохранить отчеты в файлы\n";
            std::cout << "  0. Назад\n\n";

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
                    if (currentUser->hasPermission("view_all_reports")) {
                        showDailyDashboard();
                    } else {
                        std::cout << "\n✗ Недостаточно прав.\n";
                        pause();
                    }
                    break;
                case 6:
                    saveReportsToFiles();
        std::cout << "\n✓ Отчеты сохранены в файлы:\n";
        std::cout << "  - financial_report_si.txt\n";
        std::cout << "  - client_report_si.txt\n";
        std::cout << "  - daily_dashboard_si.txt\n";
                    pause();
                    break;
                case 0:
                    return;
                default:
                    std::cout << "\n✗ Неверный выбор.\n";
                    pause();
            }
        }
    }

    void showFinancialReport() {
        clearScreen();
        std::string report = reportGenerator->generateFinancialReport("2025-01-01", "2025-12-31");
        std::cout << report << "\n";
        std::cout << "Текущий доход за день: " << std::fixed << std::setprecision(2) << dailyRevenue << " руб.\n";
        pause();
    }

    void showClientReport() {
        clearScreen();
        std::cout << reportGenerator->generateClientReport(clients) << "\n";
        pause();
    }

    // Запись строки в текстовый файл (используется для логов и отчетов)
    void appendToFile(const std::string& filename, const std::string& text) {
        // Пишем в "правильное" место сохранения (родительская папка, если запуск из подпапки cpp/)
        std::ofstream file(findSaveFilePath(filename), std::ios::app);
        if (!file.is_open()) return;
        file << text << "\n";
    }

    // Логирование оформления аренды (rentals_si.txt)
    void logRental(Rental* rental, const std::vector<VideoCarrier*>& items, Client* client, int days) {
        if (!rental || !client) return;
        std::ostringstream oss;
        // Логи тоже выравниваем по фиксированной ширине (разделитель '|' сохраняем)
        oss << std::left
            << std::setw(8)   << rental->getRentalId()          << "|"
            << std::setw(6)   << client->getClientId()          << "|"
            << std::setw(12)  << rental->getRentalDate()        << "|"
            << std::setw(12)  << rental->getPlannedReturnDate() << "|"
            << std::setw(4)   << days                           << "|";
        bool first = true;
        for (auto item : items) {
            if (!item) continue;
            if (!first) oss << ",";
            first = false;
            oss << item->getInventoryNumber();
        }
        appendToFile("rentals_si.txt", oss.str());
    }

    // Логирование возврата аренды (returns_si.txt)
    void logReturn(Rental* rental, int overdueDays, double totalReturn, bool hasDamage) {
        if (!rental) return;
        Client* client = rental->getClient();
        int clientId = client ? client->getClientId() : 0;
        std::ostringstream oss;
        oss << std::left
            << std::setw(8)   << rental->getRentalId()          << "|"
            << std::setw(6)   << clientId                       << "|"
            << std::setw(12)  << rental->getRentalDate()        << "|"
            << std::setw(12)  << rental->getPlannedReturnDate() << "|"
            << std::setw(4)   << overdueDays                    << "|"
            << std::setw(10)  << std::fixed << std::setprecision(2) << totalReturn << "|"
            << (hasDamage ? "damage" : "ok");
        appendToFile("returns_si.txt", oss.str());
    }

    void showTopItemsReport() {
        clearScreen();
        auto topItems = catalog->getTopRentedItems(10);
        std::string report = reportGenerator->generateTopItemsReport(topItems);
        std::cout << report << "\n";
        appendToFile("report_top_items_si.txt", report);
        pause();
    }

    void showOverdueReport() {
        clearScreen();
        auto overdueRentals = rentalManager->getOverdueRentals(getCurrentDate());
        std::string report = reportGenerator->generateOverdueReport(overdueRentals);
        std::cout << report << "\n";
        appendToFile("report_overdue_si.txt", report);
        pause();
    }

    void showDailyDashboard() {
        clearScreen();
        auto stats = catalog->getStatistics();
        std::string dashboard = reportGenerator->generateDailyDashboard(
            static_cast<int>(rentalManager->getActiveRentals().size()),
            static_cast<int>(rentalManager->getOverdueRentals(getCurrentDate()).size()),
            dailyRevenue,
            static_cast<int>(clients.size()),
            stats
        );
        std::cout << dashboard << "\n";
        appendToFile("report_dashboard_si.txt", dashboard);
        pause();
    }

    void usersMenu() {
        while (true) {
            clearScreen();
            std::cout << "\n═══ УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ ═══\n\n";

            std::cout << "Список пользователей системы:\n\n";
            std::cout << std::setw(5) << "ID" << " " << std::setw(20) << "Логин" << " " 
                << std::setw(25) << "ФИО" << " " << std::setw(20) << "Роль" << " " 
                << std::setw(10) << "Статус" << "\n";
            std::cout << std::string(85, '-') << "\n";

            for (auto user : users) {
                if (user) {
                    std::cout << std::setw(5) << user->getUserId() << " " 
                        << std::setw(20) << user->getUsername() << " "
                        << std::setw(25) << truncate(user->getFullName(), 25) << " "
                        << std::setw(20) << user->getRole() << " "
                        << std::setw(10) << (user->isActive() ? "Активен" : "Неактивен") << "\n";
                }
            }

            std::cout << "\nОпции:\n";
            std::cout << "  1. Добавить нового пользователя\n";
            std::cout << "  0. Назад\n\n";

            int choice = readInt("Выберите пункт меню: ");
            if (choice == 0) {
                return;
            } else if (choice == 1) {
                registerNewUser();
            } else {
                std::cout << "\n✗ Неверный выбор.\n";
                pause();
            }
        }
    }

    void registerNewUser() {
        clearScreen();
        std::cout << "\n═══ ДОБАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯ ═══\n\n";

        std::string username, password, role, fullName;

        std::cout << "Логин: ";
        std::getline(std::cin, username);
        if (username.empty()) {
            std::cout << "\n✗ Логин не может быть пустым.\n";
            pause();
            return;
        }

        std::cout << "Пароль: ";
        std::getline(std::cin, password);
        if (password.empty()) {
            std::cout << "\n✗ Пароль не может быть пустым.\n";
            pause();
            return;
        }

        std::cout << "Роль (Operator / Senior Operator / Administrator): ";
        std::getline(std::cin, role);
        if (role != "Operator" && role != "Senior Operator" && role != "Administrator") {
            std::cout << "\n✗ Роль должна быть одной из: Operator, Senior Operator, Administrator.\n";
            pause();
            return;
        }

        std::cout << "ФИО: ";
        std::getline(std::cin, fullName);
        if (fullName.empty()) {
            std::cout << "\n✗ ФИО не может быть пустым.\n";
            pause();
            return;
        }

        int maxId = 0;
        for (auto user : users) {
            if (user) {
                maxId = std::max(maxId, user->getUserId());
            }
        }
        int newId = maxId + 1;

        // Создаём и добавляем нового пользователя в систему
        UserReal* newUser = new UserReal(newId, username, password, role, fullName);
        users.push_back(newUser);
        
        // Сохраняем обновлённый список пользователей в текстовую БД
        saveUsersToFile();

        std::cout << "\n✓ Пользователь добавлен. ID: " << newId << "\n";
        
        // Ждём клавишу «Ввод» или 0 для возврата в меню
        waitForBackPrompt("\n" + std::string(60, '-') + "\nНажмите Enter или введите 0 для возврата в меню...\n");
    }

    void showHeader() {
        std::cout << "\n╔════════════════════════════════════════════════════════════════╗\n";
        if (currentUser) {
            std::cout << "║  Пользователь: " << std::setw(45) << std::left << currentUser->getFullName() << "            ║\n";
            std::cout << "║  Роль: " << std::setw(53) << std::left << currentUser->getRole() << "   ║\n";
        }
        std::cout << "╚════════════════════════════════════════════════════════════════╝\n";
    }

    // Очистка экрана консоли (кроссплатформенно)
    void clearScreen() {
        #ifdef _WIN32
            system("cls");  // Команда для «Виндовс»
        #else
            std::cout << "\033[H\033[2J";  // Управляющие последовательности для Юникс/Линукс
            std::cout.flush();
        #endif
    }

    // Пауза: ожидание нажатия клавиши «Ввод»
    void pause() {
        std::cout << "\nНажмите Enter для возврата в предыдущее меню...";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    // Ввод целого числа с проверкой
    int readInt(const std::string& prompt) {
        while (true) {
            try {
                std::cout << prompt;
                std::string input;
                std::getline(std::cin, input);
                return std::stoi(input);
            } catch (const std::exception&) {
                std::cout << "✗ Введите корректное число.\n";
            }
        }
    }

    // Ввод дробного числа с проверкой
    double readDouble(const std::string& prompt) {
        while (true) {
            try {
                std::cout << prompt;
                std::string input;
                std::getline(std::cin, input);
                return std::stod(input);
            } catch (const std::exception&) {
                std::cout << "✗ Введите корректное число.\n";
            }
        }
    }

    // Убирает пробельные символы в начале и конце строки
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (std::string::npos == first) {
            return str;
        }
        size_t last = str.find_last_not_of(" \t\n\r");
        return str.substr(first, (last - first + 1));
    }

    // Обрезает строку до заданной длины и добавляет "..." при необходимости
    std::string truncate(const std::string& str, int maxLength) {
        if (str.length() <= static_cast<size_t>(maxLength)) {
            return str;
        }
        return str.substr(0, maxLength - 3) + "...";
    }

    // === Вспомогательные функции для выравнивания таблиц в консоли (ЮТФ-8) ===
    // std::setw() выравнивает по количеству байт; для ЮТФ-8 (кириллица) это ломает колонки.
    // Здесь выравниваем по "видимой ширине" — приблизительно по количеству символов ЮТФ-8.
    size_t utf8CodepointCount(const std::string& s) {
        size_t count = 0;
        for (size_t i = 0; i < s.size();) {
            unsigned char c = static_cast<unsigned char>(s[i]);
            if ((c & 0x80) == 0x00) {
                i += 1;
            } else if ((c & 0xE0) == 0xC0 && i + 1 < s.size()) {
                i += 2;
            } else if ((c & 0xF0) == 0xE0 && i + 2 < s.size()) {
                i += 3;
            } else if ((c & 0xF8) == 0xF0 && i + 3 < s.size()) {
                i += 4;
            } else {
                // Некорректная последовательность байт — считаем как один видимый символ
                i += 1;
            }
            ++count;
        }
        return count;
    }

    std::string utf8TruncateToWidth(const std::string& s, size_t maxWidth) {
        if (utf8CodepointCount(s) <= maxWidth) {
            return s;
        }
        if (maxWidth == 0) {
            return "";
        }
        if (maxWidth <= 3) {
            return std::string(maxWidth, '.');
        }

        const size_t target = maxWidth - 3; // под "..."
        std::string out;
        out.reserve(s.size());
        size_t width = 0;

        for (size_t i = 0; i < s.size() && width < target;) {
            unsigned char c = static_cast<unsigned char>(s[i]);
            size_t adv = 1;
            if ((c & 0x80) == 0x00) adv = 1;
            else if ((c & 0xE0) == 0xC0) adv = 2;
            else if ((c & 0xF0) == 0xE0) adv = 3;
            else if ((c & 0xF8) == 0xF0) adv = 4;
            if (i + adv > s.size()) adv = 1;
            out.append(s, i, adv);
            i += adv;
            ++width;
        }

        out += "...";
        return out;
    }

    std::string padRightUtf8(const std::string& s, size_t width) {
        size_t w = utf8CodepointCount(s);
        if (w >= width) return s;
        return s + std::string(width - w, ' ');
    }

    std::string padLeftUtf8(const std::string& s, size_t width) {
        size_t w = utf8CodepointCount(s);
        if (w >= width) return s;
        return std::string(width - w, ' ') + s;
    }

    void printCellLeft(const std::string& s, size_t width) {
        std::string t = utf8TruncateToWidth(s, width);
        std::cout << padRightUtf8(t, width);
    }

    void printCellRight(const std::string& s, size_t width) {
        std::string t = utf8TruncateToWidth(s, width);
        std::cout << padLeftUtf8(t, width);
    }

    // Пытается открыть файл, поднимаясь вверх по дереву директорий (до 5 уровней)
    // Это позволяет запускать программу из подпапки cpp/ или из корня проекта
    bool openFileWithFallback(std::ifstream& file, const std::string& filename) {
        namespace fs = std::filesystem;
        fs::path cur = fs::current_path();
        // Пробуем текущую директорию + 5 родительских
        for (int i = 0; i < 6; ++i) {
            fs::path candidate = cur / filename;
            file.open(candidate);
            if (file.is_open()) {
                return true;
            }
            file.clear();
            if (cur.has_parent_path()) {
                cur = cur.parent_path();
            } else {
                break;
            }
        }
        return false;
    }

    // Перебирает список имён файлов и открывает первый существующий (с учётом резервных путей).
    bool openFileWithFallbacks(std::ifstream& file, const std::vector<std::string>& filenames) {
        for (const auto& name : filenames) {
            file.close();
            if (openFileWithFallback(file, name)) {
                return true;
            }
        }
        return false;
    }

    // Определяет лучший путь для сохранения файлов (сначала пробуем родительскую папку)
    std::string findSaveFilePath(const std::string& filename) {
        namespace fs = std::filesystem;
        // Сначала пробуем родительскую директорию (когда запуск из подпапки cpp/)
        fs::path parentPath = fs::current_path().parent_path() / filename;
        if (fs::exists(parentPath.parent_path())) {
            return parentPath.string();
        }
        // Иначе сохраняем в текущую директорию
        return filename;
    }

    // Убирает метку порядка байтов и пробелы по краям из данных текстового файла
    std::string stripBomAndTrim(const std::string& value) {
        std::string trimmed = trim(value);
        // Проверяем метку порядка байтов (сигнатура: EF BB BF)
        if (trimmed.size() >= 3 &&
            static_cast<unsigned char>(trimmed[0]) == 0xEF &&
            static_cast<unsigned char>(trimmed[1]) == 0xBB &&
            static_cast<unsigned char>(trimmed[2]) == 0xBF) {
            trimmed = trimmed.substr(3);
        }
        return trimmed;
    }

    // Ожидание: «Ввод» или 0 для возврата в предыдущее меню
    void waitForBackPrompt(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string back;
            std::getline(std::cin, back);
            std::string cleaned = trim(back);
            // Принимаем пустую строку («Ввод») или "0" как возврат
            if (cleaned.empty() || cleaned == "0") {
                break;
            }
            std::cout << "Для возврата нажмите Enter или введите 0.\n";
        }
    }

    std::wstring toLowerWide(const std::string& str) {
#ifdef _WIN32
        int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
        if (len <= 1) {
            return std::wstring();
        }
        std::wstring wide(static_cast<size_t>(len - 1), L'\0');
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wide[0], len);
#else
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(str);
#endif
        for (auto& ch : wide) {
            ch = static_cast<wchar_t>(::towlower(ch));
        }
        return wide;
    }

    bool containsIgnoreCaseUtf8(const std::string& haystack, const std::string& needle) {
        return toLowerWide(haystack).find(toLowerWide(needle)) != std::wstring::npos;
    }

    std::string getStatusRussian(const std::string& status) {
        if (status == "available") return "Доступен";
        if (status == "rented") return "Арендован";
        if (status == "maintenance") return "Реставрация";
        if (status == "written_off") return "Списан";
        return status;
    }

    std::string getCurrentDate() {
        return "2025-01-18";
    }

    std::string addDays(const std::string& date, int days) {
        return "2025-01-" + std::to_string(18 + days);
    }

    Client* findClientById(int id) {
        for (auto client : clients) {
            if (client && client->getClientId() == id) return client;
        }
        return nullptr;
    }

    Client* findClientByPhone(const std::string& phone) {
        for (auto client : clients) {
            if (client && client->getPhoneNumber() == phone) return client;
        }
        return nullptr;
    }

    std::vector<Client*> findClientsByLastName(const std::string& lastName) {
        std::vector<Client*> results;
        for (auto client : clients) {
            if (client) {
                if (containsIgnoreCaseUtf8(client->getLastName(), lastName)) {
                    results.push_back(client);
                }
            }
        }
        return results;
    }

    Rental* findRentalById(const std::vector<Rental*>& rentals, int id) {
        for (auto rental : rentals) {
            if (rental && rental->getRentalId() == id) return rental;
        }
        return nullptr;
    }

    void displayCarrierDetails(VideoCarrier* item) {
        if (!item) return;
        std::cout << std::string(70, '-') << "\n";
        std::cout << "Инв. №: " << item->getInventoryNumber() << "\n";
        std::cout << "Название: " << item->getTitle() << "\n";
        std::cout << "Тип: " << item->getCarrierType() << " | Жанр: " << item->getGenre() << "\n";
        std::cout << "Год: " << item->getReleaseYear() << " | Режиссер: " << item->getDirector() << "\n";
        std::cout << "Возраст: " << item->getAgeRating() << "\n";
        std::cout << "Стоимость проката: " << item->getRentalPricePerDay() << " руб/день\n";
        std::cout << "Полная стоимость: " << item->getFullPrice() << " руб\n";
        std::cout << "Статус: " << getStatusRussian(item->getStatus()) << "\n";
        std::cout << "Всего аренд: " << item->getTotalRentals() << "\n";
    }

    void displayClientDetails(Client* client) {
        if (!client) return;
        std::cout << "\n" << std::string(70, '-') << "\n";
        std::cout << "ID: " << client->getClientId() << "\n";
        std::cout << "ФИО: " << client->getLastName() << " " << client->getFirstName() << " " 
            << client->getMiddleName() << "\n";
        std::cout << "Телефон: " << client->getPhoneNumber() << "\n";
        std::cout << "Email: " << client->getEmail() << "\n";
        std::cout << "Паспорт: " << client->getPassportSeries() << " " 
            << client->getPassportNumber() << "\n";
        std::cout << "Дата рождения: " << client->getBirthDate() << "\n";
        std::cout << "Бонусы: " << client->getBonusPoints() << "\n";
        std::cout << "Статус: " << (client->isBlacklisted() ? "ЗАБЛОКИРОВАН" : "Активен") << "\n";
        if (client->isBlacklisted()) {
            std::cout << "Причина: " << client->getBlacklistReason() << "\n";
        }
        std::cout << std::string(70, '-') << "\n";
    }

    // Загрузка всех данных из текстовых файлов БД
    void loadDataFromFiles() {
        loadClientsFromFile();
        loadVideoCarriersFromFile();
    }
    
    // Загрузка пользователей из текстовой БД (формат: поля разделены символом '|')
    void loadUsersFromFile(const std::string& filename = "users_si.txt") {
        std::ifstream file;
        // Ищем файл в текущей папке и по родительским (как и для клиентов/каталога)
        if (!openFileWithFallback(file, filename)) return;
        
        std::string line;
        // Читаем файл построчно
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            // Разбиваем строку по разделителю '|'
            std::stringstream ss(line);
            std::string part;
            std::vector<std::string> parts;
            
            while (std::getline(ss, part, '|')) {
                parts.push_back(stripBomAndTrim(part));
            }
            
            // Парсим данные пользователя (формат: ид|логин|пароль|роль|фио)
            if (parts.size() >= 5) {
                try {
                    int id = std::stoi(parts[0]);
                    UserReal* user = new UserReal(id, parts[1], parts[2], parts[3], parts[4]);
                    users.push_back(user);
                } catch (const std::exception&) {
                    // Пропускаем битые строки и продолжаем
                }
            }
        }
        file.close();
    }
    
    // Сохранение пользователей в текстовую БД (формат: поля разделены символом '|')
    void saveUsersToFile(const std::string& filename = "users_si.txt") {
        std::ofstream file(findSaveFilePath(filename), std::ios::out | std::ios::trunc);
        if (!file.is_open()) return;
        
        // Записываем каждого пользователя одной строкой, поля разделяем '|'
        for (auto user : users) {
            if (user) {
                // Формат "БД": фиксированная ширина полей + разделитель '|'
                file << std::left
                     << std::setw(6)  << user->getUserId()   << "|"
                     << std::setw(20) << user->getUsername() << "|"
                     << std::setw(12) << user->getPassword() << "|"
                     << std::setw(22) << user->getRole()     << "|"
                     << user->getFullName()
                     << "\n";
            }
        }
        file.close();
    }
    
    // Загрузка клиентов из текстовой БД (формат: поля разделены символом '|')
    void loadClientsFromFile(const std::string& filename = "clients_si.txt") {
        std::ifstream file;
        // Пытаемся открыть файл, при необходимости поднимаясь вверх по дереву директорий
        if (!openFileWithFallback(file, filename)) return;
        
        std::string line;
        // Читаем файл построчно
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            // Разбиваем строку по разделителю '|'
            std::stringstream ss(line);
            std::string part;
            std::vector<std::string> parts;
            
            while (std::getline(ss, part, '|')) {
                parts.push_back(stripBomAndTrim(part));  // Убираем метку порядка байтов и пробелы
            }
            
            // Парсим данные клиента (формат: ид|имя|фамилия|отчество|телефон|почта|серияПасп|номерПасп|датаРожд|датаРег|бонус|вЧерномСписке)
            if (parts.size() >= 10) {
                try {
                    int id = std::stoi(parts[0]);
                    ClientReal* client = new ClientReal(id, parts[1], parts[2], parts[3]);
                    
                    // Заполняем дополнительные поля, если они есть
                    if (parts.size() > 4) client->setMiddleName(parts[4]);
                    if (parts.size() > 5) client->setEmail(parts[5]);
                    if (parts.size() > 7) client->setPassport(parts[6], parts[7]);
                    if (parts.size() > 8) client->setBirthDate(parts[8]);
                    if (parts.size() > 9) client->setRegistrationDate(parts[9]);
                    if (parts.size() > 10) client->addBonusPoints(std::stoi(parts[10]));
                    if (parts.size() > 11) {
                        client->setBlacklisted(parts[11] == "1");
                    }
                    
                    clients.push_back(client);
                    nextClientId = std::max(nextClientId, id + 1);  // Обновляем следующий идентификатор
                } catch (const std::exception&) {
                    // Пропускаем битые строки и продолжаем
                }
            }
        }
        file.close();
    }
    
    // Загрузка каталога видеоносителей из текстовой БД (формат: поля разделены символом '|')
    void loadVideoCarriersFromFile(const std::string& filename = "videos_si.txt") {
        std::ifstream file;
        // Пытаемся открыть файл, при необходимости поднимаясь вверх по дереву директорий
        if (!openFileWithFallback(file, filename)) return;
        
        std::string line;
        // Читаем файл построчно
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            // Разбиваем строку по разделителю '|'
            std::stringstream ss(line);
            std::string part;
            std::vector<std::string> parts;
            
            while (std::getline(ss, part, '|')) {
                parts.push_back(stripBomAndTrim(part));  // Убираем метку порядка байтов и пробелы
            }
            
            // Парсим данные видеоносителя (формат: инвНомер|название|тип|жанр|год|режиссёр|возрРейтинг|ценаПроката|полнаяЦена)
            if (parts.size() >= 9) {
                try {
                    int inventoryNumber = std::stoi(parts[0]);
                    double rentPerDay = std::stod(parts[7]);
                    double fullPrice = std::stod(parts[8]);

                    // Создаём объект видеоносителя
                    VideoCarrierReal* item = new VideoCarrierReal(inventoryNumber, parts[1], parts[2], parts[3],
                        rentPerDay, fullPrice);
                    item->setReleaseYear(std::stoi(parts[4]));
                    item->setDirector(parts[5]);
                    item->setAgeRating(parts[6]);
                    if (parts.size() > 9) {
                        item->setDescription(parts[9]);
                    }
                    
                    catalog->addItem(item);
                    nextInventoryNumber = std::max(nextInventoryNumber, inventoryNumber + 1);  // Обновляем следующий идентификатор
                } catch (const std::exception&) {
                    // Пропускаем битые строки и продолжаем загрузку остальных записей
                }
            }
        }
        file.close();
    }

    // Сохранение клиентов в текстовую БД (формат: поля разделены символом '|')
    void saveClientsToFile(const std::string& filename = "clients_si.txt") {
        // Сначала пробуем сохранить в родительскую папку, затем — в текущую
        std::ofstream file(findSaveFilePath(filename), std::ios::out | std::ios::trunc);
        if (!file.is_open()) return;
        
        // Записываем каждого клиента одной строкой, поля разделяем '|'
        for (auto client : clients) {
            if (client) {
                // Формат "БД": фиксированная ширина полей + разделитель '|'
                file << std::left
                     << std::setw(6)  << client->getClientId()         << "|"
                     << std::setw(16) << client->getFirstName()        << "|"
                     << std::setw(18) << client->getLastName()         << "|"
                     << std::setw(18) << client->getMiddleName()       << "|"
                     << std::setw(18) << client->getPhoneNumber()      << "|"
                     << std::setw(26) << client->getEmail()            << "|"
                     << std::setw(6)  << client->getPassportSeries()   << "|"
                     << std::setw(10) << client->getPassportNumber()   << "|"
                     << std::setw(12) << client->getBirthDate()        << "|"
                     << std::setw(12) << client->getRegistrationDate() << "|"
                     << std::setw(6)  << client->getBonusPoints()      << "|"
                     << (client->isBlacklisted() ? "1" : "0")
                     << "\n";
            }
        }
        file.close();
    }

    // Сохранение каталога видеоносителей в текстовую БД (формат: поля разделены символом '|')
    void saveVideoCarriersToFile(const std::string& filename = "videos_si.txt") {
        std::ofstream file(findSaveFilePath(filename), std::ios::out | std::ios::trunc);
        if (!file.is_open()) return;
        
        // Записываем каждый видеоноситель одной строкой, поля разделяем '|'
        auto items = catalog->getAllItems();
        for (auto item : items) {
            if (item) {
                // Формат "БД": фиксированная ширина полей + разделитель '|'
                file << std::left
                     << std::setw(8)  << item->getInventoryNumber() << "|"
                     << std::setw(36) << item->getTitle()           << "|"
                     << std::setw(10) << item->getCarrierType()     << "|"
                     << std::setw(16) << item->getGenre()           << "|"
                     << std::setw(6)  << item->getReleaseYear()     << "|"
                     << std::setw(22) << item->getDirector()        << "|"
                     << std::setw(6)  << item->getAgeRating()       << "|"
                     << std::setw(10) << std::fixed << std::setprecision(2) << item->getRentalPricePerDay() << "|"
                     << std::setw(10) << std::fixed << std::setprecision(2) << item->getFullPrice()
                     << "\n";
            }
        }
        file.close();
    }

    // Сохранение финансовых данных в текстовый файл (формат: ключ=значение)
    void saveFinancialDataToFile(const std::string& filename = "financial_data_si.txt") {
        std::ofstream file(findSaveFilePath(filename), std::ios::out | std::ios::trunc);
        if (!file.is_open()) return;
        
        // Записываем финансовые данные в формате ключ=значение
        file << "dailyRevenue=" << dailyRevenue << "\n";
        file << "lastUpdate=" << getCurrentDate() << "\n";
        file.close();
    }

    void loadFinancialDataFromFile(const std::string& filename = "financial_data_si.txt") {
        std::ifstream file(filename);
        if (!file.is_open()) return;
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            size_t pos = line.find("=");
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                if (key == "dailyRevenue") {
                    try {
                        dailyRevenue = std::stod(value);
                    } catch (const std::exception& e) {
                        // Игнорируем ошибки парсинга
                    }
                }
                // При необходимости можно добавить загрузку других финансовых данных
            }
        }
        file.close();
    }

    void saveReportsToFiles() {
        saveReportToFile("financial_report_si.txt", reportGenerator->generateFinancialReport("2025-01-01", "2025-12-31"));
        saveReportToFile("client_report_si.txt", reportGenerator->generateClientReport(clients));
        
        // Сохраняем дашборд текущего дня
        auto activeRentals = rentalManager->getActiveRentals();
        auto overdueRentals = rentalManager->getOverdueRentals(getCurrentDate());
        auto statistics = catalog->getStatistics();
        std::string dashboard = reportGenerator->generateDailyDashboard(activeRentals.size(), 
            overdueRentals.size(), dailyRevenue, clients.size(), statistics);
        saveReportToFile("daily_dashboard_si.txt", dashboard);
    }

    void saveReportToFile(const std::string& filename, const std::string& content) {
        std::ofstream file(filename);
        if (!file.is_open()) return;
        
        file << content;
        file.close();
    }

    // Завершение работы: сохраняем все данные и освобождаем память
    void cleanup() {
        // Сохраняем все данные в текстовые файлы БД
        saveClientsToFile();
        saveVideoCarriersToFile();
        saveUsersToFile();
        saveFinancialDataToFile();
        saveReportsToFiles();
        
        // Освобождаем выделенную память
        if (rentalManager) {
            rentalManager->close();
            delete rentalManager;
        }
        if (catalog) {
            delete catalog;
        }
        if (reportGenerator) {
            delete reportGenerator;
        }
        for (auto client : clients) {
            delete client;
        }
        for (auto user : users) {
            delete user;
        }
    }
};

// Точка входа в программу
int main() {
    VideoprokatInteractiveApp app;
    app.run();
    return 0;
}
