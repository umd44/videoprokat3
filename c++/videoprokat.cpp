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

    std::cout << "\n=== Демонстрация try/catch/throw ===\n";
    auto riskyClient = std::make_shared<Client>(3, "Олег", "Рисковый", "+7-111");
    riskyClient->addToDeposit(100.0);

    try {
        std::cout << "Попытка заблокировать 300 единиц залога...\n";
        riskyClient->blockDepositFundsOrThrow(300.0);
        std::cout << "Средства успешно заблокированы\n";
    }
    catch (const InsufficientFundsException& e) {
        std::cout << "Перехвачено исключение недостатка средств: " << e.what() << "\n";
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
        std::cout << "Перехвачено исключение поиска: " << e.what() << "\n";
    }
    catch (const VideoRentalException& e) {
        std::cout << "Другое исключение видеопроката: " << e.what() << "\n";
    }

    return 0;
}

