#include <iostream>
#include <vector>

#include "Client.hpp"
#include "VideoCarrier.hpp"
#include "Catalog.hpp"
#include "FinancialCalculator.hpp"
#include "Rental.hpp"
#include "RentalManager.hpp"
#include "ReportGenerator.hpp"

int main()
{
    // Статические объекты
    Client staticClient(1, "Ivan", "Ivanov", "+7-000");
    VideoCarrier staticItem(100, "Matrix", "DVD", "Sci-Fi", 50.0, 500.0);

    // Динамические объекты
    Client* dynClient = new Client(2, "Petr", "Petrov", "+7-111");
    VideoCarrier* dynItem = new VideoCarrier(101, "Interstellar", "BluRay", "Sci-Fi", 60.0, 600.0);

    // Ссылка и указатель
    Client& refClient = *dynClient;
    VideoCarrier* ptrItem = dynItem;

    // Динамический массив объектов
    std::vector<VideoCarrier> objectArray;
    objectArray.emplace_back(200, "Alien", "DVD", "Horror", 40.0, 400.0);
    objectArray.emplace_back(201, "Alien 2", "DVD", "Horror", 40.0, 400.0);

    // Массив динамических объектов
    std::vector<VideoCarrier*> pointerArray;
    pointerArray.push_back(new VideoCarrier(300, "Avatar", "BluRay", "Fantasy", 70.0, 700.0));
    pointerArray.push_back(new VideoCarrier(301, "Avatar 2", "BluRay", "Fantasy", 80.0, 800.0));

    // Заполнение каталога
    Catalog catalog;
    catalog.addItem(&staticItem);
    catalog.addItem(ptrItem);
    for (auto& item : objectArray) catalog.addItem(&item);
    for (auto* p : pointerArray) catalog.addItem(p);

    // Создание аренды
    RentalManager manager;
    std::vector<VideoCarrier*> itemsForRental;
    itemsForRental.push_back(catalog.findItemByNumber(100));
    itemsForRental.push_back(catalog.findItemByNumber(101));

    Rental* r = manager.createRental(&refClient, itemsForRental, 3, "2025-10-15", "2025-10-18");
    if (r) {
        std::cout << "Аренда создана. Стоимость=" << r->getRentalCost() << ", депозит=" << r->getDepositAmount() << "\n";
        double total = manager.processReturn(r, 2);
        std::cout << "Возврат выполнен. Итого к оплате=" << total << "\n";
    }

    // Отчеты
    ReportGenerator rg;
    std::cout << rg.generateFinancialReport("2025-10-01", "2025-10-31") << "\n";
    auto inv = rg.generateInventoryReport(catalog.getAvailableItems());
    std::cout << inv << "\n";

    for (auto* p : pointerArray) delete p;
    // Освобождение памяти
    delete dynClient;
    delete dynItem;

    return 0;
}
