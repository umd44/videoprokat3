#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Client.hpp"
#include "VideoCarrier.hpp"
#include "Rental.hpp"
#include "Catalog.hpp"
#include "RentalManager.hpp"
#include "ReportGenerator.hpp"
#include "FinancialCalculator.hpp"
#include "VideoRentalException.hpp"

int main()
{
    auto ivan = std::make_shared<Client>(1, "Иван", "Иванов", "+7-000");

    auto matrix = std::make_shared<VideoCarrier>(100, "Матрица", "DVD", "Фантастика", 50.0, 500.0);
    auto interstellar = std::make_shared<VideoCarrier>(101, "Интерстеллар", "BluRay", "Фантастика", 60.0, 600.0);
    auto alien = std::make_shared<VideoCarrier>(102, "Чужой", "DVD", "Ужасы", 40.0, 400.0);

    Catalog catalog;
    catalog.addItem(matrix);
    catalog.addItem(interstellar);
    catalog.addItem(alien);

    RentalManager manager;
    std::vector<std::shared_ptr<VideoCarrier>> items;
    items.push_back(catalog.findItemByNumber(100));
    items.push_back(catalog.findItemByNumber(101));
    items.erase(std::remove_if(items.begin(), items.end(),
                               [](const std::shared_ptr<VideoCarrier>& ptr) { return !ptr; }),
                items.end());

    auto rental = manager.createRental(ivan, items, 3, "2025-10-15", "2025-10-18");
    if (rental) {
        std::cout << "Стоимость аренды: " << rental->getRentalCost() << "\n";
        std::cout << "Сумма к оплате при возврате: " << manager.processReturn(rental, 2) << "\n";
    }

    ReportGenerator report;
    std::cout << "Финансовый отчёт: " << report.generateFinancialReport("2025-10-01", "2025-10-31") << "\n";
    std::cout << "Отчёт по складу: " << report.generateInventoryReport(catalog.getAvailableItems()) << "\n";

    VideoCarrier::configureDefaultPricing(45.0, 450.0);
    VideoCarrier promo;
    std::cout << "Статические цены по умолчанию: "
              << VideoCarrier::getDefaultRentalPricePerDay() << "/"
              << VideoCarrier::getDefaultFullPrice() << "\n";
    std::cout << "Промо-носитель создан с этими значениями: "
              << promo.getRentalPricePerDay() << "/"
              << promo.getFullPrice() << "\n";

    VideoCarrier deluxe(900, "Коллекционное издание", "BluRay", "Экшен", 90.0, 900.0);
    VideoCarrier standard(901, "Стандартное издание", "BluRay", "Экшен", 60.0, 600.0);
    VideoCarrier economy(902, "Эконом версия", "DVD", "Экшен", 35.0, 350.0);
    deluxe.alignPricingWith(standard).alignPricingWith(economy);
    std::cout << "Выравненные цены: " << deluxe.getRentalPricePerDay()
              << "/" << deluxe.getFullPrice() << "\n";

    std::cout << "\n=== Демонстрация перегрузки операторов ===\n";
    
    // Пример 1: operator!= для Client - проверка неравенства клиентов
    Client client1_obj(10, "Петр", "Петров", "+7-222");
    Client client2_obj(11, "Сидор", "Сидоров", "+7-333");
    std::cout << "Клиенты разные: " << (client1_obj != client2_obj ? "да" : "нет") << "\n";
    
    // Пример 2: operator+= для Client - пополнение депозита через оператор
    client1_obj += 150.0;
    client1_obj += 50.0;
    std::cout << "Депозит после += 150 и += 50: " << client1_obj.getDepositBalance() << "\n";
    
    // Пример 3: operator+ для VideoCarrier - сложение цен аренды
    double totalPrice = *matrix + *interstellar;
    std::cout << "Сумма цен аренды (Матрица + Интерстеллар): " << totalPrice << " руб/день\n";
    
    // Пример 4: operator[] для Rental - доступ к носителям по индексу
    if (rental && rental->getItems().size() > 0) {
        auto firstItem = (*rental)[0];
        if (firstItem) {
            std::cout << "Первый носитель в аренде: " << firstItem->getTitle() << "\n";
        }
        if (rental->getItems().size() > 1) {
            auto secondItem = (*rental)[1];
            if (secondItem) {
                std::cout << "Второй носитель в аренде: " << secondItem->getTitle() << "\n";
            }
        }
    }
    
    // Пример 5: operator> для Rental - сравнение аренд по стоимости
    auto rental2 = manager.createRental(ivan, {alien}, 1, "2025-10-20", "2025-10-21");
    if (rental && rental2) {
        std::cout << "Первая аренда дороже второй: " << (*rental > *rental2 ? "да" : "нет") << "\n";
        std::cout << "  Первая: " << rental->getRentalCost() << ", вторая: " << rental2->getRentalCost() << "\n";
    }
    
    // Пример 6: operator* для FinancialCalculator - умножение стоимости на коэффициент
    FinancialCalculator calc;
    double baseCost = 100.0;
    double adjustedCost = baseCost * calc;
    std::cout << "Стоимость " << baseCost << " с коэффициентом калькулятора: " << adjustedCost << "\n";

    std::cout << "\n=== Демонстрация конструкторов копирования ===\n";
    
    // Конструктор копирования Client
    Client clientCopy(client1_obj);
    std::cout << "Оригинальный клиент ID: " << client1_obj.getClientId() 
              << ", копия ID: " << clientCopy.getClientId() << "\n";
    
    // Конструктор копирования VideoCarrier
    VideoCarrier matrixCopy(*matrix);
    std::cout << "Оригинальный носитель: " << matrix->getTitle() 
              << ", копия: " << matrixCopy.getTitle() << "\n";
    
    // Конструктор копирования Rental
    if (rental) {
        Rental rentalCopy(*rental);
        std::cout << "Оригинальная аренда ID: " << rental->getRentalId() 
                  << ", копия ID: " << rentalCopy.getRentalId() << "\n";
    }

    std::cout << "\n=== Тестирование исключений ===\n";
    auto riskyClient = std::make_shared<Client>(3, "Олег", "Рисковый", "+7-111");
    riskyClient->addToDeposit(100.0);

    try {
        std::cout << "Попытка заблокировать 300 единиц залога...\n";
        riskyClient->blockDepositFundsOrThrow(300.0);
        std::cout << "Средства успешно заблокированы\n";
    }
    catch (const InsufficientFundsException& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
        std::cout << "Требуется " << e.getRequired() << ", доступно " << e.getAvailable() << "\n";
    }

    try {
        std::cout << "Поиск несуществующего носителя...\n";
        auto missing = catalog.findItemByNumber(999);
        if (!missing) {
            throw ItemNotFoundException("VideoCarrier", 999);
        }
        std::cout << "Носитель найден: " << missing->getTitle() << "\n";
    }
    catch (const ItemNotFoundException& e) {
        std::cout << "Ошибка поиска: " << e.what() << "\n";
    }
    catch (const VideoRentalException& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}

