#include <iostream>
#include <vector>
#include <iomanip>

#include "Client.hpp"
#include "PremiumClient.hpp"
#include "VideoCarrier.hpp"
#include "DVDCarrier.hpp"
#include "BluRayCarrier.hpp"
#include "PaymentProcessor.hpp"

void printSeparator(const std::string& title)
{
    std::cout << "\n========================================\n";
    std::cout << title << "\n";
    std::cout << "========================================\n\n";
}

void demonstrateVirtualFunctions()
{
    printSeparator("ДЕМОНСТРАЦИЯ ВИРТУАЛЬНЫХ ФУНКЦИЙ");
    
    std::cout << "--- 1. Вызов через указатель базового класса ---\n";
    Client* basePtr = new PremiumClient(1, "Alice", "Johnson", "+7-222", "alice@example.com", 15.0);
    
    std::cout << "\nДобавление депозита через указатель базового класса:\n";
    basePtr->addToDeposit(1000.0);
    
    std::cout << "\n--- 2. Вызов виртуальной функции через не виртуальную ---\n";
    basePtr->processTransaction(500.0);
    
    delete basePtr;
    
    std::cout << "\n--- 3. Демонстрация изменения поведения БЕЗ virtual ---\n";
    std::cout << "Если бы методы не были виртуальными, вызывались бы методы базового класса\n";
    std::cout << "и не было бы сообщений о начислении бонусных баллов.\n";
}

void demonstratePolymorphismWithArray()
{
    printSeparator("ПОЛИМОРФИЗМ С МАССИВОМ ОБЪЕКТОВ");
    
    std::vector<VideoCarrier*> carriers;
    carriers.push_back(new VideoCarrier(100, "Classic Film", "VHS", "Drama", 30.0, 300.0));
    carriers.push_back(new DVDCarrier(101, "Modern Film", "Action", 45.0, 450.0, 1, "2"));
    carriers.push_back(new BluRayCarrier(102, "New Release", "Sci-Fi", 60.0, 600.0, true, true));
    
    for (auto* carrier : carriers) {
        std::cout << "\nНоситель: " << carrier->getTitle() 
                  << " (" << carrier->getCarrierType() << ")\n";
        std::cout << "Цена аренды: " << carrier->getRentalPricePerDay() << " руб.\n";
        carrier->markAsRented();
        
        if (DVDCarrier* dvd = dynamic_cast<DVDCarrier*>(carrier)) {
            std::cout << "Это DVD диск #" << dvd->getDiskNumber() 
                      << ", регион: " << dvd->getRegion() << "\n";
        } else if (BluRayCarrier* bluray = dynamic_cast<BluRayCarrier*>(carrier)) {
            std::cout << "Это BluRay " << (bluray->isIs4K() ? "4K " : "")
                      << (bluray->hasHDR() ? "HDR " : "")
                      << bluray->getStorageGB() << "GB\n";
        }
    }
    
    for (auto* carrier : carriers) {
        delete carrier;
    }
}

void demonstrateCloning()
{
    printSeparator("ДЕМОНСТРАЦИЯ КЛОНИРОВАНИЯ");
    
    std::cout << "--- Поверхностное клонирование ---\n";
    DVDCarrier* original1 = new DVDCarrier(500, "Inception", "Sci-Fi", 45.0, 450.0, 1, "2");
    original1->addSubtitle("English");
    original1->addSubtitle("Russian");
    
    std::cout << "\nОригинал создан с субтитрами: ";
    for (const auto& sub : original1->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\n";
    
    DVDCarrier* shallowClone = original1->shallowClone();
    std::cout << "Субтитры клона: ";
    for (const auto& sub : shallowClone->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\n";
    
    std::cout << "\nДобавляем Spanish в клон...\n";
    shallowClone->addSubtitle("Spanish");
    
    std::cout << "Субтитры оригинала: ";
    for (const auto& sub : original1->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\nВНИМАНИЕ: При поверхностном клонировании указатель на вектор разделяется!\n";
    
    delete original1;
    
    std::cout << "\n--- Глубокое клонирование ---\n";
    DVDCarrier* original2 = new DVDCarrier(501, "Matrix", "Sci-Fi", 50.0, 500.0, 1, "1");
    original2->addSubtitle("English");
    original2->addSubtitle("Russian");
    
    std::cout << "Оригинал создан с субтитрами: ";
    for (const auto& sub : original2->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\n";
    
    DVDCarrier* deepClone = original2->deepClone();
    std::cout << "Субтитры глубокого клона: ";
    for (const auto& sub : deepClone->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\n";
    
    std::cout << "\nДобавляем French в клон...\n";
    deepClone->addSubtitle("French");
    
    std::cout << "Субтитры оригинала: ";
    for (const auto& sub : original2->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\nСубтитры клона: ";
    for (const auto& sub : deepClone->getSubtitles()) {
        std::cout << sub << " ";
    }
    std::cout << "\nПри глубоком клонировании векторы независимы!\n";
    
    delete original2;
    delete deepClone;
}

void demonstrateAssignmentOperator()
{
    printSeparator("ПЕРЕГРУЗКА ОПЕРАТОРА ПРИСВАИВАНИЯ");
    
    std::cout << "Создаем обычного клиента:\n";
    Client baseClient(10, "John", "Doe", "+7-100");
    baseClient.addToDeposit(2000.0);
    
    std::cout << "\nСоздаем премиум-клиента:\n";
    PremiumClient premiumClient(20, "Jane", "Smith", "+7-200", "jane@example.com", 20.0);
    
    std::cout << "\nПрисваиваем базовый класс производному:\n";
    premiumClient = baseClient;
    
    std::cout << "Имя премиум-клиента после присваивания: " 
              << premiumClient.getFirstName() << " " << premiumClient.getLastName() << "\n";
    std::cout << "Баланс: " << premiumClient.getDepositBalance() << "\n";
    std::cout << "Скидка (сброшена на дефолт): " << premiumClient.getDiscountPercentage() << "%\n";
}

void demonstrateAbstractClass()
{
    printSeparator("ДЕМОНСТРАЦИЯ АБСТРАКТНОГО КЛАССА");
    
    std::cout << "PaymentProcessor - абстрактный класс с чисто виртуальными функциями\n";
    std::cout << "Нельзя создать объект PaymentProcessor напрямую\n\n";
    
    std::cout << "--- Работа через указатель базового класса ---\n";
    PaymentProcessor* processor1 = new CashPaymentProcessor();
    processor1->executePayment(1500.0, "Оплата аренды");
    delete processor1;
    
    std::cout << "\n";
    PaymentProcessor* processor2 = new CardPaymentProcessor();
    processor2->executePayment(2000.0, "Оплата депозита");
    delete processor2;
}

void demonstrateVirtualDestructor()
{
    printSeparator("ВИРТУАЛЬНЫЙ ДЕСТРУКТОР");
    
    std::cout << "--- С виртуальным деструктором ---\n";
    std::cout << "При удалении через указатель базового класса\n";
    std::cout << "вызываются деструкторы и производного, и базового класса:\n\n";
    
    Client* client = new PremiumClient(30, "Bob", "Brown", "+7-300", "bob@example.com", 10.0);
    delete client;
    
    std::cout << "\nЕсли бы деструктор не был виртуальным,\n";
    std::cout << "вызывался бы только деструктор базового класса,\n";
    std::cout << "что могло бы привести к утечке памяти в производном классе.\n";
}

void demonstrateProtected()
{
    printSeparator("ИСПОЛЬЗОВАНИЕ PROTECTED");
    
    std::cout << "Protected поля и методы базового класса доступны в производном:\n\n";
    
    std::cout << "PremiumClient имеет доступ к protected полям Client:\n";
    std::cout << "- m_clientId, m_firstName, m_depositBalance и др.\n\n";
    
    std::cout << "DVDCarrier имеет доступ к protected полям VideoCarrier:\n";
    std::cout << "- m_inventoryNumber, m_title, m_rentalPricePerDay и др.\n\n";
    
    std::cout << "Это позволяет производным классам напрямую работать с данными,\n";
    std::cout << "но скрывает их от внешнего кода.\n";
}

void demonstrateDeletedCopyConstructor()
{
    printSeparator("ЗАПРЕЩЕННЫЙ КОНСТРУКТОР КОПИРОВАНИЯ");
    
    std::cout << "PremiumClient и BluRayCarrier имеют удаленный конструктор копирования:\n";
    std::cout << "PremiumClient(const PremiumClient&) = delete;\n";
    std::cout << "BluRayCarrier(const BluRayCarrier&) = delete;\n\n";
    
    std::cout << "Попытка копирования приведет к ошибке компиляции:\n";
    std::cout << "// PremiumClient client2 = client1; // ОШИБКА!\n";
    std::cout << "// BluRayCarrier bluray2 = bluray1; // ОШИБКА!\n";
}

int main()
{
    std::cout << "╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║   ДЕМОНСТРАЦИЯ КОНЦЕПЦИЙ ООП В C++                      ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    
    demonstrateVirtualFunctions();
    demonstratePolymorphismWithArray();
    demonstrateCloning();
    demonstrateAssignmentOperator();
    demonstrateAbstractClass();
    demonstrateVirtualDestructor();
    demonstrateProtected();
    demonstrateDeletedCopyConstructor();
    
    std::cout << "\n╔══════════════════════════════════════════════════════════╗\n";
    std::cout << "║   ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА                                 ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════╝\n";
    
    return 0;
}
