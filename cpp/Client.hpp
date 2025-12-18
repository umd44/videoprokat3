#pragma once
#include <string>

/**
 * Абстрактный класс, описывающий клиента видеопроката.
 * Содержит базовую структуру и методы для работы с клиентом.
 */
class Client
{
protected:
    int clientId;
    std::string firstName;
    std::string lastName;
    std::string middleName;
    std::string phoneNumber;
    std::string email;
    std::string passportSeries;
    std::string passportNumber;
    std::string address;
    std::string birthDate;
    std::string registrationDate;
    double depositBalance;
    bool blacklisted;
    std::string blacklistReason;
    int bonusPoints;
    std::string status;

    /**
     * Конструктор по умолчанию.
     * Инициализирует все поля значениями по умолчанию.
     */
    Client();

    /**
     * Конструктор с параметрами.
     */
    Client(int clientId, const std::string& firstName, const std::string& lastName, const std::string& phoneNumber);

public:
    virtual ~Client() = default;

    /**
     * Получить идентификатор клиента.
     */
    virtual int getClientId() = 0;

    /**
     * Получить имя клиента.
     */
    virtual std::string getFirstName() = 0;

    /**
     * Получить фамилию клиента.
     */
    virtual std::string getLastName() = 0;

    /**
     * Получить номер телефона клиента.
     */
    virtual std::string getPhoneNumber() = 0;

    /**
     * Получить баланс депозита клиента.
     */
    virtual double getDepositBalance() = 0;

    /**
     * Проверить, находится ли клиент в черном списке.
     */
    virtual bool isBlacklisted() = 0;

    /**
     * Пополнить депозит клиента.
     */
    virtual void addToDeposit(double amount) = 0;

    /**
     * Заблокировать средства депозита.
     */
    virtual bool blockDepositFunds(double amount) = 0;

    /**
     * Разблокировать средства депозита.
     */
    virtual void unblockDepositFunds(double amount) = 0;

    /**
     * Установить статус черного списка.
     */
    virtual void setBlacklisted(bool value) = 0;

    /**
     * Получить отчество клиента.
     */
    virtual std::string getMiddleName() = 0;

    /**
     * Получить email клиента.
     */
    virtual std::string getEmail() = 0;

    /**
     * Получить серию паспорта клиента.
     */
    virtual std::string getPassportSeries() = 0;

    /**
     * Получить номер паспорта клиента.
     */
    virtual std::string getPassportNumber() = 0;

    /**
     * Получить адрес клиента.
     */
    virtual std::string getAddress() = 0;

    /**
     * Получить дату рождения клиента.
     */
    virtual std::string getBirthDate() = 0;

    /**
     * Получить дату регистрации клиента.
     */
    virtual std::string getRegistrationDate() = 0;

    /**
     * Получить причину блокировки клиента.
     */
    virtual std::string getBlacklistReason() = 0;

    /**
     * Получить количество бонусных баллов клиента.
     */
    virtual int getBonusPoints() = 0;

    /**
     * Получить статус клиента.
     */
    virtual std::string getStatus() = 0;

    /**
     * Установить отчество клиента.
     */
    virtual void setMiddleName(const std::string& middleName) = 0;

    /**
     * Установить email клиента.
     */
    virtual void setEmail(const std::string& email) = 0;

    /**
     * Установить серию и номер паспорта клиента.
     */
    virtual void setPassport(const std::string& series, const std::string& number) = 0;

    /**
     * Установить адрес клиента.
     */
    virtual void setAddress(const std::string& address) = 0;

    /**
     * Установить дату рождения клиента.
     */
    virtual void setBirthDate(const std::string& birthDate) = 0;

    /**
     * Установить дату регистрации клиента.
     */
    virtual void setRegistrationDate(const std::string& registrationDate) = 0;

    /**
     * Установить причину блокировки клиента.
     */
    virtual void setBlacklistReason(const std::string& reason) = 0;

    /**
     * Начислить бонусные баллы клиенту.
     */
    virtual void addBonusPoints(int points) = 0;

    /**
     * Списать бонусные баллы клиента.
     */
    virtual bool useBonusPoints(int points) = 0;

    /**
     * Установить статус клиента.
     */
    virtual void setStatus(const std::string& status) = 0;
};
